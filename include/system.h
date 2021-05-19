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
  Processor& Cpu();                   // TODO: See src/system.cpp
  std::vector<Process> Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          // TODO: See src/system.cpp
  long UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  std::string Kernel();               // TODO: See src/system.cpp
  std::string OperatingSystem();      // TODO: See src/system.cpp
  void buildPids();
  void buildProcess();
  static bool compare(Process p1,Process p2){
    if(p1.Command().length() > p2.Command().length()){
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