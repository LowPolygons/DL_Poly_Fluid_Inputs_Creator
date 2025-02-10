#ifndef FIELD_LINE_CREATOR

#define FIELD_LINE_CREATOR

#include <iostream>
#include <vector>
#include "../../general/structs/structures.h"
#include "../../general/molecule/Molecule.h"
#include "../../general/moleculeConstructor/MoleculeConstructor.h"

class f_LineCreator {
public:
  f_LineCreator(FieldParameters _widths, std::string _description, UNITS _unit, int _moleculeCount, 
                 std::vector<std::string> _moleculeNames,
                 std::vector<int> _perMoleculeCount, 
                 std::vector<Molecule> _moleculeList,
                 std::vector<Potential> _potentialList) {
    widths = _widths;
    description = _description;
    unit = _unit;
    moleculeNames = _moleculeNames;
    moleculeCount = _moleculeCount;
    perMoleculeCount = _perMoleculeCount;
    moleculeList = _moleculeList;
    potentialList = _potentialList;
  };
  
  auto formatter(int size, std::string var) -> std::string;

  auto CreateLines(MoleculeConstructor& MolCon, std::vector<std::string>& potentialPairs) -> std::vector<std::string>;

  auto GetDescription() -> std::string;

  auto GetUnit() -> std::vector<std::string>;

  auto GetMoleculeCount() -> std::vector<std::string>;  

  auto GetMoleculeNames() -> std::vector<std::string>;  

  auto GetPerMoleculeCount() -> std::vector<std::string>;

  auto GetMoleculeList(MoleculeConstructor& MolCon) -> std::vector<std::string>;

  auto GetVDWS(std::vector<std::string> potentialPairs) -> std::vector<std::string>;

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
  std::vector<Potential> potentialList;
};

#endif
