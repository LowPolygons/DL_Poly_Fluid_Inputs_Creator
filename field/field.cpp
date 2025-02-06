#include <iostream>
#include <unordered_map>

#include "Field.h"

#include "paramFormatter/ParamFormatter.h"
#include "../general/structs/structures.h"
#include "../general/parameterReader/ParameterReader.h"

auto Field::GetFileLengths(/* Pass by Ref the Field Organiser */) -> void {
  ParameterReader reader("parameters/fieldParameters.txt");

  auto values = reader.readFile();

  f_ParamFormatter formatter;

  formatter.convertToStructure(values);

  FieldParameters fP = formatter.FieldLengths();

  std::cout << fP.description << std::endl;
  std::cout << fP.units << std::endl;
  std::cout << fP.molecules << std::endl;
  std::cout << fP.moleculeNames << std::endl;
}
