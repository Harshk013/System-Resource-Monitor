#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <dirent.h>
using namespace std;
using ll = long long;


void bar(double percent){
    int width = 20;
    int filled = percent * width / 100;

    cout << "[";

    for(int i=0;i<filled;i++) cout << "█";
    for(int i=filled;i<width;i++) cout << "-";

    cout << "]";
}


bool isNumber(string s){
    for(char c : s){
        if(!isdigit(c)){
            return false;
        }
    }

    return true;
}


void readCPU(ll &user,ll &nice,ll &system,ll &idle){
    ifstream file("/proc/stat");

    string line;
    getline(file, line);

    string cpu;
    stringstream ss(line);

    ss >> cpu >> user >> nice >> system >> idle;
}


void usage(ll &user1,ll &nice1,ll &system1,ll &idle1,
           ll &user2,ll &nice2,ll &system2,ll &idle2){

	ll total1 = user1 + nice1 + system1 + idle1;
    ll total2 = user2 + nice2 + system2 + idle2;

    ll totalDiff = total2 - total1;
    ll idleDiff = idle2 - idle1;

    double cpuUsage = (double)(totalDiff - idleDiff) / totalDiff * 100;

    system("clear");

    cout << "==================================================" << endl;
    cout << "                SYSTEM RESOURCE MONITOR           " << endl;
    cout << "==================================================" << endl;
    cout << endl;

    cout << "CPU Usage : ";
    bar(cpuUsage);
    cout << " " << cpuUsage << " %" << endl;
    cout << endl;
}

void memory(ll &totalMem,ll &availableMem){
    ifstream file("/proc/meminfo");

    string key;
    ll value;
    string unit;

    while(file >> key >> value >> unit){
        if(key == "MemTotal:")
            totalMem = value;

        if(key == "MemAvailable:")
            availableMem = value;
    }
    ll usedMem = totalMem - availableMem;

double totalGB = totalMem / (1024.0 * 1024);
double usedGB = usedMem / (1024.0 * 1024);
double freeGB = availableMem / (1024.0 * 1024);

double usedPercent = (double)usedMem / totalMem * 100;
double freePercent = (double)availableMem / totalMem * 100;

int width = 15;

int usedBars = usedPercent * width / 100;
int freeBars = freePercent * width / 100;

cout << "Memory Usage" << endl;
cout << "----------------------------------------------" << endl;

cout << "Used  : [";
for(int i=0;i<usedBars;i++) cout << "█";
for(int i=usedBars;i<width;i++) cout << "-";
cout << "] " << usedGB << " GB" << endl;

cout << "Free  : [";
for(int i=0;i<freeBars;i++) cout << "█";
for(int i=freeBars;i<width;i++) cout << "-";
cout << "] " << freeGB << " GB" << endl;

cout << "Total : " << totalGB << " GB" << endl;
cout << endl;
}

void pid(){
    DIR *dir = opendir("/proc");
    struct dirent *entry;

    cout << "Running Processes" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "PID        NAME                MEMORY" << endl;
    cout << "----------------------------------------------" << endl;

    while((entry = readdir(dir)) != NULL){
        string pid = entry->d_name;

        if(isNumber(pid)){
            string path = "/proc/" + pid + "/status";

            ifstream file(path);
            string line;

            string name = "";
            string memory = "0 MB";

            while(getline(file, line)){
                if(line.substr(0,5) == "Name:"){
                    name = line.substr(6);
                }

                if(line.substr(0,6) == "VmRSS:"){
                    stringstream ss(line);
                    string key, unit;
                    ll mem;

                    ss >> key >> mem >> unit;

                    double memMB = mem / 1024.0;
                    memory = to_string(memMB) + " MB";
                }
            }

            if(name != ""){
                cout << pid;

                if(pid.length() < 10) cout << string(10 - pid.length(), ' ');

                cout << name;

                if(name.length() < 20) cout << string(20 - name.length(), ' ');

                cout << memory << endl;
            }
        }
    }

    closedir(dir);
}


int main(){
    while(true){
        ll user1, nice1, system1, idle1;
        ll user2, nice2, system2, idle2;
	    ll totalMem, availableMem;

        readCPU(user1, nice1, system1, idle1);

        sleep(1);

        readCPU(user2, nice2, system2, idle2);

	    usage(user1,nice1,system1,idle1,user2,nice2,system2,idle2);

	    memory(totalMem,availableMem);

	    pid();
    }
    return 0;
}
