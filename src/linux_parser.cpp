#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }

  filestream.close();

  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }

  stream.close();
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization     SCAM
float LinuxParser::MemoryUtilization() { 
  float memfree = 0.0f;
  string line[2];
  string key[2];
  float value[2];
  string size[2];
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if(filestream.is_open()){
    
    for(int i=0;i<2;i++){
      std::getline(filestream,line[i]);
      std::istringstream linestream(line[i]);
      linestream>>key[i]>>value[i]>>size[i];
    }

    memfree = abs(value[0] - value[1]);
    memfree = memfree/value[0];

    filestream.close();
    return memfree;
    
  }
  if(filestream.is_open()){
    filestream.close();
  }
  
  return memfree;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  long total_uptime = 0.0l;
  string line;
  string intermediate;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);
    linestream >> intermediate;
  }

  total_uptime = long(stof(intermediate));
  // std::cout<<total_uptime<<std::endl;
  filestream.close();
  return total_uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  return 0; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { 
  return 0; 
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  return 0; 
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  return 0; 
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line;
  vector<string> cpu_stats;
  

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);
    while(linestream){
      string temp;
      linestream >> temp;
      cpu_stats.push_back(temp);
    }
    filestream.close();
    return cpu_stats;
  }

  if(filestream.is_open()){
    filestream.close();
  }
  return cpu_stats; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  int total_processes = 0;
  string line;
  string key;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    while (std::getline(filestream,line)){
      std::istringstream linestream(line);
      string word;
      linestream >> word;
      if(word == "processes"){
        linestream>>total_processes;

        filestream.close();
        return total_processes;
      }
    }
  }

  filestream.close();
  return total_processes;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  int running_processes = 0;
  string line;
  string key;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    while (std::getline(filestream,line)){
      std::istringstream linestream(line);
      string word;
      linestream >> word;
      if(word == "procs_running"){
        linestream>>running_processes;

        filestream.close();
        return running_processes;
      }
    }
  }

  filestream.close();
  return running_processes;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid){
  string cmdline;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if(filestream.is_open()){
    filestream >> cmdline;
  }
  
  filestream.close();
  return cmdline; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string process_ram_usage;
  std::string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::istringstream linestream(line);
      // while(linestream){
          string key;
          linestream >> key;
          if(key == "VmSize:"){
            linestream >> process_ram_usage;
            process_ram_usage =  to_string(stoi(process_ram_usage)/1024);
            return process_ram_usage;
          }
        // }
      }
    }

  filestream.close();
  return process_ram_usage; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid){ 
  string process_uid;
  std::string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::istringstream linestream(line);
          string key;
          linestream >> key;
          if(key == "Uid:"){
            linestream >> process_uid;
            filestream.close();
            return process_uid;
          }
      }
    }

  filestream.close();
  return process_uid; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
//username
string LinuxParser::User(int pid) { 
  string process_uid = LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  std::string line;
  std::string user_name , x ,etc_uid;
  while(std::getline(filestream,line)){
    std::replace(line.begin(),line.end(),':',' ');
    std::istringstream linestream(line);
    linestream >> user_name;
    linestream >> x;
    linestream >> etc_uid;
    if(etc_uid == process_uid){
      filestream.close();
      return user_name;
    }
  }
  filestream.close();
  return user_name; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  long starttime= 0.0l;
  long system_hertz= 0.0l;

  int count = 0;
  string key;
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  std::getline(filestream,line);
  std::istringstream linestream(line);
  while(count<22){

    if(count==21){
      linestream>>key;
      starttime = long(stoi(key));
    }

    linestream>>key;
    count++;
  }

  system_hertz = _SC_CLK_TCK;
  filestream.close();
  return starttime/system_hertz;
}


float LinuxParser::processCpuUtilization(int pid) { 
  
  long int system_uptime= 0.0l;
  long int utime= 0.0l;
  long int stime= 0.0l;
  long int cutime= 0.0l;
  long int cstime= 0.0l;
  long int starttime= 0.0l;
  long int system_hertz= 0.0l;

  std::ifstream open_system_uptime(kProcDirectory + kUptimeFilename);
  std::string line;
  std::getline(open_system_uptime,line);
  std::istringstream linestream_system(line);
  std::string key;
  linestream_system >> key;
  system_uptime = (stol(key));
  open_system_uptime.close();

  int count = 0;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  std::getline(filestream,line);
  std::istringstream linestream(line);
  while(count<22){

    if(count==13){
      linestream>>key;
      utime = (stol(key));
    }else if(count==14){
      linestream>>key;
      stime = (stol(key));
    }else if(count==15){
      linestream>>key;
      cutime = (stol(key));
    }else if(count==16){
      linestream>>key;
      cstime = (stol(key));
    }
    else if(count==21){
      linestream>>key;
      starttime = (stol(key));
    }

    linestream>>key;
    count++;
  }

  system_hertz = _SC_CLK_TCK;


  long int total_time = utime + stime;
  total_time = total_time + cutime + cstime;
  long int seconds = system_uptime - (starttime / system_hertz);
  float cpu_usage = ((total_time / system_hertz) / seconds);

  filestream.close();
  return cpu_usage;
}