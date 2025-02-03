#include "Writer.h"

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <stdlib.h>

auto Writer::GetLines() -> std::vector<std::string> { return lines; }
auto Writer::FilePath()    -> std::string              { return filePath; }

auto Writer::addLine(std::string line) -> void {
  lines.push_back(line);
}

auto Writer::writeFile() -> bool {
  std::filesystem::path targetPath(filePath);

  if ( std::filesystem::exists(targetPath) ) {
    //if already exists, delete and recreate the file here
    if ( !std::filesystem::remove(targetPath) ) {
      std::cout << "[Error] There was an issue trying to replace the current config file. Try deleting it manually?" << std::endl;
      return false;
    }
  }

  std::ofstream output(targetPath);

  //check it was created correctly
  if (!output) {
    std::cout << "[Error] There was an issue trying to create a new config file" << std::endl;
    return false;
  }

  //loop through lines and write to file
  for (std::string currLine : lines) {
    output << currLine << std::endl;
  }

  output.close();

  //if it reached here, it passed
  return true;
}
