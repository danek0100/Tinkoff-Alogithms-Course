/* Простая очередь
Реализуйте структуру данных «очередь». Напишите программу, содержащую описание очереди и моделирующую работу очереди, реализовав все указанные здесь методы. Программа считывает последовательность команд и в зависимости от команды выполняет ту или иную операцию. После выполнения каждой команды программа должна вывести одну строчку. Возможные команды для программы:

push n Добавить в очередь число 
n
 (значение 
n
 задается после команды). Программа должна вывести «ok».

pop Удалить из очереди первый элемент. Программа должна вывести его значение.

front Программа должна вывести значение первого элемента, не удаляя его из очереди.

size Программа должна вывести количество элементов в очереди.

clearПрограмма должна очистить очередь и вывести «ok».

exit Программа должна вывести «bye» и завершить работу.

Гарантируется, что набор входных команд удовлетворяет следующим требованиям: максимальное количество элементов в очереди в любой момент не превосходит 
100
, все команды pop и front корректны, то есть при их исполнении в очереди содержится хотя бы один элемент.

Использовать стандартную очередь и дек из stl нельзя.

Формат входных данных
Вводятся команды управления очередью, по одной на строке.

Формат результата
Требуется вывести протокол работы с очередью, по одному сообщению на строке. */


#include <iostream>
#include <string>


class Node {
private:
	int data = 0;
	Node* next = nullptr;
	
public:
	Node() {};

	Node(int data) {
		this->data = data;
	};

	void setNext(Node* next) {
		this->next = next;
	}

	void setValue(int data) {
		this->data = data;
	}

	int getData() {
		return this->data;
	}

	Node* getNext() {
		return this->next;
	}
};

// :-)
class myQueue {
private:
	Node* queue;
	Node* head;
	Node* tail;
	int size = 0;
public:
	myQueue() {
		queue = new Node;
		head = queue;
		tail = queue;
	}

	int getSize() {
		return this->size;
	}

	int getFront() {
		return head->getData();
	}

	void addNode(int data) {

		if (size != 0) {
			Node* newNode = new Node(data);
			this->tail->setNext(newNode);
			this->tail = newNode;
			this->size++;
		}
		else {
			head->setValue(data);
			size++;
		}
	}

	void clear() {
		while (size != 0)
		{
			this->pop();
		}
	}

	int pop() {
		int temp = head->getData();
		if (head->getNext() != nullptr) {
			Node* temptr = head->getNext();
			delete(head);
			head = temptr;
			size--;
		}
		else {
			queue = new Node;
			delete(head);
			head = queue;
			tail = queue;
			size = 0;
		}
		return temp;
	}

	~myQueue() {
		this->clear();
		delete(queue);
	}

};

int main() {
	myQueue queue;

	std::string command;
	while (true) {
		std::cin >> command;
		if (command == std::string("exit")) {
			std::cout << "bye";
			break;
		}
		else if (command == std::string("size")) {
			std::cout << queue.getSize() << std::endl;
		}
		else if (command == std::string("front")) {
			std::cout << queue.getFront() << std::endl;
		}
		else if (command == std::string("push")) {
			int n;
			std::cin >> n;
			queue.addNode(n);
			std::cout << "ok"<< std::endl;
		}
		else if (command == std::string("pop")) {
			std::cout << queue.pop() << std::endl;
		}
		else if (command == std::string("clear")) {
			queue.clear();
			std::cout << "ok" << std::endl;
		}
	}
}