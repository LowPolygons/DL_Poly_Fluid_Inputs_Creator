#include <iostream>
#include <array>
#include <vector>
#include <memory> //shared_ptr
#include <string> //to_string

#include "../../general/structs/structures.h"
#include "LineCreator.h"
#include "../../general/writer/Writer.h"

//TODO: IMPLEMENT DEFAULTS IN THE EVENT OF NO DATA

auto LineCreator::formatter(int size, std::string var) -> std::string {
  int stringSize = var.size();

  if (stringSize < size) {
    for (int _ = 0; _ < (size-stringSize); _++){ 
      var = " " + var;
    }
  } else if (stringSize > size) {
    var = var.substr(0, size-1); 
  }

  return var;
}

auto LineCreator::Description() -> std::string {
  //This one should only truncate, therefore handle separately
  if (description.size() > widths.description) {
    return description.substr(0, widths.description-1); 
  }
  return description;
}

auto LineCreator::Levcfg() -> std::string {
  std::string ret = formatter(widths.levcfg, std::to_string(levcfg));

  return ret;
}

auto LineCreator::Imcon() -> std::string {
  std::string ret = formatter(widths.imcon, std::to_string(imcon));

  return ret;
}

//TODO: switch numparticles to camel case in all code pieces
auto LineCreator::NumParticles() -> std::string {
  std::string ret = formatter(widths.numparticles, std::to_string(numParticles));

  return ret;
}

//TODO: the CONFIG_PARAMETERS contains an x y and z array, either switch to ints for each or have only one array
//      Alternatively, have a constant for numbers in general
//      Lastly, change any reference to x y and z to be more vocally correct: they describe the 3 unit vectors of a cell
auto LineCreator::Axis() -> std::vector<std::string> {
  std::string _x, _y, _z;

  _x = formatter(widths.vec1[0], std::to_string(vec1[0])) 
    + formatter(widths.vec1[1], std::to_string(vec1[1])) + formatter(widths.vec1[2], std::to_string(vec1[2]));

  _y = formatter(widths.vec2[0], std::to_string(vec2[0])) 
    + formatter(widths.vec2[1], std::to_string(vec2[1])) + formatter(widths.vec2[2], std::to_string(vec2[2]));

  _z = formatter(widths.vec3[0], std::to_string(vec3[0])) 
    + formatter(widths.vec3[1], std::to_string(vec3[1])) + formatter(widths.vec3[2], std::to_string(vec3[2]));

  return { _x, _y, _z };
}

//Have the argument be 0 indexed, therefore add 1 to it for the 'index' section
// aka, prioritise array indexing, not config file indexing
auto LineCreator::ParticleAndIndex(int index) -> std::string { 
  std::string ret = formatter(widths.particleType, particleType[index]); 
  ret = ret + formatter(widths.index, std::to_string(index+1));

  return ret;
}

//Because of the redundant x y and z array, just default to the types corresponding index
auto LineCreator::Position(int index) -> std::string {
  std::string ret = formatter(widths.vec1[0], std::to_string(positions[index][0]))
                  + formatter(widths.vec2[1], std::to_string(positions[index][1]))
                  + formatter(widths.vec3[2], std::to_string(positions[index][2]));
  
  return ret;
}

auto LineCreator::Velocity(int index) -> std::string {  
  std::string ret = formatter(widths.vec1[0], std::to_string(velocities[index][0]))
                  + formatter(widths.vec2[1], std::to_string(velocities[index][1]))
                  + formatter(widths.vec3[2], std::to_string(velocities[index][2]));
  
  return ret;
}

auto LineCreator::Force(int index) -> std::string {
  std::string ret = formatter(widths.vec1[0], std::to_string(forces[index][0]))
                  + formatter(widths.vec2[1], std::to_string(forces[index][1]))
                  + formatter(widths.vec3[2], std::to_string(forces[index][2]));
  
  return ret;
}

//Pointer passed, therefore doesn't need a return type. Helps prevent otherwise redundant code
auto LineCreator::CreateLines(Writer& writer) -> void {
  //Description
  writer.addLine(Description());
  //Levcfg, imcon, num NumParticles
  writer.addLine(Levcfg()+Imcon()+NumParticles());
 
    auto unitVectors = Axis();
    //Unit vectors
    writer.addLine(unitVectors[0]);
    writer.addLine(unitVectors[1]);
    writer.addLine(unitVectors[2]);

    //Each particle 
    for (int i = 0; i < numParticles; i++) {
      // Particle type, index
      writer.addLine(ParticleAndIndex(i));
      // Position
      writer.addLine(Position(i));

      if (levcfg != 0) {
        // Velocities
        writer.addLine(Velocity(i));

        if (levcfg == 2) {
          // Forces
        writer.addLine(Force(i));
      }
    }
  }
}
