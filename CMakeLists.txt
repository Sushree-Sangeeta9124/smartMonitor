cmake_minimum_required(VERSION 3.10)
project(SmartLinuxMonitor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(smart_monitor
    src/main.cpp
    src/system_monitor.cpp
    src/process_monitor.cpp
    src/file_monitor.cpp
    src/logger.cpp
)

target_include_directories(smart_monitor PRIVATE include)
target_link_libraries(smart_monitor PRIVATE Threads::Threads)
