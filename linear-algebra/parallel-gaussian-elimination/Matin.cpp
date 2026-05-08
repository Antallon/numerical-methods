 #include "Matin.h"

int fromfile(double *A, int n, string filename)
{
    int counter = 0;

    ifstream file(filename); // Открываем файл для чтения

    if (!file.is_open())
    {
        cerr << "Error: Unable to open file '" << filename << "'" << endl;
        return -1; // Возвращаем код ошибки
    }

    for (int i = 0; i < n * n; i++)
    {
        if (!(file >> A[i]))
        {
            cerr << "Error: Invalid or insufficient data in file '" << filename << "'" << endl;
            file.close(); // Закрываем файл
            return -1;    // Возвращаем код ошибки
        }
        else
        {
            counter++;
        }
    }

    file.close(); // Закрываем файл

    return 0; // Всё прошло успешно
}
