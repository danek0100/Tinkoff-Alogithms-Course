/*
Формат входных данных
В первой строке входных данный записано число 
N(1≤N≤10^5)−количество запросов. Следующие N строк содержат описание запросов в формате:
+ i − гоблин с номером i(1≤i≤N)встаёт в конец очереди.
* i − привилегированный гоблин с номером i встает в середину очереди.
- − первый гоблин из очереди уходит к шаманам. Гарантируется, что на момент такого запроса очередь не пуста.

Формат результата
Для каждого запроса типа - программа должна вывести номер гоблина, который должен зайти к шаманам.
*/
#include <iostream>
#include <string>
#include <deque>

int main() {
	std::deque<int> queue;
	long long numCommand = 0;
	std::cin >> numCommand;
	std::string command;
	long long i = 0;
	long long middle = 1;
	long long size = 0;
	while (i < numCommand) {
		std::cin >> command;
		if (command == std::string("+")) {
			long long n;
			std::cin >> n;
			queue.push_back(n);
			size++;
			if (size % 2 == 1 && size > middle) {
				middle++;
			}

		}
		else if (command == std::string("*")) {
			long long n;
			std::cin >> n;
			if (size != 0) {
				auto it = queue.begin() + middle;
				queue.insert(it, n);
				size++;
				if (size % 2 == 1 && size > middle) {
					middle++;
				}
			}
			else {
				queue.push_back(n);
				size++;
				if (size % 2 == 1 && size > middle) {
					middle++;
				}
			}
		}
		else if (command == std::string("-")) {
			if (size != 0) {
				std::cout << queue.front() << std::endl;
				queue.pop_front();
				size--;
				if (size % 2 == 0 && middle > 0) {
					middle--;
				}
			}
		}
		++i;
	}
} 