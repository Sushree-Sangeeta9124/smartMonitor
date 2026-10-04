#pragma once
#include <string>

struct SystemStats {
    double cpu_percent{};
    long long mem_total_kb{};
    long long mem_available_kb{};
    long long disk_total_kb{};
    long long disk_available_kb{};
};

class SystemMonitor {
public:
    SystemStats sample();
private:
    double readCpuTotalIdle();
};
