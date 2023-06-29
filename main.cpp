//
//  main.cpp
//  OS
//
//  Created by William Chen on 12/13/22.
//


#include "SimulatedOS.h"

int main(int argc, const char * argv[]) {
   
    SimulatedOS osSim{ 1, 300, 100 };

        osSim.NewProcess(10);
        osSim.NewProcess(5);

        osSim.PrintRAM();
        // Frame    Page    PID
        // 0        0        1
        // 1        0        2
        // 2

        osSim.FetchFrom(120);
        osSim.PrintRAM();
        // Frame    Page    PID
        // 0        0        1
        // 1        0        2
        // 2        1        1

        osSim.DiskReadRequested(0, "job.docx");
        osSim.PrintRAM();
        // Frame    Page    PID
        // 0        0        1
        // 1        0        2
        // 2        1        1

        osSim.FetchFrom(777);
        osSim.PrintRAM();
        // Frame    Page    PID
        // 0        7        2
        // 1        0        2
        // 2        1        1
    osSim.PrintCPU();
    osSim.NewProcess(1);
        osSim.PrintRAM();
        // Frame    Page    PID
        // 0        7        2
        // 1        0        2
        // 2        0        3
    
    osSim.DiskJobCompleted(0);
    // The following happens after this command:
    // The process 1 returns to ready-queue after the hard disk finished reading file for it.
    // Since the process 1 has the higher priority than the one currently running, the process 1 starts using the CPU immedeately
    // To use the CPU, the process one need its last used page (page 1) in memory (and thats what your simulation should provide)
    osSim.PrintRAM();
    // Frame    Page    PID
    // 0        7        2
    // 1        1        1
    // 2        0        3


    return 0;
}

