#include "ncurses_display.h"
#include "system.h"


// #include "linux_parser.h"
// #include <vector>
// #include <iostream>

int main() {
  System system;
  NCursesDisplay::Display(system,50);

  // std::vector<int> pids = LinuxParser::Pids();
  // for(auto pid:pids){
  //   std::cout<<pid<<" ";
  // }
  // std::cout<<"\n";

  return 0;
}