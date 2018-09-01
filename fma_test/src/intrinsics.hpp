#include <iostream>
#include <chrono>
#include <x86intrin.h>

using namespace std;

/*
This is inspired from a brilliant article I read from the link below
https://www.codeproject.com/Articles/874396/Crunching-Numbers-with-AVX-and-AVX
*/


void display(int x, int y, int z){
    cout<<"Whatever is being displayed has a size of "<<x<<" and we are casting to something which has a size "<<y<<", so "<<z<<" iterations are needed."<<endl;
}

template<typename O, typename I>
void display(I v){
    int x=sizeof(v), y=sizeof(O), iterations=x/y;
    display(x,y,iterations);

    O *p=(O*)&v;
    cout<<"[\t";
    for(uint8_t i=0;i<iterations;i++){
        cout<<p[i]<<"\t";
    }
    cout<<"]"<<endl;
}

template<typename I>
void display(I* m, uint x, uint y){
    cout<<"Matrix "<<m<<" is as follows : "<<endl;
	for(uint i=0;i<x;i++){
		for(uint j=0;j<y;j++){
			cout<<"\t"<<m[i][j];
		}
		cout<<endl;
	}
}

void multiplyExample(){
    __m256d veca = _mm256_setr_pd(6.0, 6.0, 6.0, 6.0);
    __m256d vecb = _mm256_setr_pd(2.0, 2.0, 2.0, 2.0);
    __m256d vecc = _mm256_setr_pd(7.0, 7.0, 7.0, 7.0);

    cout<<"\n************ Hardware multiply example ************"<<endl;
    
    display<double>(veca);
    display<double>(vecb);
    cout<<"Multiplying "<<&veca<<" and "<<&vecb<<endl;
    __m256d result = _mm256_mul_pd(veca, vecb);
    display<double>(result);

    cout<<"\n*********** Fused multiply add example ************"<<endl;
    display<double>(vecc);
    cout<<"Fused-Multiply-Add-ing "<<&veca<<", "<<&vecb<<" and "<<&vecc<<endl;

    result = _mm256_fmadd_pd(veca, vecb, vecc);
    display<double>(result);

    cout<<"\n******* Fused multiply add-subtract example *******"<<endl;
    cout<<"Fused-Multiply-Add-Subtract-ing "<<&veca<<", "<<&vecb<<" and "<<&vecc<<endl;

    result = _mm256_fmaddsub_pd(veca, vecb, vecc);
    display<double>(result);
}

void run(){
    multiplyExample();

    int a[2][2]={1,2,3,4};
    int b[2][2]={1,2,3,4};
    display(a,2,2);
    
}