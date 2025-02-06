#ifndef FIELD_LINE_CREATOR

#define FIELD_LINE_CREATOR

#include <iostream>
#include <vector>
#include "../config/structs/structures.h"
#include "../config/molecule/Molecule.h"

class f_Line_Creator {
public:
  f_Line_Creator(std::string _description, UNITS _unit, int _moleculeCount, 
                 std::vector<std::string> _moleculeNames, 
                 std::vector<int> _moleculeCount, 
                 std::vector<Molecule> _moleculeList) {
    description = _description;
    unit = _unit;
    moleculeNames = _moleculeNames;
    moleculeCount = _moleculeCount;
    moleculeList = _moleculeList;
  };
  
  auto GetDescription() -> std::vector<std::string>;

  auto GetUnit() -> std::vector<std::string>;

  auto GetMoleculeCount() -> std::vector<std::string>;  

  auto GetMoleculeNames() -> std::vector<std::string>;  

  auto GetMoleculeCount() -> std::vector<std::string>;

  auto GetMoleculeList() -> std::vector<string>;

private:
  // Same description as the config file 
  std::string description;
  // Sources
  UNITS unit;

  int moleculeCount;
  
  std::vector<std::string> moleculeNames; 
  std::vector<int> moleculeCount;
  std::vector<Molecule> moleculeList;
};

#endif
