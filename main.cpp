#include <iostream>
#include <stdexcept>
#include <exception>
#include <type_traits>
#include <vector>
#include <cmath>

using namespace std;


template<class T> class Matrix;
template<class T> Matrix<T> operator-(const Matrix<T>& other);
template<class T> Matrix<T> operator*(const T& number, const Matrix<T>& matrix);
template<class T> Matrix<T> operator*(const Matrix<T>& matrix, const T& number);
template<class T> Matrix<T> operator+(const Matrix<T>& left, const Matrix<T>& right);
template<class T> Matrix<T> operator-(const Matrix<T>& left, const Matrix<T>& right);
template<class T> Matrix<T> operator*(const Matrix<T>& left, const Matrix<T>& right);
template<class T> ostream& operator<<(ostream& out, const Matrix<T>& matrix);

template <class T>
class Matrix {
public:
    Matrix() = delete;
    Matrix(int rows, int columns);
    Matrix(const Matrix& other);
    ~Matrix();
    Matrix<T>& operator=(const Matrix<T>& other);

    T* operator[](int index);
    const T* operator[](int index) const;

    friend Matrix<T> operator- <>(const Matrix<T>& other);

    Matrix<T>& operator+=(const Matrix<T>& other);
    Matrix<T>& operator-=(const Matrix<T>& other);
    Matrix<T>& operator*=(const Matrix<T>& other);
    Matrix<T>& operator*=(const T& number);

    friend bool operator==(const Matrix<T>& left, const Matrix<T>& right);
    friend bool operator!=(const Matrix<T>& left, const Matrix<T>& right);

    friend Matrix<T> operator* <>(const T& number, const Matrix<T>& matrix);
    friend Matrix<T> operator* <>(const Matrix<T>& matrix, const T& number);
    friend Matrix<T> operator+ <>(const Matrix<T>& left, const Matrix<T>& right);
    friend Matrix<T> operator- <>(const Matrix<T>& left, const Matrix<T>& right);
    friend Matrix<T> operator* <>(const Matrix<T>& left, const Matrix<T>& right);
    friend ostream& operator<< <>(ostream& out, const Matrix<T>& matrix);

    [[nodiscard]] int Rows() const;
    [[nodiscard]] int Columns() const;

    [[nodiscard]] Matrix<T> Transpose() const;

    void SetValue(int row, int column, T value);
    void Show();
    void InputMatrix();

    T Determinant();
    static T Determinant(const Matrix& matrix, int n);

    static Matrix<T> Identity(int size);

private:
    T** matrix;
    int rows{}, columns{};
};

template <class T>
Matrix<T>::Matrix(int rows, int columns) {
    if constexpr (std::is_same<T, std::string>::value) {
        throw std::runtime_error("string cannot be a matrix type");
    }

    this->columns = columns;
    this->rows = rows;
    matrix = new T* [rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new T [columns];
    }

    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = 0;
        }
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &other) {
    rows = other.rows;
    columns = other.rows;
    matrix = new T* [rows];

    for (int i = 0; i < rows; ++i) {
        matrix[i] = new T [columns];
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = other[i][j];
        }
    }
}

template <class T>
Matrix<T>::~Matrix() {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

template <class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other) {
    if(this == &other) {
        return *this;
    }

    if (rows != other.rows || columns != other.rows) {
        for (int i = 0; i < other.rows; ++i) {
            delete[] matrix[i];
        }

        delete[] matrix;

        rows = other.rows;
        columns = other.columns;
        matrix = new T*[rows];

        for (int i = 0; i < rows; ++i) {
            matrix[i] = new T[columns];
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = other.matrix[i][j];
        }
    }

    return *this;
}

template <class T>
const T *Matrix<T>::operator[](int index) const {
    if(index < 0 || index > rows || index > columns) {
        throw std::out_of_range("out of range");
    }

    return matrix[index];
}

template <class T>
Matrix<T> operator-(const Matrix<T> &other) {
    Matrix<T> result(other.rows, other.columns);

    for (int i = 0; i < other.rows; ++i) {
        for (int j = 0; j < other.columns; ++j) {
            result.matrix[i][j] = (-1)*other.matrix[i][j];
        }
    }

    return result;
}

