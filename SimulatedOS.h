//
//  SimulatedOS.hpp
//  OS
//
//  Created by William Chen on 12/13/22.
//

#ifndef SimulatedOS_hpp
#define SimulatedOS_hpp

#include "Process.h"
#include <string>
#include <vector>
class SimulatedOS{
private:
    int num_of_Disks_;
    int AmountRAM_;
    int PageSize_;
    int pid_counter{1};
    

   
    std::vector<Process>Disk_Q_;
    std::vector<Process>Ready_Q_;
    std::vector<Process>RAM_;
    
    Process CPU_USE_; //process using cpu currently
   
    
public:
    
    SimulatedOS(int numberOfDisks, int amountOfRAM, int pageSize);

       // Creates a new process with the specified priority in the simulated system
    void NewProcess(int priority);
   
       // Removes the process from the system and frees all the memory it was using
    void Exit();

       // Currently running process requests to read the specified file from the disk with a given number
    void DiskReadRequested(int diskNumber, std::string fileName);
 

       // A currently running process wants to fetch instruction from RAM at the specified logical address
    void FetchFrom(unsigned int memoryAddress);
    

       // A disk with a specified number reports that a single job is completed
    void DiskJobCompleted(int diskNumber);
   
       // Prints the PID of the process currently using the CPU
    void PrintCPU();
       

       // Prints the PIDs of processes in the ready-queue in any order
    void PrintReadyQueue();
    
          

       // Prints a sorted list of all used frames, page number stored in it, and PID of the process that owns that page
    void PrintRAM();
     

       // Prints the PID of the process served by specified disk and the name of the file read for that process
    void PrintDisk(int diskNumber);
      

       // Prints PIDs of the processes in the I/O-queue of the specified disk starting from the “next to be served” process PID
    void PrintDiskQueue(int diskNumber);
    
    void Set_Cpu_Use(Process process);
    
    int GetPageSize();
    
    
     
};
#endif /* SimulatedOS_hpp */
