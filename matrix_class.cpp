#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Matrix {
public:
    int** matrix;
    int row;
    int column;
    int rand_start = 10;
    int rand_end = 100;

    Matrix(int r, int c) {
        if (r >= 1 && c >= 1) {
            this->row = r;
            this->column = c;
            this->init();
            this->fill();
        }
        else {
            cout << "Matrix sizes must be greather than or equal to 1." << endl;
        }
    }
    Matrix(const Matrix& obj) {
        this->row = obj.row;
        this->column = obj.column;
        this->init();
        for (int i = 0; i < this->row; i++) {
            for (int g = 0; g < this->column; g++) {
                this->matrix[i][g] = obj.matrix[i][g];
            }
        }
    }
    Matrix(Matrix&& obj) {
        cout << "Matrix move constructor" << endl;
        this->row = obj.row;
        this->column = obj.column;
        this->matrix = obj.matrix;
        obj.matrix = nullptr;
        obj.row = 0;
        obj.column = 0;
    }

    Matrix& operator = (const Matrix& obj) {
        if (this != &obj) {
            for (int i = 0; i < this->row; i++) {
                delete[] this->matrix[i];
                this->matrix[i] = nullptr;
            }
            delete[] this->matrix;
            this->matrix = nullptr;
            this->row = obj.row;
            this->column = obj.column;
            this->init();
            for (int i = 0; i < this->row; i++) {
                for (int g = 0; g < this->column; g++) {
                    this->matrix[i][g] = obj.matrix[i][g];
                }
            }
        }
        return *this;
    }

     Matrix& operator = (Matrix&& obj) {
         cout << "Matrix operator move assignment" << endl;
         if (this != &obj) {
            for (int i = 0; i < this->row; i++) {
                delete[] this->matrix[i];
                this->matrix[i] = nullptr;
            }
            delete[] this->matrix;
            this->matrix = nullptr;
             this->row = obj.row;
             this->column = obj.column;
             this->matrix = obj.matrix;
             obj.matrix = nullptr;
             obj.row = 0;
             obj.column = 0;
         }

         return *this;
     }

    void swap_columns(int column_1, int column_2) {
        if (column_1 > 0 && column_1 <= column && column_2 > 0 && column_2 <= column && column_1 != column_2) {
            for (int i = 0; i < this->row; i++) {
                swap(&this->matrix[i][column_1 - 1], &this->matrix[i][column_2 - 1]);
            }
        }
        else {
            cout << "Columns' numbers must match matrix sizes and can't be equal to each other." << endl;
        }
    }

    void swap_rows(int row_1, int row_2) {
        if (row_1 > 0 && row_1 <= this->row && row_2 > 0 && row_2 <= this->row && row_1 != row_2) {
            for (int i = 0; i < this->column; i++) {
                swap(&this->matrix[row_1 - 1][i], &this->matrix[row_2 - 1][i]);
            }
        }
        else {
            cout << "Rows' numbers must match matrix sizes and can't be equal to each other." << endl;
        }
    }

    void output() {
        for (int i = 0; i < this->row; i++) {
            for (int g = 0; g < this->column; g++) {
                cout << this->matrix[i][g] << " ";
            }
            cout << endl;
        }
    }

    void print_in_file() {
        ofstream my_file;
        my_file.open("matrix.txt");
        for (int i = 0; i < this->row; i++) {
            for (int g = 0; g < this->column; g++) {
                my_file << this->matrix[i][g] << " ";
            }
            my_file << endl;
        }
        my_file.close();
    }

    ~Matrix() {
        for (int i = 0; i < this->row; i++) {
            delete[] this->matrix[i];
            this->matrix[i] = nullptr;
        }
        delete[] this->matrix;
        this->matrix = nullptr;
    }

private:
    int gen_rand() {
        return rand() % (this->rand_end - this->rand_start) + rand_start;
    }

    void init() {
        this->matrix = new int* [this->row];
        for (int i = 0; i < this->row; i++) {
            this->matrix[i] = new int[this->column];
        }
    }

    void fill() {
        for (int i = 0; i < this->row; i++) {
            for (int g = 0; g < this->column; g++) {
                this->matrix[i][g] = this->gen_rand();
            }
        }
    }

    void swap(int* a, int* b) {
        int temp;
        temp = *a;
        *a = *b;
        *b = temp;
    }


};


void class_matrix_with_operator_assign_and_copy_constructor() {
    int row = 3, column = 4;

    /*cout << "Enter matrix rows' count: ";
    cin >> row;
    cout << endl;

    cout << "Enter matrix columns' count: ";
    cin >> column;
    cout << endl;*/

    Matrix matrix(row, column);
    cout << "Initialized first matrix: " << endl;
    matrix.output();
    cout << endl;

    Matrix matrix_2 = matrix;
    cout << "Copy of first matrix: " << endl;
    matrix_2.output();

    matrix.swap_columns(1, 3);
    cout << endl << "First matrix columns swaped: " << endl;
    matrix.output();
    cout << endl;

    Matrix matrix_1(row, column);
    cout << "Initialized second matrix: " << endl;
    matrix_1.output();


    matrix_1.swap_rows(1, 3);
    cout << endl << "Second matrix rows swaped: " << endl;
    matrix_1.output();
    cout << endl;

    cout << "Copy of first matrix in the end: " << endl;
    matrix_2.output();
    cout << endl;

    Matrix matrix_3(4, 5);
    cout << "Initialized third matrix: " << endl;
    matrix_3.output();
    cout << endl;

    matrix_3 = matrix_2;
    cout << "The value of first matrix's copy assigned to third one: " << endl;
    matrix_3.output();
}

void check_move() {
    cout << endl;
    Matrix m_1 = move(Matrix(4, 3));
    cout << endl;
    m_1.output();
    cout << endl;
    m_1 = move(Matrix(2, 3));
    cout << endl;
    m_1.output();
    cout << endl;
}

int main() {
    srand(time(nullptr));
    //class_matrix_with_operator_assign_and_copy_constructor();
    //check_move();

    Matrix matrix(9, 7);
    matrix.print_in_file();

    return 0;
}