#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <vector>
#include <iostream>
#include <string>

// To compile c++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) example.cpp -o example$(python3-config --extension-suffix)

// need to make our own struct that acts as an array in order to create the overload 

int addInt(int i, int j) {
    return i + j;
}

int subtractInt(int i, int j) {
    return i - j;
}

int multiplyInt(int i, int j) {
    return i * j;
}

std::vector<std::vector<int>> addMatrixMatrix(std::vector<std::vector<int>> m1, std::vector<std::vector<int>> m2) {
    std::vector<std::vector<int>> m3 = {};
    if (m1.size() != m2.size()) {
        throw std::invalid_argument("Size of Matrix #1 and Matrix #2 must be the same!");
    }
    for (size_t x = 0; x < m1.size(); x++) {
        if (m1[x].size() != m2[x].size()) {
            throw std::invalid_argument("Size of Matrix #1 and Matrix #2 must be the same!");
        }
        std::vector<int> tmp = {};
        for (size_t y = 0; y < m1[x].size(); y++) {
            tmp.push_back(m1[x][y] + m2[x][y]);
        }
        m3.push_back(tmp);
    }
    return m3;
}

std::vector<std::vector<int>> subtractMatrixMatrix(std::vector<std::vector<int>> m1, std::vector<std::vector<int>> m2) {
    std::vector<std::vector<int>> m3 = {};
    if (m1.size() != m2.size()) {
        throw std::invalid_argument("Size of Matrix #1 and Matrix #2 must be the same!");
    }
    for (size_t x = 0; x < m1.size(); x++) {
        if (m1[x].size() != m2[x].size()) {
            throw std::invalid_argument("Size of Matrix #1 and Matrix #2 must be the same!");
        }
        std::vector<int> tmp = {};
        for (size_t y = 0; y < m1[x].size(); y++) {
            tmp.push_back(m1[x][y] - m2[x][y]);
        }
        m3.push_back(tmp);
    }
    return m3;
}

std::vector<std::vector<int>> multiplyMatrixMatrix(std::vector<std::vector<int>> m1, std::vector<std::vector<int>> m2) {
    std::vector<std::vector<int>> m3 = {};
    for (size_t m1_row = 0; m1_row < m1.size(); m1_row++) {
        if (m1[m1_row].size() != m2.size()) {
            throw std::invalid_argument("Length of each row in matrix #1 must equal length of each column in matrix #2!");
        }
        std::vector<int> tmp = {};
        for (size_t m2_col = 0; m2_col < m2[0].size(); m2_col++) {
            int acc = 0;
            for (size_t idx = 0; idx < m1[m1_row].size(); idx++) {
                if (m1.size() != m2[idx].size()) {
                    throw std::invalid_argument("Length of each column in matrix #1 must equal length of each row in matrix #2!");
                }
                acc += m1[m1_row][idx] * m2[idx][m2_col];
            }
            tmp.push_back(acc);
        }
        m3.push_back(tmp);
    }
    return m3;
}

std::vector<std::vector<int>> multiplyVectorMatrix(std::vector<int> arr, std::vector<std::vector<int>> mat) {
    std::vector<std::vector<int>> mat_b = {};
    for (size_t i = 0; i < mat.size(); i++) {
        if (arr.size() != mat[i].size()) {
            throw std::invalid_argument("Length of all rows in the matrix must == legnth of the vector!");
        }

        mat_b.push_back({});
        for (size_t j = 0; j < mat[i].size(); j++) {
            mat_b[i].push_back(arr[j] * mat[i][j]);
        }
    }
    return mat_b;
}

std::vector<int> addVectorVector(std::vector<int> arr_x, std::vector<int> arr_y) {
    if (arr_x.size() != arr_y.size()){
        throw std::invalid_argument("Length of vectors must the same!");
    }

    std::vector<int> arr_z = {};
    for (size_t i = 0; i < arr_x.size(); i++) {
        arr_z.push_back(arr_x[i] + arr_y[i]);
    }
    return arr_z;
}

std::vector<int> subtractVectorVector(std::vector<int> arr_x, std::vector<int> arr_y) {
    if (arr_x.size() != arr_y.size()){
        throw std::invalid_argument("Length of vectors must the same!");
    }

    std::vector<int> arr_z = {};
    for (size_t i = 0; i < arr_x.size(); i++) {
        arr_z.push_back(arr_x[i] - arr_y[i]);
    }
    return arr_z;
}

std::vector<int> multiplyVectorVector(std::vector<int> arr_x, std::vector<int> arr_y) {
    if (arr_x.size() != arr_y.size()){
        throw std::invalid_argument("Length of vectors must the same!");
    }

    std::vector<int> arr_z = {};
    for (size_t i = 0; i < arr_x.size(); i++) {
        arr_z.push_back(arr_x[i] * arr_y[i]);
    }
    return arr_z;
}

std::vector<std::vector<int>> scalarMatrix(int x, std::vector<std::vector<int>> mat) {
    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat[i].size(); j++) {
            mat[i][j] *= x;
        }
    }
    return mat;
}

std::vector<int> scalarVector(int x, std::vector<int> arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] *= x;
    }
    return arr;
}

