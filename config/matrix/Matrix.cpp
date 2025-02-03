#include "Matrix.h"

#include <iostream>
#include <vector>
#include <array>
#include <cmath>


auto Matrix::Rotate(std::vector<std::array<double,3 >> pos, double xAng, double yAng, double zAng) -> std::vector<std::array<double, 3>> {
  const double PI = 3.14159265358979323;
  xAng = xAng * PI / 180;
  yAng = yAng * PI / 180; //Degrees to radians
  zAng = zAng * PI / 180;
  //           [1,    0,     0]             [ cosA, 0, sinA]            [cosA, -sinA, 0]  
  //  Rx(A) =  [0, cosA, -sinA]    Ry(A) =  [    0, 1,    0]    Rz(A) = [sinA,  cosA, 0]
  //           [0, sinA,  cosA]             [-sinA, 0, cosA]            [   0,     0, 1]
  //  Mz*My*Mx*pos = returnVal
  for (int i = 0; i < pos.size(); i++) {
    //Temporary variables needed
    double tempX = pos[i][0];
    double tempY = pos[i][1];
    double tempZ = pos[i][2];

    //X Axis
    pos[i][1] = (cos(xAng) * tempY) - (sin(xAng) * tempZ);
    pos[i][2] = (sin(xAng) * tempY) + (cos(xAng) * tempZ);

    tempY = pos[i][1];
    tempZ = pos[i][2];

    //Y axis
    pos[i][0] = (cos(yAng) * tempX) + (sin(yAng) * tempZ);
    pos[i][2] = (-sin(yAng) * tempX) + (cos(yAng) * tempZ);

    tempX = pos[i][0];

    //Z axis
    pos[i][0] = (cos(zAng) * tempX) - (sin(zAng) * tempY);
    pos[i][1] = (sin(zAng) * tempX) + (cos(zAng) * tempY);
  }

  //Add a clamper
  return pos;
}

auto Matrix::Translate(std::vector<std::array<double, 3>> pos, std::array<double, 3> offset) -> std::vector<std::array<double, 3>> {
  //loop through, add offset, simple, possibly switch to pointers
  for (int i = 0; i < pos.size(); i++) {
    pos[i][0] = pos[i][0] + offset[0];
    pos[i][1] = pos[i][1] + offset[1];
    pos[i][2] = pos[i][2] + offset[2];
  }

  return pos;
}

auto Matrix::Scale(std::vector<std::array<double, 3>> pos, std::array<double, 3> scaleFactor) -> std::vector<std::array<double, 3>> {
  for (int i = 0; i < pos.size(); i++) {
    pos[i][0] = pos[i][0] * scaleFactor[0];
    pos[i][1] = pos[i][1] * scaleFactor[1];
    pos[i][2] = pos[i][2] * scaleFactor[2];
  }

  return pos;
}

auto Matrix::Clamp(std::vector<std::array<double, 3>> pos, double epsilon) -> std::vector<std::array<double, 3>> {
  for (int i = 0; i < pos.size(); i++) {
    if (std::fabs(pos[i][0]) < epsilon) { pos[i][0] = 0; }
    if (std::fabs(pos[i][1]) < epsilon) { pos[i][1] = 0; }
    if (std::fabs(pos[i][2]) < epsilon) { pos[i][2] = 0; }
  }

  return pos;
};

auto Matrix::MaxModulus(std::vector<std::array<double, 3>> pos) -> double {
  double returnValue = 0;

  for (std::array<double, 3> curr : pos) {
    double temp = sqrt(curr[0]*curr[0] + curr[1]*curr[1] + curr[2]*curr[2]);

    if (temp > returnValue) { returnValue = temp ;}
  }

  return returnValue;
}
