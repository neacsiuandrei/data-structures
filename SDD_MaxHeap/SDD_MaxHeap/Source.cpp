#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Student {
	int id;
	char name[50];
	int age;
};


struct MaxHeap {
	Student** students;
	int noStudends;
	int capacity;
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

MaxHeap* createMaxHeap(int iniSize) {
	MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
	heap->students = (Student**)malloc(iniSize * sizeof(Student*));
	heap->capacity = iniSize;
	heap->noStudends = 0;
	return heap;
}

void resizeHeap(MaxHeap* heap) {
	heap->capacity *= 2;
	Student** temp = (Student**)malloc(heap->capacity * sizeof(Student*));
	for (int i = 0; i < heap->noStudends; i++)
		temp[i] = initStudent(heap->students[i]->id, heap->students[i]->name, heap->students[i]->age);
	/*for (int i = 0; i < heap->noStudends; i++)
		free(heap->students[i]);*/
	free(heap->students);
	heap->students = temp;
}

int getParent(int index) {
	return (index - 1) / 2;
}

int getLeft(int index) {
	return index * 2 + 1;
}

int getRight(int index) {
	return getLeft(index) + 1;
}

void swap(MaxHeap* heap, int i1, int i2) {
	Student* s = heap->students[i1];
	heap->students[i1] = heap->students[i2];
	heap->students[i2] = s;
}

void add(MaxHeap* heap, Student* s) {
	if (heap->noStudends == heap->capacity)
		resizeHeap(heap);
	heap->students[heap->noStudends] = s;
	int current = heap->noStudends;
	heap->noStudends++;
	while (current != 0) {
		int parentIndex = getParent(current);
		if (heap->students[parentIndex]->age < heap->students[current]->age) {
			swap(heap, parentIndex, current);
			current = parentIndex;
		}
		else
			current = 0;
	}
}

void filterHeap(MaxHeap* heap, int index) {
	int root = index;
	int left = getLeft(index);
	int right = getRight(index);

	if (left < heap->noStudends && heap->students[left]->age > heap->students[root]->age)
		root = left;
	if (right < heap->noStudends && heap->students[right]->age > heap->students[root]->age)
		root = right;
	if (root != index) {
		swap(heap, root, index);
		filterHeap(heap, root);
	}
}

void deleteStudent(MaxHeap* heap, int index) {
	heap->students[index] = heap->students[heap->noStudends - 1];
	heap->noStudends--;
	filterHeap(heap, index);
}

void main() {
	Student** students = (Student**)malloc(sizeof(Student*) * 9);
	students[0] = initStudent(1, "Andrei", 20);
	students[1] = initStudent(2, "Alice", 18);
	students[2] = initStudent(3, "Adi", 22);
	students[3] = initStudent(4, "Bob", 44);
	students[4] = initStudent(5, "Vader", 27);
	students[5] = initStudent(6, "White", 19);
	students[6] = initStudent(7, "Mark", 30);
	students[7] = initStudent(8, "Me", 24);
	students[8] = initStudent(9, "Boja", 50);

	MaxHeap* heap = createMaxHeap(100);

	for(int i=0;i<9;i++)
		add(heap, students[i]);
	printf("Students:\n\n");
	for (int i = 0; i < heap->noStudends; i++)
		printStudent(heap->students[i]);

	printf("\n\nAfter deleting: \n\n");
	deleteStudent(heap, 2);
	deleteStudent(heap, 4);
	for (int i = 0; i < heap->noStudends; i++)
		printStudent(heap->students[i]);

}