#include <deque>
#include <iostream>
#include <string>

using namespace std;

class Item {
public:
  Item(const char *name="", const int weight=0, double price=0, int count=0);
  int getCount(const uint count);
  int setCount();
  double getPrice();
  int setPrice();

private:
  string name;
  int weight;
  double price;
  int count;
};

Item::Item(const char* name0, const int weight0, const double price0, const int count0) : 
  name(name0), 
  weight(weight0),
  price(price0),
  count(count0)
{}

int Item::getCount(const uint &index) {
  return count;
}

int Item::setCount(const uint &count0) {
}


int main() {
  
}

