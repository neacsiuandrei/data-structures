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

struct SimpleLinkedList {
	Node* head=NULL;
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

SimpleLinkedList* initList() {
	SimpleLinkedList* list = (SimpleLinkedList*)malloc(sizeof(SimpleLinkedList));
	list->head = NULL;
	return list;
}

void addNode(SimpleLinkedList* list, Student* s) {
	if (list->head == NULL)
		list->head = initNode(s);
	else {
		Node* iterator = list->head;
		while (iterator->next!=NULL)
		{
			iterator = iterator->next;
		}
		iterator->next = initNode(s);
	}
}

void printList(SimpleLinkedList* list) {
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

SimpleLinkedList* deleteNode(SimpleLinkedList* list, int id) {
	if (list->head->student->id == id) {
		list->head = list->head->next;
		return list;
	}
	else {
		Node* iterator = list->head;
		while (iterator->next != NULL) {
			if (iterator->next->student->id == id) {
				iterator->next = iterator->next->next;
				return list;
			}
			iterator = iterator->next;
		}
	}
}

void main() {
	Student** students = (Student**)malloc(sizeof(Student*) * 5);
	students[0] = initStudent(1, "Andrei", 20);
	students[1] = initStudent(2, "Alice", 18);
	students[2] = initStudent(3, "Adi", 22);
	students[3] = initStudent(4, "Bob", 44);
	students[4] = initStudent(5, "Vader", 27);
	SimpleLinkedList* list = initList();
	for (int i = 0; i < 5; i++)
		addNode(list, students[i]);
	printList(list);


	printf("\n\nDeleting\n\n");
	list = deleteNode(list, 3);
	list = deleteNode(list, 1);
	list = deleteNode(list, 5);
	printList(list);
}