#pragma once
#include <fstream>
#include <mutex>
#include <string>

class Logger {
public:
    explicit Logger(const std::string& file);
    void info(const std::string& message);
    void alert(const std::string& message);
private:
    void write(const std::string& level, const std::string& message);
    std::ofstream out_;
    std::mutex mutex_;
};
