#include <iostream>
#include <exception>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;


class Matrix {
private:
    int num_rows;
    int num_cols;
    vector<vector<int>> values;

public:
    Matrix() {
        num_rows = 0;
        num_cols = 0;
    }

    Matrix(int num_row, int num_col){
        Reset(num_row, num_col);
    }

    void Reset(int num_row, int num_col){
        if(num_row < 0){
            throw out_of_range("Number of rows must be >= 0");
        }
        if(num_col < 0){
            throw out_of_range("Number of columns must be >= 0");
        }
        if(num_col == 0 || num_row == 0){
            num_row = 0;
            num_col = 0;
        }

        num_rows = num_row;
        num_cols = num_col;
        values.assign(num_row, vector<int>(num_col));
    }

    int At(int num_row, int num_col) const{
        return values.at(num_row).at(num_col);
    }

    int& At(int num_row, int num_col) {
        return values.at(num_row).at(num_col);
    }

    int GetNumRows() const{
        return num_rows;
    }

    int GetNumColumns() const{
        return num_cols;
    }

};

bool operator==(const Matrix& a,const Matrix& b){
    int a_rows = a.GetNumRows();
    int a_cols = a.GetNumColumns();
    int b_rows = b.GetNumRows();
    int b_cols = b.GetNumColumns();

    if(a_rows != b_rows || a_cols != b_cols){
        return false;
    } else{
        for(int i = 0; i < a_rows; i++){
            for(int j = 0; j < a_cols; j++){
                if(a.At(i,j) != b.At(i,j)){
                    return false;
                }
            }
        }
    }

    return true;
}

Matrix operator+(const Matrix& first, const Matrix& second){
    int first_rows = first.GetNumRows();
    int first_cols = first.GetNumColumns();
    int second_rows = second.GetNumRows();
    int second_cols = second.GetNumColumns();

    if(first_rows != second_rows){
        throw invalid_argument("Mismatched number of rows");
    }
    if(first_cols != second_cols){
            throw invalid_argument("Mismatched number of columns");
    }

    Matrix res(first_rows, first_cols);

    for(int row = 0; row < first_rows; row++){
        for(int column = 0; column < first_cols; column++){
            res.At(row,column) = first.At(row,column) + second.At(row, column);
        }
    }
    return res;
}
istream& operator>>(istream& in, Matrix& matrix){
    int num_rows, num_cols;
    in >> num_rows >> num_cols;

    matrix.Reset(num_rows, num_cols);
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            in >> matrix.At(i,j);
        }
    }

    return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix){
    int num_rows = matrix.GetNumRows();
    int num_cols = matrix.GetNumColumns();

    out << num_rows << " " << num_cols << endl;
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            if(j > 0){
                out << " ";
            }
            out << matrix.At(i, j);
        }
        out << endl;
    }

    return out;
}

int main(){
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}
