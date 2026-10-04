#include "file_monitor.h"
#include "logger.h"
#include "process_monitor.h"
#include "system_monitor.h"
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <thread>

int main(int argc, char** argv) {
    std::string watchDir = argc > 1 ? argv[1] : ".";
    if (!std::filesystem::is_directory(watchDir)) {
        std::cerr << "Directory does not exist: " << watchDir << "\n";
        return 1;
    }

    Logger logger("logs/activity.log");
    SystemMonitor system;
    ProcessMonitor processes;
    FileMonitor files(watchDir, logger);

    files.start();
    logger.info("Smart Linux Monitor started. Watching: " + watchDir);
    std::cout << "\nSMART LINUX SYSTEM & FILE ACTIVITY MONITOR\n";
    std::cout << "Watching: " << watchDir << " | Press q + Enter to stop.\n\n";

    while (true) {
        auto stats = system.sample();
        auto list = processes.listProcesses();

        long long usedMem = stats.mem_total_kb - stats.mem_available_kb;
        double memPct = stats.mem_total_kb
            ? 100.0 * usedMem / stats.mem_total_kb : 0.0;
        double diskPct = stats.disk_total_kb
            ? 100.0 * (stats.disk_total_kb - stats.disk_available_kb)
              / stats.disk_total_kb : 0.0;

        std::cout << "\033[2J\033[H";
        std::cout << "=== SMART LINUX SYSTEM & FILE ACTIVITY MONITOR ===\n";
        std::cout << "CPU Usage : " << stats.cpu_percent << "%\n";
        std::cout << "RAM Usage : " << memPct << "% (" << usedMem/1024 << " MB)\n";
        std::cout << "Disk Usage: " << diskPct << "%\n";
        std::cout << "Processes : " << list.size() << "\n\n";

        std::sort(list.begin(), list.end(),
                  [](const auto& a, const auto& b) { return a.memory_kb > b.memory_kb; });

        std::cout << "Top processes by RAM:\n";
        std::cout << "PID\tNAME\t\tRAM(MB)\n";
        for (size_t i=0; i<std::min<size_t>(10, list.size()); ++i)
            std::cout << list[i].pid << "\t" << list[i].name
                      << "\t" << list[i].memory_kb/1024 << "\n";

        if (stats.cpu_percent > 85.0)
            logger.alert("High CPU usage detected: " + std::to_string(stats.cpu_percent) + "%");
        if (memPct > 85.0)
            logger.alert("High memory usage detected: " + std::to_string(memPct) + "%");

        std::cout << "\nActivity is logged to logs/activity.log\n";
        std::cout << "Type q + Enter to stop.\n";

        // Non-blocking keyboard is deliberately kept simple for training/demo use.
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (std::cin.rdbuf()->in_avail() > 0) {
            char c; std::cin.get(c);
            if (c == 'q' || c == 'Q') break;
        }
    }

    files.stop();
    logger.info("Monitor stopped.");
    return 0;
}
