#include <vector>
#include <array>
#include <iostream>
#include <random>
#include <algorithm>

#include "../../general/molecule/Molecule.h"
#include "../xyzGenerator/XyzGenerator.h"
#include "../matrix/Matrix.h"

#include "MoleculePlacer.h"

auto MoleculePlacer::Particles() -> std::vector<std::array<double, 3>> { return particles; }
auto MoleculePlacer::AtomTypes() -> std::vector<std::string> { return atomTypes; }

auto MoleculePlacer::ConfirmGridFitsMoleculeCount() -> bool {
  bool success = true;
  //Create the object to generate the lattice
  XyzGenerator localXYZ( {vec1, vec2, vec3}, numMolecules);
  
  double maxBound = 0;
  
  for (Molecule mol : molecules) {
    if (mol.GetBoundingRadius() > maxBound) {
      maxBound = mol.GetBoundingRadius();
    }
  }

  //Get the dimensions of the lattice
  std::array<int, 3> grid = localXYZ.generateLattice(numMolecules);
  
  //How much the grid divides each axis
  std::array<double, 3> rangePerVector = {
    (vec1[0]+vec2[0]+vec3[0]) / static_cast<double>(grid[0]),
    (vec1[1]+vec2[1]+vec3[1]) / static_cast<double>(grid[1]),
    (vec1[2]+vec2[2]+vec3[2]) / static_cast<double>(grid[2])
  };

  //Check X axis
  if (rangePerVector[0] < maxBound*boundMultiplier*2) {
    success = false;
    double neededMultiplier = grid[0]*maxBound*2*boundMultiplier / (vec1[0]+vec2[0]+vec3[0]);

    std::cout << "[Error] The system is too dense in the X axis. Consider multiplying the X components of your cell vectors by at least more than " << neededMultiplier << std::endl;
  }

  //Check Y Axis
  if (rangePerVector[1] < maxBound*boundMultiplier*2) {
    success = false;
    double neededMultiplier = grid[1]*maxBound*2*boundMultiplier / (vec1[1]+vec2[1]+vec3[1]);

    std::cout << "[Error] The system is too dense in the Y axis. Consider multiplying the Y components of your cell vectors by at least more than " << neededMultiplier << std::endl;
  }

  //Check Z Axis
  if (rangePerVector[2] < maxBound*boundMultiplier*2) {
    success = false;
    double neededMultiplier = grid[2]*maxBound*2*boundMultiplier / (vec1[2]+vec2[2]+vec3[2]);

    std::cout << "[Error] The system is too dense in the Z axis. Consider multiplying the Z components of your cell vectors by at least more than " << neededMultiplier << std::endl;
  }

  //Close program after all logging
  if (!success) {
    exit(EXIT_FAILURE);
  }

  return success;
}

auto MoleculePlacer::MoleculeCounts() -> std::vector<int> { return moleculeCounts; }

auto MoleculePlacer::PlaceMolecules(int angleRandSeed, int offsetRandSeed) -> void { 
  //Calculate the number of molecules for each variation
  std::vector<int> _moleculeCount(moleculePercentages.size());

  float precisionLoss = 0.0f;
  //Currently, the number of particles will not exactly match in the event of a non perfect fraction
  //This should account for less than 1 molecule though
  for (int i = 0; i < moleculePercentages.size(); i++) {
    float currentPercentage = static_cast<float>(moleculePercentages[i]) / 100.0f;
    
    int currentNum = static_cast<int>(static_cast<float>(numMolecules) * currentPercentage);
  
    precisionLoss += (numMolecules*currentPercentage - static_cast<float>(currentNum));

    _moleculeCount[i] = currentNum;
  }
  //Log the precision loss, let the user decide whether to modify or not
  std::cout << "[Info]  Total number of molecules lost due to percentage issues: " << precisionLoss << std::endl;
  //Assign to the member
  moleculeCounts = _moleculeCount;

  std::mt19937 angleGenerator(angleRandSeed);
  std::mt19937 offsetIndexGenerator(offsetRandSeed);

  //0 -> 1 so they can be scaled rather than reforming them every time an array size changes, etc
  std::uniform_real_distribution<> angles(0, 1);
  std::uniform_real_distribution<> offsets_rand(0, 1);

  Matrix local_maths;

  //Now loop through each molecule in turn, Randomise rotation, offset, add to particles, remove offset from list
  for (int i = 0; i < _moleculeCount.size(); i++) {
    int count = _moleculeCount[i];
    Molecule currentMolecule = molecules[i];
    std::vector<std::string> types = currentMolecule.GetTypes();
    //May not actually need the variable itself, therefore _
    for (int _ = 0; _< count; _++) {
      double xAng = static_cast<double>(angles(angleGenerator)*360);
      double yAng = static_cast<double>(angles(angleGenerator)*360);
      double zAng = static_cast<double>(angles(angleGenerator)*360);

      int offsetIndex = static_cast<int>(offsets_rand(offsetIndexGenerator)*(offsets.size()-1));
      
      auto currOffset = offsets[offsetIndex];
      //Remove the offset
      offsets.erase(offsets.begin() + offsetIndex);

      //Get the relative positions of the current molecules
      std::vector<std::array<double, 3>> poses = currentMolecule.GetMolecules();
      //Rotate
      poses = local_maths.Rotate(poses, xAng, yAng, zAng); 
      //Translate to the offset
      poses = local_maths.Translate(poses, currOffset);
      
      //Load the new poses into the particles folder 
      //TODO: the starting index of where these will go needs to be added to the bond indexes which can be retrieved from currentMolecule
      //TODO: the particle types need to be added to the types array too
      for( auto pos : poses) {
        particles.push_back(pos); 
      }

      for( std::string atom : types ) {
        atomTypes.push_back(atom);
      }
    }
  }
}
