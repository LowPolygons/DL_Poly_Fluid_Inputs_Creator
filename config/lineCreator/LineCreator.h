#ifndef LINE_CREATOR

#define LINE_CREATOR

#include "../structs/structures.h"
#include "../writer/Writer.h"
#include <iostream>
#include <array>
#include <vector>
#include <memory>

//Class for creating the formatted lines to be written by the config writer
class LineCreator {
public:
  LineCreator(ConfigParameters _widths, ConfigDefaults _defaults, 
      std::string _description, LEVCFG _levcfg, IMCON _imcon, int _numParticles, 
      std::array<double, 3> v1, std::array<double, 3> v2, std::array<double, 3> v3, 
      std::vector<std::string> _particleType, std::vector<std::array<double, 3>> _positions,
      std::vector<std::array<double, 3>> _velocities, std::vector<std::array<double, 3>> _forces) {
    
    widths = _widths;
    defaults = _defaults;
    description = _description;
    levcfg = _levcfg;
    imcon = _imcon;
    numParticles = _numParticles;
    vec1 = v1;
    vec2 = v2;
    vec3 = v3;
    particleType = _particleType;
    positions = _positions;
    velocities = _velocities;
    forces = _forces;
  }

  //The overseeing function which will calls all other methods necessary to save the file
  auto CreateLines(Writer& writer) -> void; 

  //Cast each data type to a string, then pass to this which does the correct formatting
  auto formatter(int size, std::string var) -> std::string;

  //Converters into strings that are formatted by using the above method
  auto Description() -> std::string;
  auto Levcfg() -> std::string;
  auto Imcon() -> std::string;
  auto NumParticles() -> std::string;
  auto Axis() -> std::vector<std::string>;
  auto ParticleAndIndex(int index) -> std::string;
  auto Position(int index) -> std::string;
  auto Velocity(int index) -> std::string;
  auto Force(int index) -> std::string;

private:
  //Formatting things 
  ConfigParameters widths;
  ConfigDefaults defaults;
  //Actual variables
  std::string description;
  LEVCFG levcfg;
  IMCON imcon;
  int numParticles;
  std::array<double, 3> vec1, vec2, vec3;
  std::vector<std::string> particleType;
  std::vector<std::array<double, 3>> positions, velocities, forces;
};

#endif
