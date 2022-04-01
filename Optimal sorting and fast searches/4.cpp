/* Минимизируем максимум
Даны n нестрого возрастающих массивов Ai и m нестрого убывающих массивов B j. Все массивы имеют одну и ту же длину l. Далее даны q
 запросов вида (i,j), ответ на запрос – такое k, что max(Aik,Bjk) минимален. Если таких k несколько, можно вернуть любое.

Формат входных данных
На первой строке числа n,m,l (1≤n,m≤900;1≤l≤3000). Следующие n строк содержат описания массивов Ai. 
Каждый массив описывается перечислением l элементов. Элементы массива – целые числа от 0 до 105−1. Далее число m и описание массивов 
B j в таком же формате. Массивы и элементы внутри массива нумеруются с 1. На следюущей строке число запросов q(1≤q≤n+m).
 Следующие q строк содержат пары чисел i,j(1≤i≤n, 1 ≤j≤m).

Формат результата
Выведите q чисел от 1 до l – ответы на запросы.
 */


#include <iostream>
#include <algorithm>

int main() {
	int n, m, l;
	std::cin >> n;
	std::cin >> m;
	std::cin >> l;
	uint64_t** n_grow = new uint64_t*[n];

	for (int i = 0; i < n; i++) {
		n_grow[i] = new uint64_t[l];
		for (int j = 0; j < l; j++) {
			std::cin >> n_grow[i][j];
		}
	}

	uint64_t** m_fall = new uint64_t*[m];

	for (int i = 0; i < m; i++) {
		m_fall[i] = new uint64_t[l];
		for (int j = 0; j < l; j++) {
			std::cin >> m_fall[i][j];
		}
	}

	long long q = 0;
	std::cin >> q;
	
	int first;
	int second;

	for (int i = 0; i < q; i++) {
		std::cin >> first;
		std::cin >> second;
		--first;
		--second;
		if (n_grow[first][0] > m_fall[second][0]) {
			std::cout << 1 << std::endl;
			continue;
		}
		if (n_grow[first][l-1] < m_fall[second][l-1]) {
			std::cout << l << std::endl;
			continue;
		}
		int left = 0;
		int right = l;
		while (left < right) {
			int middle = (left + right) / 2;
			if (n_grow[first][middle] >= m_fall[second][middle] && n_grow[first][middle - 1] <= m_fall[second][middle - 1]) {
				if (std::max(n_grow[first][middle], m_fall[second][middle]) > std::max(n_grow[first][middle - 1], m_fall[second][middle - 1])) {
					std::cout << middle << std::endl;
					break;
				}
				else {
					std::cout << middle + 1 << std::endl;
					break;
				}
			}

			if (n_grow[first][middle] < m_fall[second][middle]) {
				left = middle + 1;
			}
			else {
				right = middle;
			}
		}

	}
} 