#ifndef FIELD_MANAGER
#define FIELD_MANAGER

#include "../general/structs/structures.h"
#include "../general/moleculeConstructor/MoleculeConstructor.h"
#include "../general/writer/Writer.h"

namespace Field {
  auto GetFileLengths() -> FieldParameters;
  
  auto WriteLinesToFile(FieldParameters& fieldParams, MoleculeConstructor& MolCon, Writer& writer) -> void;
};

#endif
