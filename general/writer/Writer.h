#ifndef INPUTS_WRITER
#define INPUTS_WRITER

#include <iostream>
#include <vector>

//TODO: Rename/Refactor this to be more generalised to just 'Writer' as it will be used by the field writer too

//The class responsible for writing the final product, NOT forming the lines
class Writer {
public:
  Writer(std::string fp) : filePath(fp) {};

  //Getters/Setters
  auto GetLines() -> std::vector<std::string>;
  auto FilePath() -> std::string;

  auto addLine(std::string line) -> void;

  auto writeFile() -> bool;
private:
  //Very dedicated class, so only needs two attributes
  std::string filePath;
  std::vector<std::string> lines;
};

#endif
