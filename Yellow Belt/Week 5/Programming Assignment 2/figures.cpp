#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <cmath>

using namespace std;

class Figure{
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const =0;
    virtual double Area() const = 0;
};

class Triangle : public Figure{
public:
    Triangle(int a, int b, int c) : a_(a), b_(b), c_(c){}
    string Name() const override{
        return "TRIANGLE";
    }
    double Perimeter() const override{
        return a_ + b_ + c_;
    }

    double Area() const override{
        double u = Perimeter() / 2.0;
        return sqrt(u * (u - a_) * (u - b_) * (u - c_));
    }

private:
    int a_, b_, c_;
};

class Rect : public Figure {
public:
    Rect(int width, int height) : width_(width), height_(height){}

    string Name() const override{
        return "RECT";
    }

    double Perimeter() const override{
        return 2*(width_ + height_);
    }

    double Area() const override{
        return width_ * height_;
    }

private:
    int width_, height_;

} ;

class Circle : public Figure{
public:
    Circle(int radius) : radius_(radius){}

    string Name() const override{
        return "CIRCLE";
    }

    double Perimeter() const override{
        return 2 * p * radius_;
    }

    double Area() const override {
        return p * radius_ * radius_;
    }

private:
    double p = 3.14;
    int radius_;
};

shared_ptr<Figure> CreateFigure(istream& in){
    string fig;
    in >> fig;
    if(fig == "TRIANGLE"){
        int a,b,c;
        in >> a >> b >> c;
        return make_shared<Triangle>(a,b,c);
    } else if( fig == "RECT") {
        int width, height;
        in >> width >> height;
        return make_shared<Rect>(width, height);
    } else {
        int radius;
        in >> radius;
        return make_shared<Circle>(radius);
    }
}
int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
