#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Spetsialnist { KOMP_NAUKY, INFORMATYKA, MAT_EKON, FIZ_INF, TRUD_NAVCH };

struct Student
{
    string prizv;
    unsigned kurs;
    Spetsialnist spets;
    int fizyka;
    int matematyka;
    union
    {
        int programuvannya;
        int chyselni_metody;
        int pedagogika;
    };
};

void Create(Student* p, const int N);
void Print(const Student* p, const int N, const string* spetsStr);
void Sort(Student* p, const int N, const string* spetsStr);
int* IndexSort(const Student* p, const int N, const string* spetsStr);
void PrintIndexSorted(const Student* p, const int* I, const int N, const string* spetsStr);
int BinSearch(const Student* p, const int N, const string prizv, const Spetsialnist spets, const unsigned kurs, const string* spetsStr);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const string spetsStr[] = {
        "Комп'ютерні науки",
        "Інформатика",
        "Математика та економіка",
        "Фізика та інформатика",
        "Трудове навчання"
    };

    int N;
    do {
        cout << "Введіть кількість студентів N (N > 0): ";
        cin >> N;
        if (cin.fail() || N <= 0) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Помилка! Введіть ціле додатне число." << endl;
            N = 0;
        }
    } while (N <= 0);

    Student* p = new Student[N];
    bool isDataEntered = false;
    bool isPhysicallySorted = false;

    int menuItem;
    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук студента" << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: ";
        cin >> menuItem;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            menuItem = -1;
        }
        cout << endl;

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            isDataEntered = true;
            isPhysicallySorted = false;
            break;
        case 2:
            if (!isDataEntered) {
                cout << "Спочатку введіть дані (пункт [1])!" << endl;
            }
            else {
                Print(p, N, spetsStr);
            }
            break;
        case 3:
            if (!isDataEntered) {
                cout << "Спочатку введіть дані (пункт [1])!" << endl;
            }
            else {
                Sort(p, N, spetsStr);
                isPhysicallySorted = true;
                cout << "Масив фізично впорядковано." << endl;
            }
            break;
        case 4:
            if (!isDataEntered) {
                cout << "Спочатку введіть дані (пункт [1])!" << endl;
            }
            else {
                int* I = IndexSort(p, N, spetsStr);
                PrintIndexSorted(p, I, N, spetsStr);
                delete[] I;
            }
            break;
        case 5:
            if (!isDataEntered) {
                cout << "Спочатку введіть дані (пункт [1])!" << endl;
            }
            else {
                if (!isPhysicallySorted) {
                    cout << "Увага! Перед бінарним пошуком масив автоматично фізично впорядковується." << endl;
                    Sort(p, N, spetsStr);
                    isPhysicallySorted = true;
                }

                int ispets;
                unsigned kurs;
                string prizv;

                cout << "Введіть ключі пошуку:" << endl;
                do {
                    cout << " спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
                    cin >> ispets;
                    if (cin.fail() || ispets < 0 || ispets > 4) {
                        cin.clear();
                        cin.ignore(32767, '\n');
                        cout << " Помилка! Введіть число від 0 до 4." << endl;
                        ispets = -1;
                    }
                } while (ispets < 0 || ispets > 4);

                do {
                    cout << " курс (1 - 6): ";
                    cin >> kurs;
                    if (cin.fail() || kurs < 1 || kurs > 6) {
                        cin.clear();
                        cin.ignore(32767, '\n');
                        cout << " Помилка! Введіть курс від 1 до 6." << endl;
                        kurs = 0;
                    }
                } while (kurs < 1 || kurs > 6);

                cin.ignore(32767, '\n');
                cout << " прізвище: ";
                getline(cin, prizv);
                cout << endl;

                int found = BinSearch(p, N, prizv, (Spetsialnist)ispets, kurs, spetsStr);
                if (found != -1)
                    cout << "Знайдено студента у фізично впорядкованому масиві на позиції " << found + 1 << endl;
                else
                    cout << "Шуканого студента не знайдено." << endl;
            }
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! Слід ввести число - номер вибраного пункту меню." << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}

