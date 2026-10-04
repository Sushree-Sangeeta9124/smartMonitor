#include "logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>

Logger::Logger(const std::string& file)
    : out_(file, std::ios::app)
{
}

void Logger::write(
    const std::string& level,
    const std::string& message)
{
    std::lock_guard<std::mutex> lock(mutex_);

    auto now =
        std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now()
        );

    std::tm tm{};
    localtime_r(&now, &tm);

    std::ostringstream timestamp;

    timestamp
        << std::put_time(
            &tm,
            "%Y-%m-%d %H:%M:%S"
        );

    std::string line =
        "[" + timestamp.str() + "] [" +
        level + "] " + message;

    std::cout << line << '\n';

    if (out_)
    {
        out_ << line << '\n';
        out_.flush();
    }
}

void Logger::info(
    const std::string& message)
{
    write("INFO", message);
}

void Logger::alert(
    const std::string& message)
{
    write("ALERT", message);
}
