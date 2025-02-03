#ifndef PARAMETER_READER
#define PARAMETER_READER

#include "../structs/structures.h"
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

  //Getters
  auto LengthsInFile() -> ConfigParameters;
  auto DefaultValues() -> ConfigDefaults;

  //Overseeing function to convert file inputs into the structs
  auto readLocalConfig() -> void;
  //Returns an array of maps which describe the lengths and defaults of each necessary key needed for the config
  auto splitLengthsAndDefaults(std::unordered_map<std::string, std::string> vals) -> std::array<std::unordered_map<std::string, std::string>, 2>;
  //Converts the lengths and defaults into correct types and stores them in the structures
  auto convertToStructure(std::array<std::unordered_map<std::string, std::string>, 2> var) -> void;

  //Given the sets of keys and values read from the localConfig file, these 
  //methods will convert their corresponding value to the correct data type expected by the CONFIG struct
  auto convertDescription (std::array<std::string, 2> vars) -> void;
  auto convertLevcfg      (std::array<std::string, 2> vars) -> void;
  auto convertImcon       (std::array<std::string, 2> vars) -> void;
  auto convertNumParticles(std::array<std::string, 2> vars) -> void;
  auto convertParticleType(std::array<std::string, 2> vars) -> void;

  auto convertXYZ         (std::array<std::array<std::string, 2>, 9> vars) -> void;
  auto convertIndex       (std::string var) -> void;
  auto convertSeed        (std::array<std::string,3 > var) -> void;

private:
  std::string filePath;

  ConfigParameters lengthsInFile;
  ConfigDefaults defaultValues;
};


#endif
