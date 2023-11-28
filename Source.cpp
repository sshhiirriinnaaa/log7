#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stack>

using namespace std;

struct Node {
	int data;
	Node* next;
};


void printAdjacencyList(Node** adjacencyList, int size) {
	for (int i = 0; i < size; i++) {
		cout << "Вершина " << i << " смежна с: ";
		Node* current = adjacencyList[i];
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
}

Node** adjacencyMatrixToAdjacencyList(int** matrix, int size) {
	Node** adjacencyList = new Node * [size];

	for (int i = 0; i < size; i++) {
		adjacencyList[i] = nullptr;  

		for (int j = size - 1; j >= 0; j--) { 
			if (matrix[i][j] == 1) {
				Node* newNode = new Node;
				newNode->data = j;
				newNode->next = adjacencyList[i];
				adjacencyList[i] = newNode;
			}
		}
	}

	printAdjacencyList(adjacencyList, size);

	return adjacencyList;
}


void freeAdjacencyList(Node** adjacencyList, int size) {
	for (int i = 0; i < size; i++) {
		Node* current = adjacencyList[i];
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] adjacencyList;
}


int** createMatrix(int size) {
	int** matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
	}
	return matrix;
}


void deleteMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}


void fillMatrixRandom(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i == j) {
				matrix[i][j] = 0;
			}
			else {
				int randomValue = rand() % 2;
				matrix[i][j] = randomValue;
				matrix[j][i] = randomValue; 
			}
		}
	}
}


void printMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << matrix[i][j];
			cout << ", ";
		}
		cout << endl;
	}
}


void depthFirstSearch(int** matrix, int size, int vertex, bool* visited, int* result, int& currentIndex) {
	visited[vertex] = true;
	result[currentIndex++] = vertex;

	for (int i = 0; i < size; i++) {
		if (matrix[vertex][i] == 1 && !visited[i]) {
			depthFirstSearch(matrix, size, i, visited, result, currentIndex);
		}
	}
}


void DFS(Node** adjacencyList, int vertex, bool* visited, int* result, int& currentIndex) {
	visited[vertex] = true; 
	result[currentIndex++] = vertex;

	
	Node* current = adjacencyList[vertex];
	while (current != nullptr) {
		int neighbor = current->data;
		if (!visited[neighbor]) {
			DFS(adjacencyList, neighbor, visited, result, currentIndex); 
		}
		current = current->next;
	}
}



int* nonRecursiveDFS(int** matrix, int size, int startVertex) {
	bool* visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false;
	}

	int* result = new int[size];
	int currentIndex = 0;

	stack<int> vertexStack;
	vertexStack.push(startVertex);

	while (!vertexStack.empty()) {
		int currentVertex = vertexStack.top();
		vertexStack.pop();

		if (!visited[currentVertex]) {
			visited[currentVertex] = true;
			result[currentIndex++] = currentVertex;

			for (int i = size - 1; i >= 0; i--) {
				if (matrix[currentVertex][i] == 1 && !visited[i]) {
					vertexStack.push(i);
				}
			}
		}
	}

	delete[] visited;
	return result;
}

int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	int size;
	string s;
	cout << "\nВведите размер матрицы смежности: ";
	abc:
	cin >> s;
	size = std ::atoi(s.c_str());
	if (size > 0) {
		int** adjacencyMatrix = createMatrix(size);
		fillMatrixRandom(adjacencyMatrix, size);
		printMatrix(adjacencyMatrix, size);

		bool* visited = new bool[size];
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}


		cout << "\nСписок смежности:\n";
		Node** adjacencyList = adjacencyMatrixToAdjacencyList(adjacencyMatrix, size);

		int startVertex;
		cout << "Введите начальную вершину для обхода: ";
		cin >> startVertex;

		int* dfsResult = new int[size];
		int currentIndex = 0;

		depthFirstSearch(adjacencyMatrix, size, startVertex, visited, dfsResult, currentIndex);

		cout << "Результат обхода в глубину матрицы смежности начиная с вершины " << startVertex << ": ";
		for (int i = 0; i < currentIndex; i++) {
			cout << dfsResult[i] << " ";
		}
		cout << "\n";

		int* dfsResult1 = nonRecursiveDFS(adjacencyMatrix, size, startVertex);

		cout << "Результат нерекурсивного обхода в глубину матрицы смежности начиная с вершины " << startVertex << ": ";
		for (int i = 0; i < currentIndex; i++) {
			cout << dfsResult1[i] << " ";
		}
		cout << "\n";

		visited = new bool[size];
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}

		int* dfsResult2 = new int[size];
		int currentIndex2 = 0;
		DFS(adjacencyList, startVertex, visited, dfsResult2, currentIndex2);

		cout << "Результат обхода в глубину списка смежности начиная с вершины " << startVertex << ": ";
		for (int i = 0; i < currentIndex2; i++) {
			cout << dfsResult2[i] << " ";
		}
		cout << "\n";

		deleteMatrix(adjacencyMatrix, size);
		delete[] visited;
	}
	else
	{
		cout << "Введите положительное число: ";
		goto abc;
	}
	return 0;
}
