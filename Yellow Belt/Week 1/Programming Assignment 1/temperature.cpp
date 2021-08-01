#include <iostream>
#include <vector>

using namespace std;


int main(){
    unsigned n = 0;
    cin >> n;

    int64_t sum = 0;
    vector<int> nums(n);
    for(size_t i = 0; i < n; i++){
        int k;
        cin >> k;
        sum += k;
        nums[i] = k;
    }

    sum = sum/static_cast<int>(n);

    vector<int> ret;

    for(size_t i = 0; i < n; i++){
        if(nums[i] > sum){
            ret.push_back(i);
        }
    }

    cout << ret.size() << endl;

    for(const auto  k : ret){
        cout << k << " ";
    }

    cout << endl;
    return 0;
}
