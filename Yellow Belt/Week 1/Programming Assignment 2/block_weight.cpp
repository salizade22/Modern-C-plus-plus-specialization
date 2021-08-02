#include <iostream>
#include <cstdint>

using namespace std;


int main(){
    int n = 0, density = 0;
    cin >> n >> density;


    uint64_t res = 0;

    for(int i = 0; i < n; ++i){
        int width = 0, height = 0, length = 0;
        cin >> width >> height >> length;
        res += static_cast<uint64_t>(width) * height * length;
    }

    res *= density;
    cout << res << endl;
    return 0;
}
