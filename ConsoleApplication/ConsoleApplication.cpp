
#include <iostream>
using namespace std; 

////задание самостоятельные задания
// Функция для добавления строки в конец двумерного массива
int** addRowToEnd(int** array, int& rowCount, int* newRow, int colCount) {
    int** newArray = new int* [rowCount + 1];
    for (int i = 0; i < rowCount; ++i) {
        newArray[i] = array[i];
    }
    newArray[rowCount] = new int[colCount];
    for (int j = 0; j < colCount; ++j) {
        newArray[rowCount][j] = newRow[j];
    }
    delete[] array; 
    rowCount++;
    return newArray;
}

// Функция для добавления строки в начало двумерного массива
int** addRowToStart(int** array, int& rowCount, int* newRow, int colCount) {
    int** newArray = new int* [rowCount + 1];
    newArray[0] = new int[colCount];
    for (int j = 0; j < colCount; ++j) {
        newArray[0][j] = newRow[j];
    }
    for (int i = 0; i < rowCount; ++i) {
        newArray[i + 1] = array[i];
    }
    //удаление массива
    delete[] array; 
    rowCount++;
    return newArray;
}

// Функция для добавления строки в указанную позицию
int** addRowAtPosition(int** array, int& rowCount, int* newRow, int colCount, int position) {
    if (position < 0 || position > rowCount) {
        cerr << "Ошибка: указана некорректная позиция." << endl;
        return array;
    }

    int** newArray = new int* [rowCount + 1];
    for (int i = 0; i < position; ++i) {
        newArray[i] = array[i];
    }
    newArray[position] = new int[colCount];
    for (int j = 0; j < colCount; ++j) {
        newArray[position][j] = newRow[j];
    }
    for (int i = position; i < rowCount; ++i) {
        newArray[i + 1] = array[i];
    }
    delete[] array; 
    rowCount++;
    return newArray;
}

// Функция для удаления строки по указанному номеру
int** removeRow(int** array, int& rowCount, int index) {
    if (index < 0 || index >= rowCount) {
        cerr << "Ошибка: указанный индекс выходит за границы." << endl;
        return array;
    }

    int** newArray = new int* [rowCount - 1];
    for (int i = 0, j = 0; i < rowCount; ++i) {
        if (i != index) {
            newArray[j++] = array[i];
        }
        else {
            delete[] array[i]; 
        }
    }
    delete[] array; 
    rowCount--;
    return newArray;
}
//дз
int**AddColumnAtPositions (int** array, int rowCount,int colCount, int* newColumn,int position, int& newColCount) {
    if (position<0||position>colCount)
    {
        cerr << "Ошибка: указана некорректная позиция." << endl;
        return array;
    }
    int** newArray = new int* [rowCount];
    for (int i = 0; i < rowCount; ++i) {
        newArray[i] = new int[colCount + 1]; // Увеличиваем количество столбцов на 1
    }

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < position; ++j) {
            newArray[i][j] = array[i][j]; // Копируем данные до указанной позиции
        }
        newArray[i][position] = newColumn[i]; // Добавляем новый столбец
        for (int j = position; j < colCount; ++j) {
            newArray[i][j + 1] = array[i][j]; // Копируем данные после указанной позиции
        }
    }

    // Освобождаем старый массив
    for (int i = 0; i < rowCount; ++i) {
        delete[] array[i];
    }
    delete[] array;

    newColCount = colCount + 1; // Увеличиваем количество столбцов
    return newArray; // Возвращаем новый массив
}

// Функция для удаления столбца по указанному номеру
int** removeColumn(int** array, int rowCount, int colCount, int index, int& newColCount) {
    if (index < 0 || index >= colCount) {
        cerr << "Ошибка: указанный индекс выходит за границы." << endl;
        return array;
    }

    int** newArray = new int* [rowCount];
    for (int i = 0; i < rowCount; ++i) {
        newArray[i] = new int[colCount - 1]; // Уменьшаем количество столбцов на 1
        for (int j = 0, k = 0; j < colCount; ++j) {
            if (j != index) { // Копируем только те столбцы, которые не были удалены
                newArray[i][k++] = array[i][j];
            }
        }
    }

    // Освобождаем старый массив
    for (int i = 0; i < rowCount; ++i) {
        delete[] array[i];
    }
    delete[] array;

    newColCount = colCount - 1; // Уменьшаем количество столбцов
    return newArray; // Возвращаем новый массив
}


void fillMatrix(int** matrix, int M, int N) {
    int value = 1;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = value++;
        }
    }
}

// Функция для циклического сдвига строк
void shiftRows(int** matrix, int M, int N, int count, bool right) {
    count %= N; // Учитываем только остаток от деления
    if (count == 0) return; // Если сдвиг 0, ничего не меняем

    for (int i = 0; i < M; ++i) {
        int* temp = new int[N];
        if (right) {
            for (int j = 0; j < N; ++j) {
                temp[j] = matrix[i][(j - count + N) % N]; // Осуществляем сдвиг вправо
            }
        }
        else {
            for (int j = 0; j < N; ++j) {
                temp[j] = matrix[i][(j + count) % N]; // Осуществляем сдвиг влево
            }
        }
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = temp[j];
        }
        delete[] temp; // Освобождение памяти
    }
}

