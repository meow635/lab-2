#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <omp.h>

using namespace std;

int main() {
    vector<int> sizes = {200, 400, 800, 1200, 1600, 2000};

    vector<int> threads_list = {1, 2, 4, 8};

    ofstream file("results.csv");
    file << "size,threads,time\n";

    for (int N : sizes) {
        for (int num_threads : threads_list) {

            omp_set_num_threads(num_threads);

            vector<vector<double>> A(N, vector<double>(N));
            vector<vector<double>> B(N, vector<double>(N));
            vector<vector<double>> C(N, vector<double>(N, 0));

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    A[i][j] = rand() % 10;
                    B[i][j] = rand() % 10;
                }
            }

            auto start = chrono::high_resolution_clock::now();

            #pragma omp parallel for
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    for (int k = 0; k < N; k++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;

            double time = elapsed.count();

            cout << "Size: " << N 
                 << " Threads: " << num_threads 
                 << " Time: " << time << endl;

            file << N << "," << num_threads << "," << time << "\n";
        }
    }

    file.close();
    cout << "\nResults saved to results.csv\n";

    return 0;
}