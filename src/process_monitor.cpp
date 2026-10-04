#include "process_monitor.h"
#include <dirent.h>
#include <fstream>
#include <sstream>

std::vector<ProcessInfo> ProcessMonitor::listProcesses() {
    std::vector<ProcessInfo> result;
    DIR* dir = opendir("/proc");
    if (!dir) return result;

    while (auto* entry = readdir(dir)) {
        std::string n = entry->d_name;
        if (n.empty() || n.find_first_not_of("0123456789") != std::string::npos) continue;
        int pid = 0;
        try { pid = std::stoi(n); } catch (...) { continue; }

        std::ifstream stat("/proc/" + n + "/status");
        std::string line, name;
        long long memory = 0;
        while (std::getline(stat, line)) {
            if (line.rfind("Name:", 0) == 0) name = line.substr(5);
            if (line.rfind("VmRSS:", 0) == 0) {
                std::istringstream iss(line.substr(6));
                iss >> memory;
            }
        }
        result.push_back({pid, name, memory});
    }
    closedir(dir);
    return result;
}
