// Operating System
// Longest Job First
//eng.AhmadAbukhuit

# include <iostream>
# include <fstream>
# include <string> 

struct Process{
	int ArrivalTime ;  
	int ProcessingTime ;
	std::string ProcessName ;
	int delay ; 
	int turn  ;
	int resp ; 
	int PStartTime ; 
	int PEndTime ; 	
	bool state ;

	Process() {
		ProcessName = "" ; 
		ArrivalTime = 0 ; 
		ProcessingTime = 0 ;
		state = false ; 
	}
	Process(std::string s , int a , int p) { 
		ProcessName = s ; 
		ArrivalTime = a ; 
		ProcessingTime = p ;
	        state = false ; 	
	}
	void print () {
		// write the processes details in out.txt file 
		std::fstream ofile ; 
		ofile.open("out.txt" , std::ios::out | std::ios::app) ; 
		if (ofile.is_open()) {
			ofile << ProcessName << ": (response=" << resp << ", "  ;
			ofile << "turnaround=" << turn << ", " ; 
			ofile << "delay=" << delay << ")\n" ; 
		}
		else 
			std::cout << "There is Problem in output file\n" ; 
		ofile.close() ; 
	}
	void print_process () {
		// writer the name of processes in out.txt file 
		std::fstream ofile ; 
		ofile.open("out.txt" , std::ios::app) ;
		ofile << ProcessName ; 
		ofile.close() ; 
	}	
};

int main () {

	std::cout << " ---------------------------------------------- \n";
	std::cout << " |       Welcome To My Scheduler Algorithm    | \n";
	std::cout << " |            Longest Job First (LJF)         | \n";
	std::cout << " |              Operating Systems             | \n";
	std::cout << " |              eng.AhmadAbukhuit             | \n";
	std::cout << " ---------------------------------------------- \n";
	
	long x ; // number of processes
        int Atime , Ptime ; 
	std::string Pname ; 
	int complet = 0 ; //indicates number of process completed 
	int Ctime = 0 ;  // track a time 
	long Rindex = 0 ; // result index

	// read data form in.txt file 
	std::fstream ifile ;

	ifile.open("in.txt" , std::ios::in) ; 

	ifile >> x ; 

	Process *process = new Process[x] ; 

	for (int i=0 ; i<x ; i++) {
		ifile >> Pname >> Atime >> Ptime ; 
		process[i] = Process(Pname,Atime,Ptime) ; 
	}

	ifile.close() ; 
	
	// start the code of choose processes
	while (complet != x) { 
		int CurrentIndex = -1 ; 
		int CurrentPTime = -1 ; 
		
		//choose the process 
		for (int i=Rindex ; i<x ; i++) {
			if (process[i].ArrivalTime <= Ctime && process[i].state == 0) {
				if (process[i].ProcessingTime > CurrentPTime) {
					CurrentPTime = process[i].ProcessingTime ;
					CurrentIndex = i ;
				}
				if (process[i].ProcessingTime == process[CurrentIndex].ProcessingTime) {
					if (process[i].ArrivalTime < process[CurrentIndex].ArrivalTime) {
						CurrentPTime = process[i].ProcessingTime ; 
						CurrentIndex = i ; 
					}
				}
			}
		}
		
		// calculate the times for the process that choose 
		if (CurrentIndex != -1) {
			process[CurrentIndex].PStartTime = Ctime ; 
			process[CurrentIndex].PEndTime = Ctime + process[CurrentIndex].ProcessingTime ; 
			process[CurrentIndex].turn = process[CurrentIndex].PEndTime - process[CurrentIndex].ArrivalTime;
			process[CurrentIndex].delay = process[CurrentIndex].turn - process[CurrentIndex].ProcessingTime;
			process[CurrentIndex].resp = Ctime - process[CurrentIndex].ArrivalTime ;
			process[CurrentIndex].state = true ; 
		   	
			Ctime = process[CurrentIndex].PEndTime ; 
			
			// sort the processes 
			std::swap(process[Rindex],process[CurrentIndex]) ; 
			
			Rindex++ ; 
			complet++ ; 
		}
		else {
			Ctime++ ; 
		}
	}
	
	// print the processes details 
	for (int i=0 ; i<x ; i++) {
		process[i].print() ; 
	}
	
	// print the processes name 
	for (int i=0 ; i<x ; i++) {
		process[i].print_process() ; 
	}
	 
	std::cout << "\n ---------------------------------------------- ";
	std::cout << "\n | You Can Now See The Result in out.txt file | ";
	std::cout << "\n ---------------------------------------------- \n";

	return 0 ;
}
