#ifndef PROGRAMME_STRUCTURES
#define PROGRAMME_STRUCTURES

#include <iostream>
#include <array>
#include <unordered_map>
#include <vector>
//---------------------------//
//          Config           // 
//---------------------------//

//Taken from DL_POLY docs
enum LEVCFG {
  COORDS = 0,
  COORDS_VELS = 1,
  COORDS_VELS_FORCES = 2
};

//Taken from DL_POLY docs
enum IMCON {
  NO_PBC = 0,
  CUBIC = 1,
  ORTHORHOMBIC = 2,
  PARALLELEPIPED = 3,
  XYPARALLELOGRAM = 6
};

//Custome enum to describe how/if the XYZ values for each particle should be generated
enum XYZGEN {
  DISABLED = -1,
  RANDOM_UNIFORM = 0,
  UNIFORM = 1
};

//Contains the character widths for each item when put in the final config file
struct ConfigParameters {
  int description;
  int levcfg;
  int imcon;
  int numparticles;
  std::array<int, 3> positions;
  std::array<int, 3> velocities;
  std::array<int, 3> forces;
  std::array<int, 3> vec1;
  std::array<int, 3> vec2;
  std::array<int, 3> vec3;
  int particleType;
  int index;
};

//---------------------------//
//           Field           // 
//---------------------------//

//The ones here aren't necessarily representitive of what they need to be in future. Add as necessary
struct FieldParameters {
  int description;
  int units;
  int molecules;
  int moleculeNames;
  int moleculeDoubles;
  int moleculeInts;
  int potentials;
  int vdwParticle;
  int vdwParams;
};

struct Atom {
  std::string name;
  double mass;
  double charge;
  int nrept;
  int ifrz;
};

struct Potential {
  std::string name;
  int numVariables;
  std::vector<double> parameters;
};

//Taken from DL_POLY docs
enum UNITS {
  EV = 1,      //Electron Volts
  KCAL = 2,    //KCAL per Mol
  KJ = 3,      //KJ per Mol
  K = 4,       //Kelvin per Boltzmann
  INTERNAL = 0 //DL_POLY Internal units (10J/Mol)
};

//The chosen implementation for the units enum
const std::unordered_map<UNITS, std::string> UNITS_STRINGS = {{
  {UNITS::EV, "eV"},
  {UNITS::KCAL, "kcal"},
  {UNITS::KJ, "kj"},
  {UNITS::K, "k"},
  {UNITS::INTERNAL, "internal"}
}};

#endif
