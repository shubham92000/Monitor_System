#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int);
  int getPid();                              // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
//   bool operator<(Process const& a) const;  // TODO: See src/process.cpp
//   bool compare(Process b);

  // TODO: Declare any necessary private members
 private:
    int pid_;
    std::string userName_;
    std::string command_;
    float CpuUtil;
    std::string Ram_;
    long int Uptime_;
};

#endif