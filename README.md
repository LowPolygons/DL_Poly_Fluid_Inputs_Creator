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
  [titleOfLine]=[characterLength]

For Example:
  description=100

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
