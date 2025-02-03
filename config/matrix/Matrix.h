#ifndef MATRIX_METHODS

#define MATRIX_METHODS

#include <iostream>
#include <vector>
#include <array>
#include <cmath>

class Matrix {

public:
  Matrix() = default;
  //Given a set of coordinates (generally aquirable by GetMolecule) will rotate them about each axis accordingly
  auto Rotate(std::vector<std::array<double, 3>> pos, double xAng, double yAng, double zAng) -> std::vector<std::array<double, 3>>;
  //Given a set of coordinates, it will translate each by the given offset
  auto Translate(std::vector<std::array<double, 3>> pos, std::array<double, 3> offset) -> std::vector<std::array<double, 3>>;
  //Given a set of coordinates, it will scale them about [0,0,0]
  auto Scale(std::vector<std::array<double, 3>> pos, std::array<double, 3> scaleFactor) -> std::vector<std::array<double, 3>>;
  //Given a set of coordinates, it will clamp any values that are excessively close but not equal to zero ( eg x10^-17)
  auto Clamp(std::vector<std::array<double, 3>> pos, double epsilon) -> std::vector<std::array<double, 3>>;
  //Calculates the modulus of each vector and returns the largest
  auto MaxModulus(std::vector<std::array<double, 3>> pos) -> double;
};
#endif
