echo "Compiling"

g++ config/config.cpp config/ParameterReader/ParameterReader.cpp config/writer/Writer.cpp config/xyzGenerator/XyzGenerator.cpp config/lineCreator/LineCreator.cpp config/configOrganiser/ConfigOrganiser.cpp config/molecule/Molecule.cpp config/moleculeConstructor/MoleculeConstructor.cpp config/matrix/Matrix.cpp config/moleculePlacer/MoleculePlacer.cpp config/inputVerifier/InputVerifier.cpp -o run

echo "Running"

./run

rm run





























