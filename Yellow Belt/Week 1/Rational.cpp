#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>

using namespace std;
int gcd (int a, int b) {
	if (b == 0)
		return a;
	else
		return gcd (b, a % b);
}

class Rational {
public:
  Rational() {
    num = 0;
    denom = 1;
  }
  Rational(int numerator, int denominator){
    if(denominator == 0){
        throw invalid_argument("Invalid argument");
    }
    d = gcd(numerator, denominator);
    num = numerator / d;
    denom = denominator / d;

    if(denom < 0){
        num*=-1;
        denom*=-1;
    }

  }

  int Numerator() const{
    return num;
  }
  int Denominator() const{
    return denom;
  }

private:
    int num;
    int denom;
    int d;
};
bool operator==(const Rational& left, const Rational& right){
    return (left.Numerator() == right.Numerator() &&
            left.Denominator() == right.Denominator());
}

Rational operator-(const Rational& lhs, const Rational& rhs){
    return (Rational(lhs.Numerator()*rhs.Denominator() - rhs.Numerator()*lhs.Denominator(),
                     lhs.Denominator()*rhs.Denominator()));
}

Rational operator+(const Rational& lhs, const Rational& rhs){
    return (Rational(lhs.Numerator()*rhs.Denominator() + rhs.Numerator()*lhs.Denominator(),
                     lhs.Denominator() * rhs.Denominator()));
}

Rational operator*(const Rational& lhs, const Rational& rhs){
    return (Rational(lhs.Numerator()*rhs.Numerator(), lhs.Denominator()*rhs.Denominator()));
}
Rational operator / (const Rational& lhs, const Rational& rhs){
    if(rhs.Numerator() == 0){
        throw domain_error( "Division by zero");
    }
    return (Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator()));
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return (((lhs-rhs).Numerator()) < 0);
}

istream& operator>>(istream& stream, Rational& r) {
	int a, b;
	char c;
	stream >> a >> c >> b;
	if (stream && c == '/')
		r = Rational(a, b);
	return stream;
}

ostream& operator<<(ostream& stream, const Rational& r) {
	return (stream << r.Numerator() << '/' << r.Denominator());
}

int main() {
    Rational a,b;
    char op;
    try {
        cin >> a >> op >> b;
        if(op == '+'){
            cout << a+b << "\n";
        } else if (op == '-'){
            cout << a-b << "\n";
        } else if (op == '*'){
            cout << a*b << "\n";
        } else {
            try {
                cout << a / b << "\n";
            } catch (domain_error& err) {
                cout << err.what() << "\n";
            }
        }
    } catch (invalid_argument& ex){
        cout << ex.what() << "\n";
    }
    return 0;
}


