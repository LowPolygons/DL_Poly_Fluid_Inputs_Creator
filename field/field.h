#ifndef FIELD_MANAGER
#define FIELD_MANAGER

#include "../general/structs/structures.h"

namespace Field {
  auto GetFileLengths() -> FieldParameters;
  
  auto WriteLinesToFile() -> void;
};

#endif
