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

void System::bubbleSort(vector<Process> &proc){
    for(int i=0;i<int(proc.size());i++){
        for(int j=0;j<int(proc.size())-i;j++){
            if(proc[i].getPid()>proc[j].getPid()){
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    return;
}

void System::buildPids(){
    pids_.clear();
    System::pids_ = LinuxParser::Pids();
    return;
}

void System::buildProcess(){
    buildPids();


    processes_.clear();
    // std::cerr<<" pid_size "<<pids_.size()<<"   "<<"\n";

    // cout<<" start ";
    // for(auto p:pids_){
    //     cout<<typeid(p).name()<<" ";
    // }
    // cout<<" done ";

    for(auto p:pids_){
        // try{
            // Process process(p);
            processes_.push_back(Process(p));
            // cout<<" u ";
        // }catch(std::exception &e){
        //     // cout<<e.what()<<" ";
        // }
    }

    // std::cout<<" reached bproc "<<processes_.size();

    // std::vector<Process>::iterator itb = processes_.begin();
    // std::vector<Process>::iterator ite = processes_.end()-1;
    
    // cout<<" ITB "<<itb->getPid()<<" ITE "<<ite->getPid()<<" size "<<processes_.size()<<endl;


    // try
    // {
        // std::sort(itb,ite+1,compare);
    // }
    // catch(const std::out_of_range& oor)
    // {
    //     std::cerr << "out of range error : "<< oor.what() <<"\n";
    // }
    
    std::sort(processes_.begin(),processes_.end(),compare);
    
    // bubbleSort(processes_);

    return;
}

// TODO: Return a container composed of the system's processes
std::vector<Process> System::Processes() {
    buildProcess();
    return processes_;
}


// TODO: Return a container composed of the system's processes
// std::vector<Process> System::Processes() {
//     vector<int> pids = LinuxParser::Pids();
//     std::vector<Process> new_proc;
//     for(auto p:pids){
//         Process process(p);
//         new_proc.push_back(process);
//     }

//     std::sort(new_proc.begin(),new_proc.end(),compare);

//     return new_proc;
// }

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