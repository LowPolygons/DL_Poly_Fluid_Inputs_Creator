#ifndef CONFIG_ORGANISER

#define CONFIG_ORGANISER

#include <iostream>
#include <vector>
#include <array>

#include "../../general/structs/structures.h"
#include "../../general/writer/Writer.h"
#include "../lineCreator/LineCreator.h"
#include "../XYZGenerator/xyzGenerator.h"

class ConfigOrganiser {
public:
  //No constructor, use setters as not everything is known immediately
  ConfigOrganiser() {};

  //Getters
  auto WidthsInFile() -> ConfigParameters;
  auto Defaults()     -> ConfigDefaults;
  auto Description()  -> std::string;
  auto Levcfg()       -> LEVCFG;
  auto Imcon()        -> IMCON;
  auto NumParticles() -> int;
  auto Vectors()      -> std::array<std::array<double, 3>, 3>;
  auto Types()        -> std::vector<std::string>;
  auto Positions()    -> std::vector<std::array<double, 3>>;
  auto Velocities()   -> std::vector<std::array<double, 3>>;
  auto Forces()       -> std::vector<std::array<double, 3>>;
  auto MoleculeCounts() -> std::vector<int>;
  //Setters
  void set_widthsInFile(ConfigParameters inp);
  void set_defaults(ConfigDefaults inp);
  void set_description(std::string inp);
  void set_levcfg(LEVCFG inp);
  void set_imcon(IMCON inp);
  void set_numParticles(int inp);
  void set_vectors(std::array<double, 3> inp1, std::array<double, 3> inp2, std::array<double, 3> inp3);
  void set_positions(std::vector<std::array<double, 3>> inp);
  void set_velocities(std::vector<std::array<double, 3>> inp);
  void set_forces(std::vector<std::array<double, 3>> inp);
  void set_types(std::vector<std::string> inp);
  void set_moleculeCounts(std::vector<int> inp);

private:
  ConfigParameters widthsInFile;
  ConfigDefaults defaults;

  std::string description;
  LEVCFG levcfg;
  IMCON imcon;
  int numParticles;
  std::array<double, 3> vec1, vec2, vec3;

  //Not all necessarily going to be used
  std::vector<std::array<double, 3>> positions;
  std::vector<std::array<double, 3>> velocities;
  std::vector<std::array<double, 3>> forces;
  std::vector<std::string> types;

  std::vector<int> moleculeCounts;
};

#endif
