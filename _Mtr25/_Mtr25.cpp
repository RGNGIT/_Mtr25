#include <iostream>
#include <string>

const double pi = 3.1415926535;
const int _size = (int)((pi * 2) / (pi / 10));
double * Arr = new double[_size];
double * A;
double * B;
double ** Mtr;
int mtrSize;
int rangeA = 0, rangeB = 0;

using namespace std;

int findMinIndex(double * Arr) {
    double min = Arr[0], index = 0;
    for (int i = 0; i < _size; i++) {
        if (Arr[i] < min) {
            min = Arr[i];
            index = i;
        }
    }
    return index;
}

double avgAryth() {
    double sum = 0;
    for (int i = 0; i < mtrSize; i++) {
        for (int j = 0; j < mtrSize; j++) {
            sum += Mtr[i][j];
        }
    }
    return sum / pow(mtrSize, 2);
}

double avgArythCol(int col) {
    double sum = 0;
    for (int i = 0; i < mtrSize; i++) {
        sum += Mtr[i][col];
    }
    return sum / mtrSize;
}

int colAmount() {
    int amount = 0;
    for (int i = 0; i < mtrSize; i++) {
        if (avgAryth() > avgArythCol(i)) {
            amount++;
        }
    }
    return amount;
}

void makeMtr() {
    int __size = rangeA < rangeB ? rangeA : rangeB;
    Mtr = new double * [__size];
    for (int i = 0; i < __size; i++) {
        Mtr[i] = new double[__size];
    }
    for (int i = 0; i < __size; i++) {
        cout << endl;
        for (int j = 0; j < __size; j++) {
            if (i > j) {
                Mtr[i][j] = A[i] + B[j];
            }
            if (i < j) {
                Mtr[i][j] = A[i] * B[j];
            }
            if (i == j) {
                Mtr[i][j] = 1;
            }
            cout << Mtr[i][j] << ' ';
        }
    }
    mtrSize = __size;
}

void shitSort(double * Arr, int __size) {
    repeat:
    for (int i = 1; i < __size; i++) {
        if (Arr[i - 1] < Arr[i]) {
            swap(Arr[i - 1], Arr[i]);
        }
    }
    for (int i = 1; i < __size; i++) {
        if (Arr[i - 1] < Arr[i]) {
            goto repeat;
        }
    }
}

void calculateRanges() {
    bool check = true;
    rangeA = 0;
    rangeB = 0;
    for (int i = 0; i < _size; i++) {
        if (i == findMinIndex(Arr)) {
            check = false;
        }
        if (check && i != findMinIndex(Arr)) {
            rangeA++;
        }
        if (!check && (i != findMinIndex(Arr) || i == findMinIndex(Arr))) {
            rangeB++;
        }
    }
}

void fillArrays() {
    A = new double[rangeA];
    B = new double[rangeB];
    for (int i = 0; i < _size; i++) {
        if (i < rangeA) {
            A[i] = Arr[i];
        }
        else {
            B[i - rangeA] = Arr[i];
        }
    }
}

void tabulation() {
    cout << "Табуляция:" << endl;
    for (double i = -pi, j = 0; i < pi; i += pi / 10, j++) {
        Arr[(int)j] = (3 * cos(5 * i)) + (2 * sin(i));
        cout << "X: " << i << " Y: " << Arr[(int)j] << endl;
    }
}

void arrayOutput(double * Arr, int __size) {
    for (int i = 0; i < __size; i++) {
        cout << Arr[i] << ' ';
    }
    cout << endl;
}

string mtrStringify() {
    string mtr = "";
    for (int i = 0; i < mtrSize; i++) {
        for (int j = 0; j < mtrSize; j++) {
            mtr += to_string(Mtr[i][j]) + " ";
        }
    }
    return mtr;
}

int main()
{
    setlocale(LC_ALL, "");
    tabulation();
    cout << "Получившийся массив:\n";
    arrayOutput(Arr, _size);
    calculateRanges();
    fillArrays();
    cout << "Получившийся массив A:\n";
    arrayOutput(A, rangeA);
    cout << "Получившийся массив B:\n";
    arrayOutput(B, rangeB);
    shitSort(A, rangeA);
    cout << "Отсортированый по убыванию массив A:\n";
    arrayOutput(A, rangeA);
    cout << "Сформированная матрица:";
    makeMtr();
    cout << endl << "Кол-во столбцов со сред.арифм. меньше, чем у всей матрицы: " << colAmount() << endl;
    cout << "Строка элементов матрицы: " << mtrStringify() << endl;
}
