/* Дремучий лес
Чтобы помешать появлению СЭС в лагере, администрация ЛКШ перекопала единственную дорогу, соединяющую «Берендеевы поляны» с Судиславлем, теперь проехать по ней невозможно. Однако, трудности не остановили инспекцию, хотя для СЭС остается только одна возможность — дойти до лагеря пешком. Как известно, Судиславль находится в поле, а «Берендеевы поляны» — в лесу.

Судиславль находится в точке с координатами (0,1).

«Берендеевы поляны» находятся в точке с координатами (1,0).
Граница между лесом и полем −горизонтальная прямая y=a, где a— некоторое число (0<a<1).

Скорость передвижения СЭС по полю составляет Vp, скорость передвижения по лесу — Vf.
 Вдоль границы можно двигаться как по лесу, так и по полю.

Администрация ЛКШ хочет узнать, сколько времени у нее осталось для подготовки к визиту СЭС.
 Она попросила вас выяснить, в какой точке инспекция СЭС должна войти в лес, чтобы дойти до «Берендеевых полян» как можно быстрее.

Формат входных данных
В первой строке входного файла содержатся два положительных целых числа Vp и Vf
 (1≤Vp,Vf≤105). Во второй строке содержится единственное вещественное число — координата по оси Oy границы между лесом и полем a (0<a<1)

Формат результата
В единственной строке выходного файла выведите вещественное число с точностью не менее 6 знаков после запятой
 — координата по оси Ox точки, в которой инспекция СЭС должна войти в лес.
 */


#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>


double get_path(double cathet_1, double cathet_2) {
	return sqrt((cathet_1 * cathet_1) + (cathet_2 * cathet_2));
}

double get_time(uint64_t speed, double path) {
	return path / speed;
}

double get_result_time(double a, uint64_t Vp, uint64_t Vf, double point) {
	double cathet_1_top = 1 - a;
	double cathet_2_top = point;
	double path_top = get_path(cathet_1_top, cathet_2_top);
	double time_top = get_time(Vp, path_top);

	double cathet_1_down = a;
	double cathet_2_down = 1 - point;
	double path_down = get_path(cathet_1_down, cathet_2_down);
	double time_down = get_time(Vf, path_down);
	return time_top + time_down;
}


int main() {
	uint64_t Vp, Vf;
	double a;
	std::cin >> Vp;
	std::cin >> Vf;
	std::cin >> a;
	double point;
	
	double eps = 0.0000001;

	double left = eps;
	double middle_point = 0.5000000;
	double right = 1 - eps;

	double left_board = get_result_time(a, Vp, Vf, left);
	double right_board = get_result_time(a, Vp, Vf, right);
	double middle = get_result_time(a, Vp, Vf, middle_point);
	bool flag = false;

	while (std::abs(right -left) > eps) {
		double left_2 = (2 * left + right) / 3;
		double right_2 = (2 * right + left) / 3;
		double left_2_board = get_result_time(a, Vp, Vf, left_2);
		double right_2_board = get_result_time(a, Vp, Vf, right_2);

		if (left_2_board - right_2_board > 0.0000000) {
			left = left_2;
			left_board = left_2_board;
			flag = true;
		}
		else if (left_2_board - right_2_board < 0.0000000) {
			right = right_2;
			right_board = right_2_board;
			flag = true;
		}
		else {
			if (middle - right_2_board < 0.000000) {
				left = left_2;
				left_board = left_2_board;
				right = right_2;
				right_board = right_2_board;
			}
		}

		if (flag) {
			middle_point = (left + right) / 2;
			flag = false;
		}
	}

	std::cout << std::fixed << std::showpoint;
	std::cout << std::setprecision(7);
	std::cout << middle_point;
	return 0;
} 