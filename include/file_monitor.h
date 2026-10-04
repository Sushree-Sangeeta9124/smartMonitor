#pragma once

#include "Logger.h"

#include <atomic>
#include <string>
#include <thread>

class FileMonitor
{
public:
    FileMonitor(const std::string& directory, Logger& logger);
    ~FileMonitor();

    void start();
    void stop();

private:
    void watchLoop();

    std::string directory_;
    Logger& logger_;

    std::atomic<bool> running_{false};
    std::thread worker_;

    int fd_{-1};
};
