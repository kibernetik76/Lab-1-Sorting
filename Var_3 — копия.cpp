/**
 * @file main.cpp
 * @brief Сортировка массива служащих бухгалтерии.
 * @details В программе реализованы чтение данных из CSV, три вида сортировок 
 * и замер времени их работы для графиков.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <random>

// ============================================================
//  СТРУКТУРА ДАННЫХ И ПЕРЕГРУЗКА ОПЕРАТОРОВ
// ============================================================

/**
 * @brief Структура, описывающая одного служащего.
 */
struct Employee {
    std::string fullName;   ///< ФИО сотрудника
    std::string position;   ///< Должность
    std::string department; ///< Подразделение
    int salary;             ///< Зарплата

    /**
     * @brief Перегрузка оператора "меньше" (<).
     * @details Сравнивает двух сотрудников по приоритетам: Подразделение -> ФИО -> Зарплата.
     * @param other Другой сотрудник, с которым мы сравниваем текущего.
     * @return true, если текущий сотрудник "меньше" (должен стоять раньше).
     */
    bool operator<(const Employee& other) const {
        // 1. Если подразделения разные, сортируем по ним (по алфавиту)
        if (department != other.department) {
            return department < other.department;
        }
        // 2. Если подразделения одинаковые, смотрим на ФИО
        if (fullName != other.fullName) {
            return fullName < other.fullName;
        }
        // 3. Если и подразделение, и ФИО совпадают, сортируем по зарплате
        return salary < other.salary;
    }

    /**
     * @brief Перегрузка оператора "больше" (>).
     * @details Строится на основе уже написанного оператора <.
     */
    bool operator>(const Employee& other) const {
        return other < *this; 
    }

    /** @brief Перегрузка оператора "меньше или равно" (<=). */
    bool operator<=(const Employee& other) const {
        return !(*this > other);
    }

    /** @brief Перегрузка оператора "больше или равно" (>=). */
    bool operator>=(const Employee& other) const {
        return !(*this < other);
    }
};

// ============================================================
//  МЕТОДЫ СОРТИРОВКИ
// ============================================================

/**
 * @brief Сортировка простыми вставками.
 * @param arr Ссылка на массив сотрудников.
 */
void insertionSort(std::vector<Employee>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        Employee key = arr[i]; // Берем текущего сотрудника
        int j = i - 1;
        
        // Сдвигаем всех сотрудников, которые больше key, на одну позицию вправо
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // Ставим сотрудника на его законное место
    }
}

/**
 * @brief Шейкер-сортировка (двунаправленный пузырек).
 * @param arr Ссылка на массив сотрудников.
 */
