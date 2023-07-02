#include <string>
#include <iostream>
#include <iomanip>

#include "format.h"

using std::string;

// DONE

string Format::ElapsedTime(long seconds) { 
    int HH = seconds / 3600;
    seconds  = seconds - (HH * 3600);
    int MM = seconds / 60;
    seconds = seconds - (MM * 60);
    int SS = seconds;
    string H = std::to_string(HH);
    string M = std::to_string(MM);
    string S = std::to_string(SS);

    std::ostringstream stream;

    stream << std::setw(2) << std::setfill('0') << H << ":" 
     << std::setw(2) << std::setfill('0') << M << ":"
     << std::setw(2) << std::setfill('0') << S;
  return stream.str();
    


 }