void Create(Student* p, const int N)
{
    int spets;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.ignore(32767, '\n');

        do {
            cout << " прізвище: ";
            getline(cin, p[i].prizv);
            if (p[i].prizv.empty())
                cout << " Помилка! Прізвище не може бути порожнім." << endl;
        } while (p[i].prizv.empty());

        do {
            cout << " курс (1 - 6): ";
            cin >> p[i].kurs;
            if (cin.fail() || p[i].kurs < 1 || p[i].kurs > 6) {
                cin.clear();
                cin.ignore(32767, '\n');
                cout << " Помилка! Введіть ціле число від 1 до 6." << endl;
                p[i].kurs = 0;
            }
        } while (p[i].kurs < 1 || p[i].kurs > 6);

        do {
            cout << " спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
            cin >> spets;
            if (cin.fail() || spets < 0 || spets > 4) {
                cin.clear();
                cin.ignore(32767, '\n');
                cout << " Помилка! Введіть число від 0 до 4." << endl;
                spets = -1;
            }
        } while (spets < 0 || spets > 4);
        p[i].spets = (Spetsialnist)spets;

        do {
            cout << " оцінка з фізики (1 - 5): ";
            cin >> p[i].fizyka;
            if (cin.fail() || p[i].fizyka < 1 || p[i].fizyka > 5) {
                cin.clear();
                cin.ignore(32767, '\n');
                cout << " Помилка! Введіть оцінку від 1 до 5." << endl;
                p[i].fizyka = 0;
            }
        } while (p[i].fizyka < 1 || p[i].fizyka > 5);

        do {
            cout << " оцінка з математики (1 - 5): ";
            cin >> p[i].matematyka;
            if (cin.fail() || p[i].matematyka < 1 || p[i].matematyka > 5) {
                cin.clear();
                cin.ignore(32767, '\n');
                cout << " Помилка! Введіть оцінку від 1 до 5." << endl;
                p[i].matematyka = 0;
            }
        } while (p[i].matematyka < 1 || p[i].matematyka > 5);

        switch (p[i].spets)
        {
        case KOMP_NAUKY:
            do {
                cout << " оцінка з програмування (1 - 5): ";
                cin >> p[i].programuvannya;
                if (cin.fail() || p[i].programuvannya < 1 || p[i].programuvannya > 5) {
                    cin.clear();
                    cin.ignore(32767, '\n');
                    cout << " Помилка! Введіть оцінку від 1 до 5." << endl;
                    p[i].programuvannya = 0;
                }
            } while (p[i].programuvannya < 1 || p[i].programuvannya > 5);
            break;
        case INFORMATYKA:
            do {
                cout << " оцінка з чисельних методів (1 - 5): ";
                cin >> p[i].chyselni_metody;
                if (cin.fail() || p[i].chyselni_metody < 1 || p[i].chyselni_metody > 5) {
                    cin.clear();
                    cin.ignore(32767, '\n');
                    cout << " Помилка! Введіть оцінку від 1 до 5." << endl;
                    p[i].chyselni_metody = 0;
                }
            } while (p[i].chyselni_metody < 1 || p[i].chyselni_metody > 5);
            break;
        case MAT_EKON:
        case FIZ_INF:
        case TRUD_NAVCH:
            do {
                cout << " оцінка з педагогіки (1 - 5): ";
                cin >> p[i].pedagogika;
                if (cin.fail() || p[i].pedagogika < 1 || p[i].pedagogika > 5) {
                    cin.clear();
                    cin.ignore(32767, '\n');
                    cout << " Помилка! Введіть оцінку від 1 до 5." << endl;
                    p[i].pedagogika = 0;
                }
            } while (p[i].pedagogika < 1 || p[i].pedagogika > 5);
            break;
        }
        cout << endl;
    }
}

