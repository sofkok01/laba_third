#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <unistd.h>

using namespace std;

int** spiralMatrix;
int** snakeMatrix;
int matrixSize;

void cleanDisplay() {
    system("clear");
}

void showMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << *(*(matrix + i) + j) << "\t";
        }
        cout << endl;
    }
}

void copyMatrixData(int** src, int** dst, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(dst + i) + j) = *(*(src + i) + j);
        }
    }
}

void generateRandomNumbers(int* array, int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, size * size);

    for (int i = 0; i < size * size; i++) {
        *(array + i) = dist(gen);
    }
}

void fillSpiral(int* randArray, int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(matrix + i) + j) = 0;
        }
    }

    cleanDisplay();
    cout << "Заполнение спиралью:\n\n";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << " . ";
        }
        cout << endl;
    }

    usleep(1000000);

    int idx = 0;
    int left = 0, right = size - 1;
    int top = 0, bottom = size - 1;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++) {
            *(*(matrix + top) + j) = *(randArray + idx);
            idx++;

            cleanDisplay();
            cout << "Заполнение спиралью:\n\n";

            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    int val = *(*(matrix + r) + c);
                    if (val == 0) cout << " . ";
                    else {
                        if (r == top && c == j) cout << "[" << val << "] ";
                        else cout << " " << val << " ";
                    }
                }
                cout << endl;
            }
            usleep(300000);
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            *(*(matrix + i) + right) = *(randArray + idx);
            idx++;

            cleanDisplay();
            cout << "Заполнение спиралью:\n\n";

            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    int val = *(*(matrix + r) + c);
                    if (val == 0) cout << " . ";
                    else {
                        if (r == i && c == right) cout << "[" << val << "] ";
                        else cout << " " << val << " ";
                    }
                }
                cout << endl;
            }
            usleep(300000);
        }
        right--;

        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                *(*(matrix + bottom) + j) = *(randArray + idx);
                idx++;

                cleanDisplay();
                cout << "Заполнение спиралью:\n\n";

                for (int r = 0; r < size; r++) {
                    for (int c = 0; c < size; c++) {
                        int val = *(*(matrix + r) + c);
                        if (val == 0) cout << " . ";
                        else {
                            if (r == bottom && c == j) cout << "[" << val << "] ";
                            else cout << " " << val << " ";
                        }
                    }
                    cout << endl;
                }
                usleep(300000);
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                *(*(matrix + i) + left) = *(randArray + idx);
                idx++;

                cleanDisplay();
                cout << "Заполнение спиралью:\n\n";

                for (int r = 0; r < size; r++) {
                    for (int c = 0; c < size; c++) {
                        int val = *(*(matrix + r) + c);
                        if (val == 0) cout << " . ";
                        else {
                            if (r == i && c == left) cout << "[" << val << "] ";
                            else cout << " " << val << " ";
                        }
                    }
                    cout << endl;
                }
                usleep(300000);
            }
            left++;
        }
    }
}

void fillSnake(int* randArray, int** matrix, int size) {
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
            for (int j = 0; j < size; j++) {
                *(*(matrix + i) + j) = *(randArray + idx);
                idx++;

                cleanDisplay();
                cout << "Заполнение змейкой:\n\n";

                for (int r = 0; r < size; r++) {
                    for (int c = 0; c < size; c++) {
                        int val = *(*(matrix + r) + c);
                        if (val == 0) cout << " . ";
                        else cout << val << " ";
                    }
                    cout << endl;
                }
                usleep(300000);
            }
        } else {
            for (int j = size - 1; j >= 0; j--) {
                *(*(matrix + i) + j) = *(randArray + idx);
                idx++;

                cleanDisplay();
                cout << "Заполнение змейкой:\n\n";

                for (int r = 0; r < size; r++) {
                    for (int c = 0; c < size; c++) {
                        int val = *(*(matrix + r) + c);
                        if (val == 0) cout << " . ";
                        else cout << val << " ";
                    }
                    cout << endl;
                }
                usleep(300000);
            }
        }
    }
}

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
            *(*(dst + i) + j) = *(*(dst + i) + j + half);
        }
    }

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *(*(dst + i) + j + half) = *(*(dst + i + half) + j + half);
        }
    }

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *(*(dst + i + half) + j + half) = *(*(dst + i + half) + j);
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

void swapBlocksDiagonally(int** src, int** dst, int size) {
    int half = size / 2;
    copyMatrixData(src, dst, size);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int temp = *(*(dst + i) + j);
            *(*(dst + i) + j) = *(*(dst + i + half) + j + half);
            *(*(dst + i + half) + j + half) = temp;

            temp = *(*(dst + i) + j + half);
            *(*(dst + i) + j + half) = *(*(dst + i + half) + j);
            *(*(dst + i + half) + j) = temp;
        }
    }
}

