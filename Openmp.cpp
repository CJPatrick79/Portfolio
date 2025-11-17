#include <iostream>
#include <omp.h>
#include <iomanip>
using namespace std;
/*
double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main() {
    const int n = 100000000; 
    double a = 0.0, b = 1.0;
    double step = (b - a) / n;
    double Final_time = 0.0;

    int max_threads = 500;

    cout << "OpenMP Integration Benchmark\n";
    cout << "Integrating f(x) = 4 / (1 + x^2) from " << a << " to " << b << endl;
    cout << "Expected result: pi = 3.14159" << endl << endl;
    cout << left << setw(12) << "Threads"
        << setw(20) << "Time (seconds)"
        << setw(15) << "Estimate"
        << "Speedup" << endl;
    cout << string(60, '-') << endl;

    double serial_time = 0.0;

    for (int num_threads = 1; num_threads <= max_threads; num_threads++) {
        omp_set_num_threads(num_threads);

        double total = 0.0;
        double start_time = omp_get_wtime();

#pragma omp parallel for reduction(+:total)
        for (int i = 0; i < n; i++) {
            double x = a + i * step;
            total += (f(x) + f(x + step)) * 0.5;
        }

        double result = total * step;
        double end_time = omp_get_wtime();
        double elapsed = end_time - start_time;

        if (num_threads == 1)
            serial_time = elapsed;

        double speedup = serial_time / elapsed;

#pragma omp critical
        {
            cout << left << setw(12) << num_threads
                << setw(20) << fixed << setprecision(6) << elapsed
                << setw(15) << result
                << fixed << setprecision(2) << speedup << endl;
            Final_time += elapsed;
        }
    }
cout << "That took " << Final_time << endl;
    return 0;
}