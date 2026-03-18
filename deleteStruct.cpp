#include <iostream>

#include "struct.h"

using namespace std;

// Фунция удаления списка
static laptops* deleteList(laptops* lst) {
    if (lst == nullptr) {
        return nullptr;
    }
    while (lst != nullptr) {
        laptops* temp = lst->next;
        free(lst);
        lst = temp;
    }
    cout << "Данные удалены" << endl;
    return nullptr;
}

// Функция удаления элемента списка по номеру
static laptops* deleteElem(laptops* head, int position) {
    if (head == nullptr) {
        cout << "Список пуст!" << endl;
        return nullptr;
    }

    if (position <= 0) {
        cout << "Некорректная позиция!" << endl;
        return head;
    }

    if (position == 1) {
        if (head->next == nullptr) {
            free(head);
            cout << "Список стал пустым!" << endl;
            return nullptr;
        }
        laptops* temp = head->next;
        temp->prev = nullptr;
        free(head);
        cout << "Элемент №" << position << " удален" << endl;
        return temp;
    }

    laptops* current = head;
    int counter = 1;

    while (current != nullptr && counter < position) {
        current = current->next;
        counter++;
    }

    if (current == nullptr) {
        cout << "Элемент №" << position << " не найден!" << endl;
        return head;
    }

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }

    free(current);
    system("cls");
    cout << "Элемент №" << position << " удален" << endl;

    return head;
}