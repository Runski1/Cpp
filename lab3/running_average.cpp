#include <deque>
#include <iostream>
#include <string>

class RunningAverage {
public:
  RunningAverage();
  RunningAverage(const int &size);
  void add_value(int value);
  double get_average();

private:
  std::deque<int> d;
  uint8_t size;
};

int main() {
  RunningAverage avg;
  std::string input;
  int number = 1;
  do {
    std::cout << "Enter numbers, '0' to stop: ";
    std::getline(std::cin, input);
    try {
      number = std::stoi(input);
      if (number != 0) {
        avg.add_value(number);
      }
    } catch (const std::invalid_argument &e) {
      std::cerr << "Bad input. Enter valid number" << std::endl;
    } catch (const std::out_of_range &e) {
      std::cerr << "Number is out of range. Use another number" << std::endl;
    }
    std::cout << avg.get_average() << std::endl;
  } while (number != 0);
}

RunningAverage::RunningAverage() { size = 5; }
RunningAverage::RunningAverage(const int &s) { size = s; }

void RunningAverage::add_value(int value) {
  d.push_back(value);
  if (d.size() > size) {
    d.pop_front();
  }
}

double RunningAverage::get_average() {
  if (d.empty()) return 0;
  double sum = 0;
  for (auto n : d) {
    sum += n;
  }
  return sum / (double) d.size(); // In case d.size() < size, d.size() has to be used here
}
