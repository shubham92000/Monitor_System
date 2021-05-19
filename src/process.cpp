#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include<iostream>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;


Process::Process(int p){
    pid_ = p;
    userName_ = User();
    command_ = Command();
    CpuUtil = CpuUtilization();
    Ram_ = Ram();
    Uptime_ = UpTime();
}

int Process::getPid(){ 
    return pid_; 
}

float Process::CpuUtilization() { 
    CpuUtil = LinuxParser::processCpuUtilization(getPid()); 
    return CpuUtil;
}

string Process::Command(){
    command_ = LinuxParser::Command(getPid());
    if(command_ == ""){
        return "NULL";
    }
    
    return  command_;
}

string Process::Ram() { 
    Ram_ = LinuxParser::Ram(getPid()); 
    return Ram_;
}

string Process::User() { 
    userName_ = LinuxParser::User(getPid()); 
    return userName_;
}

long int Process::UpTime() { 
    Uptime_ = LinuxParser::UpTime(getPid()); 
    return Uptime_;
}
