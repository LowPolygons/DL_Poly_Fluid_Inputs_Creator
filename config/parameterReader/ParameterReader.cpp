#include <iostream>
#include <array>
#include <fstream>
#include <stdlib.h>

#include <unordered_map>
#include <string>

#include "../structs/structures.h"
#include "ParameterReader.h"

ParameterReader::ParameterReader(std::string path) {
  filePath = path;
}

auto ParameterReader::LengthsInFile() -> ConfigParameters { return lengthsInFile; }
auto ParameterReader::DefaultValues() -> ConfigDefaults   { return defaultValues; }

//Given the map of values, you split apart the character lengths and default values into two separate maps
//This will also filter out unwanted key-value pairs
auto ParameterReader::splitLengthsAndDefaults(std::unordered_map<std::string, std::string> vals) -> 
  std::array<std::unordered_map<std::string, std::string>, 2> {

  //This will just be the input map split into two separate ones
  //0th index is lengths, 1st index is defaults
  std::array<std::unordered_map<std::string, std::string>, 2> lengthsAndDefaults;
  
  //The desired keys
  std::vector<std::string> keys = {
    "description",
    "levcfg",
    "imcon",
    "numparticles",
    "v1x",
    "v1y",
    "v1z",
    "v2x",
    "v2y",
    "v2z",
    "v3x",
    "v3y",
    "v3z",
    "particleType",
    "index",
  };

  //If a value doesn't have a default add the key to this string surrounded by "- [var] -"
  std::string noDefaults = "-index-rand_seed-";

  for (std::string key : keys) {
    auto exists = vals.find(key);

    //Check if the key exists
    if (exists == vals.end()) { //vals.end returns an iterator which points to one after the last item, basically it says it doesn't exist
      std::cout << "[Error] Missing expected value: " << key << ", terminating program" << std::endl;
      exit(EXIT_FAILURE);
    }

    std::string currValue = vals[key];
    
    //Check if a default value exists, if applicable
    if (noDefaults.find(key) == std::string::npos) {
      //If it wasnt in noDefaults, expecting a :
      size_t colon = currValue.find(":");

      //If there isn't a colon, or the colon is the last item in the line, it is incorrect
      if (colon == std::string::npos || colon == currValue.length() - 1) {
        std::cout << "[Error] Missing Default Value for key: " << key << ", include by putting a colon and a default value with no spaces onto the end of the line" << std::endl;
        exit(EXIT_FAILURE);
      }

      //If there is a colon and there is a default value, separate them and store in
      lengthsAndDefaults[0][key] = currValue.substr(0, colon);
      lengthsAndDefaults[1][key] = currValue.substr(colon+1, currValue.length()-1);
    } else {
      lengthsAndDefaults[0][key] = currValue;
    }
  }

  return lengthsAndDefaults; 
}

//UNSAFE METHODS: DO NOT CHECK IF THEY CAN BE CASTED BEFORE CASTING

auto ParameterReader::convertDescription(std::array<std::string, 2> vars) -> void {
  lengthsInFile.description = std::stoi(vars[0]);
  defaultValues.description = vars[1];
}

auto ParameterReader::convertLevcfg(std::array<std::string, 2> vars) -> void {
  lengthsInFile.levcfg = std::stoi(vars[0]);
  defaultValues.levcfg = static_cast<LEVCFG>(
    std::stoi(vars[1])
  );
}

auto ParameterReader::ParameterReader::convertImcon(std::array<std::string, 2> vars) -> void {
  lengthsInFile.imcon = std::stoi(vars[0]);
  defaultValues.imcon = static_cast<IMCON>(
    std::stoi(vars[1])
  );}

auto ParameterReader::convertNumParticles(std::array<std::string, 2> vars) -> void {
  lengthsInFile.numparticles = std::stoi(vars[0]);
  defaultValues.numparticles = std::stoi(vars[1]);
}

