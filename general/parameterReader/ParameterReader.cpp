#include <iostream>
#include <array>
#include <fstream>
#include <stdlib.h>

#include <unordered_map>
#include <string>

#include "../../config/structs/structures.h"
#include "ParameterReader.h"

ParameterReader::ParameterReader(std::string path) {
  filePath = path;
}

//Given the map of values, you split apart the character lengths and default values into two separate maps
//This will also filter out unwanted key-value pairs
auto ParameterReader::splitLengthsAndDefaults(std::unordered_map<std::string, std::string> vals, std::vector<std::string> keys, std::string noDefaults) -> 
  std::array<std::unordered_map<std::string, std::string>, 2> {

  //This will just be the input map split into two separate ones
  //0th index is lengths, 1st index is defaults
  std::array<std::unordered_map<std::string, std::string>, 2> lengthsAndDefaults;

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

auto ParameterReader::readLocalConfig() -> std::unordered_map<std::string, std::string> {  

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

  return keyAndVals;
}

