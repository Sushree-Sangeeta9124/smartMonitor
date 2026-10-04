#pragma once
#include <string>
#include <vector>

struct ProcessInfo {
    int pid{};
    std::string name;
    long long memory_kb{};
};

class ProcessMonitor {
public:
    std::vector<ProcessInfo> listProcesses();
};
