#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) {
   pid_ = pid;
};

// TODO: Return this process's ID
int Process::Pid() const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
   string key, line, value;
   vector<string> cpu;
   std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid_) + LinuxParser::kStatFilename);
   if(filestream.is_open()) {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      for(int i = 0; i < 22; i++) {
         linestream >> value;
         cpu.push_back(value);
      }
   }
   float time = std::stoi(cpu[13]) + std::stoi(cpu[14]) + std::stoi(cpu[15]) + std::stoi(cpu[16]);
   float seconds = LinuxParser::UpTime() - (std::stoi(cpu[21]) / sysconf(_SC_CLK_TCK));
   return time/sysconf(_SC_CLK_TCK)/seconds;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
   return a.CpuUtilization() < CpuUtilization(); 
}

