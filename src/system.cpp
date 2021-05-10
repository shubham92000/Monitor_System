#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

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
vector<Process>& System::Processes() {
    processes_.clear();
    vector<int> pids = LinuxParser::Pids();
    std::cout<<"pids size:"<<pids.size()<<std::endl;
    for(auto p:pids){
        Process process;
        process.setPid(p);
        // process.User();
        // process.Command();
        // process.CpuUtilization();
        // process.Ram();
        // process.UpTime();
        processes_.push_back(process);
        // cout<<"<Command> :"<<process.Command();
        // if(p==1 || p == 2 || p==3398){
        //     cout<<"<Command> :"<<process.Command()<<endl;
        // }
        // std::cout<<p<<"  ";
    }
    // std::cout<<processes_.size()<<std::endl;
    return processes_; 
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }