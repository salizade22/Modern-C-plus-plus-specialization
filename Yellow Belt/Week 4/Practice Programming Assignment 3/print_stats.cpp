#include <vector>
#include <iostream>
#include <algorithm>

enum class Gender
{
    FEMALE,
    MALE
};

struct Person
{
    int age;
    Gender gender;
    bool is_employed;
};


template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  std::vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

void PrintStats(std::vector<Person> persons){

    auto females = partition(begin(persons), end(persons), [](const Person& p){
                                   return p.gender == Gender::FEMALE;
                                   });


    auto employed_females = partition(begin(persons), females, [](const Person& p){
                                      return p.is_employed;
                                    });
    auto employed_males = partition(females, end(persons), [](const Person& p){
                                        return p.is_employed;
                                    });
    std::cout << "Median age = "
        << ComputeMedianAge(begin(persons), end(persons)) << "\n";
    std::cout << "Median age for females = "
        << ComputeMedianAge(begin(persons), females) << "\n";
    std::cout << "Median age for males = "
        << ComputeMedianAge(females, end(persons)) << "\n";
    std::cout << "Median age for employed females = "
        << ComputeMedianAge(begin(persons), employed_females) << "\n";
    std::cout << "Median age for unemployed females = "
        << ComputeMedianAge(employed_females, females) << "\n";
    std::cout << "Median age for employed males = "
        << ComputeMedianAge(females, employed_males) << "\n";
    std::cout << "Median age for unemployed males = "
        << ComputeMedianAge(employed_males, end(persons)) << "\n";
}

int main(){
    std::vector<Person> persons =
    {
       {31, Gender::MALE, false},
       {40, Gender::FEMALE, true},
       {24, Gender::MALE, true},
       {20, Gender::FEMALE, true},
       {80, Gender::FEMALE, false},
       {78, Gender::MALE, false},
       {10, Gender::FEMALE, false},
       {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}
