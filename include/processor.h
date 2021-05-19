#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<vector>
#include<string>

class Processor {
 public:
  float Utilization();  

 private:
    std::vector<std::string> cpu_stats;
    std::vector<std::string> prev_cpu_stats;
};

#endif