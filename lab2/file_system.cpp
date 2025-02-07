#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

int main() {
  std::string dir_name;
  std::vector<std::string> dir_names;
  fs::path path;
  std::cout << "Enter directory names or empty string to stop program:"
            << std::endl;
  do { // read directory names until empty line
    std::getline(std::cin, dir_name);
    if (dir_name.length() > 0) {
      dir_names.push_back(dir_name); // add dir to dir_names vector
    }
  } while (dir_name.length() > 0);

  // construct relative path from dir_names
  for (auto i : dir_names) {
    path.append(i);
  }
  // mkdir -p
  fs::create_directories(path);
  // append file to path
  path.append("result.txt");
  // open file
  std::ofstream file(path);

  // absolute path
  auto absolute_path = fs::absolute(path);
  std::cout << "Absolute path: " << absolute_path << std::endl;
  file << absolute_path << std::endl;
  // vector contents
  std::cout << "Vector contents:" << std::endl;
  for (auto i : dir_names) {
    std::cout << i << std::endl;
    file << i << std::endl;
  }
  // relative path
  std::cout << "relative path: " << path << std::endl;
  file << path << std::endl;

  // close file
  file.close();

  std::cout << "Tree for show:" << std::endl;
  std::system("tree");

  return 0;
}
