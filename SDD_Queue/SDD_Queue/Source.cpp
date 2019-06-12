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

struct Queue {
	Node* head = NULL;
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

Queue* initList() {
	Queue* list = (Queue*)malloc(sizeof(Queue));
	list->head = NULL;
	return list;
}

void addNode(Queue* list, Student* s) {
	if (list->head == NULL)
		list->head = initNode(s);
	else {
		Node* iterator = list->head;
		while (iterator->next != NULL)
		{
			iterator = iterator->next;
		}
		iterator->next = initNode(s);
	}
}

void printList(Queue* list) {
	if (list->head == NULL)
		printf("No list exists.\n");
	else {
		Node* iterator = list->head;
		while (iterator != NULL) {
			printStudent(iterator->student);
			iterator = iterator->next;
		}
	}
}

Student* getLast(Queue* list){
	if (list->head == NULL) {
		Student* s = initStudent(0, " ", 0);
		return s;
	}
	Node* iterator = list->head;
	while (iterator->next->next != NULL) {
		iterator = iterator->next;
	}
	Student* s = iterator->next->student;
	free(iterator->next);
	iterator->next = NULL;
	return s;
}

void main() {
	Student** students = (Student**)malloc(sizeof(Student*) * 5);
	students[0] = initStudent(1, "Andrei", 20);
	students[1] = initStudent(2, "Alice", 18);
	students[2] = initStudent(3, "Adi", 22);
	students[3] = initStudent(4, "Bob", 44);
	students[4] = initStudent(5, "Vader", 27);
	Queue* list = initList();
	for (int i = 0; i < 5; i++)
		addNode(list, students[i]);
	printList(list);

	printf("\n\nGet students\n\n");
	printStudent(getLast(list));
	printStudent(getLast(list));
	printStudent(getLast(list));


	printf("\n\nCurrent queue\n\n");
	printList(list);

}