#include <iostream>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <exception>

#include "struct.h"

using namespace std;

// Функция обмена узлов списка без замены указателей
static laptops* swap(laptops* lst1, laptops* lst2) {
    if (lst1 == nullptr && lst2 != nullptr)
        return lst2;
    else if (lst2 == nullptr && lst1 != nullptr)
        return lst1;
    else if (lst1 == nullptr && lst2 == nullptr)
        return nullptr;
    laptops* temp = (laptops*)calloc(1, sizeof(laptops));

    strcpy_s(temp->firmware, lst1->firmware);
    strcpy_s(temp->model, lst1->model);
    temp->price = lst1->price;
    strcpy_s(temp->processor, lst1->processor);
    temp->RAM_Volume = lst1->RAM_Volume;
    temp->diskVolume = lst1->diskVolume;
    strcpy_s(temp->videocard, lst1->videocard);
    temp->screenSize = lst1->screenSize;
    temp->availability = lst1->availability;

    strcpy_s(lst1->firmware, lst2->firmware);
    strcpy_s(lst1->model, lst2->model);
    lst1->price = lst2->price;
    strcpy_s(lst1->processor, lst2->processor);
    lst1->RAM_Volume = lst2->RAM_Volume;
    lst1->diskVolume = lst2->diskVolume;
    strcpy_s(lst1->videocard, lst2->videocard);
    lst1->screenSize = lst2->screenSize;
    lst1->availability = lst2->availability;

    strcpy_s(lst2->firmware, temp->firmware);
    strcpy_s(lst2->model, temp->model);
    lst2->price = temp->price;
    strcpy_s(lst2->processor, temp->processor);
    lst2->RAM_Volume = temp->RAM_Volume;
    lst2->diskVolume = temp->diskVolume;
    strcpy_s(lst2->videocard, temp->videocard);
    lst2->screenSize = temp->screenSize;
    lst2->availability = temp->availability;

    free(temp);
    return lst1;
}

// Пузырьковая сортировка полей по выбору пользователя
static void bubbleSort(laptops* head) {
    if (head == nullptr) {
        cout << "Список пуст!" << endl;
        return;
    }

    bool swapped;
    laptops* ptr1;
    laptops* lptr = nullptr;

    laptops* tail = head;
    while (tail->next != nullptr)
        tail = tail->next;

    int sortField, sortOrder;

    cout << "Выберите поле для сортировки:\n";
    cout << "[1] Производитель\n[2] Модель\n[3] Цена\n[4] Процессор\n";
    cout << "[5] Объем оперативной памяти\n[6] Объем дисковой памяти\n";
    cout << "[7] Видеокарта\n[8] Размер экрана\n[9] Количество на складе\n";
    cout << "[0] Выход\nПункт меню: ";
    while (!(cin >> sortField) || sortField < 0 || sortField > 10) {
        system("cls");
        cout << "Неверный ввод\n";
        cout << "Выберите поле для сортировки:\n";
        cout << "[1] Производитель\n[2] Модель\n[3] Цена\n[4] Процессор\n";
        cout << "[5] Объем оперативной памяти\n[6] Объем дисковой памяти\n";
        cout << "[7] Видеокарта\n[8] Размер экрана\n[9] Количество на складе\n";
        cout << "[0] Выход\nПункт меню: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    system("cls");
    if (sortField == 0) return;

    if (sortField != 2 && sortField != 4 && sortField != 7) {
        cout << "Порядок сортировки:\n[1] По возрастанию\n[2] По убыванию\nВыбор: ";
        while (!(cin >> sortOrder) || sortOrder < 1 || sortOrder > 2) {
            system("cls");
            cout << "Неверный ввод\n";
            cout << "Порядок сортировки:\n[1] По возрастанию\n[2] По убыванию\nВыбор: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    system("cls");

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            bool needSwap = false;

            switch (sortField) {
            case 1: // Производитель (строка)
            {
                if (sortOrder == 1)
                    needSwap = strcmp(ptr1->firmware, ptr1->next->firmware) > 0;
                else
                    needSwap = strcmp(ptr1->firmware, ptr1->next->firmware) < 0;
                break;

            }
            case 2: // Модель (строка)
            {
                needSwap = strcmp(ptr1->model, ptr1->next->model) > 0;
                break;
            }
            case 3: // Цена (число)
            {
                if (sortOrder == 1)
                    needSwap = ptr1->price > ptr1->next->price;
                else
                    needSwap = ptr1->price < ptr1->next->price;
                break;
            }
            case 4: // Процессор (строка)
            {
                needSwap = strcmp(ptr1->processor, ptr1->next->processor) > 0;
                break;
            }
            case 5: // RAM (число)
            {
                if (sortOrder == 1)
                    needSwap = ptr1->RAM_Volume > ptr1->next->RAM_Volume;
                else
                    needSwap = ptr1->RAM_Volume < ptr1->next->RAM_Volume;
                break;
            }
            case 6: // Диск (число)
            {
                if (sortOrder == 1)
                    needSwap = ptr1->diskVolume > ptr1->next->diskVolume;
                else
                    needSwap = ptr1->diskVolume < ptr1->next->diskVolume;
                break;
            }
            case 7: // Видеокарта (строка)
            {
                needSwap = strcmp(ptr1->videocard, ptr1->next->videocard) > 0;
                break;
            }
            case 8: // Экран (число с плав. точкой)
            {
                if (sortOrder == 1)
                    needSwap = ptr1->screenSize > ptr1->next->screenSize;
                else
                    needSwap = ptr1->screenSize < ptr1->next->screenSize;
                break;

            }
            case 9: // Наличие (число)
            {
                if (sortOrder == 1)
                    needSwap = ptr1->availability > ptr1->next->availability;
                else
                    needSwap = ptr1->availability < ptr1->next->availability;
                break;
            }
            } 

            if (needSwap) {
                swap(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    cout << "Данные отсортированы!\n";
}