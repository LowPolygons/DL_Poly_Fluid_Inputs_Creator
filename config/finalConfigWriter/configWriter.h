#ifndef CONFIG_WRITER
#define CONFIG_WRITER

#include <iostream>
#include <vector>

//The class responsible for writing the final product, NOT forming the lines
class ConfigWriter {
public:
  ConfigWriter(std::string fp) : filePath(fp) {};

  //Getters/Setters
  auto ConfigLines() -> std::vector<std::string>;
  auto FilePath() -> std::string;

  auto addConfigLine(std::string line) -> void;

  auto writeConfigFile() -> bool;
private:
  //Very dedicated class, so only needs two attributes
  std::string filePath;
  std::vector<std::string> configLines;
};

#endif
