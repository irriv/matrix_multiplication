#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <iomanip>

const int SIZE = 5500; // Modify this to change matrix dimensions
int matrix_a[SIZE][SIZE];
int matrix_b[SIZE][SIZE];
int flat_a[SIZE*SIZE];
int flat_b[SIZE*SIZE];
int matrix_result[SIZE*SIZE];

// std::random_device dev;
// std::mt19937 rng(dev());
// std::uniform_int_distribution<std::mt19937::result_type> dist(1,9);

void fill_matrix(int matrix[SIZE][SIZE]){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            matrix[i][j] = j+1; // dist(rng) for random numbers, uncomment lines above
        }
    }
}

void flatten_matrices(){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            flat_a[i*SIZE+j] = matrix_a[i][j];
            flat_b[j*SIZE+i] = matrix_b[i][j];
        }
    }
}

void parallel_multiplication(int dimension_start, int dimension_stop){
    for(int i=dimension_start;i<dimension_stop;i++){
        int i_offset = SIZE*i;
        for(int j=0;j<SIZE;j++){
            int j_offset = SIZE*j;
            int total = 0;
            for(int k=0;k<SIZE;k++){
                total += flat_a[i_offset+k] * flat_b[j_offset+k];
            }
            matrix_result[i_offset+j] = total;
        }
    }
}

void sequential_multiplication(){
    for(int i=0;i<SIZE;i++){
            int i_offset = SIZE*i;
            for(int j=0;j<SIZE;j++){
                int j_offset = SIZE*j;
                int total = 0;
                for(int k=0;k<SIZE;k++){
                    total += flat_a[i_offset+k] * flat_b[j_offset+k];
                }
                matrix_result[i_offset+j] = total;
            }
        }
}

void print_matrix(int matrix[SIZE*SIZE], bool row_major){
    if(row_major){
        for(int i=0;i<SIZE;i++){
                for(int j=0;j<SIZE;j++){
                    std::cout << matrix[SIZE*i+j] << " ";
                }
                std::cout << "\n";
            }
    }
    else{
        for(int i=0;i<SIZE;i++){
                for(int j=0;j<SIZE;j++){
                    std::cout << matrix[SIZE*j+i] << " ";
                }
                std::cout << "\n";
            }
    }
    std::cout << "\n";
}



int main()
{
    fill_matrix(matrix_a);
    fill_matrix(matrix_b);
    flatten_matrices();
    // print_matrix(flat_a, true);
    // print_matrix(flat_b, false);
    auto start = std::chrono::high_resolution_clock::now();
    
    sequential_multiplication();

    // Parallel test example
    // std::thread first (parallel_multiplication, 0, 2750);
    // std::thread second (parallel_multiplication, 2750, 5500);
    // first.join();
    // second.join();

    auto stop = std::chrono::high_resolution_clock::now();
    // print_matrix(matrix_result, true);
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Execution time: " << std::setprecision(9) << duration.count()*0.000000001 << " seconds" << std::endl;
    return 0;
}
