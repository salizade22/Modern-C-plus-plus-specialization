#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
    int range_length = range_end - range_begin;
    if(range_length < 2){
        return;
    }

    std::vector<typename RandomIt::value_type> elems(range_begin, range_end);

    auto first_third = begin(elems) + range_length / 3;
    auto second_third = begin(elems) + range_length * 2 / 3;

    MergeSort(begin(elems), first_third);
    MergeSort(first_third, second_third);
    MergeSort(second_third, end(elems));

    std::vector<typename RandomIt::value_type> temp;
    merge(begin(elems), first_third, first_third, second_third, back_inserter(temp));
    merge(begin(temp), end(temp), second_third, end(elems), range_begin);
}

int main() {
  std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
  return 0;
}
