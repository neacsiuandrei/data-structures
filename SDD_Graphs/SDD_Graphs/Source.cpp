#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct LinkedNode;

struct MainNode {
	char name[100];
	LinkedNode* linkedNodes;
	MainNode* next;
};

struct LinkedNode {
	MainNode* destination;
	LinkedNode* next;
	int travelTime;
};

MainNode* initMainNode(const char* name) {
	MainNode* newNode = (MainNode*)malloc(sizeof(MainNode));
	strcpy(newNode->name, name);
	newNode->linkedNodes = NULL;
	newNode->next = NULL;
	return newNode;
}

LinkedNode* initLinkedNode(MainNode* destination, int tt) {
	LinkedNode* newNode = (LinkedNode*)malloc(sizeof(LinkedNode));
	newNode->destination = destination;
	newNode->travelTime = tt;
	newNode->next = NULL;
	return newNode;
}

void addMainNode(MainNode*& head, const char* name) {
	MainNode* newNode = initMainNode(name);
	if (head == NULL)
		head = newNode;
	else {
		MainNode* it = head;
		while (it->next != NULL)
			it = it->next;
		it->next = newNode;
	}
}

void addLinkedNode(LinkedNode*& head, MainNode* destination, int tt) {
	LinkedNode* newNode = initLinkedNode(destination, tt);
	newNode->next = head;
	head = newNode;
}

MainNode* searchDestination(MainNode* root, const char* name) {
	while (root != NULL) {
		if (strcmp(root->name, name) == 0)
			return root;
		root = root->next;
	}
	return root;
}

void printNeighbours(MainNode* root, const char* name) {
	LinkedNode* listHead = searchDestination(root, name)->linkedNodes;
	while (listHead!=NULL)
	{
		printf("Close-by: %s (TT: %d)\n", listHead->destination->name, listHead->travelTime);
		listHead = listHead->next;
	}
}

void printMainNodes(MainNode* root) {
	while (root != NULL) {
		printf("%s\n", root->name);
		root = root->next;
	}
}

struct Queue {
	MainNode* graphNode;
	Queue* next;
};

Queue* initQueueNode(MainNode* graphNode) {
	Queue* newNode = (Queue*)malloc(sizeof(Queue));
	newNode->graphNode = graphNode;
	newNode->next = NULL;
	return newNode;
}

void addQueueNode(Queue*& head, MainNode* graphNode) {
	Queue* newNode = initQueueNode(graphNode);

	if (head == NULL) {
		head = newNode;
	}
	else {
		Queue* iterator = head;
		while (iterator->next!=NULL)
		{
			iterator = iterator->next;
		}
		iterator->next = newNode;
	}
}

MainNode* getNodeFromQueue(Queue*& head) {
	if (head == NULL)
		return NULL;
	else {
		Queue* temp = head;
		head = head->next;
		MainNode* wanted = temp->graphNode;
		free(temp);
		return wanted;
	}
}

bool isVisited(Queue* head, MainNode* graphNode) {
	if (head == NULL)
		return false;
	else {
		Queue* iterator = head;
		while (iterator != NULL) {
			if (strcmp(iterator->graphNode->name, graphNode->name)==0)
				return true;
			iterator = iterator->next;
		}
		return false;
	}
}

void breathFirst(MainNode* graph) {
	if (graph == NULL)
		printf("No such graph exists.\n");
	else {
		Queue* visitedNodes = NULL;
		Queue* availableNodes = NULL;

		MainNode* iterator = graph;
		while (iterator != NULL) {

			if (!isVisited(visitedNodes, iterator))
				printf("Visited: %s\n", iterator->name);
			addQueueNode(visitedNodes, iterator);

			LinkedNode* neighbourIterator = iterator->linkedNodes;
			while (neighbourIterator != NULL) {
				if (!isVisited(visitedNodes, neighbourIterator->destination))
					addQueueNode(availableNodes, neighbourIterator->destination);
				neighbourIterator = neighbourIterator->next;
			}
			iterator = getNodeFromQueue(availableNodes);
		}
	}
}

struct Stack {
	MainNode* graphNode;
	Stack* next;
};

Stack* initStackNode(MainNode* graphNode) {
	Stack* newNode = (Stack*)malloc(sizeof(Stack));
	newNode->next = NULL;
	newNode->graphNode = graphNode;
	return newNode;
}

void addNodeInStack(Stack*& head, MainNode* graphNode) {
	Stack* newNode = initStackNode(graphNode);
	newNode->next = head;
	head = newNode;
}

MainNode* getNodeFromStack(Stack*& head) {
	if (head == NULL)
		return NULL;
	else {
		MainNode* wanted = head->graphNode;
		Stack* temp = head;
		head = head->next;
		free(temp);
		return wanted;
	}
}

