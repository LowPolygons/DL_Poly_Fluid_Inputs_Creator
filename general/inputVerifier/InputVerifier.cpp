#include "../../parameters/Inputs.h"
#include "InputVerifier.h"

#include <cmath>
//Checks the variables lengths, and that they do not exceed 100 
auto InputVerifier::ValidateMolecule() -> bool {
  bool success = true;

  size_t molecules_size = inputs.molecules.size();
  size_t moleculePercentages_size = inputs.moleculePercentages.size();

  if (molecules_size != moleculePercentages_size) {
    std::cout << "[Error] Mismatch in sizes between molecules list and the corresponding percentages list" << std::endl;
    success = false;
  }

  //Confirm the percentages sum to 100
  if (success) {
    int sum = 0;
    for (int i : inputs.moleculePercentages) {
     sum += i;
    }

    if (sum > 100) {
     std::cout << "[Error] The percentages in the molecule percentages array exceed 100" << std::endl;
     success = false;
    }
  }

  return success; 
}

//Cross products each vector pair, if any are a zero vector they are parallel
auto InputVerifier::ValidateVectors() -> bool {
  const double epsilon = 1e-06;

  bool success = true;
  //Coefficients 1, 2 and 3
  double v1, v2, v3;
  //Vec1 and Vec2
  v1 = inputs.vector1[1]*inputs.vector2[2] - inputs.vector1[2]*inputs.vector2[1];
  v2 = inputs.vector1[0]*inputs.vector2[2] - inputs.vector1[2]*inputs.vector2[0];
  v3 = inputs.vector1[0]*inputs.vector2[1] - inputs.vector1[1]*inputs.vector2[0];

  if (std::fabs(v1) < epsilon && std::fabs(v2) < epsilon && std::fabs(v3) < epsilon) {
    std::cout << "[Error] Vectors 1 and 2 are parallel" << std::endl;
    success = false;
  }
  //Vec1 and Vec3
  v1 = inputs.vector1[1]*inputs.vector3[2] - inputs.vector1[2]*inputs.vector3[1];
  v2 = inputs.vector1[0]*inputs.vector3[2] - inputs.vector1[2]*inputs.vector3[0];
  v3 = inputs.vector1[0]*inputs.vector3[1] - inputs.vector1[1]*inputs.vector3[0];

  if (std::fabs(v1) < epsilon && std::fabs(v2) < epsilon && std::fabs(v3) < epsilon) {
    std::cout << "[Error] Vectors 1 and 3 are parallel" << std::endl;
    success = false;
  }  
  //Vec2 and Vec3
  v1 = inputs.vector2[1]*inputs.vector3[2] - inputs.vector2[2]*inputs.vector3[1];
  v2 = inputs.vector2[0]*inputs.vector3[2] - inputs.vector2[2]*inputs.vector3[0];
  v3 = inputs.vector2[0]*inputs.vector3[1] - inputs.vector2[1]*inputs.vector3[0];

  if (std::fabs(v1) < epsilon && std::fabs(v2) < epsilon && std::fabs(v3) < epsilon) {
    std::cout << "[Error] Vectors 2 and 2 are parallel" << std::endl;
    success = false;
  } 

  return success;
}

auto InputVerifier::ValidateBounding() -> bool {
  bool success = true;
  //Compare all useBounding functions and ensure only one is active
  return success;
}

auto InputVerifier::ConductValidation() -> void {
  bool molecule_success = ValidateMolecule();
  bool vectors_success  = ValidateVectors();
  bool bounding_success = ValidateBounding();

  if (!molecule_success || !vectors_success || !bounding_success) {
    exit(EXIT_FAILURE);
  }
}


