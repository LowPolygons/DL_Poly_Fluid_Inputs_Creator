echo "Compiling"

g++ main.cpp config/config.cpp general/parameterReader/ParameterReader.cpp config/paramFormatter/ParamFormatter.cpp config/writer/Writer.cpp config/xyzGenerator/XyzGenerator.cpp config/lineCreator/LineCreator.cpp config/configOrganiser/ConfigOrganiser.cpp config/molecule/Molecule.cpp config/moleculeConstructor/MoleculeConstructor.cpp config/matrix/Matrix.cpp config/moleculePlacer/MoleculePlacer.cpp config/inputVerifier/InputVerifier.cpp field/field.cpp field/paramFormatter/ParamFormatter.cpp -o run

echo "Running"

./run

rm run





























