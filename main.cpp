#include <iostream>
#include "shape.hpp"
#include <cmath>
#include <string>
#include <stdexcept>

void CheckEqual(double left, double right) {
    if (fabs(left - right) > 1e-6) {
        throw std::runtime_error("Wrong answer: " + std::to_string(left));
    }
}

int main() {
    Triangle* triangle = new Triangle({{0, 0}, {0, 1}, {1, 0}});
    Polygon* polygon = new Polygon({{0, 0}, {0, 1}, {1, 1}, {1, 0}});

    {  // inheritance test
        static_cast<Shape*>(new Square(5));
        static_cast<Shape*>(new Circle(5));
        static_cast<Shape*>(polygon);
        static_cast<Shape*>(triangle);
        static_cast<Polygon*>(triangle);
    }

    {  // area test
        CheckEqual(Square(2.5).Area(), 6.25);
        CheckEqual(Circle(1).Area(), acos(-1.0));
        CheckEqual(triangle->Area(), 0.5);
        CheckEqual(polygon->Area(), 1.0);
    }

    {  // CalcPerimeter// test
        CheckEqual(Square(1.5).CalcPerimeter(), 6);
        CheckEqual(Circle(2).CalcPerimeter(), 4 * acos(-1.0));
        CheckEqual(triangle->CalcPerimeter(), 2 + sqrt(2));
        CheckEqual(polygon->CalcPerimeter(), 4);
    }

    {  // test that triangle throws exception in case of wrong number of vertices
        try {
            try {
                Triangle({{0, 0}, {0, 1}});
            } catch (...) {
                throw std::runtime_error("Error in creating triangle");
            }
            throw "No exception for triangle";
        } catch (const std::runtime_error&) {

        }
    }

    std::cout << Square(4).DescribedArea() << "\n";
    std::cout << Square(7).InscribedArea() << "\n";

    std::cout << triangle->InscribedArea() << "\n";
    std::cout << triangle->DescribedArea() << "\n";
    std::cout << triangle->IsObtuse() << "\n";
    std::cout << triangle->IsOxygon() << "\n";
    std::cout << triangle->IsRight() << "\n";
    std::cout << triangle->IsConvex() << "\n";
    std::cout << triangle->IsRegular() << "\n";

    std::cout << polygon->CalcPerimeter() << "\n";
    std::cout << polygon->IsRegular() << "\n";
    std::cout << polygon->IsConvex() << "\n";
    std::cout << polygon->Area() << "\n";

    delete polygon;
    delete triangle;

    return 0;
}
