#include "file_monitor.h"

#include <sys/inotify.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

FileMonitor::FileMonitor(const std::string& directory, Logger& logger)
    : directory_(directory), logger_(logger) {}

FileMonitor::~FileMonitor()
{
    stop();
}

void FileMonitor::start()
{
    if (running_)
        return;

    fd_ = inotify_init1(IN_NONBLOCK);

    if (fd_ < 0)
    {
        logger_.alert(
            "Unable to initialize inotify: " +
            std::string(std::strerror(errno))
        );
        return;
    }

    int wd = inotify_add_watch(
        fd_,
        directory_.c_str(),
        IN_CREATE | IN_DELETE | IN_MODIFY |
        IN_MOVED_FROM | IN_MOVED_TO
    );

    if (wd < 0)
    {
        logger_.alert(
            "Unable to watch directory: " +
            directory_ + " : " +
            std::string(std::strerror(errno))
        );

        close(fd_);
        fd_ = -1;
        return;
    }

    running_ = true;
    worker_ = std::thread(&FileMonitor::watchLoop, this);
}

void FileMonitor::stop()
{
    if (!running_)
        return;

    running_ = false;

    if (worker_.joinable())
        worker_.join();

    if (fd_ >= 0)
    {
        close(fd_);
        fd_ = -1;
    }
}

void FileMonitor::watchLoop()
{
    char buffer[4096];

    while (running_)
    {
        int len = read(fd_, buffer, sizeof(buffer));

        if (len <= 0)
        {
            usleep(150000);
            continue;
        }

        for (int i = 0; i < len;)
        {
            auto* ev =
                reinterpret_cast<inotify_event*>(&buffer[i]);

            std::string action;

            if (ev->mask & IN_CREATE)
                action = "CREATED";
            else if (ev->mask & IN_DELETE)
                action = "DELETED";
            else if (ev->mask & IN_MODIFY)
                action = "MODIFIED";
            else if (ev->mask & IN_MOVED_FROM)
                action = "MOVED_FROM";
            else if (ev->mask & IN_MOVED_TO)
                action = "MOVED_TO";

            if (!action.empty())
            {
                std::string name =
                    ev->len ? ev->name : "(unknown)";

                logger_.info(
                    "FILE " + action + ": " +
                    directory_ + "/" + name
                );
            }

            i += sizeof(inotify_event) + ev->len;
        }
    }
}
