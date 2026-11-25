#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.2.B/Lab_10.2.B.cpp" // Шлях до заголовного файлу проєкту Рівня В

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLevelB
{
    TEST_CLASS(UnitTestLevelB)
    {
    public:
        TEST_METHOD(TestUnionSortAndBinSearch_LevelB)
        {
            const string spetsStr[] = {
                "Комп'ютерні науки",
                "Інформатика",
                "Математика та економіка",
                "Фізика та інформатика",
                "Трудове навчання"
            };

            const int N = 4;
            Student* p = new Student[N];

            p[0].prizv = "Коваленко"; p[0].kurs = 3; p[0].spets = TRUD_NAVCH;
            p[0].fizyka = 4; p[0].matematyka = 4; p[0].pedagogika = 5;

            p[1].prizv = "Бондаренко"; p[1].kurs = 2; p[1].spets = INFORMATYKA;
            p[1].fizyka = 5; p[1].matematyka = 5; p[1].chyselni_metody = 4;

            p[2].prizv = "Шевченко"; p[2].kurs = 1; p[2].spets = KOMP_NAUKY;
            p[2].fizyka = 5; p[2].matematyka = 4; p[2].programuvannya = 5;

            p[3].prizv = "Мельник"; p[3].kurs = 1; p[3].spets = KOMP_NAUKY;
            p[3].fizyka = 4; p[3].matematyka = 5; p[3].programuvannya = 4;

            // 1. Перевірка спільного використання пам'яті в union
            Assert::AreEqual(5, p[2].programuvannya);
            Assert::AreEqual(5, p[2].pedagogika); // Одне поле в пам'яті

            // 2. Перевірка індексного сортування
            // Порядок: Інформатика (1) -> Комп'ютерні науки/Мельник (3) -> Комп'ютерні науки/Шевченко (2) -> Трудове навчання (0)
            int* I = IndexSort(p, N, spetsStr);
            Assert::AreEqual(1, I[0]);
            Assert::AreEqual(3, I[1]);
            Assert::AreEqual(2, I[2]);
            Assert::AreEqual(0, I[3]);
            delete[] I;

            // 3. Перевірка фізичного сортування та бінарного пошуку
            Sort(p, N, spetsStr);
            Assert::AreEqual(string("Бондаренко"), p[0].prizv);
            Assert::AreEqual(string("Мельник"), p[1].prizv);
            Assert::AreEqual(string("Шевченко"), p[2].prizv);
            Assert::AreEqual(string("Коваленко"), p[3].prizv);

            int idx1 = BinSearch(p, N, "Мельник", KOMP_NAUKY, 1, spetsStr);
            Assert::AreEqual(1, idx1);

            int idx2 = BinSearch(p, N, "Неіснуючий", INFORMATYKA, 2, spetsStr);
            Assert::AreEqual(-1, idx2);

            delete[] p;
        }
    };
}