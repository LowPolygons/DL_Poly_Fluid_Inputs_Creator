
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "../../general/structs/structures.h"
#include "../../general/molecule/Molecule.h"
#include "../../general/moleculeConstructor/MoleculeConstructor.h"

#include "LineCreator.h"
//Vector so they are all standardised
auto f_LineCreator::formatter(int size, std::string var) -> std::string {
  int stringSize = var.size();

  if (stringSize < size) {
    for (int _ = 0; _ < (size-stringSize); _++){ 
      var = var + " ";
    }
  } else if (stringSize > size) {
    var = var.substr(0, size-1); 
  }

  return var;
}

auto f_LineCreator::GetDescription() -> std::string { 
  return description.substr(0, std::min(description.size(), static_cast<size_t>(widths.description))); 
};

auto f_LineCreator::GetUnit() -> std::string {
  return "UNITS " + formatter(widths.units, UNITS_STRINGS.at(unit)); 
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

//This is the function to be called for anything relating to molecules outside of the calss itself
auto f_LineCreator::GetMoleculeList(MoleculeConstructor& MolCon) -> std::vector<std::string> {
  std::vector<std::string> ret;
  int index = 0;
  for (Molecule currentMol : moleculeList) {
    //The index of the current molecule stored in 'index'
    
    //Get the name first
    ret.push_back(GetMoleculeNames()[index]);

    //Get the num of mols 
    ret.push_back("NUMMOLS " + GetPerMoleculeCount()[index]);

    //Get the ATOMS
    auto atoms = currentMol.GetTypes(); //the array of atoms
        auto atomList = MolCon.Atoms();
    
    //The number of atoms
    ret.push_back("ATOMS " + formatter(7, std::to_string(atoms.size())));

    for (std::string curr_atom : atoms) {
      Atom listOfParts = atomList[curr_atom];

      ret.push_back(
        formatter( 8, listOfParts.name) +
        formatter(10, std::to_string(listOfParts.mass))   +
        formatter(10, std::to_string(listOfParts.charge)) +
        formatter( 5, std::to_string(listOfParts.nrept))   +
        formatter( 5, std::to_string(listOfParts.ifrz))
      );
    }
    
    ret.push_back("FINISH");
    index++;
  } 

  return ret;
}

auto f_LineCreator::GetVDWS(std::vector<std::string> potentialPairs) -> std::vector<std::string> {
  std::vector<std::string> ret;
  
  //VDW count
  ret.push_back("VDW " + formatter(6, std::to_string(potentialList.size())));

  int index = 0;

  for ( Potential curr : potentialList) {
    std::string currentLine;
    //split the name by the underscore
    std::string at1 = potentialPairs[0].substr(0, potentialPairs[0].find("_"));
    std::string at2 = potentialPairs[0].substr(potentialPairs[0].find("_")+1, std::string::npos);

    //The atom pair
    currentLine = currentLine + formatter(6, at1) + formatter(6, at2);

    //The potential 
    currentLine = currentLine + formatter(8, curr.name);

    //Loop through the numbers
    for (int i = 0; i < curr.numVariables; i++) {
      currentLine = currentLine + formatter(12, std::to_string(curr.parameters[i]));
    }

    ret.push_back(currentLine);

    index++;
  }

  ret.push_back("CLOSE");

  return ret;
}

//TODO: REWORK FUNCTIONS THAT RETURN VECTORS WHEN THEY DONT NEED TO
auto f_LineCreator::CreateLines(MoleculeConstructor& MolCon, std::vector<std::string>& potentialPairs) -> std::vector<std::string> {
  std::vector<std::string> allLines;
  //Description
  allLines.push_back(GetDescription());

  //Units 
  allLines.push_back(GetUnit());

  //Molecules 
  allLines.push_back(GetMoleculeCount()[0]);

  //Molecule Lines
  for (std::string curr : GetMoleculeList(MolCon)) {
    allLines.push_back(curr);
  }

  //VDWs
  for (std::string curr : GetVDWS(potentialPairs)) {
    allLines.push_back(curr);
  } 

  return allLines;
}
