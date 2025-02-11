#ifndef PARAMETER_FORMATTER_CONFIG
#define PARAMETER_FORMATTER_CONFIG

#include "../../general/structs/structures.h"
#include <iostream>
#include <array>
#include <fstream>
#include <unordered_map>
#include <vector>

//-The class will read a locally stored config file and determine some default 
// values as well as determining the lengths of each var in the final file
class c_ParamFormatter {
public:
  //Constructor
  c_ParamFormatter() = default;

  //Getters
  auto LengthsInFile() -> ConfigParameters;
  //Converts the lengths and defaults into correct types and stores them in the structures
  auto convertToStructure(std::unordered_map<std::string, std::string> var) -> void;

  //Given the sets of keys and values read from the localConfig file, these 
  //methods will convert their corresponding value to the correct data type expected by the CONFIG struct
  auto convertDescription (std::string vars) -> void;
  auto convertLevcfg      (std::string vars) -> void;
  auto convertImcon       (std::string vars) -> void;
  auto convertNumParticles(std::string vars) -> void;
  auto convertParticleType(std::string vars) -> void;

  auto convertXYZ         (std::array<std::string, 9> vars) -> void;
  auto convertIndex       (std::string var) -> void;

private:
  ConfigParameters lengthsInFile;
};


#endif
