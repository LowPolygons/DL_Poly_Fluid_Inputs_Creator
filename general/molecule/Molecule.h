#ifndef MOLECULE

#define MOLECULE

#include <iostream>
#include <vector>
#include <array>
#include <utility>

#include "../../config/matrix/Matrix.h"

//Important distinction: this is not to be used as an instance of a given molecule, this molecule describes only the relative positions of a molecule
//Angles and things can be calculated when necessary
//This will be called and return a copy of the necessary things. They can be transformed using the same class 
class Molecule {
public:
  Molecule() = default; //Without a defautl constructor, it makes accessing a Molecule in an unordered_map far less pretty
  Molecule(std::vector<std::array<double, 3>> _positions, std::vector<std::string> _atomTypes, std::vector<std::array<int, 2>> _bonds) {
    positions = _positions;
    atomTypes = _atomTypes;
    bonds = _bonds;

    Matrix m;

    boundingRadius = m.MaxModulus(positions);
  }
  //Gets a copy of the coordinates of the molecule 
  auto GetMolecules() -> std::vector<std::array<double, 3>>;
  //Gets a copy of the bonds
  auto GetBonds() -> std::vector<std::array<int, 2>>;
  //Gets a copy of the atom types 
  auto GetTypes() -> std::vector<std::string>;
  //Gets a copy of the bounding radius
  auto GetBoundingRadius() -> double;
  //Useful debugging tool 
  auto PrintSelf() -> void;
private:
  std::vector<std::array<double,3 >> positions;
  std::vector<std::string> atomTypes;
  //These may not necessarily be used by the config file
  std::vector<std::array<int, 2>> bonds;

  double boundingRadius;

  // These values are Field file exclusive
  std::string name;

};

#endif
