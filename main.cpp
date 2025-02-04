#include <iostream>
#include <memory>

#include "config/structs/structures.h"
#include "config/parameterReader/ParameterReader.h"
#include "config/writer/Writer.h"
#include "config/xyzGenerator/XyzGenerator.h"
#include "config/lineCreator/LineCreator.h"
#include "config/configOrganiser/ConfigOrganiser.h"
#include "config/molecule/Molecule.h"
#include "config/moleculeConstructor/MoleculeConstructor.h"
#include "config/matrix/Matrix.h"
#include "config/moleculePlacer/MoleculePlacer.h"
#include "config/inputVerifier/InputVerifier.h"

#include "parameters/Inputs.h"

#include "config/config.h"

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
  initBasicOrganiserVals(inputs, organiser);

  auto moleculeVector = generateMolecules(inputs, organiser);

  //Get the position values based on inputs (CONFIG.H)
  getPositionValues(inputs, organiser, moleculeVector);
  //Get the velocity values assuming, if they are desired (CONFIG.H)
  getVelocityValues(inputs, organiser);
  //One for Forces
  getForceValues(inputs, organiser);

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
    organiser.Types(),   //change this
    organiser.Positions(),
    organiser.Velocities(),
    organiser.Forces()
  );

  creator.CreateLines(writer);
  writer.writeFile();


  //==================================// 
  //               Field              //
  //==================================//


  return 0;
}
