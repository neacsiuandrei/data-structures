#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Student {
	int id;
	char name[50];
	int age;
};

struct Node {
	Node* next;
	Student* student;
};

struct HashTable {
	Node** listNodes = NULL;
	int noKeys = 0;
};

Student* initStudent(int id, const char* name, int age) {
	Student* s = (Student*)malloc(sizeof(Student));
	s->id = id;
	strcpy(s->name, name);
	s->age = age;
	return s;
}

void printStudent(Student* s) {
	printf("ID: %d - Name: %s - Age: %d\n", s->id, s->name, s->age);
}

Node* initNode(Student* s) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->student = initStudent(s->id, s->name, s->age);
	return newNode;
}

int getHashCode(int id, int size) {
	return id % size;
}

HashTable* createHT(int size) {
	HashTable* HT = (HashTable*)malloc(sizeof(HashTable));
	HT->noKeys = size;
	HT->listNodes = (Node**)malloc(size * sizeof(Node*));
	for (int i = 0; i < size; i++)
		HT->listNodes[i] = NULL;
	return HT;
}

void addNode(HashTable* HT, Student* s) {
	Node* newNode = initNode(s);
	newNode->next = HT->listNodes[getHashCode(s->id, HT->noKeys)];
	HT->listNodes[getHashCode(s->id, HT->noKeys)] = newNode;
}

void getElement(HashTable* HT, int id) {
	int hashCode = getHashCode(id, HT->noKeys);
	int OK = 1;
	Node* iterator = HT->listNodes[hashCode];
	while (iterator != NULL) {
		if (iterator->student->id == id) {
			printStudent(iterator->student);
			OK = 0;
		}
		iterator = iterator->next;
	}
	if (OK == 1)
		printf("No such element found.\n");
}

void deleteElement(HashTable* HT, int id) {
	int hashCode = getHashCode(id, HT->noKeys);
	int OK = 1;
	if (HT->listNodes[hashCode]->student->id == id) {
		HT->listNodes[hashCode] = HT->listNodes[hashCode]->next;
		OK = 0;
	}
	else {
		Node* iterator = HT->listNodes[hashCode];
		while (iterator->next->next != NULL) {
			if (iterator->student->id == id) {
				iterator->next = iterator->next->next;
				OK = 0;
			}
			iterator = iterator->next;
		}
		if (iterator->next->next == NULL) {
			if (iterator->next->student->id == id)
				iterator->next = NULL;
			OK = 0;
		}
	}
	if (OK == 1)
		printf("No such element found in order to delete.\n");
}

void updateElement(HashTable* HT, int id, const char* newName) {
	int hashCode = getHashCode(id, HT->noKeys);
	int OK = 1;
	Node* iterator = HT->listNodes[hashCode];
	while (iterator != NULL) {
		if (iterator->student->id == id) {
			strcpy(iterator->student->name, newName);
			OK = 0;
		}
		iterator = iterator->next;
	}
	if (OK == 1)
		printf("No such element found.\n");
}

void main() {
	Student** students = (Student**)malloc(sizeof(Student*) * 5);
	students[0] = initStudent(1, "Andrei", 20);
	students[1] = initStudent(2, "Alice", 18);
	students[2] = initStudent(3, "Adi", 22);
	students[3] = initStudent(4, "Bob", 44);
	students[4] = initStudent(5, "Vader", 27);
	HashTable* hashTable = createHT(101);
	for (int i = 0; i < 5; i++)
		addNode(hashTable, students[i]);
	getElement(hashTable, 1);
	getElement(hashTable, 2);
	getElement(hashTable, 3);
	getElement(hashTable, 4);
	getElement(hashTable, 5);
	getElement(hashTable, 20);

	printf("\n\nDeleting\n\n");
	updateElement(hashTable, 1, "ANDREI");
	getElement(hashTable, 1);
	updateElement(hashTable, 3, "ADI");
	getElement(hashTable, 3);
	updateElement(hashTable, 5, "VADER");
	getElement(hashTable, 5);

	printf("\n\nDeleting\n\n");
	deleteElement(hashTable, 1);
	deleteElement(hashTable, 2);
	deleteElement(hashTable, 5);

	printf("\n\nPrint new HashTable\n\n");
	getElement(hashTable, 1);
	getElement(hashTable, 2);
	getElement(hashTable, 3);
	getElement(hashTable, 4);
	getElement(hashTable, 5);
	getElement(hashTable, 20);
}