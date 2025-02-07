#ifndef FIELD_LINE_CREATOR

#define FIELD_LINE_CREATOR

#include <iostream>
#include <vector>
#include "../../general/structs/structures.h"
#include "../../general/molecule/Molecule.h"

class f_LineCreator {
public:
  f_LineCreator(FieldParameters _widths, std::string _description, UNITS _unit, int _moleculeCount, 
                 std::vector<std::string> _moleculeNames, 
                 std::vector<int> _perMoleculeCount, 
                 std::vector<Molecule> _moleculeList) {
    widths = _widths;
    description = _description;
    unit = _unit;
    moleculeNames = _moleculeNames;
    perMoleculeCount = _perMoleculeCount;
    moleculeList = _moleculeList;
  };
  
  auto formatter(int size, std::string var) -> std::string;

  auto GetDescription() -> std::vector<std::string>;

  auto GetUnit() -> std::vector<std::string>;

  auto GetMoleculeCount() -> std::vector<std::string>;  

  auto GetMoleculeNames() -> std::vector<std::string>;  

  auto GetPerMoleculeCount() -> std::vector<std::string>;

  auto GetMoleculeList() -> std::vector<std::string>;

private:
  // Field Parameters
  FieldParameters widths;
  // Same description as the config file 
  std::string description;
  // Sources
  UNITS unit;

  int moleculeCount;
  
  std::vector<std::string> moleculeNames; 
  std::vector<int> perMoleculeCount;
  std::vector<Molecule> moleculeList;
};

#endif
