#include <vector>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <stdlib.h>

#include "../molecule/Molecule.h"
#include "MoleculeConstructor.h"

auto MoleculeConstructor::Molecules() -> std::unordered_map<std::string, Molecule> { return molecules; }

auto ParseCartPosition(std::string line) -> std::array<double, 3> {
  size_t index1 = line.find("=");
  size_t index2 = line.find(",");
  size_t index3 = line.find(",", index2+1); //Sets an index to start at 
  
  return {
    std::stod(line.substr(index1+1, index2-index1-1)),
    std::stod(line.substr(index2+1, index3-index2-1)),
    std::stod(line.substr(index3+1, std::string::npos))
  };
}

auto ParseBond(std::string line) -> std::array<int, 2> {
  int indexOne = std::stoi(line.substr(0,line.find("->")));
  int indexTwo = std::stoi(line.substr(line.find("->")+2,line.length()-1));

  return { indexOne, indexTwo };
}

auto MoleculeConstructor::FormatAtomDescription(std::string line) -> void {
  //There should be 5 commas, separating each value
  size_t index1 = line.find("[ATOM],");
  size_t index2 = line.find(",", index1+7);
  size_t index3 = line.find(",", index2+1);
  size_t index4 = line.find(",", index3+1);
  size_t index5 = line.find(",", index4+1);

  Atom curr;

  curr.name = line.substr(index1+7, index2-index1-7);
  curr.mass = std::stod(line.substr(index2+1, index3-index2-1));
  curr.charge = std::stod(line.substr(index3+1, index4-index3-1));
  curr.nrept = std::stod(line.substr(index4+1, index5-index4-1));
  curr.ifrz = std::stod(line.substr(index5+1, std::string::npos-index5-1));

  atoms[curr.name] = curr;
}

auto MoleculeConstructor::FormatLinesToValues(std::vector<std::string> linesToFilter, std::string moleculeName) -> void {
  //if a line contains a :, it represents
  //Look for the number of atoms at the top
 
  //Make sure that some number of lines were found
  if (linesToFilter.size() < 0) {
    std::cout << "[Error] No expected lines found in the file for " << moleculeName << std::endl;
    exit(EXIT_FAILURE);
  }
  //Check the first line contains the number of lines
  if (linesToFilter[0].find("Atoms=") == std::string::npos) {
    std::cout << "[Error] No specification of the number of atoms found on first line for " << moleculeName << ". Try 'Atoms=[your number here]'" << std::endl;
    exit(EXIT_FAILURE);
  }

  int numAtoms = std::stoi(
    linesToFilter[0].substr(6, linesToFilter[0].length()-1)
  );

  //Initialised so that you can directly index it
  std::vector<std::array<double, 3>> positions(numAtoms, {0.0, 0.0, 0.0});
  std::vector<std::string> atomTypes(numAtoms, "");
  std::vector<std::array<int, 2>> bonds;

  for (std::string currLine : linesToFilter) {
    //If it contains a : it is a position, first index of the string is the index 
    //If it contains a -> it is a bond description
    //If it contains [ATOM], it describes an atom 
    if ( currLine.find(":") != std::string::npos ) {
      int index = std::stoi(currLine.substr(0, currLine.find(":")));
      atomTypes[index] = currLine.substr(currLine.find(":")+1, currLine.find("=")-currLine.find(":")-1);
      positions[index] = ParseCartPosition(currLine);
    } 
    else if ( currLine.find("->") != std::string::npos ) {
      bonds.push_back(ParseBond(currLine));
    }
    else if ( currLine.find("[ATOM],") != std::string::npos ) {
      FormatAtomDescription(currLine); 
    }
  }

  //Create the molecule and add to the classes map
  molecules.insert({moleculeName, Molecule(positions, atomTypes, bonds)});
}

auto MoleculeConstructor::GenerateMolecules() -> void {
  //Open moleculeFiles
  for (std::string moleculeName : moleculeFiles) {

    std::ifstream currentMolecule("parameters/molecules/"+moleculeName+".txt");

    if (!currentMolecule) {
      std::cout << "[Error] There has been an issue attempting to locate the molecule file for " << moleculeName << std::endl;
      exit(EXIT_FAILURE);
    }

    std::vector<std::string> lines;
    std::string currLine;

    //Filter through all the lines, if it contains a // at the start, ignore
    while ( std::getline(currentMolecule, currLine) ) {
      size_t linelength = currLine.length();
      
      //this will prevent blank space being included
      if (linelength > 2) {
        std::string commentChecker = currLine.substr(0, 2);

        if (commentChecker != "//") {
          lines.push_back(currLine);
        }
      }
    }

    //Go through the filtered lines and sort between bonds and positions
    FormatLinesToValues(lines, moleculeName);
  }
}


