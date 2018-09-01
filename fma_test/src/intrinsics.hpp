#include <iostream>
#include <chrono>
#include <immintrin.h>

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

void fiddleWithIntrinsics(){
	int int_array[8] = {100, 200, 300, 400, 500, 600, 700, 800};

	__m256i mask = _mm256_setr_epi32(-20, -72, -48, -9, -100, 3, 5, 8);

	/* Selectively load data into the vector */
	__m256i result = _mm256_maskload_epi32(int_array, mask);

    display<int>(result);
}

void loadDataExample(){
    __m256i int_vector = _mm256_setr_epi32(1, 2, 3, 4, 5, 6, 7, 8);
    display<int>(int_vector);
}

void multiplyExample(){
    __m256d veca = _mm256_setr_pd(6.0, 6.0, 6.0, 6.0);
    __m256d vecb = _mm256_setr_pd(2.0, 2.0, 2.0, 2.0);
    __m256d vecc = _mm256_setr_pd(7.0, 7.0, 7.0, 7.0);

    __m256d result = _mm256_fmaddsub_pd(veca, vecb, vecc);
    display<int>(result);
    result = _mm256_mul_pd(veca, vecb);
    display<int>(result);
}

void run(){
    //fiddleWithIntrinsics();
    //loadDataExample();
    //multiplyExample();

    __m256i x=_mm256_setr_epi64x(3,2,9,6);
    display<int64_t>(x);
    __m256d a = _mm256_setr_pd(6.1, 6.0, 6.0, 6.0);
    display<double>(a);
}