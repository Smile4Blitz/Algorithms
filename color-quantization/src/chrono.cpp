
#include "chrono.h"
#include<iostream>
Chrono::Chrono(){}

void Chrono::start(){
   begin = std::chrono::steady_clock::now();
}

void Chrono::stop(){
   end = std::chrono::steady_clock::now();
}

double Chrono::time() const{
   std::chrono::duration<double, std::milli> elapsed = end - begin;
   return elapsed.count();
}


