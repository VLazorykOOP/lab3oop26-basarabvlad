#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// ======================================================
// ====================== TASK 1 =========================
// ======================= TIME ==========================
// ======================================================

class Time {
private:
    int hour;
    int minute;
    int second;

public:
    // Конструктор без параметрів
    Time() : hour(0), minute(0), second(0) {}

    // Конструктор з параметрами
    Time(int h, int m, int s) {
        setHour(h);
        setMinute(m);
        setSecond(s);
    }

    // Set-методи з перевіркою
    bool setHour(int h) {
        if (h >= 0 && h <= 23) {
            hour = h;
            return true;
        }
        return false;
    }

    bool setMinute(int m) {
        if (m >= 0 && m <= 59) {
            minute = m;
            return true;
        }
        return false;
    }

    bool setSecond(int s) {
        if (s >= 0 && s <= 59) {
            second = s;
            return true;
        }
        return false;
    }

    bool setTime(int h, int m, int s) {
        bool ok1 = setHour(h);
        bool ok2 = setMinute(m);
        bool ok3 = setSecond(s);
        return ok1 && ok2 && ok3;
    }

    // Get-методи
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }

    // Друк: “16 годин 18 хвилин 3 секунди”
    void print24() const {
        cout << hour << " годин "
             << minute << " хвилин "
             << second << " секунди" << endl;
    }

    // Друк: “4 p.m. 18 хвилин 3 секунди”
    void print12() const {
        int h = hour;
        string period = "a.m.";

        if (h == 0) {
            h = 12;
            period = "a.m.";
        } else if (h < 12) {
            period = "a.m.";
        } else if (h == 12) {
            period = "p.m.";
        } else {
            h -= 12;
            period = "p.m.";
        }

        cout << h << " " << period << " "
             << minute << " хвилин "
             << second << " секунди" << endl;
    }

    // Ввід з клавіатури
    void inputKeyboard() {
        int h, m, s;
        cout << "Введіть годину, хвилини, секунди: ";
        cin >> h >> m >> s;

        if (!setTime(h, m, s)) {
            cout << "Помилка: некоректний час. Встановлено 00:00:00\n";
            hour = minute = second = 0;
        }
    }

    // Ввід з файлу
    bool inputFile(const string& filename) {
        ifstream fin(filename);
        if (!fin) return false;

        int h, m, s;
        fin >> h >> m >> s;

        if (!setTime(h, m, s)) {
            hour = minute = second = 0;
        }

        fin.close();
        return true;
    }

    // Випадкове заповнення
    void inputRandom() {
        hour = rand() % 24;
        minute = rand() % 60;
        second = rand() % 60;
    }
};

// ======================================================
// ====================== TASK 2 =========================
// ====================== VECTOR =========================
// ======================================================

class Vector {
private:
    float* data;
    int size;
    int state;

    static int objectCount;

public:
    enum ErrorCode {
        OK = 0,
        MEMORY_ERROR = 1,
        INDEX_ERROR = 2,
        SIZE_ERROR = 3
    };

    // Конструктор без параметрів
    Vector() : size(1), state(OK) {
        data = new(nothrow) float[size];
        if (!data) {
            state = MEMORY_ERROR;
            size = 0;
        } else {
            data[0] = 0.0f;
        }
        objectCount++;
    }

    // Конструктор з одним параметром
    Vector(int n) : size(n), state(OK) {
        if (n <= 0) {
            size = 1;
        }

        data = new(nothrow) float[size];
        if (!data) {
            state = MEMORY_ERROR;
            size = 0;
        } else {
            for (int i = 0; i < size; i++) {
                data[i] = 0.0f;
            }
        }
        objectCount++;
}

    // Конструктор з двома параметрами
    Vector(int n, float value) : size(n), state(OK) {
        if (n <= 0) {
            size = 1;
        }

        data = new(nothrow) float[size];
        if (!data) {
            state = MEMORY_ERROR;
            size = 0;
        } else {
            for (int i = 0; i < size; i++) {
                data[i] = value;
            }
        }
        objectCount++;
    }

    // Конструктор копії
    Vector(const Vector& other) : size(other.size), state(other.state) {
        data = new(nothrow) float[size];
        if (!data) {
            state = MEMORY_ERROR;
            size = 0;
        } else {
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        objectCount++;
    }

    // Оператор присвоєння
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }

        float* newData = new(nothrow) float[other.size];
        if (!newData) {
            state = MEMORY_ERROR;
            return *this;
        }

        for (int i = 0; i < other.size; i++) {
            newData[i] = other.data[i];
        }

        delete[] data;
        data = newData;
        size = other.size;
        state = other.state;

