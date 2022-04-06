/* Поиск позиции
В шеренгу друг за другом стоят n человек, рост i-го из них равен ai условных единиц.
 Вы тоже собираетесь встать в эту шеренгу, при чем вам хочется встать на такую позицию p, чтобы f(p) =
[количество людей слева от вас того же роста, что и вы]
умножить на
[количество людей справа от вас с ростом, не равным вашему] было максимально.

Для этого вы можете встать в начало шеренги, в её конец, или между любыми 2мя соседними людьми.

К сожалению вы не можете точно вспомнить ваш рост, у вас есть только m предположений о том, каким он может быть,
 и для каждого из них вы хотели бы знать оптимальную позицию, на которую вам стоило бы встать.-

Формат входных данных
В первой строке даны два целых числа n и m (1≤m,n≤10^5). Во второй строке даны n целых чисел ai - рост людей, стоящих в шеренге 
(1≤ai≤105) В третьей строке даны m целых чисел xi - ваш предполагаемый рост (1≤xi≤105)

Формат результата
В единственной строке выведите выведите m целых чисел  - значение f(p) в оптимальной для данного роста позиции.
 */


#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

int main() {
	uint64_t n, m, mi;
	std::cin >> n;
	std::cin >> m;

	uint64_t* a = new uint64_t[n];
	for (uint64_t i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	uint64_t* x = new uint64_t[m];
	for (uint64_t i = 0; i < m; ++i) {
		std::cin >> x[i];
	}

	std::map<uint64_t, std::vector<uint64_t>*> aPositions = {};

	for (uint64_t i = 0; i < n; i++) {
		if (aPositions.find(a[i]) == aPositions.end()) {
			aPositions.insert({ a[i], new std::vector< uint64_t> });
		}
		aPositions[a[i]]->push_back(i + 1);
	}

	std::map<uint64_t, uint64_t> aMax = {};
	for (auto v : aPositions) {
		auto v_pos = aPositions[v.first];
		uint64_t max_f = 0;
		for (uint64_t i = 0; i < v_pos->size(); ++i) {
			uint64_t l_weight = i + 1;
			uint64_t r_weight = n - (*v_pos)[i] - ((v_pos->size() - (i + 1)));
			max_f = std::max(max_f, l_weight * r_weight);
		}
		aMax.insert({v.first, max_f });
	}

	for (uint64_t i = 0; i < m; ++i) {
		std::cout << aMax[x[i]] << ' ';
	}
	return 0;
} 