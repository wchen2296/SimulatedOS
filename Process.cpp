//
//  Process.cpp
//  OS
//
//  Created by William Chen on 12/14/22.
//

#include "Process.h"
Process::Process(int pid, int priority):pid_{pid},priority_{priority}{
    
}

int Process::GetPID(){
    return pid_;
}
int Process::getPriority(){
    return priority_;
}
int Process::getPage(){
    return page_;
}

std::string Process::GetFileName(){
    return file_name_;
}

void Process::SetPC(int pc){
    this->pc_=pc;
}
void Process::setFileName(std::string name){
    this->file_name_=name;
}

void Process::operator=(const Process b){
    this->pid_=b.pid_;
    this->priority_=b.priority_;
    this->pc_=b.pc_;
    this->page_=b.page_;
    this->file_name_=b.file_name_;
    
}

void Process::SetPage(int page){
    this->page_=page;
}
void Process::SetPID(int pid){
    this->pid_=pid;
}
