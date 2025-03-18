#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>


#include "QuickSelect.h"
#include "kNN.h"
#include "chrono.cpp"
#include <climits>



void testQuickselect(){

  std::vector<int> list = {0,1,2,3,4,5,6,7,8,9,10};

  std::vector<int> elements = {3,4,8};
  for(int e : elements){
    std::cout << "Quick select " << e;
    // int r = Quickselect_rec(list, e);
    int r = Quickselect(list, e);
    std::cout << " --> " << r << std::endl;
  }
}

int testLocalization(){
  int k = 7; // TODO: find optimal k value

  std::cout << "Executing localization test" << std::endl;
  std::vector<location> trainingData = leesData("TrainingSet.csv");
  std::vector<location> testData = leesData("TestSet.csv");
  
  auto rng = std::default_random_engine {};
  Chrono chrono;

  std::vector<double> errors(testData.size());
  int nrTestPoint = 0;
  chrono.start();
  for(auto& testPoint : testData){
    // update the distance between the fingerprint of the testing point and all training points
    updateDistance(testPoint, trainingData);

    // TODO: estimate location based on KNN 
    Quickselect(trainingData, k);
    location location = kNN_location(trainingData, k);

    // Calculate the error of the new location based on the testpoint's coordinates
    double error = euclideanDistance(location, testPoint);
    errors[nrTestPoint++] = error;
    
    std::cout << nrTestPoint << ". Error: " <<  error  << " m" << std::endl;
  }
  chrono.stop();

  std::cout << std::fixed << std::setprecision(2) << "Time elapsed for " << testData.size() << " test points: " << chrono.time()/1000 << " s " << std::endl;
  std::cout << "Average error for k = " << k << " is " << 1.0 * std::accumulate(errors.begin(), errors.end(),0.0) / errors.size() << " m " << std::endl;
  std::cout << "Maximal error for k = " << k << " is " << *std::max_element(errors.begin(), errors.end()) << " m " << std::endl;

  return 0;
}


int main()  
{ 
  testQuickselect();
  testLocalization();
  return 0;
}

