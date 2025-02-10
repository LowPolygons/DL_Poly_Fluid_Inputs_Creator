#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <stdlib.h>

#include "../../general/structs/structures.h"
#include "VdwManager.h"

auto VdwManager::UsableVDWs() -> std::vector<Potential> { return usableVDWs; }

auto VdwManager::ReadVDWs() -> void {
  //For each potential, create an ifstream
  for ( std::string currentPair : vdwList) {
    std::ifstream current("parameters/vdws/"+currentPair+".txt");

    if (!current) {
      std::cout << "[ERROR] There was an issue attempting to locate the VDW file for " << currentPair << std::endl;
      exit(EXIT_FAILURE);
    }
  
    std::string currentLine;
  
    std::string _name;
    int _numVariables;
    std::vector<double> _parameters;

    while ( std::getline(current, currentLine) ) {
      //If it is not a comment
      if (currentLine.substr(0, 2) != "//") {
        
        if (currentLine.find("Name=") != std::string::npos) {
          _name = currentLine.substr(currentLine.find("Name=")+5, std::string::npos);
        }
        else if (currentLine.find("Count=") != std::string::npos) {
          _numVariables = std::stoi(currentLine.substr(currentLine.find("Count=")+6, std::string::npos));
        }
        else {
          if (currentLine.length() > 0) {
            _parameters.push_back(std::stod(currentLine));
          }
        }
      }
    }

    Potential currentP;

    currentP.name = _name;
    currentP.numVariables = _numVariables;
    currentP.parameters = _parameters;

    usableVDWs.push_back(currentP);
  }
}
