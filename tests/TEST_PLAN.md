# Test Plan

1. Build
   - `cmake -S . -B build`
   - `cmake --build build`
   - Expected: executable `build/smart_monitor`

2. System statistics
   - Run the application.
   - Expected: CPU, RAM, disk and process count are displayed.

3. File creation
   - While monitoring a directory, create a file in it.
   - Expected log: `FILE CREATED`.

4. File modification
   - Edit a file in the monitored directory.
   - Expected log: `FILE MODIFIED`.

5. File deletion
   - Delete a file in the monitored directory.
   - Expected log: `FILE DELETED`.

6. Alert
   - Run a CPU/RAM intensive workload.
   - Expected: an alert can appear when the configured threshold is exceeded.

7. Logging
   - Check `logs/activity.log`.
   - Expected: timestamped INFO/ALERT records.
