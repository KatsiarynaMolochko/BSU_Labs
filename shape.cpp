#include "shape.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <iostream>

int binpow (int a, int n) {
    if (n == 0)
        return 1;
    if (n % 2 == 1)
        return binpow (a, n-1) * a;
    else {
        int b = binpow (a, n/2);
        return b * b;
    }
}

Polygon::Polygon(const std::initializer_list<std::pair<int, int> >& l) {
    if (l.end() - l.begin() < 3) {
        throw std::out_of_range ("In two-dimensional space, at least three points are needed to construct the shape.");
    }
    for (const auto& point: l) {
        points.push_back({point.first, point.second});
    }
    CalcSides();
    CalcAngles();
    sort(sides.begin(),sides.end());
}

Polygon::Polygon(const Polygon& obj) {
    points = obj.points;
    sides = obj.sides;
}

double Polygon::Area() {
    double res = 0;
    for (int i=0; i<points.size(); i++) {
        Point p1 = i ? points[i-1] : points.back();
        Point p2 = points[i];
        res += (p1.x - p2.x) * (p1.y + p2.y);
    }
    return fabs (res) / 2.;
}

double Polygon::CalcPerimeter() {
    double res = 0;
    for (const auto& side : sides) {
        res += side;
    }
    return res;
}

bool Polygon::IsRegular() {
    for (int i = 1; i < sides.size(); ++i) {
        if (sides[0] != sides[i]) {
            return false;
        }
    }
    return true;
}

void Polygon::CalcSides() {
    double side;
    for (int i = 1; i < points.size(); ++i) {
        side = sqrt(binpow(points[i-1].x - points[i].x,2) + binpow((points[i-1].y) - points[i].y,2));
        sides.push_back(side);
    }
    side = sqrt(binpow(points[points.size() - 1].x - points[0].x,2) + binpow((points[points.size() - 1].y) - points[0].y,2));
    sides.push_back(side);
}

void Polygon::CalcAngles() {
    double angle = 0;
    for (int i = 2; i < points.size(); ++i) {
        angle = CalcAngle(points[i-2], points[i-1], points[i]);
        angles.push_back(angle);
    }
    angle = CalcAngle(points[points.size()-1],points[0], points[1]);
    angles.push_back(angle);
}


double Polygon::CalcAngle(Point p1, Point p2, Point p3) {
    double sq_side1 = binpow(p1.x - p2.x,2) + binpow(p1.y - p2.y,2);
    double sq_side2 = binpow(p3.x - p2.x,2) + binpow(p3.y - p2.y,2);
    double sq_side3 = binpow(p3.x - p1.x,2) + binpow(p3.y - p1.y,2);
    double angle = acos((sq_side1 + sq_side2 - sq_side3) / 2 * sq_side2 * sq_side1);
    return angle;
}

bool Polygon::IsConvex() {
    return true;
}


void Triangle::DoesExist() const {
    if (!(((side2 + side3 - side1) > 0) && ((side1 + side3 - side2) > 0) && ((side1 + side2 - side3) > 0))) {
        throw std::runtime_error("Triangle doesn't exist");
    }
}

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
    : Polygon({{x1, y1},{x2, y2},{x3, y3}}) {
    side1 = sides[0];
    side2 = sides[1];
    side3 = sides[2];
    DoesExist();
}


Triangle::Triangle(const std::initializer_list<std::pair<int, int> >& l) : Polygon(l) {
    if (l.end() - l.begin() != 3) {
        throw std::runtime_error("Triangle must be 3 sides only");
    }
    side1 = sides[0];
    side2 = sides[1];
    side3 = sides[2];
    DoesExist();
}

bool Triangle::IsRight() {
    return binpow(sides[0],2) + binpow(sides[1],2) == binpow(sides[3],2);

}

bool Triangle::IsOxygon() {
    return binpow(sides[0],2) + binpow(sides[1],2) > binpow(sides[3],2);
}

bool Triangle::IsObtuse() {
    if(!IsOxygon() && !IsRight()) {
        return true;
    }
    return false;
}

void Triangle::CheckType() {
    if(IsRight()) {
        std::cout << "This triangle is right";
    } else if (IsOxygon()) {
        std::cout << "This triangle is oxygon";
        } else {
        std::cout << "This triangle is obtuse";
    }
}

double Triangle::InscribedArea() {
    double p = CalcPerimeter()/ 2;
    return M_PI * pow((p - sides[0]) * tan(angles[1]/2),2);
}

double Triangle::DescribedArea() const {
    return M_PI * pow((sides[0] / (2 * sin(angles[1]))), 2);
}

Circle::Circle(double r) : r(r) { }

double Circle::Area() {
    return M_PI * r * r;
}

double Circle::CalcPerimeter() {
    return 2 * M_PI * r;
}

Circle::Circle(const Circle &obj) {
    r = obj.r;
}

Square::Square(double side) : side(side) { }

double Square::CalcPerimeter() {
    return 4 * side;
}

double Square::Area() {
    return side * side;
}

Square::Square(const Square& obj) {
    side = obj.side;
}

double Square::DescribedArea() const {
    return M_PI * 0.5 * side * side;
}

double Square::InscribedArea() const{
    return M_PI * side/2. * side/2.;
}


