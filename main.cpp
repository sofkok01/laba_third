#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <unistd.h>

using namespace std;

// Очистка экрана консоли
void cleanDisplay() {
    system("clear");
}

// Вывод матрицы на экран
void showMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << *(*(matrix + i) + j) << "\t";
        }
        cout << endl;
    }
}

// Копирование данных из одной матрицы в другую
void copyMatrixData(int** src, int** dst, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(dst + i) + j) = *(*(src + i) + j);
        }
    }
}

// Генерация массива случайных чисел
void generateRandomNumbers(int* array, int count, int maxValue) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, maxValue);

    for (int i = 0; i < count; i++) {
        *(array + i) = dist(gen);
    }
}

// Заполнение матрицы по спирали (по часовой стрелке)
void fillSpiral(int* randArray, int** matrix, int size) {
    // Инициализация матрицы нулями
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(matrix + i) + j) = 0;
        }
    }

    cleanDisplay();
    cout << "Заполнение спиралью:\n\n";

    int idx = 0;
    int left = 0, right = size - 1;
    int top = 0, bottom = size - 1;

    while (top <= bottom && left <= right) {
        // Верхняя строка слева направо
        for (int j = left; j <= right; j++) {
            *(*(matrix + top) + j) = *(randArray + idx);
            idx++;

            cleanDisplay();
            cout << "Заполнение спиралью:\n\n";
            showMatrix(matrix, size);
            usleep(50000);
        }
        top++;

        // Правый столбец сверху вниз
        for (int i = top; i <= bottom; i++) {
            *(*(matrix + i) + right) = *(randArray + idx);
            idx++;

            cleanDisplay();
            cout << "Заполнение спиралью:\n\n";
            showMatrix(matrix, size);
            usleep(50000);
        }
        right--;

        // Нижняя строка справа налево
        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                *(*(matrix + bottom) + j) = *(randArray + idx);
                idx++;

                cleanDisplay();
                cout << "Заполнение спиралью:\n\n";
                showMatrix(matrix, size);
                usleep(50000);
            }
            bottom--;
        }

        // Левый столбец снизу вверх
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                *(*(matrix + i) + left) = *(randArray + idx);
                idx++;

                cleanDisplay();
                cout << "Заполнение спиралью:\n\n";
                showMatrix(matrix, size);
                usleep(50000);
            }
            left++;
        }
    }
}

// Заполнение матрицы змейкой (зигзагом по строкам)
void fillSnake(int* randArray, int** matrix, int size) {
    // Инициализация матрицы нулями
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(matrix + i) + j) = 0;
        }
    }

    cleanDisplay();
    cout << "Заполнение змейкой:\n\n";

    int idx = 0;

    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            // Слева направо для четных строк
            for (int j = 0; j < size; j++) {
                *(*(matrix + i) + j) = *(randArray + idx);
                idx++;

                cleanDisplay();
                cout << "Заполнение змейкой:\n\n";
                showMatrix(matrix, size);
                usleep(50000);
            }
        } else {
            // Справа налево для нечетных строк
            for (int j = size - 1; j >= 0; j--) {
                *(*(matrix + i) + j) = *(randArray + idx);
                idx++;

                cleanDisplay();
                cout << "Заполнение змейкой:\n\n";
                showMatrix(matrix, size);
                usleep(50000);
            }
        }
    }
}

// Поворот блоков матрицы по часовой стрелке (a→b→c→d→a)
void rotateBlocksClockwise(int** src, int** dst, int size) {
    int half = size / 2;
    copyMatrixData(src, dst, size);

    int** tempBlock = new int*[half];
    for (int i = 0; i < half; i++) {
        *(tempBlock + i) = new int[half];
    }

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *(*(tempBlock + i) + j) = *(*(dst + i) + j);
        }
    }

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *(*(dst + i) + j) = *(*(dst + i) + (j + half));
        }
    }

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *(*(dst + i) + (j + half)) = *(*(dst + i + half) + (j + half));
        }
    }

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *(*(dst + i + half) + (j + half)) = *(*(dst + i + half) + j);
        }
    }

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *(*(dst + i + half) + j) = *(*(tempBlock + i) + j);
        }
    }

    for (int i = 0; i < half; i++) {
        delete[] *(tempBlock + i);
    }
    delete[] tempBlock;
}

