#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Item {
  public:
    Item(const char *name0 = "", const int weight0 = 0, const double price0 = 0,
         const int count0 = 0)
        : name(name0), weight(weight0), price(price0), count(count0) {}
    int getCount() { return count; };
    void setCount(const uint &count0) { count = count0; };
    double getPrice() { return price; };
    void setPrice(const uint &price0) { price = price0; };
    friend ostream &operator<<(ostream &out, const Item &i);
    friend istream &operator>>(istream &in, Item &i);
    friend bool operator<(const Item &item1, const Item &item2) {
        return item1.price < item2.price;
    }

  private:
    std::string name;
    int weight;
    double price;
    int count;
};

ostream &operator<<(ostream &out, const Item &i) {
    out << "{ \"Name\":\"" << i.name << "\", \"Weight\":" << i.weight
        << ", \"Price\":" << i.price << ", \"Count\":" << i.count << " }";
    return out;
};

istream &operator>>(istream &in, Item &i) {
    try {
        string input_line;
        while (getline(in, input_line, ':')) {
            if (input_line.find("Name") != string::npos) {
                getline(in, input_line, ',');
                input_line.erase(0, 1);
                input_line.erase(input_line.length() - 1, 1);
                i.name = input_line;
            }
            if (input_line.find("Weight") != string::npos) {
                getline(in, input_line, ',');
                i.weight = stoi(input_line);
            }
            if (input_line.find("Price") != string::npos) {
                getline(in, input_line, ',');
                i.price = stod(input_line);
            }
            if (input_line.find("Count") != string::npos) {
                getline(in, input_line, ',');
                i.count = stoi(input_line);
            }
        }
    } catch (const exception &e) {
        cout << e.what() << endl;
        in.setstate(ios::failbit);
    }
    return in;
}

int parse_json(vector<Item> &items, string &object) {
    istringstream stream(object);
    Item i;
    stream >> i;
    if (stream.fail()) {
        if (stream.eof()) {
            items.push_back(i);
            return 0;
        } else {
            cout << "stream fail\n";
            return 1;
        }
    }
    return 0;
}

double get_networth(vector<Item> &items) {
    double total = 0;
    for (auto &i : items) {
        total += i.getCount() * i.getPrice();
    }
    return total;
}

void print_items(vector<Item> &items) {
    int index = 0;
    sort(items.begin(), items.end());
    for (auto &i : items) {
        cout << ++index << ": " << i << endl;
    }
    cout << "Stock net worth: " << get_networth(items) << "EUR" << endl;
}

int main() {
    vector<Item> items;
    string user_input = "";
    while (user_input.find("stop") != 0) {
        cout << "Enter name of item or \"json\" for json input or \"stop\" to "
                "stop: ";
        getline(cin, user_input);
        if (user_input.find("json") == 0) {
            cout << "Paste in the json object:\n";
            getline(cin, user_input);
            size_t begin = 0;
            size_t end = 0;
            while (begin < user_input.length()) {
                end = user_input.find('}', begin);
                if (end != string::npos) {
                    string obj = user_input.substr(begin, end - begin + 1);
                    parse_json(items, obj);
                    begin = end + 1;
                }
            }
        } else if (user_input.find("stop") == 0) {
            break;
        } else if (user_input.length() > 0) {
            string name = user_input;
            int weight;
            cout << "Weight: ";
            getline(cin, user_input);
            weight = stoi(user_input);
            double price;
            cout << "Price: ";
            getline(cin, user_input);
            price = stod(user_input);
            int count;
            cout << "Count: ";
            getline(cin, user_input);
            count = stoi(user_input);
            Item i(name.c_str(), weight, price, count);
            items.push_back(i);
        }
    }
    print_items(items);
    cout << "Choose an item to change 1-" << items.size() << ": ";
    int item_num;
    cin >> item_num;
    cout << endl << "Set the new price: ";
    double new_price;
    cin >> new_price;
    items[item_num - 1].setPrice(new_price);
    print_items(items);
    return 0;
}
