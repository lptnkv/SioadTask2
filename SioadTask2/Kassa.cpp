#include "Kassa.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// ������� ���������� ����� � ������
// id ����� ����������� �������������
// ���������� ������ ������� ������
Kassa* addKassa(Kassa* head) {
	Kassa* curr = head;
	int id = 1;
	// ���� ������ ������� NULL
	if (head == nullptr || head->isNull) {
		Kassa* kassa = new Kassa;
		kassa->id = id;
		head = kassa;
		curr = head;
		head->isNull = false;
		id++;
	}
	// ����� ������� �� ����� ������
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

// ������� �������� ������ �������� �����
// ���������� ������ ������� ������
Operation* createList(Operation* head) {
	Operation* curr = head;
	cout << "������� ���-�� ��������: ";
	int n;
	cin >> n;
	// �������� �� ������������ �����
	while (cin.fail())
	{
		cout << "������" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> n;
	}
	for (int i = 0; i < n; i++) {
		cout << "�������� � " << i << endl;
		Operation* node = new Operation;
		cout << "��� ������: ";
		cin >> node->product_id;
		cout << "����������: ";
		cin >> node->amount;
		cout << "������� ���������: ";
		cin >> node->unit;
		cout << "���� �� �������: ";
		cin >> node->price;
		node->cost = node->price * node->amount;
		cout << "���������: " << node->cost << endl;
		cout << "���� � ������� ��.��.����: ";
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

// ������� ���������� �������� � ����������� ��������
void addOperation(Operation* head) {
	Operation* curr = head;
	while (curr->next != nullptr) {
		curr = curr->next;
	}
	Operation* node = new Operation;
	cout << "��� ������: ";
	cin >> node->product_id;
	cout << "����������: ";
	cin >> node->amount;
	cout << "������� ���������: ";
	cin >> node->unit;
	cout << "���� �� �������: ";
	cin >> node->price;
	node->cost = node->price * node->amount;
	cout << "���������: " << node->cost;
	cout << "���� � ������� ��.��.����: ";
	cin >> node->date;
	node->id = curr->id + 1;
	curr->next = node;
	node->prev = curr;
}

// ������� ����������� ������� �� ����� � ������������ ����
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


// ������� �������� ��������
// ���������� ��������� �� ������ ������� ������ ��������
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
	// ���� ������� �� ������
	if (curr == nullptr) {
		return head;
	}	
	// ���� ����� ������� ������ �������
	if (curr == head) {
		// ���� ������� �� ������������ � ������
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
	// ������� �� ������
	else {
		// ������� �� ���������
		if (curr->next != nullptr) {
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			Operation* toDelete = curr;
			curr = curr->next;
			delete(toDelete);
		}
		// ������� ���������
		else {
			curr->prev->next = nullptr;
			delete(curr);
		}
	}
	// ������ ��������� ������ ��������� � ������
	curr = head;
	int node_id = 0;
	while (curr != nullptr) {
		node_id++;
		curr->id = node_id;
		curr = curr->next;
	}
	return head;
}

// ������� ������ �������� �����
void printOperations(Kassa* kassa) {

	Operation* curr_op = kassa->list;
	cout << "����� � " << kassa->id << endl;
	while (curr_op != nullptr) {
		cout << curr_op->id << ") ���: " << curr_op->product_id << " " << curr_op->amount << " " << curr_op->unit << " ����: " 
			<< curr_op->price << " ���������: " << curr_op->cost << " ����: " << curr_op->date << endl;
		curr_op = curr_op->next;
	}
}

// ������� ������ ���� �������� ���� ����
void printList(Kassa* head) {
	if (head == nullptr)
		return;
	Kassa* curr = head;
	while (curr != nullptr) {
		printOperations(curr);
		curr = curr->next;
	}
}

// ������� ������ ���� �������� ���� ���� � �������� �������
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

// ������� ������ ����� �� id
// ���� ����� �� �������, �� ������ nullptr
Kassa* findKassa(Kassa* head, int id) {
	// ���� ������ ���� ������
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

// ������� �������� ������ �������� �� ����� ��� ���������� ������������
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