bool isVisitedStack(Stack* head, MainNode* graphNode) {
	if (head == NULL)
		return false;
	else {
		Stack* iterator = head;
		while (iterator != NULL) {
			if (strcmp(iterator->graphNode->name, graphNode->name) == 0)
				return true;
			iterator = iterator->next;
		}
		return false;
	}
}

void depthFirst(MainNode* graph) {
	if (graph == NULL)
		printf("No such graph exists.\n");
	else {
		Stack* visitedNodes = NULL;
		Stack* availableNodes = NULL;

		MainNode* iterator = graph;
		while (iterator != NULL) {

			if (!isVisitedStack(visitedNodes, iterator))
				printf("Visited: %s\n", iterator->name);
			addNodeInStack(visitedNodes, iterator);

			LinkedNode* neighbourIterator = iterator->linkedNodes;
			while (neighbourIterator != NULL) {
				if (!isVisitedStack(visitedNodes, neighbourIterator->destination))
					addNodeInStack(availableNodes, neighbourIterator->destination);
				neighbourIterator = neighbourIterator->next;
			}
			iterator = getNodeFromStack(availableNodes);
		}
	}
}

void deleteLinkedNode(LinkedNode*& head, const char* name) {
	if (head != NULL) {
		if (strcmp(head->destination->name, name) == 0) {
			LinkedNode* temp = head;
			head = head->next;
			free(temp);
			//return head;
		}
		else if (head->next != NULL) {
			if (strcmp(head->next->destination->name, name) == 0) {
				LinkedNode* temp = head->next;
				head->next = head->next->next;
				free(temp);
			}
		}
		else {
			LinkedNode* iterator = head;
			while (iterator->next->next != NULL) {
				if (strcmp(iterator->next->destination->name, name) == 0) {
					LinkedNode* temp = iterator->next;
					iterator->next = iterator->next->next;
					free(temp);
					//return head;
				}
				iterator = iterator->next;
			}
			if (strcmp(iterator->next->destination->name, name) == 0) {
				free(iterator->next);
				iterator->next = NULL;
			}
			//return head;
		}
	}
}

void deleteMainhNode(MainNode*& head, const char* name) {
	MainNode* iterator = head;
	while (iterator != NULL) {
		deleteLinkedNode(iterator->linkedNodes, name);
		iterator = iterator->next;
	}
	if (strcmp(head->name, name) == 0) {
		MainNode* temp = head;
		head = head->next;
		free(temp);
		//return head;
	}
	else {
		MainNode* iterator = head;
		while (iterator->next->next != NULL) {
			if (strcmp(iterator->next->name, name) == 0) {
				MainNode* temp = iterator->next;
				iterator->next = iterator->next->next;
				free(temp);
				//return head;
			}
			iterator = iterator->next;
		}
		if (strcmp(iterator->next->name, name) == 0) {
			free(iterator->next);
			iterator->next = NULL;
		}
		//return head;
	}
}

void main() {
	MainNode* graph = NULL;

	const char* cities[] = { "Bucuresti","Ploiesti","Brasov","Craiova", "Bacau", "Sibiu", "Galati" };
	for (int i = 0; i < 7; i++)
		addMainNode(graph, cities[i]);

	printf("Cities in the graph:\n\n");
	printMainNodes(graph);

	//adding neighbours to Buc
	addLinkedNode(searchDestination(graph, "Bucuresti")->linkedNodes, searchDestination(graph, "Craiova"), 3);
	addLinkedNode(searchDestination(graph, "Bucuresti")->linkedNodes, searchDestination(graph, "Ploiesti"), 2);
	addLinkedNode(searchDestination(graph, "Bucuresti")->linkedNodes, searchDestination(graph, "Brasov"), 3);

	//adding neighbours to Ploiesti
	addLinkedNode(searchDestination(graph, "Ploiesti")->linkedNodes, searchDestination(graph, "Craiova"), 4);
	addLinkedNode(searchDestination(graph, "Ploiesti")->linkedNodes, searchDestination(graph, "Galati"), 6);

	//adding neighbours to Brasov
	addLinkedNode(searchDestination(graph, "Brasov")->linkedNodes, searchDestination(graph, "Sibiu"), 1);
	addLinkedNode(searchDestination(graph, "Brasov")->linkedNodes, searchDestination(graph, "Bacau"), 5);

	printf("\n\nCities you can reach from Bucuresti:\n\n");
	printNeighbours(graph, "Bucuresti");

	printf("\n\nCities you can reach from Ploiesti:\n\n");
	printNeighbours(graph, "Ploiesti");

	printf("\n\nCities you can reach from Brasov:\n\n");
	printNeighbours(graph, "Brasov");

	printf("\n\nBreathFirst:\n\n");
	breathFirst(graph);

	printf("\n\nDepthFirst:\n\n");
	depthFirst(graph);

	printf("\n\nDeleting graph node(s):\n\n");
	deleteMainhNode(graph, "Ploiesti");
	breathFirst(graph);
	//depthFirst(graph);
}