#include "Kassa.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Функция добавления кассы в список
// id кассы назначается автоматически
// возвращает первый элемент списка
Kassa* addKassa(Kassa* head) {
	Kassa* curr = head;
	int id = 1;
	// Если первый элемент NULL
	if (head == nullptr || head->isNull) {
		Kassa* kassa = new Kassa;
		kassa->id = id;
		head = kassa;
		curr = head;
		head->isNull = false;
		id++;
	}
	// Иначе доходим до конца списка
	else {
		while (curr->next != nullptr) {
			curr->id = id;
			curr = curr->next;
			id++;
		}
		id++;
		Kassa* kassa = new Kassa;
		kassa->id = id;
		kassa->prev = curr;
		curr->next = kassa;
	}
	return head;
}

// Функция создания списка операций кассы
// Возвращает первый элемент списка
Operation* createList(Operation* head) {
	Operation* curr = head;
	cout << "Введите кол-во операций: ";
	int n;
	cin >> n;
	// проверка на корректность ввода
	while (cin.fail())
	{
		cout << "Ошибка" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> n;
	}
	for (int i = 0; i < n; i++) {
		cout << "Операция № " << i << endl;
		Operation* node = new Operation;
		cout << "Код товара: ";
		cin >> node->product_id;
		cout << "Количество: ";
		cin >> node->amount;
		cout << "Единицы измерения: ";
		cin >> node->unit;
		cout << "Цена за единицу: ";
		cin >> node->price;
		node->cost = node->price * node->amount;
		cout << "Стоимость: " << node->cost << endl;
		cout << "Дата в формате дд.мм.гггг: ";
		cin >> node->date;
		node->isNull = false;
		if (head == nullptr || head->isNull) {
			node->id = 1;
			head = node;
			curr = head;
		}
		else {
			node->id = curr->id + 1;
			curr->next = node;
			node->prev = curr;
			curr = node;
		}
	}
	return head;
}

// Функция добавления сведений о проведенной операции
void addOperation(Operation* head) {
	Operation* curr = head;
	while (curr->next != nullptr) {
		curr = curr->next;
	}
	Operation* node = new Operation;
	cout << "Код товара: ";
	cin >> node->product_id;
	cout << "Количество: ";
	cin >> node->amount;
	cout << "Единицы измерения: ";
	cin >> node->unit;
	cout << "Цена за единицу: ";
	cin >> node->price;
	node->cost = node->price * node->amount;
	cout << "Стоимость: " << node->cost;
	cout << "Дата в формате дд.мм.гггг: ";
	cin >> node->date;
	node->id = curr->id + 1;
	curr->next = node;
	node->prev = curr;
}

// Функция определения прихода по кассе в определенную дату
float getProfit(Kassa* kassa, string date) {
	float profit = 0;
	if (kassa == nullptr) {
		return profit;
	}
	Operation* curr_op = kassa->list;
	while (curr_op != nullptr) {
		if (curr_op->date == date) {
			profit += curr_op->cost;
		}
		curr_op = curr_op->next;
	}
	return profit;
}


// Функция удаления операции
// Возвращает указатель на первый элемент списка операций
Operation* deleteOperation(Operation* head, int id){
	if (head == nullptr) {
		return head;
	}
	Operation* curr = head;
	while (curr != nullptr) {
		if (curr->id == id)
			break;
		curr = curr->next;
	}
	// Если элемент не найден
	if (curr == nullptr) {
		return head;
	}	
	// Если нужно удалить первый элемент
	if (curr == head) {
		// Если элемент не единственный в списке
		if (curr->next != nullptr) {
			head = curr->next;
			Operation* toDelete = curr;
			curr = curr->next;
			curr->prev = nullptr;
			delete(toDelete);
		}
		else {
			head = nullptr;
			delete(curr);
		}
	}
	// Элемент не первый
	else {
		// Элемент не последний
		if (curr->next != nullptr) {
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			Operation* toDelete = curr;
			curr = curr->next;
			delete(toDelete);
		}
		// Элемент последний
		else {
			curr->prev->next = nullptr;
			delete(curr);
		}
	}
	// Заново назначаем номера продуктам в списке
	curr = head;
	int node_id = 0;
	while (curr != nullptr) {
		node_id++;
		curr->id = node_id;
		curr = curr->next;
	}
	return head;
}

// Функция вывода операций кассы
void printOperations(Kassa* kassa) {

	Operation* curr_op = kassa->list;
	cout << "Касса № " << kassa->id << endl;
	while (curr_op != nullptr) {
		cout << curr_op->id << ") Код: " << curr_op->product_id << " " << curr_op->amount << " " << curr_op->unit << " цена: " 
			<< curr_op->price << " стоимость: " << curr_op->cost << " Дата: " << curr_op->date << endl;
		curr_op = curr_op->next;
	}
}

// Функция вывода всех операций всех касс
void printList(Kassa* head) {
	if (head == nullptr)
		return;
	Kassa* curr = head;
	while (curr != nullptr) {
		printOperations(curr);
		curr = curr->next;
	}
}

// Функция вывода всех операций всех касс в обратном порядке
void printListBackwards(Kassa* head) {
	if (head == nullptr) {
		return;
	}
	Kassa* curr = head;
	while (curr->next != nullptr) {
		curr = curr->next;
	}
	while (curr != nullptr) {
		printOperations(curr);
		curr = curr->prev;
	}
}

// Функция поиска кассы по id
// Если касса не найдена, то вернет nullptr
Kassa* findKassa(Kassa* head, int id) {
	// Если список касс пустой
	if (head == nullptr) {
		return nullptr;
	}
	Kassa* curr = head;
	while (curr != nullptr) {
		if (curr->id == id) {
			break;
		}
		curr = curr->next;
	}
	return curr;
}

// Функция создания списка операций из файла для облегчения тестирования
Operation* createListFromFile(Operation* head) {
	Operation* curr = head;
	ifstream fin("test_db.txt");
	while (!fin.eof()) {
		string buff;
		getline(fin, buff);
		stringstream ss(buff);
		Operation* node = new Operation;
		ss >> node->product_id;
		ss >> node->amount;
		ss >> node->unit;
		ss >> node->price;
		ss >> node->cost;
		ss >> node->date;
		node->isNull = false;
		if (head == nullptr || head->isNull) {
			node->id = 1;
			head = node;
			curr = head;
		}
		else {
			curr->next = node;
			node->prev = curr;
			node->id = node->prev->id + 1;
			curr = node;
		}
	}
	return head;
}