from random import randrange
from multiprocessing import Process
import time
SIZE = 800 # Modify this to change matrix dimensions


def create_matrix():
    matrix = []
    for i in range(SIZE):
        row = []
        for j in range(SIZE):
            row.append(randrange(1, 10))
        matrix.append(row)
    return matrix


matrix_a = create_matrix()
matrix_b = create_matrix()
flat_a = [0 for i in range(SIZE*SIZE)]
flat_b = [0 for j in range(SIZE*SIZE)]
matrix_result = [0 for k in range(SIZE*SIZE)]


def flatten_matrices():
    for i in range(SIZE):
        for j in range(SIZE):
            flat_a[i*SIZE+j] = matrix_a[i][j]
            flat_b[j*SIZE+i] = matrix_b[i][j]


def parallel_multiplication(dimension_start, dimension_stop):
    for i in range(dimension_start, dimension_stop):
        i_offset = SIZE*i
        for j in range(SIZE):
            j_offset = SIZE*j
            total = 0
            for k in range(SIZE):
                total += flat_a[i_offset+k] * flat_b[j_offset+k]
            matrix_result[i_offset+j] = total


def sequential_multiplication():
    for i in range(SIZE):
        i_offset = SIZE*i
        for j in range(SIZE):
            j_offset = SIZE*j
            total = 0
            for k in range(SIZE):
                total += flat_a[i_offset+k] * flat_b[j_offset+k]
            matrix_result[i_offset+j] = total


def print_matrix(matrix, row_major):
    if row_major:
        for i in range(SIZE):
            for j in range(SIZE):
                print(f"{matrix[SIZE*i+j]} ", end="")
            print()
    else:
        for i in range(SIZE):
            for j in range(SIZE):
                print(f"{matrix[SIZE*j+i]} ", end="")
            print()
    print()


if __name__ == '__main__':
    flatten_matrices()
    # print_matrix(flat_a, True)
    # print_matrix(flat_b, False)
    start = time.time()

    sequential_multiplication()

    # Parallel test example
    # first = Process(target=parallel_multiplication, args=(0, 400,))
    # second = Process(target=parallel_multiplication, args=(400, 800,))
    # first.start()
    # second.start()
    # first.join()
    # second.join()

    stop = time.time()
    # print_matrix(matrix_result, True)
    duration = stop - start
    print(f"Execution time: {duration:.9f} seconds")