        return *this;
    }

    // Деструктор
    ~Vector() {
        delete[] data;
        objectCount--;
    }

    // Отримати кількість об'єктів
    static int getObjectCount() {
        return objectCount;
    }

    int getSize() const {
        return size;
    }

    int getState() const {
        return state;
    }

    // Присвоїти елементу масиву значення
    bool setElement(int index, float value = 0.0f) {
        if (index < 0 || index >= size) {
            state = INDEX_ERROR;
            return false;
        }
        data[index] = value;
        state = OK;
        return true;
    }

    // Одержати елемент масиву
    float getElement(int index) {
        if (index < 0 || index >= size) {
            state = INDEX_ERROR;
            return 0.0f;
        }
        state = OK;
        return data[index];
    }

    // Друк
    void print() const {
        cout << "[ ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << "]" << endl;
    }

    // Ввід з клавіатури
    void inputKeyboard() {
        cout << "Введіть " << size << " елементів вектора:\n";
        for (int i = 0; i < size; i++) {
            cin >> data[i];
        }
        state = OK;
    }

    // Ввід з файлу
    bool inputFile(const string& filename) {
        ifstream fin(filename);
        if (!fin) return false;

        for (int i = 0; i < size; i++) {
            if (!(fin >> data[i])) {
                fin.close();
                return false;
            }
        }

        fin.close();
        state = OK;
        return true;
    }

    // Випадкове заповнення
    void inputRandom(int minVal = 0, int maxVal = 9) {
        for (int i = 0; i < size; i++) {
            data[i] = static_cast<float>(minVal + rand() % (maxVal - minVal + 1));
        }
        state = OK;
    }

    // Додавання
    Vector add(const Vector& other) const {
        if (size != other.size) {
            Vector temp;
            temp.state = SIZE_ERROR;
            return temp;
        }

        Vector result(size);
        for (int i = 0; i < size; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Віднімання
    Vector subtract(const Vector& other) const {
        if (size != other.size) {
            Vector temp;
            temp.state = SIZE_ERROR;
            return temp;
        }

        Vector result(size);
        for (int i = 0; i < size; i++) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Множення на long
    Vector multiply(long k) const {
        Vector result(size);
        for (int i = 0; i < size; i++) {
            result.data[i] = data[i] * k;
        }
        return result;
    }
// Порівняння за сумою елементів
    float sum() const {
        float s = 0;
        for (int i = 0; i < size; i++) {
            s += data[i];
        }
        return s;
    }

    bool isEqual(const Vector& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool isGreater(const Vector& other) const {
        return sum() > other.sum();
    }

    bool isLess(const Vector& other) const {
        return sum() < other.sum();
    }
};

int Vector::objectCount = 0;

// ======================================================
// ====================== TASK 3 =========================
// ====================== MATRIX =========================
// ======================================================

class Matrix {
private:
    float* data;
    int rows;
    int cols;
    int state;

public:
    enum ErrorCode {
        OK = 0,
        MEMORY_ERROR = 1,
        INDEX_ERROR = 2,
        SIZE_ERROR = 3
    };

    // Конструктор без параметрів
    Matrix() : rows(2), cols(2), state(OK) {
        data = new(nothrow) float[rows * cols];
        if (!data) {
            state = MEMORY_ERROR;
            rows = cols = 0;
        } else {
            for (int i = 0; i < rows * cols; i++) {
                data[i] = 0.0f;
            }
        }
    }

    // Конструктор n x n
    Matrix(int n) : rows(n), cols(n), state(OK) {
        if (n <= 0) rows = cols = 2;

        data = new(nothrow) float[rows * cols];
        if (!data) {
            state = MEMORY_ERROR;
            rows = cols = 0;
        } else {
            for (int i = 0; i < rows * cols; i++) {
                data[i] = 0.0f;
            }
        }
    }

    // Конструктор n x m із value
    Matrix(int n, int m, float value) : rows(n), cols(m), state(OK) {
        if (n <= 0 || m <= 0) {
            rows = cols = 2;
        }

        data = new(nothrow) float[rows * cols];
        if (!data) {
            state = MEMORY_ERROR;
            rows = cols = 0;
        } else {
            for (int i = 0; i < rows * cols; i++) {
                data[i] = value;
            }
        }
    }

    // Конструктор копії
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), state(other.state) {
        data = new(nothrow) float[rows * cols];
        if (!data) {
            state = MEMORY_ERROR;
            rows = cols = 0;
        } else {
            for (int i = 0; i < rows * cols; i++) {
                data[i] = other.data[i];
            }
        }
    }

    // Оператор присвоєння
    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this;

        float* newData = new(nothrow) float[other.rows * other.cols];
        if (!newData) {
            state = MEMORY_ERROR;
            return *this;
        }

        for (int i = 0; i < other.rows * other.cols; i++) {
            newData[i] = other.data[i];
        }

        delete[] data;
        data = newData;
        rows = other.rows;
        cols = other.cols;
        state = other.state;

        return *this;
    }

    // Деструктор
    ~Matrix() {
        delete[] data;
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int getState() const { return state; }

    // Присвоїти елемент
    bool setElement(int i, int j, float value = 0.0f) {
        if (i < 0  i >= rows  j < 0 || j >= cols) {
            state = INDEX_ERROR;
            return false;
        }
        data[i * cols + j] = value;
        state = OK;
        return true;
    }

    // Отримати елемент
    float getElement(int i, int j) {
        if (i < 0  i >= rows  j < 0 || j >= cols) {
            state = INDEX_ERROR;
            return 0.0f;
        }
        state = OK;
        return data[i * cols + j];
    }

    // Друк
    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << setw(8) << data[i * cols + j] << " ";
            }
cout << endl;
        }
    }

    // Ввід з клавіатури
    void inputKeyboard() {
        cout << "Введіть " << rows * cols << " елементів матриці:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> data[i * cols + j];
            }
        }
        state = OK;
    }

    // Ввід з файлу
    bool inputFile(const string& filename) {
        ifstream fin(filename);
        if (!fin) return false;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (!(fin >> data[i * cols + j])) {
                    fin.close();
                    return false;
                }
            }
        }

        fin.close();
        state = OK;
        return true;
    }

    // Випадкове заповнення
    void inputRandom(int minVal = 0, int maxVal = 9) {
        for (int i = 0; i < rows * cols; i++) {
            data[i] = static_cast<float>(minVal + rand() % (maxVal - minVal + 1));
        }
        state = OK;
    }

    // Додавання
    Matrix add(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            Matrix temp;
            temp.state = SIZE_ERROR;
            return temp;
        }

        Matrix result(rows, cols, 0.0f);
        for (int i = 0; i < rows * cols; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Віднімання
    Matrix subtract(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            Matrix temp;
            temp.state = SIZE_ERROR;
            return temp;
        }

        Matrix result(rows, cols, 0.0f);
        for (int i = 0; i < rows * cols; i++) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Множення на скаляр
    Matrix multiply(float k) const {
        Matrix result(rows, cols, 0.0f);
        for (int i = 0; i < rows * cols; i++) {
            result.data[i] = data[i] * k;
        }
        return result;
    }

    // Сума елементів
    float sum() const {
        float s = 0;
        for (int i = 0; i < rows * cols; i++) {
            s += data[i];
        }
        return s;
    }

    // Порівняння
    bool isEqual(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) return false;
        for (int i = 0; i < rows * cols; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool isGreater(const Matrix& other) const {
        return sum() > other.sum();
    }

    bool isLess(const Matrix& other) const {
        return sum() < other.sum();
    }
};

// ======================================================
// =================== TEST FUNCTIONS ====================
// ======================================================

void testTime() {
    cout << "\n========== ТЕСТУВАННЯ КЛАСУ TIME ==========\n";

    Time t1;
    cout << "Конструктор без параметрів:\n";
    t1.print24();
    t1.print12();

    Time t2(16, 18, 3);
    cout << "\nКонструктор з параметрами:\n";
    t2.print24();
    t2.print12();

    cout << "\nЗміна значень через set:\n";
    t2.setHour(23);
    t2.setMinute(45);
    t2.setSecond(59);
    t2.print24();

    cout << "\nОтримання значень через get:\n";
    cout << "Година: " << t2.getHour() << endl;
    cout << "Хвилина: " << t2.getMinute() << endl;
    cout << "Секунда: " << t2.getSecond() << endl;

    cout << "\nВвід з клавіатури:\n";
    Time t3;
    t3.inputKeyboard();
    t3.print24();
    t3.print12();

    cout << "\nВвід з файлу time.txt:\n";
    Time t4;
    if (t4.inputFile("time.txt")) {
        t4.print24();
        t4.print12();
    } else {
        cout << "Не вдалося відкрити файл time.txt\n";
    }

    cout << "\nВипадковий час:\n";
    Time t5;
    t5.inputRandom();
    t5.print24();
    t5.print12();
}

void testVector() {
    cout << "\n========== ТЕСТУВАННЯ КЛАСУ VECTOR ==========\n";

    Vector v1;
    cout << "v1 (без параметрів): ";
    v1.print();
Vector v2(5);
    cout << "v2 (розмір 5): ";
    v2.print();

    Vector v3(5, 2.5f);
    cout << "v3 (розмір 5, значення 2.5): ";
    v3.print();

    cout << "\nsetElement / getElement:\n";
    v3.setElement(2, 10.0f);
    v3.print();
    cout << "Елемент [2] = " << v3.getElement(2) << endl;

    cout << "\nКонструктор копії:\n";
    Vector v4 = v3;
    v4.print();

    cout << "\nОператор присвоєння:\n";
    Vector v5;
    v5 = v3;
    v5.print();

    cout << "\nВвід з клавіатури для v2:\n";
    v2.inputKeyboard();
    v2.print();

    cout << "\nВвід з файлу vector.txt для нового вектора:\n";
    Vector v6(5);
    if (v6.inputFile("vector.txt")) {
        v6.print();
    } else {
        cout << "Не вдалося відкрити файл vector.txt\n";
    }

    cout << "\nВипадковий вектор:\n";
    Vector v7(5);
    v7.inputRandom();
    v7.print();

    cout << "\nДодавання v3 + v7:\n";
    Vector addRes = v3.add(v7);
    addRes.print();

    cout << "\nВіднімання v3 - v7:\n";
    Vector subRes = v3.subtract(v7);
    subRes.print();

    cout << "\nМноження v3 * 3:\n";
    Vector mulRes = v3.multiply(3);
    mulRes.print();

    cout << "\nПорівняння:\n";
    cout << "v3 == v4 ? " << (v3.isEqual(v4) ? "true" : "false") << endl;
    cout << "v3 > v7 ? " << (v3.isGreater(v7) ? "true" : "false") << endl;
    cout << "v3 < v7 ? " << (v3.isLess(v7) ? "true" : "false") << endl;

    cout << "\nКількість об'єктів Vector: " << Vector::getObjectCount() << endl;

    cout << "\nПеревірка виходу за межі масиву:\n";
    v3.setElement(100, 5.0f);
    cout << "Стан = " << v3.getState() << endl;
}

void testMatrix() {
    cout << "\n========== ТЕСТУВАННЯ КЛАСУ MATRIX ==========\n";

    Matrix m1;
    cout << "m1 (без параметрів):\n";
    m1.print();

    Matrix m2(3);
    cout << "\nm2 (3x3):\n";
    m2.print();

    Matrix m3(2, 3, 5.0f);
    cout << "\nm3 (2x3, значення 5):\n";
    m3.print();

    cout << "\nsetElement / getElement:\n";
    m3.setElement(1, 2, 11.0f);
    m3.print();
    cout << "Елемент [1][2] = " << m3.getElement(1, 2) << endl;

    cout << "\nКонструктор копії:\n";
    Matrix m4 = m3;
    m4.print();

    cout << "\nОператор присвоєння:\n";
    Matrix m5;
    m5 = m3;
    m5.print();

    cout << "\nВвід з клавіатури для m2:\n";
    m2.inputKeyboard();
    m2.print();

    cout << "\nВвід з файлу matrix.txt:\n";
    Matrix m6(2, 3, 0.0f);
    if (m6.inputFile("matrix.txt")) {
        m6.print();
    } else {
        cout << "Не вдалося відкрити файл matrix.txt\n";
    }

    cout << "\nВипадкова матриця:\n";
    Matrix m7(2, 3, 0.0f);
    m7.inputRandom();
    m7.print();

    cout << "\nДодавання m3 + m7:\n";
    Matrix addRes = m3.add(m7);
    addRes.print();

    cout << "\nВіднімання m3 - m7:\n";
    Matrix subRes = m3.subtract(m7);
    subRes.print();

    cout << "\nМноження m3 * 2:\n";
    Matrix mulRes = m3.multiply(2);
    mulRes.print();

    cout << "\nПорівняння:\n";
    cout << "m3 == m4 ? " << (m3.isEqual(m4) ? "true" : "false") << endl;
    cout << "m3 > m7 ? " << (m3.isGreater(m7) ? "true" : "false") << endl;
    cout << "m3 < m7 ? " << (m3.isLess(m7) ? "true" : "false") << endl;

    cout << "\nПеревірка виходу за межі матриці:\n";
    m3.setElement(10, 10, 7.0f);
    cout << "Стан = " << m3.getState() << endl;
}

// ======================================================
// ========================= MAIN ========================
// ======================================================

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int choice;

    do {
        cout << "\n============== МЕНЮ ==============\n";
        cout << "1 - Тест класу Time\n";
        cout << "2 - Тест класу Vector\n";
        cout << "3 - Тест класу Matrix\n";
        cout << "0 - Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 1:
                testTime();
                break;
            case 2:
                testVector();
                break;
            case 3:
                testMatrix();
                break;
            case 0:
cout << "Завершення програми.\n";
                break;
            default:
                cout << "Невірний вибір.\n";
        }
    } while (choice != 0);

    return 0;
}

