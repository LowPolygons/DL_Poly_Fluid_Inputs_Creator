#ifndef INPUTS_FOR_GENERATOR
#define INPUTS_FOR_GENERATOR

#include "../general/structs/structures.h"
#include <vector>
#include <iostream>
#include <array>

struct ConfigInputs {
  //==================================// 
  //             Standard             //
  //==================================//

  // The title that goes at the top of the config file
  std::string description = "Oh hello";

  // Input the number of molecules to be generated in total, not the number of particles
  // That can be calculated in the program
  int numOfMolecules = 20000;

  // These are all the molecules that are to be used in the config file
  // The order matters 
  std::vector<std::string> molecules    = { "H2OBEAD" }; // { "H2O", "H2SO4" };
  
  // The percentages of each molecule in the generated fluid, according to the above order
  // Stored as integers, as you want to check if it sums to 100 
  // which is much less likely to result in a precision issue as opposed to floats summing to 1
  std::vector<int> moleculePercentages = { 100 };

  //==================================// 
  //              Config              //
  //==================================//

  //Check DL_POLY documentation for what these mean. Alternatively, checking out the enum in the structures.h file will show all options
  LEVCFG levcfg = LEVCFG::COORDS;
  IMCON imcon = IMCON::PARALLELEPIPED;

  // The three unit vectors, these will be labelled in the config file in the same order here
  // The positions of the particles will be described by the sum of some multiple of the below vectors
  std::array<double, 3> vector1 = { 111.0,  0.0,  0.0};
  std::array<double, 3> vector2 = {  0.0, 111.0,  0.0};
  std::array<double, 3> vector3 = {  0.0,  0.0, 300.0};

  // The two vectors will describe the minimum/(largest negative) and maximum/(largest postive) velocity a molecule can be randomly assigned
  std::array<double, 3> vel_minimum = { -200.0, -200.0, -200.0 };
  std::array<double, 3> vel_maximum = {  200.0,  200.0,  200.0 };

  // Just as above, but for forces
  std::array<double, 3> fce_minimum = { -200.0, -200.0, -200.0 };
  std::array<double, 3> fce_maximum = {  200.0,  200.0,  200.0 };

  //The distribution types for the vector components to be generated
  XYZGEN gen_position = XYZGEN::UNIFORM;
  XYZGEN gen_velocity = XYZGEN::RANDOM_UNIFORM;
  XYZGEN gen_force    = XYZGEN::RANDOM_UNIFORM;

  //The random seesd for rotating the molecules and offets picking
  int randSeed_Angle = 123123;
  int randSeed_Offsets = 4393;

  //If the distribution type isn't random, these will be ignored: DO NOT delete from the file
  int randSeed_Position = 5;
  int randSeed_Velocity = 6;
  int randSeed_Force = 7;

  // Bounding Region calculations
  
  // Only have one enabled (if there are varying bounding region calculations)
  bool useBoundingSpheres = true;
    // WARNING: Allowing this to be true may result in either simulation explosion or lack of reproduceabiity in results
    // If true  -> possibility for molecules/bonds to intersect or overlap each other
    // If false -> forces a totally uniform distribution and ensures that the positions of generated points on the grid
    //             cannot possibly overlap by ensuring each point is at least 2x the largest bounding-sphere radius away from any other point
    bool allowIntersectingBoundingSpheres = false;
    // If this is exactly 1, it means that some particles could touch in an exact scenario. This forces the bounding sphere to be slightly larger
    double boundingSphereMultiplier = 1.1;

  
  //==================================// 
  //               Field              //
  //==================================//

  // These are the units used by DL_POLY
  UNITS units = UNITS::KCAL;

  //These are all the VDWs to be listed at the bottom of the field file
  std::vector<std::string> vdwInteracts = { "WT_WT" };

};

#endif
