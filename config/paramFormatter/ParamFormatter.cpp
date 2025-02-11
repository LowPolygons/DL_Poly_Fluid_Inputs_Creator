#include <iostream>
#include <array>
#include <fstream>
#include <stdlib.h>

#include <unordered_map>
#include <string>

#include "../../general/structs/structures.h"
#include "ParamFormatter.h"

auto c_ParamFormatter::LengthsInFile() -> ConfigParameters { return lengthsInFile; }

//UNSAFE METHODS: DO NOT CHECK IF THEY CAN BE CASTED BEFORE CASTING

auto c_ParamFormatter::convertDescription(std::string vars) -> void {
  lengthsInFile.description = std::stoi(vars);
}

auto c_ParamFormatter::convertLevcfg(std::string vars) -> void {
  lengthsInFile.levcfg = std::stoi(vars);
}

auto c_ParamFormatter::convertImcon(std::string vars) -> void {
  lengthsInFile.imcon = std::stoi(vars);
}

auto c_ParamFormatter::convertNumParticles(std::string vars) -> void {
  lengthsInFile.numparticles = std::stoi(vars);
}

auto c_ParamFormatter::convertXYZ(std::array<std::string, 9> vars) -> void {
  lengthsInFile.vec1 = { std::stoi(vars[0]), std::stoi(vars[1]), std::stoi(vars[2]) };
  lengthsInFile.vec2 = { std::stoi(vars[3]), std::stoi(vars[4]), std::stoi(vars[5]) };
  lengthsInFile.vec3 = { std::stoi(vars[6]), std::stoi(vars[7]), std::stoi(vars[8]) };
}

auto c_ParamFormatter::convertParticleType(std::string vars) -> void {
  lengthsInFile.particleType = std::stoi(vars);
}
auto c_ParamFormatter::convertIndex(std::string var) -> void {
  lengthsInFile.index = std::stoi(var);
}

auto c_ParamFormatter::convertToStructure(std::unordered_map<std::string, std::string> var) -> void {
  //Just one at a time
  convertDescription(var["description"]);
  convertLevcfg(var["levcfg"]);
  convertImcon(var["imcon"]);
  convertNumParticles(var["numparticles"]);

  std::array<std::string, 9> input = {{
    { var["v1x"] },
    { var["v1y"] },
    { var["v1z"] },

    { var["v2x"] },
    { var["v2y"] },
    { var["v2z"] },

    { var["v3x"] },
    { var["v3y"] },
    { var["v3z"] }
  }};

  convertXYZ(input);
  convertParticleType(var["particleType"]);
  convertIndex(var["index"]);
}
