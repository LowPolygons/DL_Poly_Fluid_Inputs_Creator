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

  VdwManager manager(inputs.vdwInteracts);
  //Format them
  manager.ReadVDWs();
  //hold them
  std::vector<Potential> potentials = manager.UsableVDWs();

  std::cout << moleculeVector.size() << std::endl;
  //Create the line creator to format the lines
  f_LineCreator lines(
    fieldParams,
    inputs.description, 
    inputs.units,
    moleculeVector.size(), 
    inputs.molecules, 
    organiser.MoleculeCounts(), //Poorly named, this is the per molecule count 
    moleculeVector, 
    potentials
  );

  //TODO: THIS IS REDUNDANT CODE
  //
  //Takes the molecule file names and turns them into Molecule templates
  MoleculeConstructor molCon(inputs.molecules);
  molCon.GenerateMolecules();

  auto fieldLines = lines.CreateLines(molCon, inputs.vdwInteracts);

  Writer fieldWriter = Writer("results/field.txt");

  for (auto curr : fieldLines) {
    fieldWriter.addLine(curr);
  }

  fieldWriter.writeFile();
  return 0;
}
