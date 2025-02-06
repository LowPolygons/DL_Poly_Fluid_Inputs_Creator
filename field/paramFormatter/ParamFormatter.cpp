#include "ParamFormatter.h"

#include <unordered_map>
#include <iostream>
#include "../../config/structs/structures.h"

auto f_ParamFormatter::FieldLengths() -> FieldParameters { return fieldLengths; }

auto f_ParamFormatter::Description(std::string var) -> void {
  fieldLengths.description = std::stoi(var);
}

auto f_ParamFormatter::Units(std::string var) -> void {
  fieldLengths.units = std::stoi(var);
}

auto f_ParamFormatter::Molecules(std::string var) -> void {
  fieldLengths.molecules = std::stoi(var);
}

auto f_ParamFormatter::MoleculeNames(std::string var) -> void {
  fieldLengths.moleculeNames = std::stoi(var);
}

auto f_ParamFormatter::convertToStructure(std::unordered_map<std::string, std::string> var) -> void {
  Description(var["description"]);
  Units(var["units"]);
  Molecules(var["molecules"]);
  MoleculeNames(var["moleculeNames"]);
}
