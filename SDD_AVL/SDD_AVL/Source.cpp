#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Student {
	int id;
	char name[50];
	int age;
};

struct AVL {
	Student* student;
	AVL* right;
	AVL* left;
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

AVL* initAVL(Student* s) {
	AVL* newNode = (AVL*)malloc(sizeof(AVL));
	newNode->student = s;
	newNode->right = newNode->left = NULL;
	return newNode;
}

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int getHeight(AVL* root) {
	if (root == NULL)
		return 0;
	else {
		return 1 + max(getHeight(root->left), getHeight(root->right));
	}
}

int getBalanceDegree(AVL* node) {
	if (node == NULL)
		return 0;
	else {
		return getHeight(node->left) - getHeight(node->right);
	}
}

AVL* rotateLeft(AVL*& root) {
	if (root != NULL) {
		AVL* temp = root->right;
		root->right = temp->left;
		temp->left = root;
		root = temp;
		return root;
	}
}

AVL* rotateRight(AVL*& root) {
	if (root != NULL) {
		AVL* temp = root->left;
		root->left = temp->right;
		temp->right = root;
		root = temp;
		return root;
	}
}

void rebalance(AVL*& root) {
	if (root != NULL) {
		if (getBalanceDegree(root) >= 2) {
			if (getBalanceDegree(root->left) != 1)
				rotateLeft(root->left);
			rotateRight(root);
		}
		if (getBalanceDegree(root) <= -2) {
			if (getBalanceDegree(root->right) != -1)
				rotateRight(root->right);
			rotateLeft(root);
		}
		rebalance(root->right);
		rebalance(root->left);
	}
}

void insertNode(AVL*& root, Student* s) {
	AVL* newNode = initAVL(s);
	if (root == NULL)
		root = newNode;
	else {
		if (root->student->id > s->id) {
			insertNode(root->left, s);
		}
		else if (root->student->id < s->id) {
			insertNode(root->right, s);
		}
		if (getBalanceDegree(root) == 2) {
			if (getBalanceDegree(root->left) != 1)
				rotateLeft(root->left);
			rotateRight(root);
		}
		if (getBalanceDegree(root) == -2) {
			if (getBalanceDegree(root->right) != -1)
				rotateRight(root->right);
			rotateLeft(root);
		}
	}
}

void printAVL_PreOrder(AVL* root) {
	if (root != NULL) {
		printf("%d  ||  ", getHeight(root));
		printStudent(root->student);
		printAVL_PreOrder(root->left);
		printAVL_PreOrder(root->right);
	}
}

AVL* getMin(AVL* root) {
	if (root != NULL) {
		while (root->left != NULL)
			root = root->left;
	}
	return root;
}

AVL* deleteNode(AVL*& root, int id) {
	if (root == NULL)
		return root;
	if (root->student->id > id)
		root->left = deleteNode(root->left, id);
	if (root->student->id < id)
		root->right = deleteNode(root->right, id);
	if (root->student->id == id) {
		if (root->left == NULL) {
			AVL* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			AVL* temp = root->left;
			free(root);
			return temp;
		}
		AVL* temp = getMin(root->right);
		root->student = temp->student;
		root->right = deleteNode(root->right, temp->student->id);
	}
}

void getStudent(AVL*& root, int id) {
	if(root==NULL)
		printf("No such student exists.");
	else if (root->student->id == id) {
		printStudent(root->student);
		root=deleteNode(root, id);
	}
	else if (root->student->id > id) {
		getStudent(root->left, id);
	}
	else if (root->student->id < id) {
		getStudent(root->right, id);
	}
	else
		printf("No such student exists.");
	rebalance(root);
}

void main() {

	Student** students = (Student**)malloc(sizeof(Student*) * 10);
	students[0] = initStudent(39, "Andrei", 20);
	students[1] = initStudent(5, "Alice", 18);
	students[2] = initStudent(22, "Adi", 22);
	students[3] = initStudent(7, "Bob", 44);
	students[4] = initStudent(1, "Vader", 27);
	students[5] = initStudent(66, "White", 20);
	students[6] = initStudent(32, "Vlad", 18);
	students[7] = initStudent(20, "Ana", 22);
	students[8] = initStudent(45, "John", 44);
	students[9] = initStudent(50, "Ion", 27);

	AVL* avl = NULL;
	for (int i = 0; i < 10; i++)
		insertNode(avl, students[i]);
	printAVL_PreOrder(avl);

	printf("\n\nGetting values\n\n");
	//getStudent(avl, 7);
	//getStudent(avl, 20);
	//getStudent(avl, 1);
	getStudent(avl, 100);
	//avl = deleteNode(avl, 22);
	//avl = deleteNode(avl, 5);
	//avl = deleteNode(avl, 50);
	//rebalance(avl);

	printf("\n\nNew print\n\n");
	printAVL_PreOrder(avl);

}
