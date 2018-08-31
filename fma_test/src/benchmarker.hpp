#include <iostream>
#include <chrono>

using namespace std;

// A macro that will fetch the current epoch time in an unsigned long. Such a simple function, yet not implemented
// right out of the box *sigh*
#define NOW()	({																										\
	uint64_t ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();	\
	ms;																													\
})

// A function that takes in a function as an argument, calculates the execution time.
void wrap(void (*fun)()){
	uint64_t t1=NOW();
	fun();
	uint64_t t2=NOW();
	cout<<"Execution of function "<<fun<<" took "<<t2-t1<<" milliseconds."<<endl;
}

// A function that takes in a function with an argument as an argument , calculates the execution time.
void wrap(void (*fun)(int x), int x){
	uint64_t t1=NOW();
	fun(x);
	uint64_t t2=NOW();
	cout<<"Execution of function "<<fun<<" took "<<t2-t1<<" milliseconds."<<endl;
}

// A function that takes in the matrix multiplication function as an argument, calculates the execution time.
int64_t** wrap(int64_t** (*fun)(int64_t **a,uint ax, uint ay, int64_t **b, uint bx, uint by), int64_t **a,uint ax, uint ay, int64_t **b, uint bx, uint by){
	uint64_t t1=NOW();
	int64_t** toReturn=fun(a,ax,ay,b,bx,by);
	uint64_t t2=NOW();
	cout<<"Execution of function "<<fun<<" took "<<t2-t1<<" milliseconds."<<endl;
	return toReturn;
}