template <typename T>
class Matrix {
    public:
        // NOTE: crashes when n = 0
        Matrix(int n, int m, T value) {
            std::vector<std::vector<T>> tmp;
            std::vector<T> subVec = {};
            for (int i = 0; i < n; i++) {
                tmp.push_back(subVec);
                for (int j = 0; j < m; j++) {
                    tmp[i].push_back(value);
                }
            }
            mat = tmp;
        }

        Matrix(std::vector<std::vector<T>> mat_b) {
            mat = mat_b;
        }

        std::string toString() {
            std::string msg = "[";
            for (size_t i = 0; i < mat.size() - 1; i++) {
                msg += rowToString(mat[i]) + ", ";
            }

            msg += rowToString(mat[mat.size() - 1]) + "]";
            return msg;
        }

        std::vector<T> operator[](int i) const {
            return mat[i];
        }

        // set individual element
        void __setitem__(int i, std::vector<T> x) {
            mat[i] = x;
        }

        // Matrix scalar operations
        Matrix operator+(T a) const {
            Matrix tmp = mat;
            for (size_t i = 0; i < mat.size(); i++) {
                for (size_t j = 0; j < mat[i].size(); j++) {                
                    tmp.mat[i][j] += a;                    
                }
            }
            
            return tmp;
        }

        Matrix operator-(T a) const {
            Matrix tmp = mat;
            for (size_t i = 0; i < mat.size(); i++) {
                for (size_t j = 0; j < mat[i].size(); j++) {                
                    tmp.mat[i][j] -= a;                    
                }
            }
            
            return tmp;
        }

        Matrix operator*(T a) const {
            Matrix tmp = mat;
            for (size_t i = 0; i < mat.size(); i++) {
                for (size_t j = 0; j < mat[i].size(); j++) {                
                    tmp.mat[i][j] *= a;                    
                }
            }
            
            return tmp;
        }

        // Matrix Matrix operations
        Matrix operator+(Matrix const &mat_b) const {
            Matrix tmp = mat;
            for (size_t i = 0; i < mat.size(); i++) {
                for (size_t j = 0; j < mat[i].size(); j++) {
                    tmp.mat[i][j] += mat_b.mat[i][j];
                }
            }
            return tmp;
        }

        Matrix operator-(Matrix const &mat_b) const {
            Matrix tmp = mat;
            for (size_t i = 0; i < mat.size(); i++) {
                for (size_t j = 0; j < mat[i].size(); j++) {
                    tmp.mat[i][j] -= mat_b.mat[i][j];
                }
            }
            return tmp;
        }

        Matrix operator*(Matrix const &mat_b) const {
            // throw error if mat a is nxm and mat_b is not mxp 
            std::vector<std::vector<T>> x;
            Matrix tmp = Matrix(x);
            tmp.mat = multiplyMatrixMatrix(mat, mat_b.mat);
            return tmp;
        }

    private:
        std::vector<std::vector<T>> mat;
        std::string rowToString(std::vector<T> &row) {
            std::string msg = "[";

            if (row.size() == 0) {
                msg = "[]";
                return msg;
            }
            for (size_t j = 0; j < row.size() - 1; j++) {
                msg += std::to_string(row[j]) + ", ";
            }
            msg += std::to_string(row[row.size() - 1]) + "]";

            return msg;
        }
      
};



PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    pybind11::class_<Matrix<int>>(m, "Matrix")
        .def(pybind11::init<std::vector<std::vector<int>>>())
        .def(pybind11::init<int, int, int>())
        .def("__getitem__", &Matrix<int>::__setitem__)
        .def("__setitem__", &Matrix<int>::operator[])
        .def("toString", &Matrix<int>::toString)
        .def(pybind11::self + int())
        .def(pybind11::self + pybind11::self)
        .def(pybind11::self - pybind11::self)
        .def(pybind11::self * pybind11::self)
        .def(pybind11::self - int())
        .def(pybind11::self * int());


    m.def("addInt", &addInt, "A function that adds two numbers");
    m.def("subtractInt", &subtractInt, "A function that subtracts two numbers");
    m.def("multiplyInt", &multiplyInt, "A function that multiplies two numbers");
    m.def("multiplyVectorMatrix", &multiplyVectorMatrix, "A function that does vector-matrix multiplication");
    m.def("addVectorVector", &addVectorVector, "A function that adds together values at equivalent indices between two vectors");
    m.def("subtractVectorVector", &subtractVectorVector, "A function that subtracts two values at equivalent indices between two vectors");
    m.def("multiplyVectorVector", &multiplyVectorVector, "A function that multiplies two values at equivalent indices between two vectors");
    m.def("scalarMatrix", &scalarMatrix, "A function that performs scalar multiplication between an integer and a matrix of integers");
    m.def("scalarVector", &scalarVector, "A function that takes an integer, and performs scalar multiplication on a vector");
    m.def("multiplyMatrixMatrix", &multiplyMatrixMatrix, "A function that peforms matrix multiplication on two matrices of integers");
    m.def("addMatrixMatrix", &addMatrixMatrix, "A function that peforms matrix addition on two matrices of integers");
    m.def("subtractMatrixMatrix", &subtractMatrixMatrix, "A function that peforms matrix subtraction on two matrices of integers");
}
