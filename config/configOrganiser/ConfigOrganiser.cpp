#include <iostream>
#include <vector>
#include <array>

#include "../../general/structs/structures.h"
#include "../../general/writer/Writer.h"
#include "../lineCreator/LineCreator.h"
#include "../XYZGenerator/xyzGenerator.h"

#include "ConfigOrganiser.h"

//Getters
auto ConfigOrganiser::WidthsInFile() -> ConfigParameters { return widthsInFile; }
auto ConfigOrganiser::Description()  -> std::string      { return description;  }
auto ConfigOrganiser::Levcfg()       -> LEVCFG           { return levcfg;       } 
auto ConfigOrganiser::Imcon()        -> IMCON            { return imcon;        }
auto ConfigOrganiser::NumParticles() -> int              { return numParticles; }
auto ConfigOrganiser::Vectors()      -> std::array<std::array<double, 3>, 3> { return { vec1, vec2, vec3 }; }
auto ConfigOrganiser::Types()        -> std::vector<std::string>             { return types;      }
auto ConfigOrganiser::Positions()    -> std::vector<std::array<double, 3>>   { return positions;  }
auto ConfigOrganiser::Velocities()   -> std::vector<std::array<double, 3>>   { return velocities; }
auto ConfigOrganiser::Forces()       -> std::vector<std::array<double, 3>>   { return forces;     }
auto ConfigOrganiser::MoleculeCounts() -> std::vector<int>                   { return moleculeCounts; }

//Setters
void ConfigOrganiser::set_widthsInFile(ConfigParameters inp) { widthsInFile = inp; }
void ConfigOrganiser::set_description(std::string inp)       { description = inp;  }
void ConfigOrganiser::set_levcfg(LEVCFG inp)                 { levcfg = inp;       }
void ConfigOrganiser::set_imcon(IMCON inp)                   { imcon = inp;        }
void ConfigOrganiser::set_numParticles(int inp)              { numParticles = inp; }
void ConfigOrganiser::set_vectors(
  std::array<double, 3> inp1,
  std::array<double, 3> inp2, 
  std::array<double, 3> inp3) { vec1 = inp1; vec2 = inp2; vec3 = inp3; }
void ConfigOrganiser::set_positions(std::vector<std::array<double, 3>> inp)    { positions = inp;      }
void ConfigOrganiser::set_velocities(std::vector<std::array<double, 3>> inp)   { velocities = inp;     }
void ConfigOrganiser::set_forces(std::vector<std::array<double, 3>> inp)       { forces = inp;         }
void ConfigOrganiser::set_types(std::vector<std::string> inp)                  { types = inp;          }
void ConfigOrganiser::set_moleculeCounts(std::vector<int> inp)                 { moleculeCounts = inp; }
