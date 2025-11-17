#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <omp.h>

using namespace std;

int main() 
{
    omp_set_num_threads(10);
    vector<string> Name;
    ifstream file("TestSheet.csv");
    double final_time;

    if (!file.is_open()) 
    {
        cerr << "Error: Could not open the file 'wrestlers.csv'.\n";
        return 1;
    }

    string line;
    vector<pair<string, string>> data;
#pragma omp parallel
    {
        double start_time = omp_get_wtime();
    #pragma omp critical
            {
                while (getline(file, line)) 
                {

                    stringstream ss(line);
                    string name, era;
                    if (getline(ss, name, ',') && getline(ss, era, ',')) 
                    {
#
                        data.emplace_back(name, era);
                    }
                }
            }

            file.close();
    #pragma omp critical
            {
                cout << "Thread# " << omp_get_thread_num() + 1 << endl;
                cout << "Wrestler List (from file): " << endl;
                for (const auto& entry : data) 
                {
                    cout << left << "Name: " << entry.first << ", " 
                    << right << setw(10) << fixed << "Era: " << entry.second << endl;
                }
                cout << endl << endl;
            }
            double end_time = omp_get_wtime();
            final_time = end_time - start_time;
            
    }
    cout << final_time << endl;
    return 0;
}
