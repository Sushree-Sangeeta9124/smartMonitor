# Smart Linux System & File Activity Monitor

## 1. Abstract
The project is a Linux user-space monitoring application written in C++17. It collects system resource information, enumerates running processes and monitors file-system events. The purpose is to demonstrate practical Linux, C++, operating-system and computer-architecture concepts in one training project.

## 2. Objectives
- Understand Linux `/proc`.
- Monitor CPU and memory.
- Inspect running processes.
- Detect file-system events using `inotify`.
- Use threads for background monitoring.
- Maintain timestamped logs.
- Generate basic resource alerts.

## 3. Architecture
The application contains four major modules:
1. System Monitor
2. Process Monitor
3. File Monitor
4. Logger

`main.cpp` coordinates the modules and presents a terminal dashboard.

## 4. Technologies
- C++17
- Linux
- `/proc`
- `inotify`
- POSIX threads through `std::thread`
- CMake
- Git

## 5. Limitations
- User-space only.
- File monitoring is for one selected directory.
- Resource alerts use simple fixed thresholds.
- It is a training/demo application, not a production security product.

## 6. Future Enhancements
- CSV/JSON export
- Configurable thresholds
- ncurses dashboard
- Multiple watched directories
- SQLite event database
- Network dashboard
- Rule-based anomaly detection