// Обмен блоков матрицы по диагонали (a↔d, b↔c)
void swapBlocksDiagonally(int** src, int** dst, int size) {
    int half = size / 2;
    copyMatrixData(src, dst, size);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int temp = *(*(dst + i) + j);
            *(*(dst + i) + j) = *(*(dst + i + half) + (j + half));
            *(*(dst + i + half) + (j + half)) = temp;

            temp = *(*(dst + i) + (j + half));
            *(*(dst + i) + (j + half)) = *(*(dst + i + half) + j);
            *(*(dst + i + half) + j) = temp;
        }
    }
}

// Обмен блоков матрицы по вертикали (a↔c, b↔d)
void swapBlocksVertically(int** src, int** dst, int size) {
    int half = size / 2;
    copyMatrixData(src, dst, size);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int temp = *(*(dst + i) + j);
            *(*(dst + i) + j) = *(*(dst + i + half) + j);
            *(*(dst + i + half) + j) = temp;

            temp = *(*(dst + i) + (j + half));
            *(*(dst + i) + (j + half)) = *(*(dst + i + half) + (j + half));
            *(*(dst + i + half) + (j + half)) = temp;
        }
    }
}

// Обмен блоков матрицы по горизонтали (a↔b, c↔d)
void swapBlocksHorizontally(int** src, int** dst, int size) {
    int half = size / 2;
    copyMatrixData(src, dst, size);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int temp = *(*(dst + i) + j);
            *(*(dst + i) + j) = *(*(dst + i) + (j + half));
            *(*(dst + i) + (j + half)) = temp;

            temp = *(*(dst + i + half) + j);
            *(*(dst + i + half) + j) = *(*(dst + i + half) + (j + half));
            *(*(dst + i + half) + (j + half)) = temp;
        }
    }
}

// Быстрая сортировка (QuickSort) массива
void quickSort(int* arr, int start, int end) {
    if (start >= end) return;

    int left = start;
    int right = end;
    int pivot = *(arr + (left + right) / 2);

    while (left <= right) {
        while (*(arr + left) < pivot) left++;
        while (*(arr + right) > pivot) right--;

        if (left <= right) {
            int temp = *(arr + left);
            *(arr + left) = *(arr + right);
            *(arr + right) = temp;
            left++;
            right--;
        }
    }

    if (start < right) quickSort(arr, start, right);
    if (left < end) quickSort(arr, left, end);
}

// Преобразование матрицы в одномерный массив
void matrixToArray(int** matrix, int* arr, int size) {
    int idx = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(arr + idx) = *(*(matrix + i) + j);
            idx++;
        }
    }
}

// Арифметические операции с элементами матрицы (+ - * /)
void modifyMatrix(int** matrix, int size, int value, char operation) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            switch(operation) {
                case '+': *(*(matrix + i) + j) += value; break;
                case '-': *(*(matrix + i) + j) -= value; break;
                case '*': *(*(matrix + i) + j) *= value; break;
                case '/':
                    if (value != 0) *(*(matrix + i) + j) /= value;
                    else cout << "Ошибка: деление на 0!" << endl;
                    break;
            }
        }
    }
}

