// parall_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <math.h>
#include <vector>
using namespace std;

mutex mut;

void calculate(const int& start,const int& end,long long int& result) {
    long long int a = 1;
    for (int i = start; i <= end; ++i)
        a *= i;

    lock_guard<mutex> lock(mut);
        result *=a;                 
}

int main() {
    long long int result = 1;
    vector<thread> threads;
    vector<double> time_result;
    double faster_threads[2];
    int measurements = 3;
    int factorial = 20;
    int num_treads, start, end;

    for (int i = 0; i < measurements; i++) {
        num_treads = pow(2,i);
        start = 1;
        end = factorial % num_treads + factorial / num_treads;

        auto start_time = chrono::high_resolution_clock::now();
        for (int j = 0; j < num_treads; j++) {
            threads.emplace_back(calculate, start, end, ref(result));
            start = 1 + end;
            end += factorial / num_treads;
        }
        for (auto& thread : threads) {
            thread.join();
        }
        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end_time - start_time;
        time_result.push_back(elapsed.count());
        cout << "Num threads[" << pow(2, i) << "] time = " << time_result.back() << "  result thread = " << result << endl;
        result = 1;
        threads.clear();
    }

    faster_threads[0] = time_result.at(0);
    faster_threads[1] = 0;
    for (int i = 1; i < measurements; i++) {
        if (faster_threads[0] > time_result.at(i)) {
            faster_threads[0] = time_result.at(i);
            faster_threads[1] = i;
        }
    }
    //cout <<endl<< "Number of threads for the fastest calculation = " << faster_threads[1]+1 << endl << "Fastest calculation time = " << faster_threads[0] << endl;
    cout << endl << "Number of threads for the fastest calculation = " << pow(2, faster_threads[1]) << endl << "Fastest calculation time = " << faster_threads[0] << endl;



    //cout << "Общие данные: " << sharedData <<endl;

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