void swapBlocksVertically(int** src, int** dst, int size) {
    int half = size / 2;
    copyMatrixData(src, dst, size);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int temp = *(*(dst + i) + j);
            *(*(dst + i) + j) = *(*(dst + i + half) + j);
            *(*(dst + i + half) + j) = temp;

            temp = *(*(dst + i) + j + half);
            *(*(dst + i) + j + half) = *(*(dst + i + half) + j + half);
            *(*(dst + i + half) + j + half) = temp;
        }
    }
}

void swapBlocksHorizontally(int** src, int** dst, int size) {
    int half = size / 2;
    copyMatrixData(src, dst, size);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int temp = *(*(dst + i) + j);
            *(*(dst + i) + j) = *(*(dst + i) + j + half);
            *(*(dst + i) + j + half) = temp;

            temp = *(*(dst + i + half) + j);
            *(*(dst + i + half) + j) = *(*(dst + i + half) + j + half);
            *(*(dst + i + half) + j + half) = temp;
        }
    }
}

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

void matrixToArray(int** matrix, int* arr, int size) {
    int idx = 0;
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < size; j++) {
                *(arr + idx) = *(*(matrix + i) + j);
                idx++;
            }
        } else {
            for (int j = size - 1; j >= 0; j--) {
                *(arr + idx) = *(*(matrix + i) + j);
                idx++;
            }
        }
    }
}

void modifyMatrix(int** matrix, int size, int value, char operation) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            switch(operation) {
                case '+': *(*(matrix + i) + j) += value; break;
                case '-': *(*(matrix + i) + j) -= value; break;
                case '*': *(*(matrix + i) + j) *= value; break;
                case '/':
                    if (value != 0) *(*(matrix + i) + j) /= value;
                    break;
            }
        }
    }
}

int getUserChoice(const string& prompt, int minVal, int maxVal) {
    int choice;
    do {
        cout << prompt;
        cin >> choice;
        if (choice < minVal || choice > maxVal) {
            cout << "Ошибка! Введите число от " << minVal << " до " << maxVal << endl;
        }
    } while (choice < minVal || choice > maxVal);
    return choice;
}

void showBlockOperations() {
    cout << "\nВыберите матрицу для перестановки блоков:\n";
    cout << "1. Матрица-спираль\n";
    cout << "2. Матрица-змейка\n";
    cout << "Ваш выбор: ";

    int matrixChoice;
    cin >> matrixChoice;

    int** selectedMatrix = (matrixChoice == 1) ? spiralMatrix : snakeMatrix;

    cleanDisplay();
    cout << "Исходная матрица:\n";
    showMatrix(selectedMatrix, matrixSize);

    cleanDisplay();
    cout << "1. Поворот блоков по часовой стрелке:\n\n";
    int** result1 = new int*[matrixSize];
    for (int i = 0; i < matrixSize; i++) *(result1 + i) = new int[matrixSize];
    rotateBlocksClockwise(selectedMatrix, result1, matrixSize);
    showMatrix(result1, matrixSize);
    for (int i = 0; i < matrixSize; i++) delete[] *(result1 + i);
    delete[] result1;

    cleanDisplay();
    cout << "2. Обмен блоков по диагонали:\n\n";
    int** result2 = new int*[matrixSize];
    for (int i = 0; i < matrixSize; i++) *(result2 + i) = new int[matrixSize];
    swapBlocksDiagonally(selectedMatrix, result2, matrixSize);
    showMatrix(result2, matrixSize);
    for (int i = 0; i < matrixSize; i++) delete[] *(result2 + i);
    delete[] result2;

    cleanDisplay();
    cout << "3. Обмен блоков по вертикали:\n\n";
    int** result3 = new int*[matrixSize];
    for (int i = 0; i < matrixSize; i++) *(result3 + i) = new int[matrixSize];
    swapBlocksVertically(selectedMatrix, result3, matrixSize);
    showMatrix(result3, matrixSize);
    for (int i = 0; i < matrixSize; i++) delete[] *(result3 + i);
    delete[] result3;

    cleanDisplay();
    cout << "4. Обмен блоков по горизонтали:\n\n";
    int** result4 = new int*[matrixSize];
    for (int i = 0; i < matrixSize; i++) *(result4 + i) = new int[matrixSize];
    swapBlocksHorizontally(selectedMatrix, result4, matrixSize);
    showMatrix(result4, matrixSize);
    for (int i = 0; i < matrixSize; i++) delete[] *(result4 + i);
    delete[] result4;
}

