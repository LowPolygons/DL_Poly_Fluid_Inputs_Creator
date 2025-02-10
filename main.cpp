#include <iostream>
#include <memory>

#include "general/structs/structures.h"
#include "general/writer/Writer.h"
#include "config/xyzGenerator/XyzGenerator.h"
#include "config/lineCreator/LineCreator.h"
#include "config/configOrganiser/ConfigOrganiser.h"
#include "general/molecule/Molecule.h"
#include "general/moleculeConstructor/MoleculeConstructor.h"
#include "config/matrix/Matrix.h"
#include "config/moleculePlacer/MoleculePlacer.h"
#include "config/inputVerifier/InputVerifier.h"

#include "parameters/Inputs.h"

#include "config/config.h"
#include "field/field.h"
#include "field/lineCreator/LineCreator.h"
#include "field/vdwManager/VdwManager.h"

int main () {
  //==================================// 
  //              Config              //
  //==================================//

  ConfigInputs inputs;
  //Run a validator on the inputs to ensure the certain conditions are met (log all issues before closing)
  InputVerifier inputValidator(inputs);
  inputValidator.ConductValidation();

  //General use class to neaten up the main file, initialise the description
  ConfigOrganiser organiser;
 
  //Basic values that can just be immediately read and interpreted (CONFIG.H) 
  Config::initBasicOrganiserVals(inputs, organiser);

  //Generate the molcule map
  auto moleculeVector = Config::generateMolecules(inputs, organiser);

  //Get the position values based on inputs (CONFIG.H)
  Config::getPositionValues(inputs, organiser, moleculeVector);
  //Get the velocity values assuming, if they are desired (CONFIG.H)
  Config::getVelocityValues(inputs, organiser);
  //One for Forces
  Config::getForceValues(inputs, organiser);

  //Line Creator and Writer here
  auto writer = Writer("results/config.txt");
  
  LineCreator creator(
    organiser.WidthsInFile(), 
    organiser.Defaults(),
    organiser.Description(),
    organiser.Levcfg(),
    organiser.Imcon(),
    organiser.NumParticles(),
    organiser.Vectors()[0],
    organiser.Vectors()[1],
    organiser.Vectors()[2],
    organiser.Types(),
    organiser.Positions(),
    organiser.Velocities(),
    organiser.Forces()
  );

  creator.CreateLines(writer);
  writer.writeFile();


  //==================================// 
  //               Field              //
  //==================================//
  
  FieldParameters fieldParams = Field::GetFileLengths();

  f_LineCreator tester(fieldParams, "ASDASDASDAD", UNITS::KCAL, 2, inputs.molecules, organiser.MoleculeCounts(), moleculeVector);

  auto values = tester.GetPerMoleculeCount();

  for (std::string s : values) {
    std::cout << s << "YAYA" << std::endl;
  }

  VdwManager manager({"WT_WT"});

  manager.ReadVDWs();

  std::vector<Potential> thing = manager.UsableVDWs();

  std::cout << thing[0].name << std::endl;
  for (double x : thing[0].parameters) {
    std::cout << x << "ahdas" << std::endl;
  }

  return 0;
}
