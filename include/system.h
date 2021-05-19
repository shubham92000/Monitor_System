#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include <iostream>
#include "linux_parser.h"
#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   
  std::vector<Process> Processes();  
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  std::string Kernel();               
  std::string OperatingSystem();      
  void buildPids();
  void buildProcess();
  static bool compare(Process p1,Process p2){
    // if(p1.Command().length() > p2.Command().length()){
    //     return true;
    // }

    if(p1.CpuUtilization() > p2.CpuUtilization()){
      return true;
    }

    return false;
  }

  
 private:
  Processor cpu_ = {};
  std::vector<int> pids_ = {};
  std::vector<Process> processes_ = {};
  long int systemUptime_;
};

#endif