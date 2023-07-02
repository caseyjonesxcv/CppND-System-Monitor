#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include "format.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using namespace std;
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes

vector<Process>& System::Processes() { 
  processes_.clear();
  vector<int> pids = LinuxParser::Pids();
    for (int i : pids) {
        Process process(i);
        processes_.emplace_back(process);
    }
    std::sort(processes_.begin(), processes_.end()); 
    return processes_;
 }

// DONE
std::string System::Kernel() { return LinuxParser::Kernel(); }

//DONE
float System::MemoryUtilization() {return LinuxParser::MemoryUtilization(); }

// DONE
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// DONE
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DONE
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// DONE
long int System::UpTime() { return LinuxParser::UpTime(); }
