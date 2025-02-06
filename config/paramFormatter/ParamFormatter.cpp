#include <iostream>
#include <array>
#include <fstream>
#include <stdlib.h>

#include <unordered_map>
#include <string>

#include "../structs/structures.h"
#include "ParamFormatter.h"

auto c_ParamFormatter::LengthsInFile() -> ConfigParameters { return lengthsInFile; }
auto c_ParamFormatter::DefaultValues() -> ConfigDefaults   { return defaultValues; }

//UNSAFE METHODS: DO NOT CHECK IF THEY CAN BE CASTED BEFORE CASTING

auto c_ParamFormatter::convertDescription(std::array<std::string, 2> vars) -> void {
  lengthsInFile.description = std::stoi(vars[0]);
  defaultValues.description = vars[1];
}

auto c_ParamFormatter::convertLevcfg(std::array<std::string, 2> vars) -> void {
  lengthsInFile.levcfg = std::stoi(vars[0]);
  defaultValues.levcfg = static_cast<LEVCFG>(
    std::stoi(vars[1])
  );
}

auto c_ParamFormatter::convertImcon(std::array<std::string, 2> vars) -> void {
  lengthsInFile.imcon = std::stoi(vars[0]);
  defaultValues.imcon = static_cast<IMCON>(
    std::stoi(vars[1])
  );}

auto c_ParamFormatter::convertNumParticles(std::array<std::string, 2> vars) -> void {
  lengthsInFile.numparticles = std::stoi(vars[0]);
  defaultValues.numparticles = std::stoi(vars[1]);
}

auto c_ParamFormatter::convertXYZ(std::array<std::array<std::string, 2>, 9> vars) -> void {
  lengthsInFile.vec1 = { std::stoi(vars[0][0]), std::stoi(vars[1][0]), std::stoi(vars[2][0]) };
  lengthsInFile.vec2 = { std::stoi(vars[3][0]), std::stoi(vars[4][0]), std::stoi(vars[5][0]) };
  lengthsInFile.vec3 = { std::stoi(vars[6][0]), std::stoi(vars[7][0]), std::stoi(vars[8][0]) };
  
  defaultValues.vec1 = { std::stod(vars[0][1]), std::stod(vars[1][1]), std::stod(vars[2][1]) };
  defaultValues.vec2 = { std::stod(vars[3][1]), std::stod(vars[4][1]), std::stod(vars[5][1]) };
  defaultValues.vec3 = { std::stod(vars[6][1]), std::stod(vars[7][1]), std::stod(vars[8][1]) };
}

auto c_ParamFormatter::convertParticleType(std::array<std::string, 2> vars) -> void {
  lengthsInFile.particleType = std::stoi(vars[0]);
  defaultValues.particleType = vars[1];
}
auto c_ParamFormatter::convertIndex(std::string var) -> void {
  lengthsInFile.index = std::stoi(var);
}

auto c_ParamFormatter::convertSeed(std::array<std::string,3 > var) -> void {
  lengthsInFile.pos_rand_seed = std::stoi(var[0]);
  lengthsInFile.vel_rand_seed = std::stoi(var[1]);
  lengthsInFile.fce_rand_seed = std::stoi(var[2]);
}

auto c_ParamFormatter::convertToStructure(std::array<std::unordered_map<std::string, std::string>, 2> var) -> void {
  //Just one at a time
  convertDescription({var[0]["description"], var[1]["description"]});
  convertLevcfg({var[0]["levcfg"], var[1]["levcfg"]});
  convertImcon({var[0]["imcon"], var[1]["imcon"]});
  convertNumParticles({var[0]["numparticles"], var[1]["numparticles"]});

  std::array<std::array<std::string, 2>, 9> input = {{
    { var[0]["v1x"], var[1]["v1x"] },
    { var[0]["v1y"], var[1]["v1y"] },
    { var[0]["v1z"], var[1]["v1z"] },

    { var[0]["v2x"], var[1]["v2x"] },
    { var[0]["v2y"], var[1]["v2y"] },
    { var[0]["v2z"], var[1]["v2z"] },

    { var[0]["v3x"], var[1]["v3x"] },
    { var[0]["v3y"], var[1]["v3y"] },
    { var[0]["v3z"], var[1]["v3z"] }
  }};

  convertXYZ(input);
  convertParticleType({var[0]["particleType"], var[1]["particleType"]});
  convertIndex(var[0]["index"]);
}
