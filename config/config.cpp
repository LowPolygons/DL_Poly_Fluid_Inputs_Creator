#include <iostream>
#include <memory>

#include "structs/structures.h"
#include "parameterReader/ParameterReader.h"
#include "writer/Writer.h"
#include "xyzGenerator/XyzGenerator.h"
#include "lineCreator/LineCreator.h"
#include "configOrganiser/ConfigOrganiser.h"
#include "molecule/Molecule.h"
#include "moleculeConstructor/MoleculeConstructor.h"
#include "matrix/Matrix.h"
#include "moleculePlacer/MoleculePlacer.h"
#include "inputVerifier/InputVerifier.h"

#include "../parameters/Inputs.h"

#include "config.h"

auto initBasicOrganiserVals(ConfigInputs& inputs, ConfigOrganiser& organiser) -> void {
  //Description read straight from inputs
  organiser.set_description(inputs.description);

  //Input the cell vectors into the organiser
  organiser.set_vectors(
    inputs.vector1,
    inputs.vector2,
    inputs.vector3
  );

  //Loads in the data for default placeholders and formatting lengths
  ParameterReader reader("parameters/configParameters.txt");
  reader.readLocalConfig();

  //Load them into the organiser
  organiser.set_widthsInFile(reader.LengthsInFile());
  organiser.set_defaults(reader.DefaultValues());

  //Load the ENUM vals into the organiser
  organiser.set_levcfg(inputs.levcfg);
  organiser.set_imcon(inputs.imcon);
}

auto generateMolecules(ConfigInputs& inputs, ConfigOrganiser& organiser) -> std::vector<Molecule> {
  //Takes the molecule file names and turns them into Molecule templates
  MoleculeConstructor molCon(inputs.molecules);
  molCon.GenerateMolecules();
  
  //Form a vector of the molecules
  auto moleculeList = molCon.Molecules();
  std::vector<Molecule> moleculeVector;

  for (std::string name : inputs.molecules) {
    moleculeVector.push_back(moleculeList[name]);
  }

  return moleculeVector;
}

auto getPositionValues(ConfigInputs& inputs, ConfigOrganiser& organiser, std::vector<Molecule> moleculeVector) -> void {
  //Switch statement for position generation
  XyzGenerator position(organiser.Vectors(), inputs.numOfMolecules);
  
  switch (inputs.gen_position) {
    case (XYZGEN::UNIFORM): {
      //Uniform grid generation, confirm the grid avoids overlaps

      MoleculePlacer uniform(
        organiser.Vectors(), 
        inputs.numOfMolecules, 
        moleculeVector,
        inputs.moleculePercentages, 
        inputs.boundingSphereMultiplier, 
        position.uniform()
      );
       
      uniform.ConfirmGridFitsMoleculeCount();
      uniform.PlaceMolecules(inputs.randSeed_Angle, inputs.randSeed_Offsets);

      //Add the number of particles, positions and types to the organiser
      organiser.set_numParticles(uniform.Particles().size());
      organiser.set_positions(uniform.Particles());
      organiser.set_types(uniform.AtomTypes());

      break;
    }
    case (XYZGEN::RANDOM_UNIFORM): {
      //Random distribution, prompt warning about collision risk 
      std::cout << "[Warn]  Uniform position generation will mean that some molecules can intersect" << std::endl;

      MoleculePlacer random(
        organiser.Vectors(), 
        inputs.numOfMolecules, 
        moleculeVector, 
        inputs.moleculePercentages, 
        inputs.boundingSphereMultiplier, 
        position.randomUniform(inputs.randSeed_Position)
      ); 

      random.PlaceMolecules(inputs.randSeed_Angle, inputs.randSeed_Offsets);

      //Add the number of particles, positions and types to the organiser
      organiser.set_numParticles(random.Particles().size());
      organiser.set_positions(random.Particles());
      organiser.set_types(random.AtomTypes());

      break;
    }
    case (XYZGEN::DISABLED): {
      //Not allowed
      std::cout << "[Error] The config file must in some form generate particles. Disabled is invalid" << std::endl;
      exit(EXIT_FAILURE);

      break;
    }
  }
}

auto getVelocityValues(ConfigInputs& inputs, ConfigOrganiser& organiser) -> void {
  //One for Velocities
  XyzGenerator velocity({inputs.vel_minimum, inputs.vel_maximum, { 0.0, 0.0, 0.0 }}, organiser.NumParticles());

  switch (inputs.gen_velocity) {
    case (XYZGEN::UNIFORM): {
      //Uniform doesn't make sense for Velocity, break out
      std::cout << "[Warn]  Uniform generation for velocity doesn't make sense" << std::endl;
      
      organiser.set_velocities(velocity.uniform());

      break;
    }
    case (XYZGEN::RANDOM_UNIFORM): {
      //Random distribution with the correct seed
      organiser.set_velocities(velocity.randomUniform(inputs.randSeed_Velocity));

      break;
    }
    case (XYZGEN::DISABLED): {
      break;
    }
  }
}

auto getForceValues(ConfigInputs& inputs, ConfigOrganiser& organiser) -> void {
  XyzGenerator force({inputs.fce_minimum, inputs.fce_maximum, { 0.0, 0.0, 0.0 }}, organiser.NumParticles());

  switch (inputs.gen_velocity) {
    case (XYZGEN::UNIFORM): {
      //Uniform doesn't make sense for Velocity, break out
      std::cout << "[Warn]  Uniform generation for forces doesn't make sense" << std::endl;
      
      organiser.set_forces(force.uniform());
      
      break;
    }
    case (XYZGEN::RANDOM_UNIFORM): {
      //Random distribution with the correct seed
      organiser.set_forces(force.randomUniform(inputs.randSeed_Force));

      break;
    }
    case (XYZGEN::DISABLED): {
      break;
    }
  }
}
