#include <iostream>
#include <string>

using namespace std;

class Item {
  public:
    Item(const char *name0 = "", const int weight0 = 0, const double price0 = 0,
         const int count0 = 0)
        : name(name0), weight(weight0), price(price0), count(count0) {}
    int getCount() { return count; };
    void setCount(const uint &count0) { count = count0; };
    double getPrice() { return price; };
    int setPrice();
    friend ostream &operator<<(ostream &out, const Item &i);
    friend istream &operator>>(istream &in, Item &i);

  private:
    string name;
    int weight;
    double price;
    int count;
};

int main() {}
