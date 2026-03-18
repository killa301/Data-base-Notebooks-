#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <fstream>

#include "struct.h"
#include "input_output.h"
#include "funcWithFiles.h"
#include "deleteStruct.h"
#include "sort.h"
#include "search&filter.h"


using namespace std;

// Функция для вывода меню в консоль
static void menu() {
    int choice;
    laptops* head = nullptr;
    laptops* tail = nullptr;
    fstream file;

    while (true) {
        cout << "Меню: " << endl;
        cout << "[1] Добавить ноутбук" << endl;
        cout << "[2] Вывести ноутбуки в табличном формате" << endl;
        cout << "[3] Новый файл .txt" << endl;
        cout << "[4] Удалить файл .txt" << endl;
        cout << "[5] Сохранить в файл .txt" << endl;
        cout << "[6] Загрузить из файла .txt" << endl;
        cout << "[7] Сортировка по полям" << endl;
        cout << "[8] Фильтрация и поиск ноутбуков" << endl;
        cout << "[9] Удаление ноутбука по номеру" << endl;
        cout << "[10] Редактирования характеристик ноутбука" << endl;
        cout << "[11] Удалить список ноутбуков" << endl;
        cout << "[0] Выйти" << endl;
        cout << "Пункт меню: ";

        if (!(cin >> choice) || choice < 0 || choice > 11) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            system("cls");
            cout << "Ошибка: введите число от 0 до 11!\n\n";
            continue;
        }
        cin.ignore();

        system("cls");

        switch (choice) {
        case 1: {
            if (head == nullptr) {
                head = tail = addLaptop(head);
            }
            else {
                tail = addLaptop(tail);
            }
            system("pause");
            break;
        }
        case 2: {
            printList(head);
            system("pause");
            break;
        }
        case 3: {
            file = new_DB();
            system("pause");
            break;
        }
        case 4: {
            remove_DB();
            system("pause");
            break;
        }
        case 5: {
            save_DB(head);
            system("pause");
            break;
        }
        case 6: {
            laptops* newTail = load_DB(tail);
            if (newTail != nullptr) {
                if (head == nullptr) {
                    head = newTail;
                    tail = head;
                    while (tail->next != nullptr) {
                        tail = tail->next;
                    }
                }
                else {
                    tail = newTail;
                }
            }
            system("pause");
            break;
        }
        case 7: {
            bubbleSort(head);
            system("pause");
            break;
        }
        case 8: {
            search(head);
            system("pause");
            break;
        }
        case 9: {
            int num;
            cout << "Введите номер узла, который нужно удалить: ";
            while (!(cin >> num)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                cout << "Введите целое число!";
                cout << "Введите номер узла, который нужно удалить: ";
            }
            head = deleteElem(head, num);
            system("pause");
            break;
        }
        case 10: {
            int num;
            cout << "Введите номер узла, который нужно изменить: ";
            while (!(cin >> num)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                cout << "Введите целое число!";
                cout << "Введите номер узла, который нужно изменить: ";
            }
            system("cls");
            changeElem(head, num);
            system("pause");
            break;
        }
        case 11: {
            head = deleteList(head);
            system("pause");
            break;
        }
        case 0: {
            deleteList(head);
            cout << "Выход из программы" << endl;
            return;
        }
        }
        system("cls");
    }
}