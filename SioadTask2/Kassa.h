#pragma once
#ifndef KASSA_H
#define KASSA_H

#include <string>

using namespace std;

struct Operation {
	int id;
	int product_id;
	float amount;
	string unit;
	float price;
	float cost;
	string date;
	Operation* next;
	Operation* prev;
	bool isNull;
	Operation() : isNull(true), prev(nullptr), next(nullptr) {};
};

struct Kassa {
	int id;
	Operation* list;
	Kassa* next;
	Kassa* prev;
	bool isNull;
	Kassa() :isNull(true), next(nullptr), prev(nullptr), list(nullptr) {};
};


Kassa* addKassa(Kassa* head);

Operation* createList(Operation* head);

void addOperation(Operation* head);

float getProfit(Kassa* kassa, string date);

Operation* deleteOperation(Operation* head, int op_id);

void printOperations(Kassa* kassa);

void printList(Kassa* head);

void printListBackwards(Kassa* head);

Kassa* findKassa(Kassa* head, int id);

Operation* createListFromFile(Operation* head);

#endif