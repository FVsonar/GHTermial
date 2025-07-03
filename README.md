# GHTerminal - 现代化Qt串口终端工具

## 🚀 项目简介

GHTerminal是一个基于现代Qt框架开发的串口通信终端工具，专门用于与Q900系列电台进行通信和配置。该项目采用最新的C++17标准和现代化架构设计，提供了高性能、可扩展和易维护的解决方案。

## ✨ 核心特性

### 🔧 现代化架构
- **CMake构建系统** - 替代qmake，提供更好的跨平台支持
- **MVVM设计模式** - 清晰的视图、视图模型、模型分离
- **依赖注入** - 松耦合的组件设计
- **智能指针** - 自动内存管理，避免内存泄漏
- **RAII原则** - 资源自动管理

### 🎨 用户界面
- **现代化UI设计** - 基于Qt Widgets的现代化界面
- **深色/浅色主题** - 支持多种主题切换
- **响应式布局** - 自适应不同屏幕尺寸
- **多语言支持** - 支持中文、英文、日文等多种语言
- **自定义控件** - 丰富的表格委托和自定义控件

### 🔄 通信功能
- **Q900协议支持** - 完整的Q900系列电台通信协议实现
- **异步通信** - 非阻塞的串口通信
- **命令队列** - 智能的命令排队和重试机制
- **实时监控** - 实时显示通信状态和数据流
- **错误处理** - 完善的错误处理和恢复机制

### 📊 数据处理
- **JSON导入导出** - 支持标准JSON格式数据交换
- **数据验证** - 完整的数据验证和错误检查
- **批量操作** - 支持批量读取和写入操作
- **数据备份** - 自动数据备份和恢复功能

## 🏗️ 技术架构

### 项目结构
```
GHTerminal/
├── CMakeLists.txt              # CMake构建配置
├── include/                    # 头文件目录
│   ├── core/                   # 核心组件
│   │   ├── application.h       # 应用程序核心
│   │   ├── config_manager.h    # 配置管理
│   │   └── logger.h           # 日志系统
│   ├── models/                 # 数据模型
│   │   ├── channel_model.h     # 信道数据模型
│   │   └── dmr_model.h        # DMR数据模型
│   ├── viewmodels/            # 视图模型
│   │   ├── main_viewmodel.h    # 主视图模型
│   │   └── channel_viewmodel.h # 信道视图模型
│   ├── services/              # 业务服务
│   │   ├── serial_service.h    # 串口服务
│   │   ├── channel_service.h   # 信道服务
│   │   └── dmr_service.h      # DMR服务
│   ├── utils/                 # 工具类
│   │   ├── serial_utils.h      # 串口工具
│   │   ├── protocol_utils.h    # 协议工具
│   │   └── json_utils.h       # JSON工具
│   ├── widgets/               # 界面组件
│   │   ├── main_window.h       # 主窗口
│   │   ├── channel_widget.h    # 信道组件
│   │   └── settings_dialog.h   # 设置对话框
│   └── delegates/             # 表格委托
│       └── custom_delegates.h  # 自定义委托
├── src/                       # 源文件目录
│   ├── core/                  # 核心实现
│   ├── models/                # 模型实现
│   ├── viewmodels/           # 视图模型实现
│   ├── services/             # 服务实现
│   ├── utils/                # 工具实现
│   ├── widgets/              # 界面实现
│   ├── delegates/            # 委托实现
│   └── main.cpp              # 程序入口
├── ui/                       # UI文件
│   ├── main_window.ui        # 主窗口界面
│   ├── channel_widget.ui     # 信道组件界面
│   └── settings_dialog.ui    # 设置对话框界面
├── resources/                # 资源文件
│   ├── resources.qrc         # 主资源文件
│   ├── translations.qrc      # 翻译资源
│   ├── images/               # 图片资源
│   └── styles/               # 样式文件
├── translations/             # 翻译文件
│   ├── lang_Chinese.ts       # 中文翻译
│   ├── lang_English.ts       # 英文翻译
│   └── lang_Japanese.ts      # 日文翻译
├── tests/                    # 测试文件
│   ├── CMakeLists.txt        # 测试构建配置
│   ├── test_channel_model.cpp # 信道模型测试
│   ├── test_serial_service.cpp # 串口服务测试
│   └── main_test.cpp         # 测试主程序
└── docs/                     # 文档
    ├── api/                  # API文档
    ├── user_guide/           # 用户指南
    └── developer_guide/      # 开发者指南
```

### 技术栈
- **C++17** - 现代C++标准
- **Qt 6/5** - 跨平台GUI框架
- **CMake 3.16+** - 现代化构建系统
- **Google Test** - 单元测试框架
- **JSON** - 数据交换格式
- **QSS** - Qt样式表

## 🛠️ 编译要求

### 系统要求
- **Windows**: Windows 10/11 (x64)
- **Linux**: Ubuntu 20.04+, CentOS 8+, Fedora 33+
- **macOS**: macOS 10.15+ (Catalina+)

