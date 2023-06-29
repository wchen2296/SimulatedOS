//
//  Process.hpp
//  OS
//
//  Created by William Chen on 12/14/22.
//

#ifndef Process_hpp
#define Process_hpp

#include <stdio.h>
#include <string>
class Process{
private:
    int pid_;
    int priority_;
    int pc_;
    int page_{0};
    std::string file_name_;

public:
    Process(int pid, int priority);
    
    int GetPID();
    int getPriority();
    int getPage();
    
    std::string GetFileName();
    
    void SetPC(int pc);
    void setFileName(std::string name);
    
    void operator=(const Process b);
    
    
    void SetPage(int page);
    void SetPID(int pid);
    
  
};

#endif /* Process_hpp */
