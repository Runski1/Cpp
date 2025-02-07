#include <iostream>
#include <map>
#include <string>

void print_map(const std::map<std::string, int> &map) {
  for (const auto &[key, value] : map) {
    std::cout << key << " : " << value << std::endl;
  }
}

int main() {
  std::string line, number;
  std::map<std::string, int> name_map;
  do {
    std::cout << "Enter name or \"stop\" or \"print\": ";
    std::getline(std::cin, line);
    if (line == "print") {
      print_map(name_map);
    } else if (line == "stop") {
      break;
    } else {
      std::cout << "Enter integer: ";
      try {
        std::getline(std::cin, number);
        name_map[line] = std::stoi(number);
      } catch (const std::invalid_argument& e) {
        std::cerr << "Bad input. Enter valid number" << std::endl;
      } catch (const std::out_of_range& e) {
        std::cerr << "Number is out of range. Use another number" << std::endl;
      }
    }
  } while (line != "stop");
  return 0;
}
