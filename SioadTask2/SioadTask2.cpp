#include <iostream>
#include "Kassa.h"
#include <fstream>
#include <windows.h>

int main()
{
    setlocale(0, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    char c;
    bool askNext = true;
    Kassa* kassa_list = new Kassa;
    kassa_list = addKassa(kassa_list);
    kassa_list->list = createListFromFile(kassa_list->list);
    

    while (askNext) {
        char c;
        cout << "1 - Вывести тестовый список\n";
        cout << "2 - Вывести тестовый список в обратном порядке\n";
        cout << "3 - Добавить сведения об операции\n";
        cout << "4 - Определить приход по кассе\n";
        cout << "5 - Отменить операцию\n";
        cout << "6 - Добавить кассу\n";
        cout << "7 - Выход\n";
        cin >> c;
        switch (c)
        {
        case '1': {
            printList(kassa_list);
            cout << endl;
            break;
        }
        case '2': {
            printListBackwards(kassa_list);
            cout << endl;
            break;
        }
        case '3': {
            cout << "Введите номер кассы: ";
            int id;
            cin >> id;
            while (cin.fail())
            {
                cout << "Ошибка: введено не число" << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cin >> id;
            }
            Kassa* kassa = findKassa(kassa_list, id);
            if (kassa == nullptr){
                cout << "Касса не найдена\n";
                break;
            }
            else {
                addOperation(kassa->list);
            }
            cout << endl;
            break;
        }
        case '4': {
            cout << "Введите номер кассы: ";
            int id;
            cin >> id;
            while (cin.fail())
            {
                cout << "Ошибка: введено не число" << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cin >> id;
            }
            Kassa* kassa = findKassa(kassa_list, id);
            if (kassa == nullptr) {
                cout << "Касса не найдена\n";
                break;
            }
            cout << "Введите дату в формате дд.мм.гггг: ";
            string date;
            cin >> date;
            
            cout << getProfit(kassa, date);
            cout << endl;
            break;
        }
        case '5': {
            cout << "Введите номер кассы: ";
            int id;
            cin >> id;
            while (cin.fail())
            {
                cout << "Ошибка: введено не число" << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cin >> id;
            }
            Kassa* kassa = findKassa(kassa_list, id);
            if (kassa == nullptr) {
                cout << "Касса не найдена\n";
                break;
            }
            printOperations(kassa);
            cout << "Введите номер операции: ";
            int op_id;
            cin >> op_id;
            while (cin.fail())
            {
                cout << "Ошибка: введено не число" << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cin >> op_id;
            }
            kassa->list = deleteOperation(kassa->list, op_id);
            printOperations(kassa);
            cout << endl;
            break;
        }
        case '6': {
            kassa_list = addKassa(kassa_list);
            Kassa* kassa = findKassa(kassa_list, 2);
            kassa->list = createList(kassa->list);
            cout << endl;
            break;
        }
        case '7': {
            askNext = false;
            cout << endl;
            break;
        }

        default:
            break;
        }
    }
    return 0;
}