void Print(const Student* p, const int N, const string* spetsStr)
{
    cout << "Список студентів (Рівень В):" << endl;
    cout << "=========================================================================================================" << endl;
    cout << "| №  | Прізвище      | Курс | Спеціальність            | Фізика | Матем. | Програм. | Чис.мет. | Педагог. |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " "
            << "| " << setw(13) << left << p[i].prizv
            << "| " << setw(4) << right << p[i].kurs << " "
            << "| " << setw(24) << left << spetsStr[p[i].spets] << " "
            << "| " << setw(6) << right << p[i].fizyka << " "
            << "| " << setw(6) << right << p[i].matematyka << " ";

        switch (p[i].spets)
        {
        case KOMP_NAUKY:
            cout << "| " << setw(8) << right << p[i].programuvannya << " |          |          |" << endl;
            break;
        case INFORMATYKA:
            cout << "|          | " << setw(8) << right << p[i].chyselni_metody << " |          |" << endl;
            break;
        case MAT_EKON:
        case FIZ_INF:
        case TRUD_NAVCH:
            cout << "|          |          | " << setw(8) << right << p[i].pedagogika << " |" << endl;
            break;
        }
    }
    cout << "=========================================================================================================" << endl;
    cout << endl;
}

void Sort(Student* p, const int N, const string* spetsStr)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((spetsStr[p[i1].spets] > spetsStr[p[i1 + 1].spets])
                ||
                (spetsStr[p[i1].spets] == spetsStr[p[i1 + 1].spets] &&
                    p[i1].kurs > p[i1 + 1].kurs)
                ||
                (spetsStr[p[i1].spets] == spetsStr[p[i1 + 1].spets] &&
                    p[i1].kurs == p[i1 + 1].kurs &&
                    p[i1].prizv > p[i1 + 1].prizv))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int* IndexSort(const Student* p, const int N, const string* spetsStr)
{
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;

    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
            j >= 0 && ((spetsStr[p[I[j]].spets] > spetsStr[p[value].spets]) ||
                (spetsStr[p[I[j]].spets] == spetsStr[p[value].spets] &&
                    p[I[j]].kurs > p[value].kurs) ||
                (spetsStr[p[I[j]].spets] == spetsStr[p[value].spets] &&
                    p[I[j]].kurs == p[value].kurs &&
                    p[I[j]].prizv > p[value].prizv));
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(const Student* p, const int* I, const int N, const string* spetsStr)
{
    cout << "Індексно впорядкований список студентів (Рівень В):" << endl;
    cout << "=========================================================================================================" << endl;
    cout << "| №  | Прізвище      | Курс | Спеціальність            | Фізика | Матем. | Програм. | Чис.мет. | Педагог. |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " "
            << "| " << setw(13) << left << p[I[i]].prizv
            << "| " << setw(4) << right << p[I[i]].kurs << " "
            << "| " << setw(24) << left << spetsStr[p[I[i]].spets] << " "
            << "| " << setw(6) << right << p[I[i]].fizyka << " "
            << "| " << setw(6) << right << p[I[i]].matematyka << " ";

        switch (p[I[i]].spets)
        {
        case KOMP_NAUKY:
            cout << "| " << setw(8) << right << p[I[i]].programuvannya << " |          |          |" << endl;
            break;
        case INFORMATYKA:
            cout << "|          | " << setw(8) << right << p[I[i]].chyselni_metody << " |          |" << endl;
            break;
        case MAT_EKON:
        case FIZ_INF:
        case TRUD_NAVCH:
            cout << "|          |          | " << setw(8) << right << p[I[i]].pedagogika << " |" << endl;
            break;
        }
    }
    cout << "=========================================================================================================" << endl;
    cout << endl;
}

int BinSearch(const Student* p, const int N, const string prizv, const Spetsialnist spets, const unsigned kurs, const string* spetsStr)
{
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].prizv == prizv && p[m].spets == spets && p[m].kurs == kurs)
            return m;

        if ((spetsStr[p[m].spets] < spetsStr[spets])
            ||
            (spetsStr[p[m].spets] == spetsStr[spets] &&
                p[m].kurs < kurs)
            ||
            (spetsStr[p[m].spets] == spetsStr[spets] &&
                p[m].kurs == kurs &&
                p[m].prizv < prizv))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);

    return -1;
}