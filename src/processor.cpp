#include "processor.h"
#include "linux_parser.h"
#include <iostream>
#include <unistd.h>
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    cpu_stats = LinuxParser::CpuUtilization();
    prev_cpu_stats = cpu_stats;

    unsigned int microsecond = 1000000;
    usleep(1 * microsecond);//sleeps for 1 second

    cpu_stats = LinuxParser::CpuUtilization();

    prev_cpu_stats.erase(prev_cpu_stats.begin());
    prev_cpu_stats.erase(prev_cpu_stats.end());

    cpu_stats.erase(cpu_stats.begin());
    cpu_stats.erase(cpu_stats.end());

    // std::cout<<"prev_cpu_stats size : "<<prev_cpu_stats.size()<<std::endl;
    // std::cout<<"cpu_stats size : "<<cpu_stats.size()<<std::endl;

    // for(auto ele : prev_cpu_stats){
    //     std::cout<<ele<<",";
    // }
    // std::cout<<std::endl;

    // for(auto ele : cpu_stats){
    //     std::cout<<ele<<",";
    // }
    // std::cout<<std::endl;

    int PrevIdle = stoi(prev_cpu_stats[LinuxParser::kIdle_]) + stoi(prev_cpu_stats[LinuxParser::kIOwait_]);
    int Idle = stoi(cpu_stats[LinuxParser::kIdle_]) + stoi(cpu_stats[LinuxParser::kIOwait_]);

    int PrevNonIdle = stoi(prev_cpu_stats[LinuxParser::kUser_]) + stoi(prev_cpu_stats[LinuxParser::kNice_]) + stoi(prev_cpu_stats[LinuxParser::kSystem_]) + stoi(prev_cpu_stats[LinuxParser::kIRQ_]) + stoi(prev_cpu_stats[LinuxParser::kSoftIRQ_]) + stoi(prev_cpu_stats[LinuxParser::kSteal_]);
    int NonIdle = stoi(cpu_stats[LinuxParser::kUser_]) + stoi(cpu_stats[LinuxParser::kNice_]) + stoi(cpu_stats[LinuxParser::kSystem_]) + stoi(cpu_stats[LinuxParser::kIRQ_]) + stoi(cpu_stats[LinuxParser::kSoftIRQ_]) + stoi(cpu_stats[LinuxParser::kSteal_]); 

    // try
    // {
    
    // int PrevIdle = stoi(prev_cpu_stats[LinuxParser::kIdle_]) + stoi(prev_cpu_stats[LinuxParser::kIOwait_]);
    // // int Idle = stoi(cpu_stats[LinuxParser::kIdle_]) + stoi(cpu_stats[LinuxParser::kIOwait_]);

    // // int PrevNonIdle = stoi(prev_cpu_stats[LinuxParser::kUser_]) + stoi(prev_cpu_stats[LinuxParser::kNice_]) + stoi(prev_cpu_stats[LinuxParser::kSystem_]) + stoi(prev_cpu_stats[LinuxParser::kIRQ_]) + stoi(prev_cpu_stats[LinuxParser::kSoftIRQ_]) + stoi(prev_cpu_stats[LinuxParser::kSteal_]);
    // // int NonIdle = stoi(cpu_stats[LinuxParser::kUser_]) + stoi(cpu_stats[LinuxParser::kNice_]) + stoi(cpu_stats[LinuxParser::kSystem_]) + stoi(cpu_stats[LinuxParser::kIRQ_]) + stoi(cpu_stats[LinuxParser::kSoftIRQ_]) + stoi(cpu_stats[LinuxParser::kSteal_]); 
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    

    

    int prevTotal = PrevIdle + PrevNonIdle;
    int Total = Idle + NonIdle;

    float totald = (Total - prevTotal);
    float idled = (Idle - PrevIdle);

    float CpuUtilization = 1 - (idled / totald);
    
    return CpuUtilization;
    
}