template <class T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &other) {
    if (rows != other.rows || columns != other.columns) {
        throw std::out_of_range("out of range");
    }

    for (int i = 0; i < other.rows; ++i) {
        for (int j = 0; j < other.columns; ++j) {
            matrix[i][j] += other.matrix[i][j];
        }
    }

    return *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &other) {
    if (rows != other.rows || columns != other.columns) {
        throw std::out_of_range("out of range");
    }

    for (int i = 0; i < other.rows; ++i) {
        for (int j = 0; j < other.columns; ++j) {
            matrix[i][j] -= other.matrix[i][j];
        }
    }

    return *this;
}

template <class T>
Matrix<T> operator+(const Matrix<T> &left, const Matrix<T> &right) {
    if (left.rows != right.rows || left.columns != right.columns) {
        throw std::out_of_range("out of range");
    }

    Matrix<T> result(right.rows, right.columns);

    for (int i = 0; i < right.rows; ++i) {
        for (int j = 0; j < right.columns; ++j) {
            result.matrix[i][j] = right[i][j] + left[i][j];
        }
    }

    return result;
}

template <class T>
void Matrix<T>::InputMatrix() {
    cout << endl << "Input matrix with size: " << rows << 'x' << columns << endl;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cin >> matrix[i][j];
        }
    }
}

template <class T>
void Matrix<T>::Show() {
    for (int i = 0; i < rows; ++i) {
        cout << endl;
        for (int j = 0; j < columns; ++j) {
            cout << matrix[i][j] << ' ';
        }
    }

    cout << endl;
}

template <class T>
Matrix<T> operator-(const Matrix<T> &left, const Matrix<T> &right) {
    if (left.rows != right.rows || left.columns != right.columns) {
        throw std::out_of_range("out of range");
    }

    Matrix<T> result(right.rows, right.columns);

    for (int i = 0; i < right.rows; ++i) {
        for (int j = 0; j < right.columns; ++j) {
            result.matrix[i][j] = right[i][j] - left[i][j];
        }
    }

    return result ;
}

template <class T>
Matrix<T> operator*(const Matrix<T> &left, const Matrix<T> &right) {
    if (left.columns != right.rows ) {
        throw std::out_of_range("out of range");
    }

    Matrix<T> result(left.rows, right.columns);

    for (int i = 0; i < left.rows; ++i) {
        for (int j = 0; j < right.columns; ++j) {
            for (int k = 0; k < left.columns; ++k) {
                result.matrix[i][j] += (left[i][k] * right[k][j]);
            }
        }
    }

    return result;
}

template <class T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &other) {
    Matrix<T> result = *this * other;
    *this = result;
    return *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator*=(const T &number) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; i < columns; ++i) {
            matrix[i][j] *= number;
        }
    }

    return *this;
}

template <class T>
Matrix<T> operator*(const T &number, const Matrix<T> &matrix) {
    return (matrix * number);
}

template <class T>
Matrix<T> operator*(const Matrix<T> &matrix, const T &number) {
    Matrix<T> result(matrix.rows, matrix.columns);
    return (result *= number);
}

template <class T>
Matrix<T> Matrix<T>::Identity(int size) {
    Matrix<T> identity(size, size);

    for (int i = 0; i < size; ++i) {
        identity[i][i] = 1;
    }

    return identity;
}

