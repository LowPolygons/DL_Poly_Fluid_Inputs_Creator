#ifndef VDW_MANAGER
#define VDW_MANAGER

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <stdlib.h>

#include "../../general/structs/structures.h"

class VdwManager {
public:
  VdwManager(std::vector<std::string> _vdwList) {
    vdwList =  _vdwList;
  }
  //Getter 
  auto UsableVDWs() -> std::vector<Potential>; 

  auto ReadVDWs() -> void;

private:
  std::vector<std::string> vdwList;

  std::vector<Potential> usableVDWs;

  int numVDWs;
};

#endif
