#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::cout;
using std::endl;

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    cpu_ = Processor();
    
    return cpu_;
}


// TODO: Return a container composed of the system's processes
std::vector<Process>& System::Processes() {
    // processes_.clear();
    vector<int> pids = LinuxParser::Pids();
    std::vector<Process> new_proc;
    for(auto p:pids){
        Process process(p);
        processes_.push_back(process);
        new_proc.push_back(process);
    }


    // std::sort(new_proc.begin(),new_proc.end(),compare);
    // std::sort(processes_.begin(),processes_.end(),compare);
    return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return LinuxParser::Kernel(); 
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization(); 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem(); 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    // cout<<"222222222222222222222222222222222222";
    return LinuxParser::RunningProcesses(); 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    // cout<<"111111111111111111111111111";
    systemUptime_ = LinuxParser::UpTime(); 
    // cout<<"uuuuuuuuuuuuuuuuu"<<systemUptime_<<" ";
    return systemUptime_;
}