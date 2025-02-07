
#include <iostream>
#include <vector>
#include <algorithm>
#include "../../general/structs/structures.h"
#include "../../general/molecule/Molecule.h"

#include "LineCreator.h"
//Vector so they are all standardised
auto f_LineCreator::formatter(int size, std::string var) -> std::string {
  int stringSize = var.size();

  if (stringSize < size) {
    for (int _ = 0; _ < (size-stringSize); _++){ 
      var = " " + var;
    }
  } else if (stringSize > size) {
    var = var.substr(0, size-1); 
  }

  return var;
}

auto f_LineCreator::GetDescription() -> std::vector<std::string> { return {formatter(widths.description, description)}; };

auto f_LineCreator::GetUnit() -> std::vector<std::string> {
  return {"UNITS " + formatter(widths.units, UNITS_STRINGS.at(unit))}; 
}

auto f_LineCreator::GetMoleculeCount() -> std::vector<std::string> {
  return {"MOLECULES " + formatter(widths.molecules, std::to_string(moleculeCount))};
}

auto f_LineCreator::GetMoleculeNames() -> std::vector<std::string> {
  std::transform(moleculeNames.begin(), moleculeNames.end(), moleculeNames.begin(), 
      [this](std::string element) {
        return formatter(widths.moleculeNames, element); 
      }
  );
  return moleculeNames;
}

auto f_LineCreator::GetPerMoleculeCount() -> std::vector<std::string> {
  std::vector<std::string> ret(perMoleculeCount.size());
  
  std::transform(perMoleculeCount.begin(), perMoleculeCount.end(), ret.begin(), 
      [this](int element) {
        return formatter(widths.molecules, std::to_string(element));
      }
  );

  return ret;
}

auto f_LineCreator::GetMoleculeList() -> std::vector<std::string> {
  std::vector<std::string> ret(moleculeList.size());

  std::transform(moleculeList.begin(), moleculeList.end(), ret.begin(), 
      [this](Molecule element) { //capturing `this` allows access to 'non-static members'
        return "TEST TEST TEST TEST"; 
      }
  );

  return ret;
}

