#ifndef CONFIG_SECTION

#define CONFIG_SECTION

#include "molecule/Molecule.h"
#include "configOrganiser/ConfigOrganiser.h"
#include "../parameters/Inputs.h"

#include <vector>

//All values which are just read from the Inputs file directly are done in this
auto initBasicOrganiserVals(ConfigInputs& inputs, ConfigOrganiser& organiser) -> void;

auto generateMolecules(ConfigInputs& inputs, ConfigOrganiser& organiser) -> std::vector<Molecule>;

auto getPositionValues(ConfigInputs& inputs, ConfigOrganiser& organiser, std::vector<Molecule> moleculeVector) -> void;
auto getVelocityValues(ConfigInputs& inputs, ConfigOrganiser& organiser) -> void;
auto getForceValues   (ConfigInputs& inputs, ConfigOrganiser& organiser) -> void;

#endif
