#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::string line;
  do {
    int count = 0, sum = 0, num = 0;
    std::cout << "Enter a line with numbers or \"stop\": ";
    std::getline(std::cin, line);
    if (line.find("stop") != 0) { // Is using break and infinite loop bad here?
      std::istringstream stream(line);
      while (stream >> num) {
        sum += num;
        count++;
      }
      std::cout << "Total of " << count << " numbers is " << sum << std::endl;
    }
  } while (line.find("stop") != 0); // Checking this condition twice feels stupid
  return 0;
}
