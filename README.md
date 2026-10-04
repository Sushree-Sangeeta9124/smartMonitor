# Smart Linux System & File Activity Monitor

A C++ based Linux project for monitoring system resources, running processes, and file activity.

## 📌 Features

- 🖥️ CPU usage monitoring
- 💾 RAM usage monitoring
- 💿 Disk usage monitoring
- ⚙️ Running process monitoring using `/proc`
- 📁 File activity monitoring using Linux `inotify`
- 🚨 High CPU and RAM usage alerts
- 📝 Timestamped activity logging
- 📊 Simple terminal dashboard

## 🛠️ Technologies Used

- **C++**
- **Linux**
- **CMake**
- **C++ STL**
- **Multithreading and Mutex**
- **Linux `/proc` interface**
- **Linux `inotify`**
- **Git**

## 📋 Requirements

- Ubuntu/Linux environment
- g++ compiler
- CMake 3.10 or newer
- pthread support

📁 Project Structure

smartMonitor/
├── src/
│   ├── main.cpp
│   ├── system_monitor.cpp
│   ├── process_monitor.cpp
│   ├── file_monitor.cpp
│   └── logger.cpp
├── include/
│   ├── system_monitor.h
│   ├── process_monitor.h
│   ├── file_monitor.h
│   └── logger.h
├── logs/
│   └── activity.log
├── tests/
│   └── TEST_PLAN.md
├── docs/
│   └── PROJECT_DOCUMENTATION.md
├── CMakeLists.txt
├── .gitignore
└── README.md