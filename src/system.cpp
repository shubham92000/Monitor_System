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


Processor& System::Cpu() { 
    cpu_ = Processor();
    return cpu_;
}

void System::buildPids(){
    pids_.clear();
    System::pids_ = LinuxParser::Pids();
    return;
}

void System::buildProcess(){
    buildPids();

    processes_.clear();

    for(auto p:pids_){
        try{
            processes_.push_back(Process(p));
            // cout<<" t ";
        }catch(std::exception &e){
        //     // cout<<e.what()<<" c ";
        }
    }

    std::sort(processes_.begin(),processes_.end(),compare);
    
    return;
}

std::vector<Process> System::Processes() {
    buildProcess();
    return processes_;
}

std::string System::Kernel() { 
    return LinuxParser::Kernel(); 
}

float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization(); 
}

std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem(); 
}

int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses(); 
}

int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
}

long int System::UpTime() { 
    systemUptime_ = LinuxParser::UpTime(); 
    return systemUptime_;
}