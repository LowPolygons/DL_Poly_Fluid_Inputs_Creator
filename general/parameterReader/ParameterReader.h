#ifndef PARAMETER_READER
#define PARAMETER_READER


#include <iostream>
#include <array>
#include <fstream>
#include <unordered_map>
#include <vector>

//-The class will read a locally stored config file and determine some default 
// values as well as determining the lengths of each var in the final file
class ParameterReader {
public:
  //Constructor
  ParameterReader(std::string path);

  //Overseeing function to convert file inputs into the structs
  auto readFile() -> std::unordered_map<std::string, std::string>;
  //Returns an array of maps which describe the lengths and defaults of each necessary key needed for the config
  auto splitLengths(std::unordered_map<std::string, std::string> vals, std::vector<std::string> keys, std::string noDefaults) -> std::unordered_map<std::string, std::string>;

private:
  std::string filePath;
};


#endif
