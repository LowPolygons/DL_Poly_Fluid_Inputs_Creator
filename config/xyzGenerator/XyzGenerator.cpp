#include "xyzGenerator.h"
#include "../../general/structs/structures.h"

#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <algorithm>

//General function for generating either Positions, Velocities or Forces
//auto XyzGenerator::generateParticleXYZ(XYZGEN genType) -> std::vector<std::array<double, 4>>;
 
auto XyzGenerator::randomUniform(unsigned int seed) -> std::vector<std::array<double, 3>> {
  //Initialises the RNG generator with a seed
  std::mt19937 generator(seed);

  //Creates the class which converts random numbers into something corresponding with the given range and the given distribution
  std::uniform_real_distribution<> distribution(0, 1);

  //Call using distribution(generator);
  
  //A point can be defined to be in the cell by being expressed as a sum of each three defining vectors, each with:
  //0 <= coefficient < 1
  std::vector<std::array<double, 3>> particles(numParticles); 

  for (int index = 1; index <= numParticles; index++) {
    //Generate a 3 random numbers beteween 0 and 1
    std::array<double, 3> coeffs;
    coeffs[0] = distribution(generator);
    coeffs[1] = distribution(generator);
    coeffs[2] = distribution(generator);

    //Just summing each axis' components for each pixel
    particles[index-1][0] = coeffs[0]*xAxis[0] + coeffs[1]*yAxis[0] + coeffs[2]*zAxis[0]; 
    particles[index-1][1] = coeffs[0]*xAxis[1] + coeffs[1]*yAxis[1] + coeffs[2]*zAxis[1];
    particles[index-1][2] = coeffs[0]*xAxis[2] + coeffs[1]*yAxis[2] + coeffs[2]*zAxis[2];
  }

  return particles;
}

auto XyzGenerator::generateLattice(int numP) -> std::array<int, 3> {
  //Calculate the nearest cubic number to the num of particles
  int cubicNumber = 1;

  while (cubicNumber*cubicNumber*cubicNumber < numP) {
    cubicNumber++;
  }

  //Calculate the prime factor decomposition of the num of particles
  std::vector<int> factors;

  int currFactor = 2; //start at 2 not 1

  //Starting at the first prime, repeatedly attempts to divide numP until it equals 1 to get prime factors
  while (numP > 1) {
    if (numP % currFactor != 0) {
      currFactor++;
    } else {
      factors.push_back(currFactor);
      
      numP = numP / currFactor;

      currFactor = 2;
    }
  }

  std::array<int, 3> rtn = {1, 1, 1};
  //Loop through and divy the factors among the 3
  for (int i = 1; i <= factors.size(); i++) {
    rtn[i % 3] = rtn[i % 3] * factors[i-1];
  }

  //If the prime factor decomposition has numbers that are excessive (for eg 1x1x73),
  const int excessiveCutoff = 3;
  //Then prefer to have them distributed with the cubic number and not take up all spots
  //if tolerable, use the decomposition
  if ( static_cast<float>(*std::max_element(rtn.begin(), rtn.end())) / 
       static_cast<float>(*std::min_element(rtn.begin(), rtn.end())) > excessiveCutoff ) {
    //Exceeds tolerance
    return {cubicNumber, cubicNumber, cubicNumber};
  }

  return rtn;
}

auto XyzGenerator::uniform() -> std::vector<std::array<double, 3>> {
  //Generate the needed positions to form a lattice - Generate a grid like in the domain decomposition problem
  //Divide each axis by the corresponding number
  std::array<int, 3> grid = generateLattice(numParticles); 

  //The increments
  std::array<double, 3> xIncrement = { xAxis[0] / grid[0], xAxis[1] / grid[0], xAxis[2] / grid[0] };
  std::array<double, 3> yIncrement = { yAxis[0] / grid[1], yAxis[1] / grid[1], yAxis[2] / grid[1] };
  std::array<double, 3> zIncrement = { zAxis[0] / grid[2], xAxis[1] / grid[2], zAxis[2] / grid[2] };

  //Return Value
  std::vector<std::array<double, 3>> particles(numParticles);

  //Starting at zero because I don't want particles to have the chance to spawn at (0,0,0)
  //Subtracting half of each increment so that they don't have a chance to spawn at {max, max, max}
  for (int index = 1; index <= numParticles; index++) {
   
    //What position the current particle should be at; Messy, but it is substrating the subsidiary layer to see how far in it should be for the current layer 
    int tempIndex = index-1;
    int zLayer = tempIndex / (grid[0]*grid[1]); //How many XY layers go into it
    int yLayer = (tempIndex - zLayer*(grid[0]*grid[1])) / grid[0];
    int xLayer = (tempIndex - zLayer*(grid[0]*grid[1])) - grid[0]*yLayer;

    //The []-axis component of each major axis, + half an increment
    particles[index-1][0] = xLayer*xIncrement[0] + yLayer*yIncrement[0] + zLayer*zIncrement[0] + (xIncrement[0] + yIncrement[0] + zIncrement[0]) / 2;
    particles[index-1][1] = xLayer*xIncrement[1] + yLayer*yIncrement[1] + zLayer*zIncrement[1] + (xIncrement[1] + yIncrement[1] + zIncrement[1]) / 2;
    particles[index-1][2] = xLayer*xIncrement[2] + yLayer*yIncrement[2] + zLayer*zIncrement[2] + (xIncrement[2] + yIncrement[2] + zIncrement[2]) / 2;
  }

  return particles;
}
