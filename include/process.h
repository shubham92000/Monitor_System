#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
 public:
  Process(int);
  int getPid();                        
  std::string User();                  
  std::string Command();               
  float CpuUtilization();              
  std::string Ram();                   
  long int UpTime();                   

 private:
    int pid_;
    std::string userName_;
    std::string command_;
    float CpuUtil;
    std::string Ram_;
    long int Uptime_;
};

#endif