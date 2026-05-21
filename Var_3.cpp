
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>   
#include <cstdlib> 


/**
 * @defgroup Struct Структура данных работника
 * @brief Стукртура сотрудника и перегрузка оператора.
 *
 * @defgroup Sorting Сортировка
 * @brief Реализация вариантов сортировки: сортировка простыми вставками, шейкер-сортировка, сортировка слиянием.
 *
 * @defgroup HelpFunc Доп функции
 * @brief Функции для работы с файловой системой.
 *
 * @defgroup MainFunc Главная функция
 * @brief ОСновная программа.
 */

/**
 * @ingroup Struct
 * @brief Структура, которая описывает одного работника
 */
struct Employee {
    std::string name;   
    std::string job;   
    std::string department; 
    int salary;             
};

/**
 * @ingroup Struct
 * @brief Перегрузка оператора меньше "<".
 * @details Сравнивает двух человек по полям: подразделение, ФИО служащего, зарплата.
 * @param a Первый сотрудник
 * @param b Второй сотрудник
 * @return true, если первый сотрудник меньше второго.
 */
bool operator<(const Employee& a, const Employee& b) {
    if (a.department != b.department) {
        return a.department < b.department;
    }
    else if (a.name != b.name) {
        return a.name < b.name;
    }
    else {
        return a.salary < b.salary;
    }
}

/**
 * @ingroup Struct
 * @brief Перегрузка оператора "больше" (>).
 * @details Сравнивает двух человек по полям: подразделение, ФИО служащего, зарплата.
 * @param a Первый сотрудник
 * @param b Второй сотрудник
 * @return true, если первый сотрудник больше второго.
 */
bool operator>(const Employee& a, const Employee& b) {
    if (a.department != b.department) {
        return a.department > b.department;
    }
    else if (a.name != b.name) {
        return a.name > b.name;
    }
    else {
        return a.salary > b.salary;
    }
}

/** 
 * @ingroup Struct
 * @brief Перегрузка оператора "меньше или равно" (<=). 
 * @details Сравнивает двух человек по полям: подразделение, ФИО служащего, зарплата.
 * @param a Первый сотрудник
 * @param b Второй сотрудник
 * @return true, если первый сотрудник <= второго.
 */
bool operator<=(const Employee& a, const Employee& b) {
    if (a.department != b.department) {
        return a.department <= b.department;
    }
    else if (a.name != b.name) {
        return a.name <= b.name;
    }
    else {
        return a.salary <= b.salary;
    }
}

/** 
 * @ingroup Struct
 * @brief Перегрузка оператора "больше или равно" (>=). 
 * @details Сравнивает двух человек по полям: подразделение, ФИО служащего, зарплата.
 * @param a Первый сотрудник
 * @param b Второй сотрудник
 * @return true, если первый сотрудник >= второго.
 */
bool operator>=(const Employee& a, const Employee& b) {
    if (a.department != b.department) {
        return a.department >= b.department;
    }
    else if (a.name != b.name) {
        return a.name >= b.name;
    }
    else {
        return a.salary >= b.salary;
    }
}




/**
 * @ingroup Sorting
 * @brief Сортировка простыми вставками.
 * @param arr Ссылка на массив сотрудников.
 */
void SimpleSort(std::vector<Employee>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        Employee a = arr[i]; 
        int j = i - 1;
        
        while (j >= 0 && arr[j] > a) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = a; 
    }
}

/**
 * @ingroup Sorting
 * @brief Шейкер-сортировка (двунаправленный пузырек).
 * @param arr Ссылка на массив сотрудников.
 */
void shakerSort(std::vector<Employee>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    bool flag = true;

    while (flag) {
        flag = false;
        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                flag = true;
            }
        }
        if (flag == false) break; 
        flag = false;
        right--; 

        for (int i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {
                std::swap(arr[i], arr[i - 1]);
                flag = true;
            }
        }
        left++; 
    }
}

/**
 * @ingroup Sorting
 * @brief Вспомогательная функция. Сливает две отсортированные части вместе.
 */
void mergeSort1(std::vector<Employee>& arr, int left, int mid, int right) {
    std::vector<Employee> L; 
    std::vector<Employee> R; 

    for (int i = left; i <= mid; i++) {
        L.push_back(arr[i]);
    }

    
    for (int j = mid + 1; j <= right; j++) {
        R.push_back(arr[j]);
    }

    
    int i = 0; 
    int j = 0; 
    int k = left; 


    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j]) {
            arr[k] = L[i]; 
            i++;           
        } else {
            arr[k] = R[j]; 
            j++;           
        }
        k++; 
    }

    
    while (i < L.size()) {
        arr[k] = L[i];
        i++;
        k++;
    }

    
    while (j < R.size()) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * @ingroup Sorting
 * @brief Основная рекурсивная функция сортировки слиянием.
 */
void mergeSort2(std::vector<Employee>& arr, int left, int right) {
    if (left >= right) {
        return; 
    }
    
    
    int mid = (left + right) / 2; 
    
    
    mergeSort2(arr, left, mid);      
    
    
    mergeSort2(arr, mid + 1, right); 
    
    
    mergeSort1(arr, left, mid, right);  
}





