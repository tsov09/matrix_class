#include <iostream>
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
                row = r;
                column = c;  
                init();
                fill();
            }
            else {
                cout << "Matrix sizes must be greather than or equal to 1." << endl;
            }
        }
        void swap_columns(int column_1, int column_2) {
            if (column_1 > 0 && column_1 <= column && column_2 > 0 && column_2 <= column && column_1 != column_2) {
                for (int i = 0; i < row; i++) {
                    swap(&matrix[i][column_1 - 1], &matrix[i][column_2 - 1]);
                }
            }
            else {
                cout << "Columns' numbers must match matrix sizes and can't be equal to each other." << endl;
            }
        }

        void swap_rows(int row_1, int row_2) {
            if (row_1 > 0 && row_1 <= row && row_2 > 0 && row_2 <= row && row_1 != row_2) {
                for (int i = 0; i < column; i++) {
                    swap(&matrix[row_1 - 1][i], &matrix[row_2 - 1][i]);
                }
            }
            else {
                cout << "Rows' numbers must match matrix sizes and can't be equal to each other." << endl;
            }
        }

        void output() {
            for (int i = 0; i < row; i++) {
                for (int g = 0; g < column; g++) {
                    cout << matrix[i][g] << " ";
                }
                cout << endl;
            }
        }

        ~Matrix() {
            for (int i = 0; i < row; i++) {
                delete[] matrix[i];
                matrix[i] = nullptr;
            }
            delete[] matrix;
            matrix = nullptr;
        }

    private:
        int gen_rand() {
            return rand() % (rand_end - rand_start) + rand_start;
        }

        void init() {
            matrix = new int* [row];
            for (int i = 0; i < row; i++) {
                matrix[i] = new int[column];
            }
        }

        void fill() {
            for (int i = 0; i < row; i++) {
                for (int g = 0; g < column; g++) {
                    matrix[i][g] = gen_rand();
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


int main(){
    srand(time(nullptr));
    int size;

    cout << "Enter matrix size: ";
    cin >> size;
    cout << endl;

    Matrix matrix(size, size);
    cout << "Initialized matrix: " << endl;
    matrix.output();
    matrix.swap_columns(1, 3);
    cout << endl << "Matrix columns swaped: " << endl;
    matrix.output();
    cout << endl;

    Matrix matrix_1(size, size);
    cout << "Initialized matrix: " << endl;
    matrix_1.output();
    matrix_1.swap_rows(1,3);
    cout << endl << "Matrix rows swaped: " << endl;
    matrix_1.output();

    return 0;
}