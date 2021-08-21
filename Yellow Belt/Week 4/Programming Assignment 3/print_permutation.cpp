#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;


int main() {
  int limit;
  cin >> limit;
  vector<int> permutation(limit);
  iota(begin(permutation), end(permutation), 1);
  reverse(begin(permutation), end(permutation));

  do{
    for(int num : permutation){
        cout << num << " ";
    }
    cout << endl;
  } while(prev_permutation(begin(permutation), end(permutation)));
  return 0;
}
