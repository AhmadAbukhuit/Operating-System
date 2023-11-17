# include <fstream>
# include <iostream>
# include <thread>
# include <iomanip>
# include <semaphore> 

using namespace std;

std::counting_semaphore<1> SID(1) ;
std::counting_semaphore<1> SCurrentVal(1) ; 
std::counting_semaphore<1> Sthreashold(1) ;
std::counting_semaphore<1> SWorker(1) ; 

float initVal = 0, threashold = 0 , CurrentVal = 0 ;
int ThreadID = 0, Counter = 0 ;
int belowThreashold = 0, aboveThreashold = 0, equalThreashold = 0 ;
int numMultiply = 0 , numDivide = 0, numAdd = 0, numSubtract = 0 ;
float MultiplyVal = 0 , DivideVal = 0 , AddVal = 0 , SubtractVal = 0 ;

// Worker threads function
void W_multiply(int id) {
	SWorker.acquire() ; 
	if (Counter == 0) {
		SCurrentVal.acquire() ;
		cout << fixed <<setprecision(6) ;
		cout << "Multiplier ThreadID=" << id << ", currentValue=" << initVal <<" -- multiplying "<<MultiplyVal<<endl;
		CurrentVal = initVal * MultiplyVal ; 
                Counter++ ; 
		SCurrentVal.release() ;
	}
	else {
		SCurrentVal.acquire() ; 
		cout << fixed <<setprecision(6) ;
		cout << "Multiplier ThreadID=" << id << ", currentValue=" << CurrentVal <<" -- multiplying "<<MultiplyVal<<endl;
		CurrentVal = CurrentVal * MultiplyVal ; 
		SCurrentVal.release() ; 
	}
	Sthreashold.acquire() ; 
	if (CurrentVal == threashold)
		equalThreashold++ ; 
    	else if (CurrentVal > threashold)
        	aboveThreashold++ ; 
    	else if (CurrentVal < threashold)
        	belowThreashold++ ; 
	Sthreashold.release() ;
	SWorker.release() ; 
}
void W_Divide(int id) {
	SWorker.acquire() ; 
        if (Counter == 0 ) {
		SCurrentVal.acquire() ; 
        	cout << fixed <<setprecision(6) ;
        	cout << "Dividing ThreadID=" << id << ", currentValue=" << initVal <<" -- dividing by "<<DivideVal<<endl;
        	CurrentVal = initVal / DivideVal ; 
        	Counter++ ;
		SCurrentVal.release() ; 
	}
    	else {
		SCurrentVal.acquire() ; 
        	cout << fixed <<setprecision(6) ;
        	cout << "Dividing ThreadID=" << id << ", currentValue=" << CurrentVal <<" -- dividing by "<<DivideVal<<endl;
        	CurrentVal = CurrentVal / DivideVal ; 
		SCurrentVal.release() ; 
        }
	Sthreashold.acquire() ; 
    	if (CurrentVal == threashold)
        	equalThreashold++ ; 
    	else if (CurrentVal > threashold)
        	aboveThreashold++ ; 
    	else if (CurrentVal < threashold)
        	belowThreashold++ ;
       Sthreashold.release() ;
       SWorker.release() ;        
}
void W_Add(int id) {
	SWorker.acquire() ; 
        if (Counter == 0 ) {
		SCurrentVal.acquire() ; 
        	cout << fixed <<setprecision(6) ;
        	cout << "Adding ThreadID=" << id << ", currentValue=" << initVal <<" -- Adding "<<AddVal<<endl;
        	CurrentVal = initVal + AddVal ; 
        	Counter++ ;    
		SCurrentVal.release() ; 
    	}
    	else {
		SCurrentVal.acquire() ; 
        	cout << fixed <<setprecision(6) ;
        	cout << "Adding ThreadID=" << id << ", currentValue=" << CurrentVal <<" -- Adding "<<AddVal<<endl;
        	CurrentVal = CurrentVal + AddVal ; 
		SCurrentVal.release() ; 
        }
	Sthreashold.acquire() ; 
    	if (CurrentVal == threashold)
        	equalThreashold++ ; 
    	else if (CurrentVal > threashold)
        	aboveThreashold++ ; 
    	else if (CurrentVal < threashold)
        	belowThreashold++ ; 
	Sthreashold.release() ;
	SWorker.release() ; 
}
void W_subtract(int id) {
	SWorker.acquire() ; 
	if (Counter == 0 ) {
		SCurrentVal.acquire() ; 
        	cout << fixed <<setprecision(6) ;
        	cout << "Subtracting ThreadID=" << id << ", currentValue=" << initVal <<" -- subtracting "<<SubtractVal<<endl;
        	CurrentVal = initVal - SubtractVal ; 
        	Counter++ ; 
		SCurrentVal.release() ; 
	}
	else {
		SCurrentVal.acquire() ; 
        	cout << fixed <<setprecision(6) ;
        	cout << "Subtracting ThreadID=" << id << ", currentValue=" << CurrentVal <<" -- subtracting "<<SubtractVal<<endl;
        	CurrentVal = CurrentVal - SubtractVal ; 
		SCurrentVal.release() ; 
	}
	Sthreashold.acquire() ; 
    	if (CurrentVal == threashold)
        	equalThreashold++ ; 
    	else if (CurrentVal > threashold)
        	aboveThreashold++ ; 
    	else if (CurrentVal < threashold)
        	belowThreashold++ ;     
	Sthreashold.release() ;
        SWorker.release() ; 	
}

