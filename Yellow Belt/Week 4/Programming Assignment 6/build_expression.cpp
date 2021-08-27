#include <iostream>
#include <vector>
#include <deque>
#include <string>

using namespace std;

struct Algebraic{
    char op = 0;
    int num = 0;
};

int main() {
    int first_num;
    cin >> first_num;
    int op_number;
    cin >> op_number;

    vector<Algebraic> elems(op_number);

    for(int i = 0; i < op_number; i++){
        cin >> elems[i].op;
        cin >> elems[i].num;
    }

    deque<string> expression;
    expression.push_back(to_string(first_num));
    for(const auto& operation : elems){
        expression.push_front("(");
        expression.push_back(") ");
        expression.push_back(string(1, operation.op));
        expression.push_back(" ");
        expression.push_back(to_string(operation.num));
    }

    for(const string& s : expression){
        cout << s;
    }

    return 0;
}
