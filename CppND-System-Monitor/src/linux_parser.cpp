#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

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
  return value; 
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
    return kernel;
  }
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

//DONE
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  float memtotal;
  float memfree;
  float buffers;
  float cache;
  float cached;
  float recla;
  float hmem;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
    std::istringstream linestream(line);
    linestream >> key;
        if (key == "MemTotal:") {
          linestream >> memtotal; 
        } 
        else if (key == "MemFree:") {
          linestream >> memfree;
        }
        else if (key == "Buffers:") {
          linestream >> buffers;
        }
        else if (key == "Cached:") {
          linestream >> cache;
        }
        else if (key == "SReclaimable:") {
          linestream >> recla;
        }
        else if (key == "Shmem:") {
          linestream >> hmem;
          break;
        }
    }
  }
  cached = cache + recla - hmem;
  return (memtotal - memfree - (buffers + cached)) / memtotal; 
}

// DONE
long LinuxParser::UpTime() {
  long uptime;
  string line, time;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> time;
    uptime = std::stof(time);
  }
    return uptime;
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
//MAYBE DONE?
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpulist;
  string line;
  string key;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
    std::istringstream linestream(line);
    linestream >> key;
      if (key == "cpu") {
        while(linestream >> key)
        cpulist.push_back(key); 
      }
      break;
    }
  } 
  return cpulist;
} 

// DONE
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
    std::istringstream linestream(line);
    linestream >> key >> value;
      if (key == "processes") {
        return value; 
        break;
      }
    }
  }
  return value; 
 }

// DONE
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
    std::istringstream linestream(line);
    linestream >> key >> value;
      if (key == "procs_running") {
        return value; 
        break;
      }
    }
  }
  return value;
 }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  return line;
 }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function

string LinuxParser::Ram(int pid) { 
  string line, key;
  int value;
  int ram;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
    std::istringstream linestream(line);
    linestream >> key >> value;
      if (key == "VmSize:") {
        ram = value/1000;
      }
    }
  }
  return to_string(ram);
 }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function

string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
    std::istringstream linestream(line);
    linestream >> key >> value;
      if (key == "Uid:") {
        return value;  
        break;
      }
    }
  }
  return value;
 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid = Uid(pid);
  string line, key, value, x;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
    std::replace(line.begin(), line.end(), ':', ' ');
    std::istringstream linestream(line);
    while(linestream >> value >> x >> key){
        if (key == uid) {
        return value;  
        break;
      }
    }
  }
  return string();
 }
}


// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { 
  string line;
  string value;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)) {
    std::istringstream linestream(line);
    for (int i = 0; i < 22; i++) {
      linestream >> value;
    }
    long time =  LinuxParser::UpTime() - (stol(value) / sysconf(_SC_CLK_TCK));
    return time;
    } 
   return 0;
 }
}
