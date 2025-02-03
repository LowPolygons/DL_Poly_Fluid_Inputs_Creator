#include "ConfigWriter.h"

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <stdlib.h>

auto ConfigWriter::ConfigLines() -> std::vector<std::string> { return configLines; }
auto ConfigWriter::FilePath()    -> std::string              { return filePath; }

auto ConfigWriter::addConfigLine(std::string line) -> void {
  configLines.push_back(line);
}

auto ConfigWriter::writeConfigFile() -> bool {
  std::filesystem::path targetPath(filePath);

  if ( std::filesystem::exists(targetPath) ) {
    //if already exists, delete and recreate the file here
    if ( !std::filesystem::remove(targetPath) ) {
      std::cout << "[Error] There was an issue trying to replace the current config file. Try deleting it manually?" << std::endl;
      return false;
    }
  }

  std::ofstream configOutput(targetPath);

  //check it was created correctly
  if (!configOutput) {
    std::cout << "[Error] There was an issue trying to create a new config file" << std::endl;
    return false;
  }

  //loop through lines and write to file
  for (std::string currLine : configLines) {
    configOutput << currLine << std::endl;
  }

  configOutput.close();

  //if it reached here, it passed
  return true;
}
