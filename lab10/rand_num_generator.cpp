#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class UniqueRng {
  public:
    UniqueRng(int min, int max) : lower(min), upper(max), numbers() {
        srand(time(NULL)); // seeding RNG rand()
    }
    void operator()(int count);
    const std::vector<int> &get_numbers() const { return numbers; };
    void clear_nums() { numbers.clear(); };

  private:
    int lower;
    int upper;
    std::vector<int> numbers;
};

void test_generator(UniqueRng &ur, int count) {
    std::cout << "Generating numbers:" << std::endl;
    try {
        ur(count);
    } catch (std::runtime_error &err) {
        std::cout << "Exception: " << err.what() << std::endl;
    }
    for (auto a : ur.get_numbers()) {
        std::cout << a << std::endl;
    }
    std::cout << "End of generator" << std::endl;
    ur.clear_nums();
};

void UniqueRng::operator()(int count) {
    int number;
    int v_len_max = upper - lower + 1;
    // generate count number of random numbers
    for (int i = 0; i < count; i++) {
        // error case has to be checked before do-while
        if (numbers.size() >= (v_len_max)) {
            const std::string err_msg =
                "Unable to produce unique random number. Tried to generate " +
                std::to_string(count) + " random numbers. Got only " +
                std::to_string(i);
            throw std::runtime_error(err_msg);
        }
        // generate numbers while vector not full and until unique number is
        // generated
        do {
            number = lower + rand() % (v_len_max);
        } while (find(numbers.begin(), numbers.end(), number) != numbers.end());
        numbers.push_back(number);
    }
    /* What if randomizing index of a vector (or array) of "free" numbers?
    * - finding free numbers is easy using sets, but:
    *       sets use sorting? (they are atleast sorted)
    *       set_difference() copies values
    * 
    * Would it ever be faster to do this kind of thing instead of spamming rand()
    * blindly until it hits?
    */
}

int main(void) {
    UniqueRng randGen(5, 13);
    test_generator(randGen, 6);
    test_generator(randGen, 9);
    test_generator(randGen, 13); // this will cause exception
    UniqueRng randGen2(1, 35);
    test_generator(randGen2, 7);
    test_generator(randGen2, 7);
    test_generator(randGen2, 7);
    test_generator(randGen2, 70); // this will cause exception
}
