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

    auto mid = begin(elems) + range_length / 2;

    MergeSort(begin(elems), mid);
    MergeSort(mid, end(elems));

    merge(begin(elems), mid, mid, end(elems), range_begin);
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
