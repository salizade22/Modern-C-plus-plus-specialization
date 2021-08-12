#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void PrintVectorPart(const vector<int>& numbers){
    auto negative_it = find_if(
        begin(numbers), end(numbers),
        [](int number){
            return number < 0;
            }
            );
    for(auto it = negative_it; it!=numbers.begin(); ){
        it--;
        cout << *it << " ";

    }
}

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  return 0;
}
