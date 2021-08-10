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
/*
class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
      last_names[year] = last_name;
  }
  string GetFullName(int year) {
      string firstname = GetFirstName(year, first_names);
      string lastname = GetLastName(year, last_names);
      int first_name_size = firstname.size();
      int last_name_size = lastname.size();
      if(first_name_size == 0 && last_name_size ==0){
        return "Incognito";
      } else if(first_name_size == 0){
        return (lastname + " with unknown first name");
      } else if(last_name_size == 0){
        return (firstname + " with unknown last name");
      }
      return (firstname + " " + lastname);
  }

private:
    map<int, string> first_names;
    map<int, string> last_names;
    string GetFirstName(int year, map<int, string>& first_name){
        while(first_name.count(year) == 0 && year > 0){
            year--;
        }
        string firstname = first_name[year];
        return firstname;
    }
    string GetLastName(int year, map<int, string>& last_name){
        while(last_name.count(year) == 0 && year > 0){
            year--;
        }
        string lastname = last_name[year];
        return lastname;
    }
};*/
void TestUnknownFirst(){
    Person person;

    person.ChangeLastName(2007, "Smith");
    person.ChangeFirstName(2010, "John");

    AssertEqual(person.GetFullName(2000), "Incognito");
    AssertEqual(person.GetFullName(2008), "Smith with unknown first name");
    AssertEqual(person.GetFullName(2011), "John Smith");
}

void TestUnknownLast(){
    Person person;

    person.ChangeFirstName(2007, "John");
    person.ChangeLastName(2009, "Smith");
    AssertEqual(person.GetFullName(2006), "Incognito");
    AssertEqual(person.GetFullName(2008), "John with unknown last name");
    AssertEqual(person.GetFullName(2010), "John Smith");

    person.ChangeFirstName(2012, "Peter");
    AssertEqual(person.GetFullName(2010), "John Smith");
    AssertEqual(person.GetFullName(2012), "Peter Smith");
    AssertEqual(person.GetFullName(2014), "Peter Smith");

    person.ChangeLastName(2011, "Parker");
    AssertEqual(person.GetFullName(2010), "John Smith");
    AssertEqual(person.GetFullName(2011), "John Parker");
    AssertEqual(person.GetFullName(2012), "Peter Parker");
}
int main() {
  TestRunner runner;
  runner.RunTest(TestUnknownFirst, "TestUnknownFirst");
  runner.RunTest(TestUnknownLast, "TestUnknownLast");
  return 0;
}
