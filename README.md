# System Resource Monitor (CLI)

A terminal-based **system monitoring tool written in C++** that displays real-time system information including CPU usage, memory consumption, and running processes.
The application reads system data directly from the Linux `/proc` filesystem and updates the information continuously in the terminal.

This project was built as part of the **Programming Club Software Division Induction Task**.

---

# Features

* Real-time **CPU usage monitoring**
* Real-time **memory usage visualization**
* **Graphical bar representation** for CPU and memory usage
* Display of **running processes**
* Shows **memory usage per process**
* Clean **CLI interface with formatted output**
* Uses Linux **/proc filesystem** directly (no external libraries)
* Automatic refresh every second

---

# Task Description

The goal of this project is to build a **terminal-based system resource monitor** that displays key system metrics such as CPU usage and memory consumption in real time.

Additionally, the application displays a list of currently running processes along with their memory usage. The program continuously updates the information to provide a live view of system activity.

The emphasis of the task is on:

* understanding system internals
* reading data from the operating system
* designing a clean and readable CLI interface
* implementing real-time monitoring.

---

# Screenshots
```
==========================================================
                 SYSTEM RESOURCE MONITOR
==========================================================

CPU Usage : [--------------------] 0.0625 %

Memory Usage
----------------------------------------------------------

Used  : [-------------] 0.503769 GB
Free  : [████████████] 7.16048 GB
Total : 7.66425 GB

Running Processes
----------------------------------------------------------
PID        NAME                MEMORY
----------------------------------------------------------
1          systemd             12.085938 MB
2          init-systemd(Ub     1.625000 MB
6          init                1.750000 MB
42         systemd-journal     14.250000 MB
88         systemd-udevd       6.000000 MB
109        systemd-resolve     11.875000 MB
111        systemd-timesyn     7.250000 MB
173        cron                2.500000 MB
174        dbus-daemon         4.625000 MB
180        snapd               36.000000 MB
181        systemd-logind      8.000000 MB
187        wsl-pro-service     13.000000 MB
198        agetty              1.875000 MB
205        rsyslogd            5.375000 MB
208        agetty              1.750000 MB
214        unattended-upgr     21.750000 MB
262        systemd-timedat     7.000000 MB
305        SessionLeader       0.875000 MB
306        Relay(307)          1.000000 MB
307        bash                5.125000 MB
308        login               4.250000 MB
359        systemd             11.000000 MB
360        (sd-pam)            3.433594 MB
371        bash                4.875000 MB
391        monitor             3.625000 MB
```


# How It Works

The program gathers system information by reading files from the **Linux `/proc` virtual filesystem**.

Important files used:

| File                 | Purpose                       |
| -------------------- | ----------------------------- |
| `/proc/stat`         | CPU statistics                |
| `/proc/meminfo`      | Memory information            |
| `/proc/[pid]/status` | Process name and memory usage |

Steps performed by the program:

1. Read CPU statistics from `/proc/stat`.
2. Calculate CPU usage using two consecutive readings.
3. Read memory information from `/proc/meminfo`.
4. Compute used and free memory.
5. Scan `/proc` to detect running processes.
6. Extract process names and memory usage.
7. Display the information in a formatted CLI interface.

---

# Instructions to Run

### 1. Clone the repository

```bash
git clone https://github.com/yourusername/system-resource-monitor.git
cd system-resource-monitor
```

### 2. Compile the program

```bash
g++ monitor.cpp -o monitor
```

### 3. Run the program

```bash
./monitor
```

The monitor will start and update system statistics every second.

Press **Ctrl+C** to stop the program.

---

# Design Decisions

### Use of the `/proc` Filesystem

The program reads system information directly from the Linux `/proc` virtual filesystem instead of using external libraries. This approach provides direct access to kernel statistics and helps understand how system monitoring tools work internally.

### Modular Structure

The program is divided into separate functions:

* `readCPU()` → reads CPU statistics
* `usage()` → calculates CPU utilization
* `memory()` → calculates memory usage
* `pid()` → lists running processes

This improves readability and makes the program easier to maintain.

### Real-Time Monitoring

CPU usage is calculated by comparing two snapshots of CPU time taken one second apart. This technique is similar to how real system monitoring tools measure CPU utilization.

### CLI Visualization

Graphical bars are used to represent CPU and memory usage to make the interface easier to read directly in the terminal.

---

# Possible Improvements

Future enhancements could include:

* Sorting processes by CPU or memory usage
* Filtering processes
* Process CPU usage tracking
* Process tree visualization
* Keyboard interaction (quit, refresh, filter)
* Reduced screen flickering using cursor control

---

# Technologies Used

* **C++**
* **Linux `/proc` filesystem**
* POSIX system calls (`dirent`, `unistd`)
* Standard C++ libraries

---

# Author

Harsh Kasera