template <class T>
Matrix<T> Matrix<T>::Transpose() const {
    Matrix<T> transposed(columns, rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            transposed.matrix[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

template <class T>
int Matrix<T>::Rows() const {
    return rows;
}

template <class T>
int Matrix<T>::Columns() const {
    return columns;
}

template <class T>
bool operator==(const Matrix<T> &left, const Matrix<T> &right) {
    if (left.columns != right.columns || left.rows != right.rows){
        throw std::out_of_range("out of range");
    }

    for (int i = 0; i < left.rows; ++i) {
        for (int j = 0; j < left.columns; ++j) {
            if (left[i][j] != right[i][j]){
                return false;
            }
        }
    }

    return true;
}

template <class T>
bool operator!=(const Matrix<T> &left, const Matrix<T> &right) {
    for (int i = 0; i < left.rows; ++i) {
        for (int j = 0; j < left.columns; ++j) {
            if (left[i][j] != right[i][j])
                return true;
        }
    }

    return false;
}

template <class T>
T* Matrix<T>::operator[](int index) {
    if (index < 0 || index > rows || index > columns) {
        throw std::out_of_range("out of range");
    }

    return matrix[index];
}

template<class T>
ostream& operator<<(ostream& out, const Matrix<T>& matrix) {
    for (int i = 0; i < matrix.Rows(); ++i) {
        for (int j = 0; j < matrix.Columns(); ++j) {
            out << matrix[i][j] << " ";
        }
        out << "\n";
    }

    return out;
}

template<class T>
void Matrix<T>::SetValue(int row, int column, T value) {
    matrix[row][column] = value;
}

template<class T>
T Matrix<T>::Determinant() {
    return Matrix<T>::Determinant(*this, rows);
}

template<class T>
T Matrix<T>::Determinant(const Matrix &matrix, int n) {
    if (matrix.rows != matrix.columns) {
        throw std::runtime_error("matrix must have rows == columns");
    }

    int det = 0;
    Matrix<T> submatrix(n, n);

    if (n == 2) {
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    }
    else {
        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x)
                        continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            det = det + (pow(-1, x) * matrix[0][x] * Determinant(submatrix, n - 1 ));
        }
    }

    return det;
}

template<class T>
T FindMin(const Matrix<T> &obj) {
    T min = std::numeric_limits<T>::max();

    for (int i = 0; i < obj.Rows(); ++i) {
        for (int j = 0; j < obj.Columns(); ++j) {
            if (min > obj[i][j]) {
                min = obj[i][j];
            }
        }
    }

    return min;
}

template<class T>
Matrix<T> Apply(Matrix<T> &obj, T (*f)(T)){
    for (int i = 0; i < obj.Rows(); ++i) {
        for (int j = 0; j < obj.Columns(); ++j) {
            obj[i][j] = (*f)(obj[i][j]);
        }
    }

    return obj;
}

template<class T>
std::vector<T> RowWiseApply(const Matrix<T>& obj, T (*f)(const T*, int)) {
    int n = obj.Columns();
    std::vector<T> ans(n);

    for(int i = 0; i < obj.Rows(); ++i) {
        ans[i] = ((*f)(obj[i], n));
    }

    return ans;
}

double Square(double x) {
    return x * x;
}

double MakeNotNegative(double x) {
    if (x < 0) {
        return 0;
    } else {
        return x;
    }
}

double RowMin(const double* row, int n) {
    double min = std::numeric_limits<double>::max();

    for (int i = 0; i < n; ++i) {
        if (min > row[i]) {
            min = row[i];
        }
    }

    return min;
}

double RowMax(const double* row, int n) {
    double max = std::numeric_limits<double>::min();

    for (int i = 0; i < n; ++i) {
        if (max < row[i]) {
            max = row[i];
        }
    }

    return max;
}

int main() {
//    Matrix<int> obj(4, 8);
//    Matrix<int> obj2 (5,7);
//    Matrix<int> obj3(2,3);
//    Matrix<int> obj4(3,5);
//    Matrix<int> obj7(5,5);
//
//    obj3.InputMatrix();
//    obj4.InputMatrix();
//
//    Matrix<int> obj5 = obj3 * obj4;
//    obj5.Show();
//    obj.Transpose();
//    obj.Rows();
//    obj5.Columns();
//    Matrix<int>::Identity(5);
//
//
//    std::cout << "\n" << FindMin(obj5) << "\n";

    Matrix<double> matrix = Matrix<double>::Identity(2);
    matrix[0][1] = -2;
    matrix[1][0] = -3;

    Matrix<double> copy(matrix);

    std::cout << std::endl << FindMin(matrix) << std::endl;
    std::cout << Apply(matrix, Square) << std::endl;
    std::cout << Apply(copy, MakeNotNegative) << std::endl;

    std::cout << "determinant is: " << matrix.Determinant() << std::endl;


    auto ans1 = RowWiseApply(matrix, RowMin);
    auto ans2 = RowWiseApply(matrix, RowMax);

    for (const auto& x: ans1) {
        std::cout << x << " ";
    }

    std::cout << std::endl;

    for (const auto& x: ans2) {
        std::cout <<  x << " ";
    }

//    try {
//        obj[-5][-10];
//    }
//    catch (const std::out_of_range& error) {
//        cout << endl;
//        cerr << "ERROR: Index can't be a negative number." << error.what() << endl;
//    }
//    try {
//       obj2*=obj;
//       obj2*obj;
//    }
//    catch (const std::out_of_range& error) {
//        cout << endl;
//        cerr << "ERROR: Matrices of this size cannot be multiplied. " << error.what() << endl;
//    }
//    try {
//        obj - obj2;
//        obj -= obj;
//        obj2 + obj;
//        obj += obj2;
//    }
//    catch (const std::out_of_range& error) {
//        cout << endl;
//        cerr << "ERROR: Matrices have different sizes" << error.what() << endl;
//    }

    return 0;
}
