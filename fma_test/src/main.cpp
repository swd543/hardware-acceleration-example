#include <iostream>
#include "benchmarker.hpp"
#include "intrinsics.hpp"

using namespace std;

// Standard definitions for dimensions of matrices
#define HEIGHT	1000
#define WIDTH	1000

// Selective compilation. Compile with debug flag enabled only to print the matrices when the matrices are small.
// You really do not want matrices of 1000x1000 overwheming your screen!
// Selective compilation can help make really efficient binaries.
#ifndef DEBUG
#define DEBUG false
#else
#define DEBUG true
#endif


// This is a macro I defined to test defining multiline 'returning' functions via macros.
#define A_MACRO_FUNCTION_THAT_RETURNS_SOMETHING()({	\
	int retval;										\
	retval = 300;									\
	retval;											\
})

// Why the extensive use of macros in this program? They offload almost whatever work they can, to the compiler.

// Return a unity matrix with dimensions
#define UNIT(x,y)({						\
	int64_t** toReturn=0;				\
	toReturn=new int64_t*[x];			\
	for(uint i=0;i<x;i++){				\
		toReturn[i]=new int64_t[y];		\
		for(uint j=0;j<y;j++){			\
			if(i==j){					\
				toReturn[i][j]=1;		\
			}							\
			else{						\
				toReturn[i][j]=0;		\
			}							\
		}								\
	}									\
	toReturn;							\
})

// Return a random matrix with dimensions
#define RANDOM(x,y)({					\
	int64_t** toReturn=0;				\
	toReturn=new int64_t*[x];			\
	for(uint i=0;i<x;i++){				\
		toReturn[i]=new int64_t[y];		\
		for(uint j=0;j<y;j++){			\
			toReturn[i][j]=rand()%10;	\
		}								\
	}									\
	toReturn;							\
})

// A function to display the entire matrix
void display(int64_t** m, uint x, uint y){

	cout<<"Matrix "<<m<<" is as follows : "<<endl;
	for(uint i=0;i<x;i++){
		for(uint j=0;j<y;j++){
			cout<<"\t"<<m[i][j];
		}
		cout<<endl;
	}
}

// A macro that makes life easier by not having to mention HEIGHT,WIDTH everytime
#define DISPLAY(a) display(a,HEIGHT,WIDTH)

int64_t** matrix_multiply(int64_t **a, uint ax, uint ay, int64_t **b, uint bx, uint by){
	if(ay!=bx){
		throw "Dimensions of the two matrices to be multipled were unexpected.";
	}
	uint x=ax,y=by;
	int64_t **toReturn=new int64_t*[x];

	for(uint i=0;i<x;i++){
		toReturn[i]=new int64_t[y];
		for(uint j=0;j<y;j++){
			int64_t temp=0;
			for(uint k=0;k<ay;k++){
				temp+=a[i][k]*b[k][j];
			}
			toReturn[i][j]=temp;
		}
	}
	return toReturn;
}

void matrix_multiply(){
	cout<<"Generating matrices of "<<HEIGHT<<"x"<<WIDTH<<" dimensions..."<<endl;
	int64_t **u=UNIT(HEIGHT,WIDTH), **r=RANDOM(HEIGHT,WIDTH);
	cout<<"Matrices generated successfully."<<endl;

	if(DEBUG){
		DISPLAY(u);
		DISPLAY(r);
	}
	
	cout<<"Commencing matrix multiplication..."<<endl;
	int64_t **result=wrap(matrix_multiply, u, HEIGHT, WIDTH, r, HEIGHT, WIDTH);

	if(DEBUG){
		DISPLAY(result);
	}
}

int main(int argc, char *argv[]) {
	cout<<"This is a test to verify hardware acceleration for AVX2/FMA instructions."<<endl;
	cout<<"My machine uses an Intel 8550u."<<endl;
	
	//matrix_multiply();
	run();
	
	return 0;
}