// Меню операций с блоками матриц
void showBlockOperations(int** spiralMatrix, int** snakeMatrix, int matrixSize) {
    int matrixChoice;
    cout << "\nВыберите матрицу для перестановки блоков:\n";
    cout << "1. Матрица-спираль\n";
    cout << "2. Матрица-змейка\n";
    cout << "Ваш выбор: ";
    cin >> matrixChoice;

    int** selectedMatrix = (matrixChoice == 1) ? spiralMatrix : snakeMatrix;

    cout << "\nИсходная матрица:\n";
    showMatrix(selectedMatrix, matrixSize);

    int** results[4];
    for (int k = 0; k < 4; k++) {
        results[k] = new int*[matrixSize];
        for (int i = 0; i < matrixSize; i++) {
            results[k][i] = new int[matrixSize];
        }
    }

    rotateBlocksClockwise(selectedMatrix, results[0], matrixSize);
    swapBlocksDiagonally(selectedMatrix, results[1], matrixSize);
    swapBlocksVertically(selectedMatrix, results[2], matrixSize);
    swapBlocksHorizontally(selectedMatrix, results[3], matrixSize);

    cout << "\n1. Поворот блоков по часовой стрелке:\n";
    showMatrix(results[0], matrixSize);

    cout << "\n2. Обмен блоков по диагонали:\n";
    showMatrix(results[1], matrixSize);

    cout << "\n3. Обмен блоков по вертикали:\n";
    showMatrix(results[2], matrixSize);

    cout << "\n4. Обмен блоков по горизонтали:\n";
    showMatrix(results[3], matrixSize);

    for (int k = 0; k < 4; k++) {
        for (int i = 0; i < matrixSize; i++) {
            delete[] results[k][i];
        }
        delete[] results[k];
    }
}

int main() {
    srand(time(0));

    int matrixSize;
    do {
        cout << "Введите размер матрицы N (6, 8 или 10): ";
        cin >> matrixSize;
    } while (matrixSize != 6 && matrixSize != 8 && matrixSize != 10);

    int totalElements = matrixSize * matrixSize;
    int* randomNumbers = new int[totalElements];
    generateRandomNumbers(randomNumbers, totalElements, matrixSize * matrixSize);

    int** spiralMatrix = new int*[matrixSize];
    int** snakeMatrix = new int*[matrixSize];
    for (int i = 0; i < matrixSize; i++) {
        spiralMatrix[i] = new int[matrixSize];
        snakeMatrix[i] = new int[matrixSize];
    }

    fillSpiral(randomNumbers, spiralMatrix, matrixSize);
    fillSnake(randomNumbers, snakeMatrix, matrixSize);

    cout << "\nМатрица-спираль:\n";
    showMatrix(spiralMatrix, matrixSize);

    cout << "\nМатрица-змейка:\n";
    showMatrix(snakeMatrix, matrixSize);

    while (true) {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
        cout << "1. Операции с блоками матриц\n";
        cout << "2. Сортировка элементов (змейка -> QuickSort)\n";
        cout << "3. Арифметические операции с матрицами\n";
        cout << "4. Выход\n";
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            showBlockOperations(spiralMatrix, snakeMatrix, matrixSize);
        } else if (choice == 2) {
            int* sortArray = new int[totalElements];
            matrixToArray(snakeMatrix, sortArray, matrixSize);

            cout << "\nМассив до сортировки:\n";
            for (int i = 0; i < totalElements; i++) {
                cout << sortArray[i] << " ";
            }

            quickSort(sortArray, 0, totalElements - 1);

            cout << "\n\nМассив после сортировки (QuickSort):\n";
            for (int i = 0; i < totalElements; i++) {
                cout << sortArray[i] << " ";
            }
            cout << endl;

            delete[] sortArray;
        } else if (choice == 3) {
            cout << "\nВыберите матрицу:\n1. Спираль\n2. Змейка\nВаш выбор: ";
            int matrixChoice;
            cin >> matrixChoice;

            int** selectedMatrix = (matrixChoice == 1) ? spiralMatrix : snakeMatrix;

            cout << "\nВыберите операцию (+, -, *, /): ";
            char operation;
            cin >> operation;

            cout << "Введите число: ";
            int value;
            cin >> value;

            modifyMatrix(selectedMatrix, matrixSize, value, operation);

            cout << "\nРезультат:\n";
            showMatrix(selectedMatrix, matrixSize);
        } else if (choice == 4) {
            break;
        }
    }

    for (int i = 0; i < matrixSize; i++) {
        delete[] spiralMatrix[i];
        delete[] snakeMatrix[i];
    }
    delete[] spiralMatrix;
    delete[] snakeMatrix;
    delete[] randomNumbers;

    return 0;
}