cmake_minimum_required(VERSION 3.16)
project(GHTerminal VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置Qt版本
find_package(Qt6 REQUIRED COMPONENTS Core Widgets SerialPort Network)
if(NOT Qt6_FOUND)
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets SerialPort Network)
endif()

# 设置编译选项
if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 启用测试
option(BUILD_TESTS "Build tests" ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 包含目录
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

# 源文件
set(SOURCES
    src/main.cpp
    src/core/application.cpp
    src/core/config_manager.cpp
    src/core/logger.cpp
    src/models/channel_model.cpp
    src/models/dmr_model.cpp
    src/viewmodels/main_viewmodel.cpp
    src/viewmodels/channel_viewmodel.cpp
    src/services/serial_service.cpp
    src/services/channel_service.cpp
    src/services/dmr_service.cpp
    src/utils/serial_utils.cpp
    src/utils/protocol_utils.cpp
    src/utils/json_utils.cpp
    src/widgets/main_window.cpp
    src/widgets/channel_widget.cpp
    src/widgets/settings_dialog.cpp
    src/delegates/custom_delegates.cpp
)

# 头文件
set(HEADERS
    include/core/application.h
    include/core/config_manager.h
    include/core/logger.h
    include/models/channel_model.h
    include/models/dmr_model.h
    include/viewmodels/main_viewmodel.h
    include/viewmodels/channel_viewmodel.h
    include/services/serial_service.h
    include/services/channel_service.h
    include/services/dmr_service.h
    include/utils/serial_utils.h
    include/utils/protocol_utils.h
    include/utils/json_utils.h
    include/widgets/main_window.h
    include/widgets/channel_widget.h
    include/widgets/settings_dialog.h
    include/delegates/custom_delegates.h
)

# UI文件
set(UI_FILES
    ui/main_window.ui
    ui/channel_widget.ui
    ui/settings_dialog.ui
)

# 资源文件
set(RESOURCE_FILES
    resources/resources.qrc
    resources/translations.qrc
)

# 翻译文件
set(TS_FILES
    translations/lang_Chinese.ts
    translations/lang_English.ts
    translations/lang_Japanese.ts
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI_FILES} ${RESOURCE_FILES})

# 链接Qt库
target_link_libraries(${PROJECT_NAME} 
    Qt::Core 
    Qt::Widgets 
    Qt::SerialPort 
    Qt::Network
)

# 设置Windows图标
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        VS_DEBUGGER_ENVIRONMENT "PATH=${CMAKE_BINARY_DIR}/bin"
    )
endif()

# 自动生成moc文件
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# 安装规则
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# 安装翻译文件
install(FILES ${TS_FILES} DESTINATION share/${PROJECT_NAME}/translations)

# 测试
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# 打包
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Qt串口终端工具 - Q900系列电台通信配置工具")
set(CPACK_PACKAGE_VENDOR "FVsonar")
set(CPACK_PACKAGE_CONTACT "1595220980@qq.com")

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_DISPLAY_NAME ${PROJECT_NAME})
    set(CPACK_NSIS_PACKAGE_NAME ${PROJECT_NAME})
    set(CPACK_NSIS_CONTACT ${CPACK_PACKAGE_CONTACT})
    set(CPACK_NSIS_ENABLE_ICON "${CMAKE_SOURCE_DIR}/resources/icon.ico")
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/resources/icon.ico")
    set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/resources/icon.ico")
endif()

include(CPack) 