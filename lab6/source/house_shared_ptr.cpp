#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class House {
  public:
    House(const string &addr, double area, double price)
        : address(addr), area(area), price(price) {};
    ~House() {};
    string getAddress() { return address; };
    void setAddress(string &addr) { address = addr; };
    void setArea(double &_area) { area = _area; };
    void setPrice(double &_price) { price = _price; };
    double getPricePerArea() { return price / area; };
    friend ostream &operator<<(ostream &out, const House &house);

  private:
    string address;
    double area;
    double price;
};
ostream &operator<<(ostream &out, const House &house) {
    out << "Address: " << house.address << ", Area: " << house.area << "(m^2), "
        << "Price: " << house.price << "EUR";
    return out;
}

class Apartment {
  public:
    Apartment(const string _number, double _area, double _rent,
              shared_ptr<House> _house)
        : number(_number), area(_area), rent(_rent), house(_house) {};
    ~Apartment() {};
    string getAddress() { return house->getAddress(); }
    void setArea(double _area) { area = _area; };
    void setPrice(double _price) { rent = _price; };
    double getRentPerArea() const { return rent / area; };
    friend ostream &operator<<(ostream &out, const Apartment &apartment);
    friend bool operator<(Apartment &a1, const Apartment &a2) {
        return a1.rent < a2.rent;
    }

  private:
    string number;
    double area;
    double rent;
    shared_ptr<House> house;
};

ostream &operator<<(ostream &out, const Apartment &a) {
    out << "Address: " << a.house->getAddress() << a.number
        << ", Area: " << a.area << "(m^2), "
        << "Price: " << a.rent << "EUR/month";
    return out;
}

int main() {
    std::shared_ptr<House> house1 =
        std::make_shared<House>("Leiritie 1", 40000, 5000000);
    std::shared_ptr<House> house2 =
        std::make_shared<House>("Karaportti 2", 3000, 1000000);
    vector<Apartment> apartments = {
        Apartment("A14", 38, 860, house1),  Apartment("B33", 45, 960, house1),
        Apartment("C53", 60, 1220, house1), Apartment("A4", 30, 650, house2),
        Apartment("A8", 35, 700, house2),   Apartment("B14", 45, 820, house2),
        Apartment("B20", 50, 900, house2)};

    sort(apartments.begin(), apartments.end());

    for (auto &a : apartments) {
        cout << a << endl;
    }

    return 0;
}
