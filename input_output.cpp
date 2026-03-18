#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <limits>

#include "struct.h"

using namespace std;

// Функция добавления новой записи
static laptops* addLaptop(laptops* tail) {
    laptops* newLaptop = (laptops*)malloc(sizeof(laptops));
    if (!newLaptop) {
        cerr << "Произошла ошибка выделения памяти" << endl;
    }

    cout << "Производитель - ";
    do {
        cin.getline(newLaptop->firmware, 99);
    } while (empty(newLaptop->firmware));
    

    cout << "Модель - ";
    do {
        cin.getline(newLaptop->model, 99);
    } while (empty(newLaptop->model));

    cout << "Цена (Положительное число, byn) - ";
    while (!(cin >> newLaptop->price) || newLaptop->price <= 0) {
        cout << "Неверный ввод. Повторите: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Процессор - ";
    do {
        cin.getline(newLaptop->processor, 99);
    } while (empty(newLaptop->processor));

    cout << "Объем опер. памяти (целое положительное число, gb) - ";
    while (!(cin >> newLaptop->RAM_Volume) || newLaptop->RAM_Volume <= 0) {
        cout << "Неверный ввод. Повторите: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Объем диск. памяти (целое положительное число, gb) - ";
    while (!(cin >> newLaptop->diskVolume) || newLaptop->diskVolume <= 0) {
        cout << "Неверный ввод. Повторите: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Видеокарта - ";
    do {
        cin.getline(newLaptop->videocard, 99);
    } while (empty(newLaptop->videocard));

    cout << "Размер экрана (число с плавающей точкой, положительное, дюймов) - ";
    while (!(cin >> newLaptop->screenSize) || newLaptop->screenSize <= 0) {
        cout << "Неверный ввод. Повторите: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Кол-во на складе (целое число, штук)- ";
    while (!(cin >> newLaptop->availability) || newLaptop->availability <= 0) {
        cout << "Неверный ввод. Повторите: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    newLaptop->prev = tail;
    newLaptop->next = nullptr;

    if (tail != nullptr) {
        tail->next = newLaptop;
    }
    cout << "Данные добавлены" << endl;
    return newLaptop;
}

// Функция вывода 1 ноутбука
static void printLaptop(laptops* lst) {
    cout << "Производитель: " << lst->firmware << "\n"
        << "Модель: " << lst->model << "\n"
        << "Цена: " << lst->price << " руб.\n"
        << "Процессор: " << lst->processor << "\n"
        << "RAM: " << lst->RAM_Volume << " GB\n"
        << "Диск: " << lst->diskVolume << " GB\n"
        << "Видеокарта: " << lst->videocard << "\n"
        << "Экран: " << lst->screenSize << "\"\n"
        << "Наличие: " << lst->availability << "\n\n";
}

// Функция вывода списка в табличном формате
static void printList(laptops* head) {
    if (head == nullptr) {
        cout << "Список пуст!" << endl;
        return;
    }

    laptops* p = head;
    int recordNumber = 1;

    cout << "+--------+--------------------+--------------------+--------------------+--------------------+";
    cout << "--------------------+--------------------+--------------------+--------------------+--------------------+" << endl;
    cout << "| " << setw(7) << left << "№" << "| " << setw(19) << left << "Производитель" << "| " << setw(19) << left << "Модель" << "| " << setw(19) << left << "Цена" << "| " << setw(19) << left << "Процессор" << "| " << setw(19) << left << "RAM (GB)";
    cout << "| " << setw(19) << left << "Диск (GB)" << "| " << setw(19) << left << "Видеокарта" << "| " << setw(19) << left << "Экран (\")" << "| " << setw(19) << left << "Наличие" << "|" << endl;
    cout << "+--------+--------------------+--------------------+--------------------+--------------------+";
    cout << "--------------------+--------------------+--------------------+--------------------+--------------------+" << endl;

    while (p != nullptr) {
        cout << "| " << setw(7) << left << recordNumber++
            << "| " << setw(19) << left << p->firmware
            << "| " << setw(19) << left << p->model
            << "| " << setw(19) << left << p->price
            << "| " << setw(19) << left << p->processor
            << "| " << setw(19) << left << p->RAM_Volume
            << "| " << setw(19) << left << p->diskVolume
            << "| " << setw(19) << left << p->videocard
            << "| " << setw(19) << left << p->screenSize
            << "| " << setw(19) << left << p->availability << "|" << endl;
        cout << "+--------+--------------------+--------------------+--------------------+--------------------+";
        cout << "--------------------+--------------------+--------------------+--------------------+--------------------+" << endl;
        p = p->next;
    }
}

// Функция редактирования поля в элемента списка по номеру узла
static void changeElem(laptops* head, int position) {
    if (head == nullptr) {
        cout << "Список пуст!" << endl;
        return;
    }
    if (position <= 0) {
        cout << "Некорректная позиция!" << endl;
        return;
    }

    int i = 1;
    laptops* lst = head;
    while (lst != nullptr && i < position) {
        lst = lst->next;
        i++;
    }

    if (lst == nullptr) {
        cout << "Элемент №" << position << " не найден!" << endl;
        return;
    }

    int counter;
    while (true) {
        cout << "[1] Производитель" << endl;
        cout << "[2] Модель" << endl;
        cout << "[3] Цена" << endl;
        cout << "[4] Процессор" << endl;
        cout << "[5] Объем оперативной памяти" << endl;
        cout << "[6] Объем дисковой памяти" << endl;
        cout << "[7] Видеокарта" << endl;
        cout << "[8] Размер экрана" << endl;
        cout << "[9] Количество на складе" << endl;
        cout << "[0] Выход" << endl;
        cout << "Пункт меню: ";

        if (!(cin >> counter)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Ошибка: введите число от 0 до 9!\n\n";
            continue;
        }

        if (counter >= 0 && counter <= 9) {
            break;
        }

        system("cls");
        cout << "Ошибка: введите число от 0 до 9!\n\n";
    }
    system("cls");

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char buffer[100];
    switch (counter) {
    case 1: {
        cout << "Текущий производитель: " << lst->firmware << endl;
        cout << "Новый производитель: ";
        cin.getline(buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            strncpy_s(lst->firmware, buffer, sizeof(lst->firmware) - 1);
            lst->firmware[sizeof(lst->firmware) - 1] = '\0';
        }
        break;
    }
    case 2: {
        cout << "Текущая модель: " << lst->model << endl;
        cout << "Новая модель: ";
        cin.getline(buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            strncpy_s(lst->model, buffer, sizeof(lst->model) - 1);
            lst->model[sizeof(lst->model) - 1] = '\0';
        }
        break;
    }
    case 3: {
        cout << "Текущая цена: " << lst->price << endl;
        cout << "Новая цена (Положительное число, byn): ";
        while (!(cin >> lst->price) || lst->price <= 0) {
            cout << "Неверный ввод. Повторите: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        break;
    }
    case 4: {
        cout << "Текущий процессор: " << lst->processor << endl;
        cout << "Новый процессор: ";
        cin.getline(buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            strncpy_s(lst->processor, buffer, sizeof(lst->processor) - 1);
            lst->processor[sizeof(lst->processor) - 1] = '\0';
        }
        break;
    }
    case 5: {
        cout << "Текущий объем ОЗУ: " << lst->RAM_Volume << endl;
        cout << "Новый объем ОЗУ (целое положительное число, gb): ";
        while (!(cin >> lst->RAM_Volume) || lst->RAM_Volume <= 0) {
            cout << "Неверный ввод. Повторите: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        break;
    }
    case 6: {
        cout << "Текущий объем диска: " << lst->diskVolume << endl;
        cout << "Новый объем диска (целое положительное число, gb): ";
        while (!(cin >> lst->diskVolume) || lst->diskVolume <= 0) {
            cout << "Неверный ввод. Повторите: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        break;
    }
    case 7: {
        cout << "Текущая видеокарта: " << lst->videocard << endl;
        cout << "Новая видеокарта: ";
        cin.getline(buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            strncpy_s(lst->videocard, buffer, sizeof(lst->videocard) - 1);
            lst->videocard[sizeof(lst->videocard) - 1] = '\0';
        }
        break;
    }
    case 8: {
        cout << "Текущий размер экрана: " << lst->screenSize << endl;
        cout << "Новый размер экрана (число с плавающей точкой, положительное, дюймов): ";
        while (!(cin >> lst->screenSize) || lst->screenSize <= 0) {
            cout << "Неверный ввод. Повторите: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        break;
    }
    case 9: {
        cout << "Текущее количество на складе: " << lst->availability << endl;
        cout << "Новое количество на складе (целое число, штук): ";
        while (!(cin >> lst->availability) || lst->availability < 0) {
            cout << "Неверный ввод. Повторите: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        break;
    }
    case 0: {
        return;
    }
    }

    system("cls");
    cout << "Элемент №" << position << " изменен" << endl;
}