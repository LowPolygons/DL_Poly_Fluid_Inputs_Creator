#include "Molecule.h"

#include <iostream>
#include <vector>
#include <array>
#include <cmath>

auto Molecule::GetMolecules() -> std::vector<std::array<double, 3>> { return positions; }
auto Molecule::GetBonds()     -> std::vector<std::array<int, 2>>    { return bonds;     }
auto Molecule::GetTypes()     -> std::vector<std::string>           { return atomTypes; }

auto Molecule::GetBoundingRadius() -> double { return boundingRadius; }

auto Molecule::PrintSelf() -> void {
  std::cout << "Atoms >>" << std::endl;

  for (int i = 0; i < atomTypes.size(); i++) {
    std::cout << "- Atom " << atomTypes[i] << ": " << positions[i][0] << ", " << positions[i][1] << ", " << positions[i][2] << std::endl;
  }
    
  std::cout << "Bonds >>" << std::endl;
  for (std::array<int, 2> c : bonds) {
    std::cout << "- "<< c[0] << " -> " << c[1] << std::endl;
  }
}


