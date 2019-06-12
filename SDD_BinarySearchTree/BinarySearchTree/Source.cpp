#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Student {
	int id;
	char name[50];
	int age;
};

struct Node {
	Node* right;
	Node* left;
	int id;
	int index;
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

Node* initNode(int id, int index) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->right = NULL;
	newNode->left = NULL;
	newNode->id = id;
	newNode->index = index;
	return newNode;
}

void addNode(Node*& root, int id, int index) {
	if (root == NULL)
		root = initNode(id, index);
	else {
		if (root->id > id) {
			if(root->left==NULL)
				root->left= initNode(id, index);
			else {
				addNode(root->left, id, index);
			}
		}
		if (root->id < id) {
			if (root->right == NULL)
				root->right = initNode(id, index);
			else {
				addNode(root->right, id, index);
			}
		}
	}
}

void printBST_InOrder(Node* root) {
	if (root != NULL) {
		printBST_InOrder(root->left);
		printf("ID: %d | Index: %d\n", root->id, root->index);
		printBST_InOrder(root->right);
	}
}

void printBST_PreOrder(Node* root) {
	if (root != NULL) {
		printf("ID: %d | Index: %d\n", root->id, root->index);
		printBST_PreOrder(root->left);
		printBST_PreOrder(root->right);
	}
}

void printBST_PostOrder(Node* root) {
	if (root != NULL) {
		printBST_PostOrder(root->left);
		printBST_PostOrder(root->right);
		printf("ID: %d | Index: %d\n", root->id, root->index);
	}
}

int getIndex(Node* root, int id) {
	if (root != NULL) {
		if (root->id == id)
			return root->index;
		if (root->id > id)
			return getIndex(root->left, id);
		if (root->id < id)
			return getIndex(root->right, id);
	}
}

Node* getMinValue(Node* root) {
	if (root != NULL) {
		while (root->left != NULL)
			root = root->left;
	}
	return root;
}

Node* deleteNode(Node*& root, int id) {
	if (root == NULL)
		return root;
	if (root->id > id)
		root->left = deleteNode(root->left, id);
	if (root->id < id)
		root->right = deleteNode(root->right, id);
	if (root->id == id) {
		if (root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp;
		}
		Node* temp = getMinValue(root->right);
		root->id = temp->id;
		root->index = temp->index;
		root->right = deleteNode(root->right, temp->id);
	}
	return root;
}

void main() {
	Student** students = (Student**)malloc(sizeof(Student*) * 5);
	students[0] = initStudent(1, "Andrei", 20);
	students[1] = initStudent(2, "Alice", 18);
	students[2] = initStudent(3, "Adi", 22);
	students[3] = initStudent(4, "Bob", 44);
	students[4] = initStudent(5, "Vader", 27);
	Node* BST_Node = NULL;

	addNode(BST_Node, students[2]->id, 2);
	addNode(BST_Node, students[0]->id, 0);
	addNode(BST_Node, students[3]->id, 3);
	addNode(BST_Node, students[4]->id, 4);
	addNode(BST_Node, students[1]->id, 1);

	printf("In Order:\n\n");
	printBST_InOrder(BST_Node);
	printf("\n\nPre Order:\n\n");
	printBST_PreOrder(BST_Node);
	printf("\n\nPost Order:\n\n");
	printBST_PostOrder(BST_Node);

	printf("\n\nGetting elements:\n\n");
	printStudent(students[getIndex(BST_Node, 1)]);
	printStudent(students[getIndex(BST_Node, 2)]);
	printStudent(students[getIndex(BST_Node, 3)]);
	printStudent(students[getIndex(BST_Node, 4)]);
	printStudent(students[getIndex(BST_Node, 5)]);

	printf("\n\nDeleting:\n\n");
	BST_Node = deleteNode(BST_Node, 3);
	BST_Node = deleteNode(BST_Node, 5);
	BST_Node = deleteNode(BST_Node, 1);
	printBST_PreOrder(BST_Node);
}