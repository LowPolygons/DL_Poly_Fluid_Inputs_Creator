#ifndef MOLECULE_PLACER

#define MOLECULE_PLACER

#include <vector>
#include <array>
#include <iostream>

#include "../molecule/Molecule.h"

class MoleculePlacer {
  public:
    MoleculePlacer(std::array<std::array<double, 3>, 3> axisVectors, int moleculeCount, 
                   std::vector<Molecule> _molecules, std::vector<int> _moleculePercentages, 
                   float _boundMultiplier, std::vector<std::array<double, 3>> _offsets) {
      vec1 = axisVectors[0];
      vec2 = axisVectors[1];
      vec3 = axisVectors[2];

      numMolecules = moleculeCount;
      molecules = _molecules;
      moleculePercentages = _moleculePercentages;
      boundMultiplier = _boundMultiplier;
      offsets = _offsets;
  }

    //Generate a lattice, check if the distacnes between each axis allows for the max particle size to be adjacent
    //If it isn't prompt the user to increase the corresponding axis(s) to whatever figure necessary to fit all particles
    auto ConfirmGridFitsMoleculeCount() -> bool;
    //Loop through the various molecules in their corresponding amounts, randomly picking an offset from the array and removing it in turn.
    //Rotate the particle by a random amount according to the given random seed
    //Add the particles to the final array ensuring offsets are fine
    auto PlaceMolecules(int angleRandSeed, int offsetRandSeed) -> void;
    //Getter
    auto Particles() -> std::vector<std::array<double, 3>>;
    auto AtomTypes() -> std::vector<std::string>;
 
private:

  std::array<double, 3> vec1;
  std::array<double, 3> vec2;
  std::array<double, 3> vec3;

  int numMolecules;
  float boundMultiplier;

  std::vector<std::array<double, 3>> particles;
  std::vector<std::string> atomTypes;
  std::vector<std::array<double, 3>> offsets;
  std::vector<Molecule> molecules;
  std::vector<int> moleculePercentages;

};

#endif