### 依赖库
- **Qt**: 5.15.2+ 或 6.0.0+
- **CMake**: 3.16.0+
- **编译器**: 
  - Windows: MSVC 2019+ 或 MinGW 8.1+
  - Linux: GCC 8+ 或 Clang 10+
  - macOS: Xcode 12+ 或 Clang 10+

## 📦 编译步骤

### 1. 克隆项目
```bash
git clone https://github.com/FVsonar/GHTermial.git
cd GHTermial
```

### 2. 配置构建
```bash
# 创建构建目录
mkdir build && cd build

# 配置CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# 或者指定Qt路径
cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt -DCMAKE_BUILD_TYPE=Release
```

### 3. 编译项目
```bash
# 编译
cmake --build . --config Release

# 或者使用多线程编译
cmake --build . --config Release --parallel
```

### 4. 运行测试
```bash
# 运行所有测试
ctest --output-on-failure

# 或者直接运行测试程序
./bin/GHTerminal_tests
```

### 5. 安装程序
```bash
# 安装到系统
cmake --install . --prefix /usr/local

# 或者打包
cpack -G NSIS  # Windows
cpack -G DEB   # Linux
cpack -G TGZ   # macOS
```

## 🚀 快速开始

### 基本使用
1. **启动程序**: 运行 `GHTerminal` 可执行文件
2. **连接设备**: 选择串口并点击连接
3. **读取数据**: 点击"读取信道"获取设备数据
4. **编辑数据**: 在表格中编辑信道参数
5. **写入数据**: 点击"写入信道"保存到设备

### 命令行参数
```bash
# 基本启动
./GHTerminal

# 指定配置文件
./GHTerminal -c /path/to/config.ini

# 指定日志文件
./GHTerminal -l /path/to/log.txt

# 启用详细日志
./GHTerminal -v

# 显示帮助
./GHTerminal --help
```

## 📚 开发指南

### 代码规范
- 遵循 **Google C++ Style Guide**
- 使用 **clang-format** 自动格式化
- 所有函数必须有文档注释
- 使用 **RAII** 和智能指针管理资源

### 添加新功能
1. 在 `include/` 目录添加头文件
2. 在 `src/` 目录实现功能
3. 更新 `CMakeLists.txt` 添加源文件
4. 编写单元测试
5. 更新文档

### 测试开发
```bash
# 运行特定测试
./bin/GHTerminal_tests --gtest_filter=ChannelModelTest*

# 生成测试覆盖率报告
cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON
make
./bin/GHTerminal_tests
gcovr --html --output=coverage.html
```

## 🔧 配置说明

### 配置文件位置
- **Windows**: `%APPDATA%/GHTerminal/config.ini`
- **Linux**: `~/.config/GHTerminal/config.ini`
- **macOS**: `~/Library/Application Support/GHTerminal/config.ini`

### 主要配置项
```ini
[Serial]
port=COM3
baudRate=9600
dataBits=8
parity=None
stopBits=1
flowControl=None

[Interface]
language=zh_CN
theme=dark
autoConnect=false
autoSave=true

[Communication]
timeout=5000
retryCount=3
enableLogging=true
```

## 📖 协议文档

详细的国赫控制协议请参考项目中的 `国赫控制协议.md` 文件。

## 🤝 贡献指南

### 开发环境设置
1. 安装Qt开发环境
2. 安装CMake和编译器
3. 克隆项目并配置
4. 运行测试确保环境正常

### 提交规范
- 使用 **Conventional Commits** 规范
- 每个提交只做一件事
- 提交前运行测试
- 更新相关文档

### 问题反馈
- 提交GitHub Issue
- 发送邮件至项目维护者
- QQ: 1595220980
- 邮箱: 1595220980@qq.com
- 微信: tmtn1234567890

## 📄 许可证

本项目采用 **LGPL-2.1** 许可证，详见 [LICENSE](LICENSE) 文件。

## 🗓️ 更新日志

### v1.0.0 (2024-01-XX)
- 🎉 完全重构项目架构
- 🏗️ 采用CMake构建系统
- 🎨 现代化UI设计
- 🔧 实现MVVM架构模式
- 📊 完善的数据模型
- 🧪 添加单元测试框架
- 🌍 多语言支持
- 📱 响应式界面设计
- 🔄 异步通信机制
- 📦 自动化打包部署

### v0.1.0
- 初始版本发布
- 支持基本的串口通信功能
- 实现Q900协议通信
- 提供信道配置功能

## 📞 联系方式

- **项目主页**: [https://github.com/FVsonar/GHTermial](https://github.com/FVsonar/GHTermial)
- **问题反馈**: [GitHub Issues](https://github.com/FVsonar/GHTermial/issues)
- **开发者**: FVsonar
- **邮箱**: 1595220980@qq.com
- **QQ**: 1595220980
- **微信**: tmtn1234567890

---

**GHTerminal** - 让串口通信更简单、更高效！ 🚀 