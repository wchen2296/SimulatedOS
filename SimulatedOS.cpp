//
//  SimulatedOS.cpp
//  OS
//
//  Created by William Chen on 12/13/22.
//

#include "SimulatedOS.h"
#include <iostream>

//constuctor
SimulatedOS::SimulatedOS(int numberOfDisks, int amountOfRAM, int pageSize):num_of_Disks_{numberOfDisks},AmountRAM_{amountOfRAM},PageSize_{pageSize},CPU_USE_{Process(0, 0)}{
    if(AmountRAM_%pageSize!=0){
        std::cout<<"ERROR: Page size must divide RAM size"<<std::endl;
    }
}

void SimulatedOS::NewProcess(int priority){
    Process NewProcess(pid_counter,priority);
    pid_counter++;
   
   
 
        for(int i{0};i<RAM_.size();i++){
            if(RAM_[i].GetPID()!=CPU_USE_.GetPID()){
                RAM_[i]=NewProcess;
                break;
            }
          
        }
    
    
        
        RAM_.push_back(NewProcess); 
    
    Ready_Q_.push_back(NewProcess);
    Set_Cpu_Use(NewProcess);//checks if new process should be using cpu
}
//Currently running process wants to terminate. Immediately remove the process from the system and free all the memory it was using.
void SimulatedOS::Exit(){
    for(int i=0;i<Ready_Q_.size();i++){
        if(Ready_Q_[i].GetPID()==CPU_USE_.GetPID()){
            Ready_Q_.erase(Ready_Q_.begin()+i);
        }
    }
    for(int i=0;i<Disk_Q_.size();i++){
        if(Disk_Q_[i].GetPID()==CPU_USE_.GetPID()){
            Disk_Q_.erase(Disk_Q_.begin()+i);
        }
    }
    for(int i=0;i<RAM_.size();i++){
        if(RAM_[i].GetPID()==CPU_USE_.GetPID()){
            RAM_.erase(RAM_.begin()+1);
        }
    }
    Set_Cpu_Use(Ready_Q_[0]);//another process takes over CPU usage
}

void SimulatedOS::Set_Cpu_Use(Process process){
    Process cpu_use= Ready_Q_[0];
    if(Ready_Q_.size()==0){
        std::cout<<"No programs using cpu"<<std::endl;
        return;
    }
    for(int i =0;i<Ready_Q_.size();i++){
        if(Ready_Q_[i].getPriority()>cpu_use.getPriority()){
            cpu_use=Ready_Q_[i];
        }
    }
    CPU_USE_=cpu_use;
}
//Currently running process requests to read the specified file from the disk with a given number. The process issuing disk reading requests immediately stops using the CPU, even if the ready-queue is empty.
void SimulatedOS::DiskReadRequested(int diskNumber, std::string fileName){
    if(diskNumber<0||diskNumber>num_of_Disks_){
        std::cout<<"Instruction ignored: no disk with such number exists"<<std::endl;
        return;
    }
    CPU_USE_.setFileName(fileName);
    Disk_Q_.push_back(CPU_USE_);
    int curr_cpu=CPU_USE_.getPriority();
    Process cpu_use(0,0);
    //checks for next priority to for CPU use and keeps old process in RAM
    for(int i=0;i<Ready_Q_.size();i++){
        if(Ready_Q_[i].getPriority()!=curr_cpu && Ready_Q_[i].getPriority()> cpu_use.getPriority()){
            cpu_use=Ready_Q_[i];
        }
        CPU_USE_=cpu_use;
    }
 
    
}

int SimulatedOS::GetPageSize(){
    return PageSize_;
}

// A currently running process wants to fetch instruction from RAM at the specified logical address
void SimulatedOS::FetchFrom(unsigned int memoryAddress){
    Process new_p(CPU_USE_.GetPID(),CPU_USE_.getPriority());
    new_p.SetPage(memoryAddress/GetPageSize());
    new_p.SetPC(memoryAddress);
   // RAM_.push_back(new_p);
    for(int i{0};i<RAM_.size();i++){
        if(RAM_[i].GetPID()!=CPU_USE_.GetPID()){
            RAM_[i]=new_p;
            break;
        }
        else{
            RAM_.push_back(new_p);
            break;
        }
    }
    
}

void SimulatedOS::DiskJobCompleted(int diskNumber){
    if(diskNumber<0||diskNumber>num_of_Disks_){
        std::cout<<"Instruction ignored: no disk with such number exists"<<std::endl;
        return;
    }
    //clears disk
    Disk_Q_.pop_back();
    //checks which process should use cpu when old process comes back
    Set_Cpu_Use(Ready_Q_[0]);
}

void SimulatedOS::PrintCPU(){
    std::cout<<"CPU: "<<CPU_USE_.GetPID()<<std::endl;
}

void SimulatedOS::PrintReadyQueue(){
    std::cout<<"Read-Queue: ";
    for(int i{0};i<Ready_Q_.size();i++){
        if(Ready_Q_[i].GetPID()!=CPU_USE_.GetPID()){
            std::cout<<Ready_Q_[i].GetPID()<<" ";}
    }
    std::cout<<std::endl;
}

void SimulatedOS::PrintRAM(){
    std::cout<<"Frame   Page    PID"<<std::endl;
    for(int i{0}; i<(AmountRAM_/PageSize_);i++){
        if(i<RAM_.size()){
            std::cout<<i<<"       "<<RAM_[i].getPage()<<"        "<<RAM_[i].GetPID()<<std::endl;
            
        }
        else{
            std::cout<<i<<std::endl;}
    }
    
    
}

void SimulatedOS::PrintDisk(int diskNumber){
    if(diskNumber<0||diskNumber>num_of_Disks_){
        std::cout<<"Instruction ignored: no disk with such number exists"<<std::endl;
        return;
    }
    std::cout<<"Disk "<<diskNumber<<":"<<" PID "<<Disk_Q_[0].GetPID()<<", "<<'"'<<Disk_Q_[0].GetFileName()<<'"'<<std::endl;
}

void SimulatedOS::PrintDiskQueue(int diskNumber){
    if(diskNumber<0||diskNumber>num_of_Disks_){
        std::cout<<"Instruction ignored: no disk with such number exists"<<std::endl;
        return;
    }
    std::cout<<"Disk "<<diskNumber<<":"<<" I/O-queue: ";
    if(Disk_Q_.size()-1==0){
        std::cout<<"Empty";
    }
    else{
        for(int i{1};i<Disk_Q_.size();i++){
            std::cout<<Disk_Q_[i].GetPID()<<" ";
        }
    }
    std::cout<<std::endl;
}