/**
 * @ingroup HelpFunc
 * @brief Чтение данных из CSV файла.
 * @param filename Имя файла для чтения.
 * @return Массив загруженных сотрудников.
 */
std::vector<Employee> readCSV(const std::string& filename) {
    std::vector<Employee> data;
    std::ifstream file(filename);
    std::string line;

    
    while (std::getline(file, line)) {
        
        
        std::stringstream lineStream(line); 
        
        Employee emp; 

        
        std::getline(lineStream, emp.name, ',');       
        
        
        std::getline(lineStream, emp.job, ',');        
        
        
        std::getline(lineStream, emp.department, ','); 
        
        
        std::string salaryText;
        std::getline(lineStream, salaryText, ',');
        
        
        emp.salary = std::stoi(salaryText); 

        
        data.push_back(emp);
    }
    
    return data; 
}

/**
 * @ingroup HelpFunc
 * @brief Запись отсортированных данных в CSV файл.
 * @param filename Имя файла для сохранения.
 * @param data Массив сотрудников для записи.
 */
void writeCSV(const std::string& filename, const std::vector<Employee>& data) {
    std::ofstream file(filename);
    for (int i = 0; i < data.size(); i++) {
        file << data[i].name << "," << data[i].job << ","
             << data[i].department << "," << data[i].salary << "\n";
    }
}

/**
 * @ingroup HelpFunc
 * @brief Генерация CSV файла со случайными данными.
 * @param filename Имя создаваемого файла.
 * @param count Количество строк для генерации.
 */
void generateCSV(const std::string& filename, int count) {
    std::vector<std::string> lastNames = {"Ivanov", "Petrov", "Sidorov", "Smirnov", "Kozlov"};
    std::vector<std::string> positions = {"Accountant", "Analyst", "Manager", "Director", "Clerk"};
    std::vector<std::string> depts = {"IT", "HR", "Finance", "Sales", "Marketing"};

    std::ofstream file(filename);
    
    for (int i = 0; i < count; i++) {
        int familia_ind = rand() % 5;
        int job_ind = rand() % 5;
        int dept_ind = rand() % 5;

        
        int salary = 50000 + (rand() % 150001);


        char bukva_1 = 'A' + (rand() % 26);
        char bukva_2 = 'A' + (rand() % 26);

        
        std::string fullName = lastNames[familia_ind] + " " + bukva_1 + "." + bukva_2 + ".";

        
        file << fullName << "," << positions[job_ind] << ","
             << depts[dept_ind] << "," << salary << "\n";
    }
}





/**
 * @ingroup MainFunc
 * @brief Точка входа.
 * @details Запускает генерацию файлов разных размеров, тестирует время выполнения 
 * всех видов сортировок и сохраняет результаты в `results.csv`.
 * @return Код завершения программы (0 при успехе).
 */
/**
 * @ingroup MainFunc
 * @brief Точка входа.
 */
int main() {
    std::vector<int> sizes = {100, 500, 1000, 2500, 5000, 10000, 20000, 30000, 50000, 100000};
    
    std::ofstream results("results.csv");
    results << "Size,Insertion,Shaker,Merge,StdSort\n";

    for (int i = 0; i < sizes.size(); i++) {
        int n = sizes[i]; 

        std::string filename = "data_" + std::to_string(n) + ".csv";
        generateCSV(filename, n);
        std::vector<Employee> original = readCSV(filename);

        std::vector<Employee> arr;
        double timeIns = 0, timeShaker = 0, timeMerge = 0, timeStd = 0;

        // 1
        if (n <= 30000) {
            arr = original; 
            int start = clock(); 
            SimpleSort(arr); 
            int end = clock();   
            timeIns = (double)(end - start) / CLOCKS_PER_SEC * 1000.0; 
        }

        // 2
        if (n <= 30000) {
            arr = original;
            int start = clock();
            shakerSort(arr);
            int end = clock();
            timeShaker = (double)(end - start) / CLOCKS_PER_SEC * 1000.0; 
        }

        // 3
        arr = original;
        int startMerge = clock(); 
        mergeSort2(arr, 0, arr.size() - 1); 
        int endMerge = clock();
        timeMerge = (double)(endMerge - startMerge) / CLOCKS_PER_SEC * 1000.0;

        if (n == 100) writeCSV("sorted_output.csv", arr);

        // 4
        arr = original;
        int startStd = clock();
        std::sort(arr.begin(), arr.end());
        int endStd = clock();
        timeStd = (double)(endStd - startStd) / CLOCKS_PER_SEC * 1000.0;

        std::cout << "n=" << n << "  Ins=" << timeIns << "  Shaker=" << timeShaker
                  << "  Merge=" << timeMerge << "  Std=" << timeStd << "\n";

        results << n << "," << timeIns << "," << timeShaker << "," << timeMerge << "," << timeStd << "\n";
    }

    results.close(); 
    return 0; 
}