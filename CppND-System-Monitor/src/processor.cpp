#include "processor.h"
#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>


using std::stof;
using std::string;
using std::to_string;
using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  string line, key, value0, value1, value2, value3, value4, value5, value6, value7, value8, value9;
  float util, user, nice, system, idle, iowait, irq, softirq, steal;
  std::ifstream filestream("/proc/stat");
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
    std::istringstream linestream(line);
      while (linestream >> key >> value0 >> value1 >> value2 >> value3 >> value4 >> value5 >> value6 >> value7 >> value8 >> value9) {
        if (key == "cpu") {
          user = std::stof(value0); 
          nice = std::stof(value1);
          system = std::stof(value2);
          idle = std::stof(value3);
          iowait = std::stof(value4);
          irq = std::stof(value5);
          softirq = std::stof(value6);
          steal = std::stof(value7);
          //guest = std::stof(value8);
          //guestnice = std::stof(value9);
        } 
      }
    }
  }
//PrevIdle = previdle + previowait

float Idle = idle + iowait;

//PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
float NonIdle = user + nice + system + irq + softirq + steal;

//PrevTotal = PrevIdle + PrevNonIdle
float Total = Idle + NonIdle;

//differentiate: actual value minus the previous one
//totald = Total - PrevTotal
//idled = Idle - PrevIdle

//CPU_Percentage = (totald - idled)/totald

util = (Total - Idle)/Total;
return util; 
}