void showMatrixOperations() {
    cout << "\nВыберите матрицу для арифметических операций:\n";
    cout << "1. Матрица-спираль\n";
    cout << "2. Матрица-змейка\n";
    cout << "Ваш выбор: ";

    int matrixChoice;
    cin >> matrixChoice;

    int** selectedMatrix = (matrixChoice == 1) ? spiralMatrix : snakeMatrix;

    cleanDisplay();
    cout << "Исходная матрица:\n";
    showMatrix(selectedMatrix, matrixSize);

    cout << "\nВыберите операцию:\n";
    cout << "1. Прибавить число\n";
    cout << "2. Вычесть число\n";
    cout << "3. Умножить на число\n";
    cout << "4. Разделить на число\n";
    cout << "Ваш выбор: ";

    int operationChoice;
    cin >> operationChoice;

    cout << "\nВведите число: ";
    int value;
    cin >> value;

    char operation;
    switch(operationChoice) {
        case 1: operation = '+'; break;
        case 2: operation = '-'; break;
        case 3: operation = '*'; break;
        case 4: operation = '/'; break;
        default: operation = '+';
    }

    modifyMatrix(selectedMatrix, matrixSize, value, operation);

    cleanDisplay();
    cout << "Матрица после операции:\n";
    showMatrix(selectedMatrix, matrixSize);
}

void mainMenu() {
    do {
        cout << "Введите размер матрицы N (6, 8 или 10): ";
        cin >> matrixSize;
        if (matrixSize != 6 && matrixSize != 8 && matrixSize != 10) {
            cout << "Ошибка! Допустимые значения: 6, 8, 10\n";
        }
    } while (matrixSize != 6 && matrixSize != 8 && matrixSize != 10);

    cleanDisplay();

    int totalElements = matrixSize * matrixSize;
    int* randomNumbers = new int[totalElements];
    generateRandomNumbers(randomNumbers, matrixSize);

    cout << "Сгенерированные числа (" << totalElements << "):\n";
    for (int i = 0; i < totalElements; i++) {
        cout << *(randomNumbers + i) << " ";
        if ((i + 1) % matrixSize == 0) cout << endl;
    }

    cleanDisplay();

    spiralMatrix = new int*[matrixSize];
    snakeMatrix = new int*[matrixSize];
    for (int i = 0; i < matrixSize; i++) {
        *(spiralMatrix + i) = new int[matrixSize];
        *(snakeMatrix + i) = new int[matrixSize];
    }

    fillSpiral(randomNumbers, spiralMatrix, matrixSize);
    fillSnake(randomNumbers, snakeMatrix, matrixSize);

    cleanDisplay();
    cout << "Готовые матрицы:\n\n";
    cout << "a) Спираль:\n\n";
    showMatrix(spiralMatrix, matrixSize);
    cout << "\nб) Змейка:\n\n";
    showMatrix(snakeMatrix, matrixSize);

    while (true) {
        cleanDisplay();
        cout << "=== ГЛАВНОЕ МЕНЮ ===\n\n";
        cout << "1. Операции с блоками матриц\n";
        cout << "2. Сортировка элементов (змейка -> QuickSort)\n";
        cout << "3. Арифметические операции с матрицами\n";
        cout << "4. Выход\n";
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;

        switch(choice) {
            case 1:
                cleanDisplay();
                showBlockOperations();
                break;
            case 2: {
                cleanDisplay();
                cout << "Сортировка элементов матрицы-змейки:\n\n";

                int* sortArray = new int[totalElements];
                matrixToArray(snakeMatrix, sortArray, matrixSize);

                cout << "Массив до сортировки:\n";
                for (int i = 0; i < totalElements; i++) {
                    cout << *(sortArray + i) << " ";
                }

                quickSort(sortArray, 0, totalElements - 1);

                cout << "\n\nМассив после сортировки (QuickSort):\n";
                for (int i = 0; i < totalElements; i++) {
                    cout << *(sortArray + i) << " ";
                }

                delete[] sortArray;
                break;
            }
            case 3:
                cleanDisplay();
                showMatrixOperations();
                break;
            case 4:
                for (int i = 0; i < matrixSize; i++) {
                    delete[] *(spiralMatrix + i);
                    delete[] *(snakeMatrix + i);
                }
                delete[] spiralMatrix;
                delete[] snakeMatrix;
                delete[] randomNumbers;

                cleanDisplay();
                cout << "Программа завершена.\n";
                return;
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
        }
    }
}

int main() {
    srand(time(0));
    mainMenu();
    return 0;
}