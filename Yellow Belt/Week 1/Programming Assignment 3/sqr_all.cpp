#include <iostream>
#include <map>
#include <vector>
using namespace std;

template<typename T>
T Sqr(T element);

template<typename T>
vector<T> Sqr(const vector<T>& vi);

template<typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m);

template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p);

template <typename T>
T Sqr(T element){
    return element * element;
}

template <typename T>
vector<T> Sqr(const vector<T>& vi){
    vector<T> res;

    for(const T& i : vi){
        res.push_back(Sqr(i));
    }
    return res;
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key,Value>& m){
    map<Key,Value> res;

    for(auto& item : m){
        res[item.first] = Sqr(item.second);
    }
    return res;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p){
    return {Sqr(p.first), Sqr(p.second)};
}

int main(){
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}


