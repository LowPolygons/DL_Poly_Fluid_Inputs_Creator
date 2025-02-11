# Inputs For Fluids
A system designed to create the input DL_POLY files for a fluid or solution, comprised of any number of molecules. This can be used atomistically or using beads 

## USE 
To make use of this, you will first need to define:
- System parameters
- Molecule Structures
- Interactions

### System Parameters 
Key Areas of System Parameters:
- Formatting Lengths
- Key Values for the system 

#### Formatting Lengths
Navigate to `parameters`, then consult `configParameters.txt` and `fieldParameters.txt`

For each of them:
- Comments are allowed, by putting // at the very start of the line
- Each line will outline how many characters the corresponding value will take up in the corresponding output file
- The very first line is ignored regardless of the presence of //
Format of each line:
  `[titleOfLine]=[characterLength]`

For Example:
  `description=100`

List of all required parameters in the `config`:
- description 
- levcfg
- imcon
- numparticles
- v1x, v2x, v3x
- v1y, v2y, v3y
- v1z, v2z, v3z
- posx, posy, posz
- velx, vely, velz
- fcex, fcey, fcez
- particleType
- index

List of all required parameters in the `field`:
- description
- units
- molecules
- moleculeNames
- moleculeDoubles
- moleculeInts
- potentials
- vdwParticle
- vdwParams

#### General Inputs
The general inputs file is the main file dictating what will appear as outputs. Navigate to `parameters` and open the `Inputs.h` file

The `Standard` sections controls any variables that are specific to all input files and can't be categorised into 1:

- description : The top of the file in both the config and field file
- numOfMolecules : This is the number of molecules that will be generated in the solution, NOT the number of particles.
- molecules : This is an array of all molecules to be included. The names will have to match what is defined in the `parameters/molecules` directory (will be explained later)
- moleculePercentages : This is an array of equal length to the molecules array. These numbers must not exceed 100, but may not necessarily reach 100. The order given will be in correspondance with the order of molecule names given in the above array

#### Config Inputs

Levcfg outlines what vectors per atom will appear in the config file
- levcfg : the options for this:
    => COORDS
    => COORDS_VELS
    => COORDS_VELS_FORCES

Imcon outlines what type of boundary will be used
- Imcon : the options for this:
    => NO_PBC
    => CUBIC
    => ORTHORHOMBIC
    => PARALLELEPIPED
    => XYPARALLELOGRAM

- Vector1, Vector2, Vector3 : the three vectors which will outline the region where particles will be considered
    => These will be used to generate the positions of the molecules

- vel_minimum, vel_maximum : the range of allowed numbers for the velocities of the particles. Right now, this is only random or disabled

- fce_minimum, fce_maximum : the same as above, except for forces

XYZGEN details what generation method will be used for each vector 
gen_position, gen_velocity, gen_force : the options are 
    => DISABLED 
    => RANDOM_UNIFORM
    => UNIFORM

- randSeed_Angle : the number used as a seed for generating the angles generated for each molecule
- randSeed_Offsets : the number used as the seed for generating the offset order of the molecules

If the distribution type for the below variables isnt RANDOM_UNIFORM, these will be ignored
- randSeed_Position : the seed for generating random points as offsets for molecules
- randSeed_Velocity : the seed used for generating random velocities 
- randSeed_Force    : the seed used for generating random forces

- boundingSphereMultiplier : this is a multiplier which will specfify how far away a particle is allowed to be relative to the largest bounding sphere of all available molecules

#### Field Inputs

Units are the chosen units that outputs from DL_POLY will be in 
- units : the options are
    => EV
    => KCAL
    => KJ
    => K 
    => INTERNAL

- vdwInteracts : this is an array of all desired VDW interactions, with filenames matching those in `parameters/vdws` which will be explained later


### Molecule Structures
This explains how to define a molecule in the `parameters/molecules` file path

Once again, lines beginning with // will be ignored so comments are supported

The first line MUST explain how many atoms there are:
    `Atoms=[atomNumber]`

From there, each subsequent [atomNumber] lines (not including blank space) must follow the given format:
    `[localIndex]:atomLabel=[POSX],[POSY],[POSZ]`

Where (POSX, POSY, POSZ) is in relative coordinates where particles are to each other

Right now, try manually picking a particle to be as close to 0,0,0 as possible. In the future, the 'centre' of the molecule will be the average position of the particles given


Next, you list the bonds between particles by writing their local index with a '->' inbetween:
    `[localIndex]->[anotherLocalIndex]`

This may be redundant, but for now it will stay

Next, you will describe the necessary parameters for eacgh atomLabel needed in the molecule with the format 
Note: [ATOM] is not a substitute, you must write those 6 characters at the beginning of each line   
    `[ATOM],<character>, <mass>, <charge>, <nrept>, <ifrz>`
Example: `[ATOM],WT, 90.076, 0.0, 1, 0`

### Interactions
This will outline how non-molecule atoms will interact, and by what potential with what parameters, listed in `parameters/vdws`

Important to note: The title of the vdw interaction MUST follow the format of 
    `[atomLabel]_[atomLabel]`

Once again, comments are allowed with // at the start of the line

The first two lines must detail the potentail type and the number of parameters respectively. Then, every subsequent line is just a number
    `Name=[potential type, all avaiable in DL_POLY docs]`
    `Count=[num variables]`
    `[Var1]`
    `[Var2]`
    `[Var3]`
    `[etc]`