auto ParameterReader::convertXYZ(std::array<std::array<std::string, 2>, 9> vars) -> void {
  lengthsInFile.vec1 = { std::stoi(vars[0][0]), std::stoi(vars[1][0]), std::stoi(vars[2][0]) };
  lengthsInFile.vec2 = { std::stoi(vars[3][0]), std::stoi(vars[4][0]), std::stoi(vars[5][0]) };
  lengthsInFile.vec3 = { std::stoi(vars[6][0]), std::stoi(vars[7][0]), std::stoi(vars[8][0]) };
  
  defaultValues.vec1 = { std::stod(vars[0][1]), std::stod(vars[1][1]), std::stod(vars[2][1]) };
  defaultValues.vec2 = { std::stod(vars[3][1]), std::stod(vars[4][1]), std::stod(vars[5][1]) };
  defaultValues.vec3 = { std::stod(vars[6][1]), std::stod(vars[7][1]), std::stod(vars[8][1]) };
}

auto ParameterReader::convertParticleType(std::array<std::string, 2> vars) -> void {
  lengthsInFile.particleType = std::stoi(vars[0]);
  defaultValues.particleType = vars[1];
}
auto ParameterReader::convertIndex(std::string var) -> void {
  lengthsInFile.index = std::stoi(var);
}

auto ParameterReader::convertSeed(std::array<std::string,3 > var) -> void {
  lengthsInFile.pos_rand_seed = std::stoi(var[0]);
  lengthsInFile.vel_rand_seed = std::stoi(var[1]);
  lengthsInFile.fce_rand_seed = std::stoi(var[2]);
}

auto ParameterReader::convertToStructure(std::array<std::unordered_map<std::string, std::string>, 2> var) -> void {
  //Just one at a time
  convertDescription({var[0]["description"], var[1]["description"]});
  convertLevcfg({var[0]["levcfg"], var[1]["levcfg"]});
  convertImcon({var[0]["imcon"], var[1]["imcon"]});
  convertNumParticles({var[0]["numparticles"], var[1]["numparticles"]});

  std::array<std::array<std::string, 2>, 9> input = {{
    { var[0]["v1x"], var[1]["v1x"] },
    { var[0]["v1y"], var[1]["v1y"] },
    { var[0]["v1z"], var[1]["v1z"] },

    { var[0]["v2x"], var[1]["v2x"] },
    { var[0]["v2y"], var[1]["v2y"] },
    { var[0]["v2z"], var[1]["v2z"] },

    { var[0]["v3x"], var[1]["v3x"] },
    { var[0]["v3y"], var[1]["v3y"] },
    { var[0]["v3z"], var[1]["v3z"] }
  }};

  convertXYZ(input);
  convertParticleType({var[0]["particleType"], var[1]["particleType"]});
  convertIndex(var[0]["index"]);
}

auto ParameterReader::readLocalConfig() -> void {  

  std::ifstream file(filePath);

  //Check the file was loaded into the stream properly
  if (!(file)) {
    std::cout << "[Error] The ifstream failed to create a file from the given filepath: " << filePath << std::endl;
    exit(EXIT_FAILURE);
  }

  //The first line of the config file is to be ignored. Skip that here
  std::string topLine;

  if ( !std::getline(file, topLine)) {
    std::cout << "[Error] An issue has occured with attempting to read the file. Is the file empty?" << std::endl;
    exit(EXIT_FAILURE);
  } else {
    //Check if it contains an equals. if it does, play it safe and reset
    if (topLine.find("=") != std::string::npos) {
      //If it does, reset the position of the stream to be at the beginning
      
      //Clears the state
      file.clear();
      //Back to beginning
      file.seekg(0);
    }
  }

  std::unordered_map<std::string, std::string> keyAndVals;

  //While it hasnt reached the end of the file  
  while ( std::getline(file, topLine) ) {
    size_t indexOfEquals = topLine.find("=");
    std::string commentChecker = topLine.substr(0, 2);
    //Add it to the unordered map for later parsing. This way, order doesn't matter in the file
    if (indexOfEquals != std::string::npos && commentChecker != "//"){// npos if it doesn't find it
      keyAndVals[topLine.substr(0, indexOfEquals)] = topLine.substr(indexOfEquals+1, topLine.length()-1);
    }
  }

  file.close();

  //lengths and defaults
  auto lsAndDs = splitLengthsAndDefaults(keyAndVals);
  ParameterReader::convertToStructure(lsAndDs);
}

