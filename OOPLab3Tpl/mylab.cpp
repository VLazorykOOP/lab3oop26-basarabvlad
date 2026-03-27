#include <iostream>
using namespace std;

// ================= TIME =================
class Time {
    int h, m, s;

public:
    Time() { h = m = s = 0; }

    Time(int h, int m, int s) {
        set(h, m, s);
    }

    void set(int hh, int mm, int ss) {
        h = (hh >= 0 && hh < 24) ? hh : 0;
        m = (mm >= 0 && mm < 60) ? mm : 0;
        s = (ss >= 0 && ss < 60) ? ss : 0;
    }

    void print1() {
        cout << h << " годин " << m << " хвилин " << s << " секунд\n";
    }

    void print2() {
        int hour12 = h % 12;
        if (hour12 == 0) hour12 = 12;
        cout << hour12 << (h < 12 ? " a.m. " : " p.m. ")
            << m << " хвилин " << s << " секунд\n";
    }
};

// ================= VECTOR =================
class Vector {
    float* data;
    int size;
    int state;

public:
    Vector() {
        size = 1;
        data = new float[1] {0};
        state = 0;
    }

    Vector(int n) {
        size = n;
        data = new float[n] {0};
        state = 0;
    }

    Vector(int n, float val) {
        size = n;
        data = new float[n];
        for (int i = 0; i < n; i++) data[i] = val;
        state = 0;
    }

    ~Vector() {
        delete[] data;
    }

    void set(int i, float val) {
        if (i >= 0 && i < size)
            data[i] = val;
        else
            state = 1;
    }

    float get(int i) {
        if (i >= 0 && i < size)
            return data[i];
        state = 1;
        return 0;
    }

    void print() {
        for (int i = 0; i < size; i++)
            cout << data[i] << " ";
        cout << endl;
    }
};

// ================= MATRIX =================
class Matrix {
    float* data;
    int rows, cols;

public:
    Matrix() {
        rows = cols = 2;
        data = new float[4] {0};
    }

    Matrix(int n) {
        rows = cols = n;
        data = new float[n * n] {0};
    }

    Matrix(int r, int c, float val) {
        rows = r;
        cols = c;
        data = new float[r * c];
        for (int i = 0; i < r * c; i++) data[i] = val;
    }

    ~Matrix() {
        delete[] data;
    }

    void set(int i, int j, float val) {
        if (i >= 0 && i < rows && j >= 0 && j < cols)
            data[i * cols + j] = val;
    }

    float get(int i, int j) {
        if (i >= 0 && i < rows && j >= 0 && j < cols)
            return data[i * cols + j];
        return 0;
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << get(i, j) << " ";
            cout << endl;
        }
    }
};

// ================= TESTS =================
void testTime() {
    Time t1(16, 18, 3);
    t1.print1();
    t1.print2();
}

void testVector() {
    Vector v(5, 2);
    v.set(2, 10);
    v.print();
}

void testMatrix() {
    Matrix m(2, 2, 1);
    m.set(0, 1, 5);
    m.print();
}

// ================= MAIN =================
int main() {
    int choice;

    do {
        cout << "\n1 - Time\n2 - Vector\n3 - Matrix\n0 - Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: testTime(); break;
        case 2: testVector(); break;
        case 3: testMatrix(); break;
        }

    } while (choice != 0);

    return 0;
}