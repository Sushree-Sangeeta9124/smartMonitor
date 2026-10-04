#include "system_monitor.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

double SystemMonitor::readCpuTotalIdle() {
    std::ifstream f("/proc/stat");
    std::string cpu;
    long long user, nice, system, idle, iowait, irq, softirq, steal;
    f >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    double total = user + nice + system + idle + iowait + irq + softirq + steal;
    return total - (idle + iowait);
}

SystemStats SystemMonitor::sample() {
    SystemStats s;
    double work1 = readCpuTotalIdle();
    std::ifstream f1("/proc/stat");
    std::string line;
    std::getline(f1, line);
    long long a1=0,b1=0,c1=0,d1=0,e1=0,f1v=0,g1=0,h1=0;
    std::istringstream iss(line);
    std::string cpu;
    iss >> cpu >> a1 >> b1 >> c1 >> d1 >> e1 >> f1v >> g1 >> h1;
    long long total1=a1+b1+c1+d1+e1+f1v+g1+h1;
    long long idle1=d1+e1;

    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    std::ifstream f2("/proc/stat");
    std::getline(f2, line);
    long long a2=0,b2=0,c2=0,d2=0,e2=0,f2v=0,g2=0,h2=0;
    std::istringstream iss2(line);
    iss2 >> cpu >> a2 >> b2 >> c2 >> d2 >> e2 >> f2v >> g2 >> h2;
    long long total2=a2+b2+c2+d2+e2+f2v+g2+h2;
    long long idle2=d2+e2;
    long long dt=total2-total1, di=idle2-idle1;
    s.cpu_percent = dt ? 100.0 * (dt-di) / dt : 0.0;

    std::ifstream mem("/proc/meminfo");
    std::string key; long long value; std::string unit;
    while (mem >> key >> value >> unit) {
        if (key=="MemTotal:") s.mem_total_kb=value;
        else if (key=="MemAvailable:") s.mem_available_kb=value;
    }

    auto space = std::filesystem::space("/");
    s.disk_total_kb = static_cast<long long>(space.capacity / 1024);
    s.disk_available_kb = static_cast<long long>(space.available / 1024);
    return s;
}
