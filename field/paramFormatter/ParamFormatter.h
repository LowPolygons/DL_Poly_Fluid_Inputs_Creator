#ifndef FIELD_PARAMETER_FORMATTER

#define FIELD_PARAMETER_FORMATTER

#include <unordered_map>
#include <iostream>
#include "../../config/structs/structures.h"


class f_ParamFormatter {
public:
  f_ParamFormatter() = default;
  //This has no defaults, so contrary to 
  auto convertToStructure(std::unordered_map<std::string, std::string> var) -> void;

  auto Description  (std::string var) -> void;
  auto Units        (std::string var) -> void;
  auto Molecules    (std::string var) -> void;
  auto MoleculeNames(std::string var) -> void;

  auto FieldLengths() -> FieldParameters;

private:
  FieldParameters fieldLengths;
};


#endif
