#ifndef MOLECULE_CONSTRUCTOR

#define MOLECULE_CONSTRUCTOR

#include <vector>
#include <iostream>
#include <unordered_map>
#include "../molecule/Molecule.h"

class MoleculeConstructor {
public:
  MoleculeConstructor(std::vector<std::string> _moleculeFiles) {
    moleculeFiles = _moleculeFiles;
  }

  auto GenerateMolecules() -> void;
  auto Molecules() -> std::unordered_map<std::string, Molecule>;
  auto FormatLinesToValues(std::vector<std::string> linesToFilter, std::string moleculeName) -> void;

private:
  //Perhaps pass these in as inputs to be registered by the main function
  std::vector<std::string> moleculeFiles;
  //Unordered_map as order is not necessarily obvious if it was a standard array
  std::unordered_map<std::string, Molecule> molecules;
};

#endif
