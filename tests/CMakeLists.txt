# 查找Qt Test模块
find_package(Qt6 REQUIRED COMPONENTS Test)
if(NOT Qt6_FOUND)
    find_package(Qt5 REQUIRED COMPONENTS Test)
endif()

# 测试源文件
set(TEST_SOURCES
    test_channel_model.cpp
    test_serial_service.cpp
    test_config_manager.cpp
    test_protocol_utils.cpp
    test_json_utils.cpp
    main_test.cpp
)

# 创建测试可执行文件
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

# 链接Qt库
target_link_libraries(${PROJECT_NAME}_tests
    Qt::Core
    Qt::Widgets
    Qt::SerialPort
    Qt::Network
    Qt::Test
)

# 自动生成moc文件
set_target_properties(${PROJECT_NAME}_tests PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# 添加测试
add_test(NAME ChannelModelTest COMMAND ${PROJECT_NAME}_tests)
add_test(NAME SerialServiceTest COMMAND ${PROJECT_NAME}_tests)
add_test(NAME ConfigManagerTest COMMAND ${PROJECT_NAME}_tests)
add_test(NAME ProtocolUtilsTest COMMAND ${PROJECT_NAME}_tests)
add_test(NAME JsonUtilsTest COMMAND ${PROJECT_NAME}_tests) 