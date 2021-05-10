#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

void Process::setPid(int p){
    pid_ = p;
}

// TODO: Return this process's ID
int Process::Pid() { 
    return pid_; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    return 0.0f; 
}

// TODO: Return the command that generated this process
string Process::Command() { 
    command_ = LinuxParser::Command(pid_);
    return  command_;
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    Ram_ = LinuxParser::Ram(pid_); 
    return Ram_;
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    userName_ = LinuxParser::User(pid_); 
    return userName_;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    Uptime_ = 0.0l; 
    return Uptime_; 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    // if(this->CpuUtilization_ > a.CpuUtilization_){
    //     return true; 
    // }
    if(this->pid_ > a.pid_){
        return true; 
    }
    return false;
}