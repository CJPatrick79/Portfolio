#include <iostream>
#include <omp.h>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    int max_threads = omp_get_max_threads();
    omp_set_num_threads(max_threads);
    omp_set_nested(1);

    volatile int current_id = 0;

    double start_time = omp_get_wtime();

#pragma omp parallel shared(current_id)
    {
        int tid = omp_get_thread_num();
        while (tid != current_id) {
#pragma omp flush(current_id)
        }

#pragma omp critical
        {
            cout << "[Main Thread] Thread " << tid << " printing in order.\n";
        }

#pragma omp atomic
        current_id++;
#pragma omp flush(current_id)

#pragma omp barrier

#pragma omp parallel
        {
            int nested_tid = omp_get_thread_num();
            int parent_tid = tid;

#pragma omp critical
            {
                cout << "   [Nested] Thread " << nested_tid
                    << " inside Parent " << parent_tid << endl;
            }
        }
    }

    double end_time = omp_get_wtime();
    cout << "Elapsed Time: " << end_time - start_time << " seconds.\n";

    return 0;
}