void shakerSort(std::vector<Employee>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    bool swapped = true;

    while (swapped) {
        swapped = false;

        // Проход слева направо (самый "большой" уходит в конец)
        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Если обменов не было, массив отсортирован
        swapped = false;
        right--; 

        // Проход справа налево (самый "маленький" уходит в начало)
        for (int i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {
                std::swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
        left++; 
    }
}

/**
 * @brief Вспомогательная функция для сортировки слиянием. Сливает две части вместе.
 */
void merge(std::vector<Employee>& arr, int left, int mid, int right) {
    // Создаем копии левой и правой частей
    std::vector<Employee> L(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<Employee> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    // Сравниваем элементы и переносим меньший в основной массив
    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    // Докидываем оставшиеся элементы (если есть)
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}

/**
 * @brief Основная рекурсивная функция сортировки слиянием.
 * @param arr Массив сотрудников.
 * @param left Индекс начала.
 * @param right Индекс конца.
 */
void mergeSort(std::vector<Employee>& arr, int left, int right) {
    if (left >= right) return; // Если остался 1 элемент, он уже "отсортирован"
    
    int mid = (left + right) / 2; // Находим середину
    mergeSort(arr, left, mid);      // Сортируем левую половину
    mergeSort(arr, mid + 1, right); // Сортируем правую половину
    merge(arr, left, mid, right);   // Сливаем их вместе
}

// ============================================================
//  ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ (ЧТЕНИЕ И ГЕНЕРАЦИЯ ДАННЫХ)
// ============================================================

std::vector<Employee> readCSV(const std::string& filename) {
    std::vector<Employee> data;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Employee emp;
        std::getline(ss, emp.fullName, ',');
        std::getline(ss, emp.position, ',');
        std::getline(ss, emp.department, ',');
        std::string sal;
        std::getline(ss, sal, ',');
        if (!sal.empty()) emp.salary = std::stoi(sal);
        data.push_back(emp);
    }
    return data;
}

void writeCSV(const std::string& filename, const std::vector<Employee>& data) {
    std::ofstream file(filename);
    for (const auto& emp : data) {
        file << emp.fullName << "," << emp.position << ","
             << emp.department << "," << emp.salary << "\n";
    }
}

void generateCSV(const std::string& filename, int count) {
    std::vector<std::string> names = {"Ivanov I.I.", "Petrov P.P.", "Sidorov S.S.", "Smirnov A.A.", "Kozlov B.B."};
    std::vector<std::string> positions = {"Accountant", "Analyst", "Manager", "Director", "Clerk"};
    std::vector<std::string> depts = {"IT", "HR", "Finance", "Sales", "Marketing"};

    std::mt19937 gen(42); 
    std::uniform_int_distribution<> dName(0, 4), dPos(0, 4), dDept(0, 4), dSal(30000, 200000);

    std::ofstream file(filename);
    for (int i = 0; i < count; i++) {
        file << names[dName(gen)] << "," << positions[dPos(gen)] << ","
             << depts[dDept(gen)] << "," << dSal(gen) << "\n";
    }
}

// ============================================================
//  ГЛАВНАЯ ФУНКЦИЯ (БЕНЧМАРК)
// ============================================================

int main() {
    std::vector<int> sizes = {100, 500, 1000, 2500, 5000, 10000, 20000, 30000, 50000, 100000};
    
    std::ofstream results("results.csv");
    results << "Size,Insertion,Shaker,Merge,StdSort\n";

    for (int n : sizes) {
        std::string filename = "data_" + std::to_string(n) + ".csv";
        generateCSV(filename, n);
        std::vector<Employee> original = readCSV(filename);

        std::vector<Employee> arr;
        double timeIns = 0, timeShaker = 0, timeMerge = 0, timeStd = 0;

        // Вставки
        if (n <= 30000) {
            arr = original;
            auto t1 = std::chrono::high_resolution_clock::now();
            insertionSort(arr);
            auto t2 = std::chrono::high_resolution_clock::now();
            timeIns = std::chrono::duration<double, std::milli>(t2 - t1).count();
        }

        // Шейкер
        if (n <= 30000) {
            arr = original;
            auto t1 = std::chrono::high_resolution_clock::now();
            shakerSort(arr);
            auto t2 = std::chrono::high_resolution_clock::now();
            timeShaker = std::chrono::duration<double, std::milli>(t2 - t1).count();
        }

        // Слияние
        arr = original;
        auto t1 = std::chrono::high_resolution_clock::now();
        mergeSort(arr, 0, arr.size() - 1);
        auto t2 = std::chrono::high_resolution_clock::now();
        timeMerge = std::chrono::duration<double, std::milli>(t2 - t1).count();

        if (n == 100) writeCSV("sorted_output.csv", arr); // Записываем в файл

        // std::sort
        arr = original;
        auto t3 = std::chrono::high_resolution_clock::now();
        std::sort(arr.begin(), arr.end());
        auto t4 = std::chrono::high_resolution_clock::now();
        timeStd = std::chrono::duration<double, std::milli>(t4 - t3).count();

        std::cout << "n=" << n << "  Ins=" << timeIns << "  Shaker=" << timeShaker
                  << "  Merge=" << timeMerge << "  Std=" << timeStd << "\n";

        results << n << "," << timeIns << "," << timeShaker << "," << timeMerge << "," << timeStd << "\n";
    }

    results.close();
    std::cout << "Готово! Результаты в results.csv\n";
    return 0;
}