// Функция для циклического сдвига столбцов
void shiftColumns(int** matrix, int M, int N, int count, bool down) {
    count %= M;
    if (count == 0) return;

    for (int j = 0; j < N; ++j) {
        int* temp = new int[M];
        if (down) {
            for (int i = 0; i < M; ++i) {
                temp[i] = matrix[(i - count + M) % M][j];
            }
        }
        else {
            for (int i = 0; i < M; ++i) {
                temp[i] = matrix[(i + count) % M][j];
            }
        }
        for (int i = 0; i < M; ++i) {
            matrix[i][j] = temp[i];
        }
        delete[] temp; // Освобождение памяти
    }
}

// Функция для вывода матрицы
void printMatrix(int** matrix, int M, int N) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    //самостоятельные задания
    setlocale(LC_ALL, "RU");
    int rowCount = 3;
    int colCount = 3;
    int** array = new int* [rowCount];

    array[0] = new int[colCount] {1, 2, 3};
    array[1] = new int[colCount] {4, 5, 6};
    array[2] = new int[colCount] {7, 8, 9};

    cout << "Исходный массив:" << endl;
    printMatrix(array, rowCount, colCount);

    // Добавление строки в конец
    int newRowEnd[] = { 10, 11, 12 };
    array = addRowToEnd(array, rowCount, newRowEnd, colCount);
    cout << "\nПосле добавления строки в конец:" << endl;
    printArray(array, rowCount, colCount);

    // Добавление строки в начало
    int newRowStart[] = { 0, 0, 0 };
    array = addRowToStart(array, rowCount, newRowStart, colCount);
    cout << "\nПосле добавления строки в начало:" << endl;
    printArray(array, rowCount, colCount);

    // Добавление строки в указанную позицию
    int newRowPos[] = { 99, 99, 99 };
    array = addRowAtPosition(array, rowCount, newRowPos, colCount, 2);
    cout << "\nПосле добавления строки в позицию 2:" << endl;
    printArray(array, rowCount, colCount);

    // Удаление строки по указанному номеру
    array = removeRow(array, rowCount, 1);
    cout << "\nПосле удаления строки с индексом 1:" << endl;
    printArray(array, rowCount, colCount);

    // Освобождение памяти
    for (int i = 0; i < rowCount; ++i) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
    int rowCount = 3;
    int colCount = 3;
    int** array = new int* [rowCount];

    array[0] = new int[colCount] {1, 2, 3};
    array[1] = new int[colCount] {4, 5, 6};
    array[2] = new int[colCount] {7, 8, 9};

    cout << "Исходный массив:" << endl;
    printArray(array, rowCount, colCount);

    // Добавление столбца в указанную позицию
    int newColumn[] = { 10, 11, 12 };
    int position = 1; // Позиция для добавления нового столбца
    array = AddColumnAtPositions(array, rowCount, colCount, newColumn, position, colCount);
    cout << "\nПосле добавления столбца в позицию " << position << ":" << endl;
    printArray(array, rowCount, colCount);

    // Удаление столбца по указанному номеру
    int indexToRemove = 2; // Индекс столбца для удаления
    array = removeColumn(array, rowCount, colCount, indexToRemove, colCount);
    cout << "\nПосле удаления столбца с индексом " << indexToRemove << ":" << endl;
    printArray(array, rowCount, colCount);

    // Освобождение памяти
    for (int i = 0; i < rowCount; ++i) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
    //задание 3
    int M, N;
    cout << "Введите количество строк (M) и столбцов (N): ";
    cin >> M >> N;

    int** matrix = new int* [M];
    for (int i = 0; i < M; ++i) {
        matrix[i] = new int[N];
    }

    fillMatrix(matrix, M, N);

    cout << "Исходная матрица:" << endl;
    printMatrix(matrix, M, N);

    int shiftCount;
    char direction;
    cout << "Введите количество сдвигов: ";
    cin >> shiftCount;
    cout << "Введите направление сдвига (r - вправо, l - влево, d - вниз, u - вверх): ";
    cin >> direction;

    // Выполнение операции сдвига
    if (direction == 'r') {
        shiftRows(matrix, M, N, shiftCount, true);
    }
    else if (direction == 'l') {
        shiftRows(matrix, M, N, shiftCount, false);
    }
    else if (direction == 'd') {
        shiftColumns(matrix, M, N, shiftCount, true);
    }
    else if (direction == 'u') {
        shiftColumns(matrix, M, N, shiftCount, false);
    }
    else {
        cout << "Некорректное направление сдвига!" << endl;
        return 1;
    }

    cout << "Матрица после сдвига:" << endl;
    printMatrix(matrix, M, N);

    // Освобождение памяти
    for (int i = 0; i < M; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}