// Manager threads function
void M_multiply() {
    thread *WorkerMultiply = new thread[numMultiply];
    for (int i=0;i<numMultiply;i++) {
    	SID.acquire() ;
        WorkerMultiply[i] = thread (W_multiply,ThreadID) ;
        ThreadID++ ;  
	SID.release() ; 
    }
}
void M_Divide() {
    thread *WorkerDivide = new thread[numDivide];
    for (int i=0;i<numDivide;i++) {
    	SID.acquire() ;
        WorkerDivide[i] = thread (W_Divide,ThreadID) ;  
        ThreadID++ ;  
	SID.release() ; 
    }
}
void M_Add() {
    thread *WorkerAdd = new thread[numAdd];
    for (int i=0;i<numAdd;i++) {
        SID.acquire() ;
        WorkerAdd[i] = thread (W_Add,ThreadID) ; 
        ThreadID++ ;  
	SID.release() ;   
    }
}
void M_subtract() {
    thread *WorkerSubtract = new thread[numSubtract];
    for (int i=0;i<numSubtract;i++) {
    	SID.acquire() ;
        WorkerSubtract[i] = thread (W_subtract,ThreadID) ;
        ThreadID++ ;  
	SID.release() ;   
    }
}
//Start Main function 
int main(int argc, char *argv[]) {
  // Get initialValue and threshold from command line arguments
  initVal = stod(argv[1]);
  threashold = stod(argv[2]);

  // read data from in.txt file
  std::fstream ifile ; 
  ifile.open("in.txt",std::ios::in) ; 
  ifile>> numMultiply >> MultiplyVal ;
  ifile>> numDivide >>DivideVal ;
  ifile>> numAdd >> AddVal ;
  ifile>> numSubtract >> SubtractVal ; 
  ifile.close() ; 

  // create manager threads
  std::thread thread1(M_multiply);
  std::thread thread2(M_Divide);
  thread1.join();
  thread2.join();
  std::thread thread3(M_Add);
  std::thread thread4(M_subtract);
  thread3.join();
  thread4.join();

  // print in out.txt file 
  std::fstream ofile ; 
  ofile.open("out.txt",std::ios::out) ; 
  ofile << fixed << setprecision(6) ; 
  ofile << "Main: Number of Multipliers="<<numMultiply <<", Amount to multiply="<<MultiplyVal<<endl;
  ofile << "Main: Number of Dividers="<<numDivide <<", Amount to divided="<<DivideVal<<endl;
  ofile << "Main: Number of Adders="<<numAdd <<", Amount to added="<<AddVal<<endl;
  ofile << "Main: Number of Subtractors="<<numSubtract <<", Amount to subtracted="<<SubtractVal<<endl;
  ofile << "Main: finalValue=" << CurrentVal << ", belowThreashold=" << belowThreashold << ", aboveThreashold=" << aboveThreashold << ", equalThreashold=" << equalThreashold << endl ; 
  ofile.close() ; 
  return 0 ;
}
