#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

/*int gcd (int a, int b) {
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
*/
void TestDefault(){
    Rational num;
    AssertEqual(num.Numerator(), 0);
    AssertEqual(num.Denominator(), 1);
}

void TestReduction(){
    AssertEqual(Rational(34,35).Numerator(), 34);
    AssertEqual(Rational(34,35).Denominator(), 35);
    AssertEqual(Rational(8,64).Numerator(), 1);
    AssertEqual(Rational(8,64).Denominator(), 8);
    AssertEqual(Rational(6,21).Numerator(), 2);
    AssertEqual(Rational(6,21).Denominator(), 7);
}

void TestNegative(){
    AssertEqual(Rational(2, -3).Numerator(), -2);
    AssertEqual(Rational(2, -3).Denominator(), 3);
    AssertEqual(Rational(8, -64).Numerator(), -1);
    AssertEqual(Rational(8, -64).Denominator(), 8);
}

void TestPositive(){
    AssertEqual(Rational(-2, -3).Numerator(), 2);
    AssertEqual(Rational(-2, -3).Denominator(), 3);
    AssertEqual(Rational(-4, -6).Numerator(), 2);
    AssertEqual(Rational(-4, -6).Denominator(), 3);
}

void TestZeroNumerator(){
    AssertEqual(Rational(0, -3).Numerator(), 0);
    AssertEqual(Rational(0, -3).Denominator(), 1);
}

int main() {
  TestRunner runner;
  runner.RunTest(TestDefault, "TestDeafult");
  runner.RunTest(TestNegative, "TestNegative");
  runner.RunTest(TestPositive, "TestPositive");
  runner.RunTest(TestReduction, "TestReduction");
  runner.RunTest(TestZeroNumerator, "TestZeroNumerator");
  return 0;
}
