#include <iostream>
#include <cstring>
#include <limits>
#include "deleteStruct.h"
#include "struct.h"
#include "input_output.h"

using namespace std;

// Функция для создания копии записи
static laptops* createCopy(laptops* src) {
    laptops* copy = (laptops*)malloc(sizeof(laptops));
    strcpy_s(copy->firmware, src->firmware);
    strcpy_s(copy->model, src->model);
    copy->price = src->price;
    strcpy_s(copy->processor, src->processor);
    copy->RAM_Volume = src->RAM_Volume;
    copy->diskVolume = src->diskVolume;
    strcpy_s(copy->videocard, src->videocard);
    copy->screenSize = src->screenSize;
    copy->availability = src->availability;
    copy->prev = copy->next = nullptr;
    return copy;
}

// Функция для подсчета записей
static int countLaptops(laptops* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Функция для поиска и фильтрации записи
static void search(laptops* head) {
    if (!head) {
        cout << "Список пуст!\n";
        return;
    }

    laptops* filteredHead = nullptr;
    laptops* filteredTail = nullptr;

    laptops* current = head;
    while (current) {
        laptops* newNode = createCopy(current);
        if (!filteredHead) {
            filteredHead = filteredTail = newNode;
        }
        else {
            filteredTail->next = newNode;
            newNode->prev = filteredTail;
            filteredTail = newNode;
        }
        current = current->next;
    }

    bool continueFiltering = true;
    while (continueFiltering) {
        system("cls");
        cout << "Текущее количество записей: " << countLaptops(filteredHead) << "\n";
        cout << "Выберите действие:\n"
            << "1. Добавить фильтр\n"
            << "2. Показать результаты\n"
            << "0. Выход\n> ";

        int action;
        while (!(cin >> action) || action < 0 || action > 2) {
            system("cls");
            cout << "Неверный ввод\n";
            cout << "Выберите действие:\n"
                << "1. Добавить фильтр\n"
                << "2. Показать результаты\n"
                << "0. Выход\n> ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (action) {
        case 1: {
            system("cls");
            cout << "Выберите поле для фильтрации:\n"
                << "1. Производитель\n2. Модель\n3. Цена\n4. Процессор\n"
                << "5. Объем RAM\n6. Объем диска\n7. Видеокарта\n"
                << "8. Размер экрана\n9. Наличие\n0. Выход\n> ";

            int choice;
            while (!(cin >> choice) || choice < 0 || choice > 9) {
                system("cls");
                cout << "Неверный ввод\n";
                cout << "Выберите поле для фильтрации:\n"
                    << "1. Производитель\n2. Модель\n3. Цена\n4. Процессор\n"
                    << "5. Объем RAM\n6. Объем диска\n7. Видеокарта\n"
                    << "8. Размер экрана\n9. Наличие\n0. Выход\n> ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (choice == 0) break;

            laptops* newFilteredHead = nullptr;
            laptops* newFilteredTail = nullptr;
            int count = 0;

            if (choice == 1 || choice == 2 || choice == 4 || choice == 7) {
                char searchStr[100];
                cout << "Введите строку для поиска: ";
                cin.ignore();
                cin.getline(searchStr, 99);

                current = filteredHead;
                while (current) {
                    bool match = false;
                    switch (choice) {
                    case 1: match = strstr(current->firmware, searchStr) != nullptr; break;
                    case 2: match = strstr(current->model, searchStr) != nullptr; break;
                    case 4: match = strstr(current->processor, searchStr) != nullptr; break;
                    case 7: match = strstr(current->videocard, searchStr) != nullptr; break;
                    }

                    if (match) {
                        laptops* newNode = createCopy(current);
                        if (!newFilteredHead) {
                            newFilteredHead = newFilteredTail = newNode;
                        }
                        else {
                            newFilteredTail->next = newNode;
                            newNode->prev = newFilteredTail;
                            newFilteredTail = newNode;
                        }
                        count++;
                    }
                    current = current->next;
                }
            }
            else {
                int filterType;
                cout << "Тип фильтра:\n1. Равно\n2. Больше\n3. Меньше\n> ";
                while (!(cin >> filterType) || filterType < 1 || filterType > 3) {
                    system("cls");
                    cout << "Неверный ввод\n";
                    cout << "Тип фильтра:\n1. Равно\n2. Больше\n3. Меньше\n> ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                current = filteredHead;
                switch (choice) {
                case 3: { 
                    float value;
                    cout << "Введите цену: ";
                    while (!(cin >> value)) {
                        system("cls");
                        cout << "Неверный ввод\n" << "Введите цену: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    while (current) {
                        bool match = false;
                        switch (filterType) {
                        case 1: match = current->price == value; break;
                        case 2: match = current->price > value; break;
                        case 3: match = current->price < value; break;
                        }
                        if (match) {
                            laptops* newNode = createCopy(current);
                            if (!newFilteredHead) {
                                newFilteredHead = newFilteredTail = newNode;
                            }
                            else {
                                newFilteredTail->next = newNode;
                                newNode->prev = newFilteredTail;
                                newFilteredTail = newNode;
                            }
                            count++;
                        }
                        current = current->next;
                    }
                    break;
                }
                case 5: {
                    float value;
                    cout << "Введите объем оперативной памяти: ";
                    while (!(cin >> value)) {
                        system("cls");
                        cout << "Неверный ввод\n" << "Введите объем оперативной памяти: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    while (current) {
                        bool match = false;
                        switch (filterType) {
                        case 1: match = current->RAM_Volume == value; break;
                        case 2: match = current->RAM_Volume > value; break;
                        case 3: match = current->RAM_Volume < value; break;
                        }
                        if (match) {
                            laptops* newNode = createCopy(current);
                            if (!newFilteredHead) {
                                newFilteredHead = newFilteredTail = newNode;
                            }
                            else {
                                newFilteredTail->next = newNode;
                                newNode->prev = newFilteredTail;
                                newFilteredTail = newNode;
                            }
                            count++;
                        }
                        current = current->next;
                    }
                    break;
                }
                case 6: {
                    float value;
                    cout << "Введите объем дисковой памяти: ";
                    while (!(cin >> value)) {
                        system("cls");
                        cout << "Неверный ввод\n" << "Введите объем дисковой памяти: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    while (current) {
                        bool match = false;
                        switch (filterType) {
                        case 1: match = current->diskVolume == value; break;
                        case 2: match = current->diskVolume > value; break;
                        case 3: match = current->diskVolume < value; break;
                        }
                        if (match) {
                            laptops* newNode = createCopy(current);
                            if (!newFilteredHead) {
                                newFilteredHead = newFilteredTail = newNode;
                            }
                            else {
                                newFilteredTail->next = newNode;
                                newNode->prev = newFilteredTail;
                                newFilteredTail = newNode;
                            }
                            count++;
                        }
                        current = current->next;
                    }
                    break;
                }
                case 8: {
                    float value;
                    cout << "Введите размер экрана: ";
                    while (!(cin >> value)) {
                        system("cls");
                        cout << "Неверный ввод\n" << "Введите размер экрана: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    while (current) {
                        bool match = false;
                        switch (filterType) {
                        case 1: match = current->screenSize == value; break;
                        case 2: match = current->screenSize > value; break;
                        case 3: match = current->screenSize < value; break;
                        }
                        if (match) {
                            laptops* newNode = createCopy(current);
                            if (!newFilteredHead) {
                                newFilteredHead = newFilteredTail = newNode;
                            }
                            else {
                                newFilteredTail->next = newNode;
                                newNode->prev = newFilteredTail;
                                newFilteredTail = newNode;
                            }
                            count++;
                        }
                        current = current->next;
                    }
                    break;
                }
                case 9: {
                    int value;
                    cout << "Введите количество на складе: ";
                    while (!(cin >> value)) {
                        system("cls");
                        cout << "Неверный ввод\n" << "Введите количество на складе: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    while (current) {
                        bool match = false;
                        switch (filterType) {
                        case 1: match = current->availability == value; break;
                        case 2: match = current->availability > value; break;
                        case 3: match = current->availability < value; break;
                        }
                        if (match) {
                            laptops* newNode = createCopy(current);
                            if (!newFilteredHead) {
                                newFilteredHead = newFilteredTail = newNode;
                            }
                            else {
                                newFilteredTail->next = newNode;
                                newNode->prev = newFilteredTail;
                                newFilteredTail = newNode;
                            }
                            count++;
                        }
                        current = current->next;
                    }
                    break;
                }

                }
            }

            deleteList(filteredHead);
            system("cls");
            filteredHead = newFilteredHead;
            filteredTail = newFilteredTail;

            cout << "Применен фильтр. Осталось записей: " << count << "\n";
            system("pause");
            break;
        }
        case 2: {
            system("cls");
            printList(filteredHead);
            system("pause");
            break;
        }
        case 0: {
            continueFiltering = false;
            break;
        }
        }
    }
    deleteList(filteredHead);
    system("cls");
    cout << "Выход из меню фильтра" << endl;
}