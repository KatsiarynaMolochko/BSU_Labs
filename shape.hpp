#ifndef X1_SHAPE_HPP
#define X1_SHAPE_HPP
#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>


struct Point {
    int x, y;
};


class Shape {
public:
    virtual double Area() = 0;
    virtual double CalcPerimeter() = 0;
};

class Polygon : public Shape {
protected:
    std::vector<Point> points;
    std::vector<double> sides;
    std::vector<double> angles;
    void CalcSides();
    double CalcAngle(Point, Point, Point);
    void CalcAngles();

public:
    Polygon() = delete;
    Polygon(const std::initializer_list<std::pair<int, int> >&);
    Polygon(const Polygon&);

    bool IsRegular();
    bool IsConvex();
    double Area() override;
    double CalcPerimeter() override;
};

class Triangle : public Polygon {
private:
    double side1;
    double side2;
    double side3;
    void DoesExist() const;

public:
    Triangle() = delete;
    Triangle (int, int, int, int, int, int);
    Triangle (const std::initializer_list<std::pair<int, int> >&);
    bool IsRight();
    bool IsOxygon();
    bool IsObtuse();
    void CheckType();
    double InscribedArea(); // площадь круга, вписанного в треугольник
    double DescribedArea() const; // площадь круга, описанного около треугольника
};

class Circle : public Shape {
private:
    double r;

public:
    Circle() = delete;
    Circle(const Circle&);
    explicit Circle(double);

    double Area() override;
    double CalcPerimeter() override;
};

class Square : public Shape {
private:
    double side;

public:
    Square() = delete;
    explicit Square(double);
    Square(const Square&);

    double CalcPerimeter() override;
    double Area() override;
    double DescribedArea() const; // площадь круга описанного около квадрата
    double InscribedArea() const; // площадь круга вписанного в квадрат
};
#endif //X1_SHAPE_HPP
