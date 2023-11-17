// Operating System
// Priority
//eng.AhmadAbukhuit

# include <iostream>
# include <fstream>
# include <string>

struct Process {
	std::string ProcessName = "" ; 
	int ArrivalTime ; 
	int ProcessingTime ; 
	int Priority ; 
	int ResponseTime = 0 ; 
	int TurnaroundTime = 0 ; 
	int PStartTime ; 
	int PEndTime ; 
	int Delay ; 
	bool State ; 
	
	Process() {
		ProcessName = " " ; 
		ArrivalTime = 0 ; 
		ProcessingTime = 0 ; 
		Priority = 0 ; 
		State = false ; 
	}
	Process(std::string s , int a , int t , int p) {
		ProcessName = s ; 
		ArrivalTime = a ; 
		ProcessingTime = t ; 
		Priority = p ; 
		State = false ; 
	}
	void Print () { //write the process details in out.txt file
		std::fstream ofile ; 
		ofile.open("out.txt" , std::ios::out | std::ios::app) ; 
		if (ofile.is_open()) {
			ofile << ProcessName << ": (response=" << ResponseTime << ", " ; 
			ofile << "turnaround=" << TurnaroundTime << ", " ;
			ofile << "delay=" << Delay << ")\n" ; 
		}
		else {
			std::cout << "There is problem in opening output file\n" ;
		}
		ofile.close() ; 
	}
	void PrintName (bool a) { // write the name of processes in out.txt file
		std::fstream ofile ; 
		ofile.open("out.txt" , std::ios::app) ; 
		if (ofile.is_open()) {
			if (a == false) 
				ofile << ProcessName ; 
			else 
				ofile << ProcessName << "\n" ; 
		}
		else {
			std::cout << "Thers is problem in opening output file\n" ; 
		}
		ofile.close() ; 
	}
};

int main () {

	std::cout << " ---------------------------------------------- \n";
	std::cout << " |       Welcome To My Scheduler Algorithm    | \n";
	std::cout << " |             Priority Scheduling            | \n";
	std::cout << " |              Operating Systems             | \n";
	std::cout << " |              eng.AhmadAbukhuit             | \n";
	std::cout << " ---------------------------------------------- \n";

	std::string PName ; 
	int Ctime = 0 ; // track a time 
	long N ; // number of processes
	int complet = 0 ; // indicates number of process completed
	long Rindex = 0 ; // result index
	int Atime , Ptime , Pri ; 
	
	// read data from int.txt file 
	std::fstream ifile ; 
	ifile.open("in.txt" , std::ios::in) ; 

	if (!ifile.is_open()) {
		std::cout << "There is probelm in opening input file\n" ; 
	}
	
	ifile >> N ; 

	Process * process = new Process[N] ;   

	for (int i=0 ; i<N ; i++) {
		ifile >> PName >> Atime >> Ptime >> Pri ; 
		process[i] = Process(PName,Atime,Ptime,Pri) ; 
	}

	ifile.close() ; 
	
	// strat the code of choose processes
	while (complet != N) {
		int CurrentIndex = -1 ; 
		int CurrentPriority = -1 ; 

		//chosse the process
		for (int i=Rindex ; i<N ; i++) {
			if (process[i].ArrivalTime <= Ctime && process[i].State == 0) {
				if (process[i].Priority > CurrentPriority) {
					CurrentPriority = process[i].Priority ;
					CurrentIndex = i ; 
				}
				else if (process[i].Priority == CurrentPriority) {
					if (process[i].ArrivalTime < process[CurrentIndex].ArrivalTime) {
						CurrentPriority = process[i].Priority ; 
						CurrentIndex = i ; 
					}
					else 
						continue ; 
				}
				else {
					continue ; 
				}
			}
		}

		// claculate the times for the process that choose
		if (CurrentIndex != -1) {
			process[CurrentIndex].State = true ; 
			process[CurrentIndex].PStartTime = Ctime ; 
			process[CurrentIndex].PEndTime = Ctime + process[CurrentIndex].ProcessingTime ;
			process[CurrentIndex].TurnaroundTime = process[CurrentIndex].PEndTime - process[CurrentIndex].ArrivalTime ; 
			process[CurrentIndex].Delay = process[CurrentIndex].TurnaroundTime - process[CurrentIndex].ProcessingTime ; 
			process[CurrentIndex].ResponseTime = Ctime - process[CurrentIndex].ArrivalTime ; 

			Ctime = process[CurrentIndex].PEndTime ; 

			//sort the process
			std::swap(process[Rindex] , process[CurrentIndex]) ;
			Rindex++ ; 
			complet++ ; 
		}
		else {
			Ctime++ ; 
		}
	}

	// print the process name 
	for (int i=0 ; i<N ; i++) {
		bool a = false ;
		if (i == N-1)
			a = true ; 
		process[i].PrintName(a) ; 
	}

	// print the process deatails
	for (int i=0 ; i<N ; i++) {
		process[i].Print() ; 
	}

	std::cout << "\n ---------------------------------------------- ";
	std::cout << "\n | You Can Now See The Result in out.txt file | ";
	std::cout << "\n ---------------------------------------------- \n";

	return 0;
}

