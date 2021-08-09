#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <string>
#include <random>;

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

int GetDistinctRealRootCount(double a, double b, double c) {
  if(a == 0){
    if(b != 0){
        return 1;
    }
  }
  double d = b*b - 4*a*c;
  if (d > 0){
    double x1 = (-b + sqrt(d))/(2*a);
    double x2 = (-b - sqrt(d))/(2*a);
    return 2;
  } else if (d == 0){
    return 1;
  }
  return 0;
}
void test_single_root(){
    mt19937 key;
    uniform_real_distribution<> unif(-20,20);

    for(auto i = 0; i < 100; i++){
        const auto x1 = unif(key);
        const auto p = x1*2;
        const auto q = x1*x1;

        const auto cnt = GetDistinctRealRootCount(1,p,q);
        stringstream description;
        description << showpos << "x^2" << p << "x" << q
        << " = 0 has 1 real root.";

        AssertEqual(cnt, 1, description.str());
    }
}

void test_max_two_roots(){
        mt19937 key;
        uniform_real_distribution<> unif(-20, 20);
        for(auto i = 0; i < 100; i++){
            const auto a = unif(key);
            const auto b = unif(key);
            const auto c = unif(key);
            const auto cnt = GetDistinctRealRootCount(a,b,c);

            Assert(cnt >= 0 && cnt <=2, "Quadratic equation has minimum 0 and maximum 2 roots");
        }
}

void test_no_roots(){
    AssertEqual(GetDistinctRealRootCount(1,0,1), 0, "no roots assertion 1");
    AssertEqual(GetDistinctRealRootCount(2,4,5), 0, "no roots assertion 2");
    AssertEqual(GetDistinctRealRootCount(3,-3,2), 0, "no roots assertion 3");
}

void test_linear_equation(){
    AssertEqual(GetDistinctRealRootCount(0,5,1), 1, "linear equation assertion 1");
    AssertEqual(GetDistinctRealRootCount(0,6,5), 1, "linear equation assertion 2");
    AssertEqual(GetDistinctRealRootCount(0,3,2), 1, "linear equation assertion 3");
}
void test_constant(){
    AssertEqual(GetDistinctRealRootCount(0, 0, 10), 0, "10 = 0, has no roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, -100), 0, "-100 = 0, has no roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, 25), 0, "25 = 0, has no roots");

}
int main() {
  TestRunner runner;
  runner.RunTest(test_linear_equation, "testing linear equation");
  runner.RunTest(test_no_roots, "testing no roots");
  runner.RunTest(test_single_root, "testing single root (i.e discriminant = 0)");
  runner.RunTest(test_max_two_roots, "testing max two roots");
  runner.RunTest(test_constant, "testing constant");
  return 0;
}
