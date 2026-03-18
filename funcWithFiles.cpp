#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <sstream>

#include "struct.h"

using namespace std;

// Функция создания файла с расширением .txt
static fstream new_DB() {
    string fileName;
    cout << "Введите название файла - ";
    while (fileName.empty()) {
        getline(cin, fileName);
    }

    if (fileName.find(".txt") == string::npos) {
        fileName = fileName + ".txt";
    }

    fstream DB(fileName, ios::out);
    if (!DB.is_open()) {
        cout << "Произошла ошибка" << endl;
        return fstream();
    }
    cout << "Файл создан" << endl;
    return DB;
}

// Функция очистки файла
static void clear(string fileName) {
    if (fileName.empty()) {
        return;
    }

    if (fileName.find(".txt") == string::npos) {
        fileName = fileName + ".txt";
    }
    fstream file(fileName, ios::out);
    if (!file.is_open()) {
        cerr << "Произошла ошибка" << endl;
        return;
    }
    cout << "Файл очищен" << endl;
    return;
}

// Функция сохранения списка в файл
static void save_DB(laptops* lst) {
    int preference;
    cout << "[1] Открыть файл для дозаписи\n[2] Перезаписать файл\n[0] Выход\nПункт: ";
    while (!(cin >> preference) || preference < 0 || preference > 2) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (preference == 0) {
        return;
    }
    string fileName;
    cout << "Введите название файла для сохранения - ";
    while (fileName.empty()) {
        getline(cin, fileName);
    }

    if (fileName.find(".txt") == string::npos) {
        fileName += ".txt";
    }

    bool fileExists = ifstream(fileName).good();
    if (preference == 2) {
        clear(fileName);
    }
    ofstream file(fileName, ios::app);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    if (lst == nullptr) {
        cout << "Список пуст!" << endl;
        file.close();
        return;
    }

    if (!fileExists) {
        file << "Производитель,Модель,Цена,Процессор,Объем опер. памяти,";
        file << "Объем диск. памяти,Видеокарта,Размер экрана,Кол-во на складе\n";
    }

    laptops* p = lst;
    while (p != nullptr) {
        file << p->firmware << "," << p->model << "," << p->price << ",";
        file << p->processor << "," << p->RAM_Volume << "," << p->diskVolume << ",";
        file << p->videocard << "," << p->screenSize << "," << p->availability << "\n";
        p = p->next;
    }

    file.close();
    cout << "Данные успешно сохранены" << endl;
}

// Функция загрузки списка из файла
static laptops* load_DB(laptops * tail) {
    string fileName;
    cout << "Введите название файла для загрузки - ";
    while (fileName.empty()) {
        getline(cin, fileName);
    }

    if (fileName.find(".txt") == string::npos) {
        fileName += ".txt";
    }

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return nullptr;
    }

    laptops* head = nullptr;
    laptops* current = tail;
    string line;

    // Пропускаем заголовок
    getline(file, line);

    while (getline(file, line)) {
        if (line.find("+") != string::npos || line.empty()) {
            continue;
        }

        laptops* newLaptop = (laptops*)malloc(sizeof(laptops));
        if (!newLaptop) {
            cerr << "Ошибка выделения памяти" << endl;
            file.close();
            return head ? head : nullptr;
        }

        istringstream ss(line);
        string token;
        int fieldCounter = 0;

        try {
            while (getline(ss, token, ',')) {
                token.erase(0, token.find_first_not_of(" \t"));
                token.erase(token.find_last_not_of(" \t") + 1);

                switch (fieldCounter) {
                case 0: strncpy_s(newLaptop->firmware, token.c_str(), sizeof(newLaptop->firmware) - 1); break;
                case 1: strncpy_s(newLaptop->model, token.c_str(), sizeof(newLaptop->model) - 1); break;
                case 2: newLaptop->price = stof(token); break;
                case 3: strncpy_s(newLaptop->processor, token.c_str(), sizeof(newLaptop->processor) - 1); break;
                case 4: newLaptop->RAM_Volume = stoi(token); break;
                case 5: newLaptop->diskVolume = stoi(token); break;
                case 6: strncpy_s(newLaptop->videocard, token.c_str(), sizeof(newLaptop->videocard) - 1); break;
                case 7: newLaptop->screenSize = stof(token); break;
                case 8: newLaptop->availability = stoi(token); break;
                }
                fieldCounter++;
            }
        }
        catch (const exception& e) {
            cerr << "Ошибка при разборе строки: " << e.what() << endl;
            free(newLaptop);
            continue;
        }

        // Инициализация указателей
        newLaptop->prev = current;
        newLaptop->next = nullptr;

        if (current != nullptr) {
            current->next = newLaptop;
        }
        else {
            head = newLaptop;
        }
        current = newLaptop;
    }

    file.close();
    cout << "Данные успешно загружены" << endl;
    return head ? head : current;
}

// Функция удаления файла
static void remove_DB() {
    string fileName;
    cout << "Введите название файла для удаления - ";
    while (fileName.empty()) {
        getline(cin, fileName);
    }

    if (fileName.find(".txt") == string::npos) {
        fileName = fileName + ".txt";
    }
    fstream file(fileName);
    if (!file.is_open()) {
        cerr << "Произошла ошибка" << endl;
        return;
    }
    file.close();
    remove(fileName.c_str());
    cout << "Файл удалён" << endl;
}