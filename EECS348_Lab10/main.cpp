/*
 * Name: Samyu Aitha
 * Lab: Lab 10: C++ Programming
 * Input: A file containing two square matrices.
 * Output: The results of seven matrix operations.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Problem 1: Matrix class
class Matrix {
private:
    int N;
    vector<vector<int> > data;

public:
    Matrix() {
        N = 0;
    }

    Matrix(int size) {
        N = size;
        data.resize(N, vector<int>(N, 0));
    }

    int size() const {
        return N;
    }

    int get(int row, int col) const {
        return data[row][col];
    }

    void set(int row, int col, int value) {
        data[row][col] = value;
    }

    void print() const {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << setw(4) << data[i][j];
            }
            cout << endl;
        }
    }

    // Problem 2: Add matrices using +
    Matrix operator+(const Matrix& B) const {
        Matrix result(N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                result.set(i, j, data[i][j] + B.get(i, j));
            }
        }
        return result;
    }

    // Problem 3: Multiply matrices using *
    Matrix operator*(const Matrix& B) const {
        Matrix result(N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int total = 0;
                for (int k = 0; k < N; k++) {
                    total += data[i][k] * B.get(k, j);
                }
                result.set(i, j, total);
            }
        }
        return result;
    }
};

// Problem 1: Read matrices from the input file
bool readMatrices(const string& filename, Matrix& A, Matrix& B) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Error: Could not open file." << endl;
        return false;
    }

    int N;
    if (!(inputFile >> N) || N <= 0) {
        cout << "Error: Invalid matrix size." << endl;
        return false;
    }

    A = Matrix(N);
    B = Matrix(N);
    int value;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!(inputFile >> value)) {
                cout << "Error: Not enough values for Matrix A." << endl;
                return false;
            }
            A.set(i, j, value);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!(inputFile >> value)) {
                cout << "Error: Not enough values for Matrix B." << endl;
                return false;
            }
            B.set(i, j, value);
        }
    }
    return true;
}

// Problem 4: Find the sums of both diagonals
void diagonalSums(const Matrix& matrix) {
    int N = matrix.size();
    int mainSum = 0;
    int secondarySum = 0;

    for (int i = 0; i < N; i++) {
        mainSum += matrix.get(i, i);
        secondarySum += matrix.get(i, N - 1 - i);
    }

    cout << "Main diagonal sum: " << mainSum << endl;
    cout << "Secondary diagonal sum: " << secondarySum << endl;
}

// Problem 5: Swap rows in a copy of the matrix
Matrix swapRows(Matrix matrix, int row1 = 0, int row2 = 1) {
    int N = matrix.size();
    if (row1 < 0 || row1 >= N || row2 < 0 || row2 >= N) {
        cout << "Invalid row index." << endl;
        return matrix;
    }

    for (int j = 0; j < N; j++) {
        int temp = matrix.get(row1, j);
        matrix.set(row1, j, matrix.get(row2, j));
        matrix.set(row2, j, temp);
    }
    return matrix;
}

// Problem 6: Swap columns in a copy of the matrix
Matrix swapColumns(Matrix matrix, int col1 = 0, int col2 = 1) {
    int N = matrix.size();
    if (col1 < 0 || col1 >= N || col2 < 0 || col2 >= N) {
        cout << "Invalid column index." << endl;
        return matrix;
    }

    for (int i = 0; i < N; i++) {
        int temp = matrix.get(i, col1);
        matrix.set(i, col1, matrix.get(i, col2));
        matrix.set(i, col2, temp);
    }
    return matrix;
}

// Problem 7: Update one value in a copy of the matrix
Matrix updateElement(Matrix matrix, int row = 0, int col = 0, int value = 100) {
    int N = matrix.size();
    if (row < 0 || row >= N || col < 0 || col >= N) {
        cout << "Invalid matrix index." << endl;
        return matrix;
    }
    matrix.set(row, col, value);
    return matrix;
}

int main() {
    string filename;
    Matrix A, B;

    cout << "Enter input filename: ";
    cin >> filename;
    cout << endl;

    if (!readMatrices(filename, A, B)) {
        return 1;
    }

    // Problem 1
    cout << "Matrix A:" << endl;
    A.print();
    cout << endl;
    cout << "Matrix B:" << endl;
    B.print();
    cout << endl;

    // Problem 2
    Matrix sum = A + B;
    cout << "A + B:" << endl;
    sum.print();
    cout << endl;

    // Problem 3
    Matrix product = A * B;
    cout << "A * B:" << endl;
    product.print();
    cout << endl;

    // Problem 4
    cout << "Diagonal sums for Matrix A:" << endl;
    diagonalSums(A);
    cout << endl;

    // Problem 5
    Matrix rowSwapped = swapRows(A, 0, 2);
    cout << "Problem 5 - Rows 0 and 2 swapped:" << endl;
    rowSwapped.print();
    cout << endl;

    // Problem 6
    Matrix columnSwapped = swapColumns(A, 0, 2);
    cout << "Problem 6 - Columns 0 and 2 swapped:" << endl;
    columnSwapped.print();
    cout << endl;

    // Problem 7
    Matrix updated = updateElement(A, 1, 2, 99);
    cout << "Problem 7 - Updated matrix:" << endl;
    updated.print();

    return 0;
}
