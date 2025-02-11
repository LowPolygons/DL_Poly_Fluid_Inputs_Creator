#include <iostream>
#include <unordered_map>

#include "Field.h"

#include "paramFormatter/ParamFormatter.h"
#include "../general/structs/structures.h"
#include "../general/parameterReader/ParameterReader.h"
#include "../parameters/Inputs.h"
#include "../general/moleculeConstructor/MoleculeConstructor.h"
#include "../general/writer/Writer.h"

auto Field::GetFileLengths(/* Pass by Ref the Field Organiser */) -> FieldParameters{
  ParameterReader reader("parameters/fieldParameters.txt");

  auto values = reader.readFile();

  std::vector<std::string> keys = {
    "description",
    "units",
    "molecules",
    "moleculeNames",
    "moleculeDoubles",
    "moleculeInts",
    "potentials",
    "vdwParticle",
    "vdwParams"
  };

  auto validatedValues = reader.splitLengths(values, keys, "");
  f_ParamFormatter formatter;

  formatter.convertToStructure(validatedValues);

  FieldParameters fP = formatter.FieldLengths();

  return fP;
}

auto Field::WriteLinesToFile(FieldParameters& fieldParams, MoleculeConstructor& MolCon, Writer& writer) -> void {
   
}
