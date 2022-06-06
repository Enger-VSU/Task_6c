#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

struct Restaurant {
	Restaurant* Next;
	string name;
	int Case;
	union
	{
		struct { int calor, gramm; } natritionalValue;
		struct { int rating, num; } ratingAndNumber;
	};
	int price;

};
Restaurant* DataBase = NULL; // указатель начала списка - базы данных

Restaurant inpDish(int Case) {
	Restaurant Restaurant;

	cout << "Введите название блюда: ";
	while (Restaurant.name == "") {
		getline(cin, Restaurant.name);
	}

	Restaurant.Case = Case;
	if (Case == 1) {
		cout << "Введите калорийность блюда: ";
		cin >> Restaurant.natritionalValue.calor;
		cout << "Введите вес в граммах: ";
		cin >> Restaurant.natritionalValue.gramm;
	}
	else {
		cout << "Введите рейтинг блюда (от 1 до 10): ";
		cin >> Restaurant.ratingAndNumber.rating;
		cout << "Введите порядковый номер в меню: ";
		cin >> Restaurant.ratingAndNumber.num;
	}

	cout << "Цена блюда: "; cin >> Restaurant.price;
	return Restaurant;
}

void outPutDish(Restaurant Restaurant) {
	cout << "Название: " << Restaurant.name << "\n";
	if (Restaurant.Case == 1) {
		cout << "Пищевая ценность: \n";
		cout << Restaurant.natritionalValue.calor << " калорий, " << Restaurant.natritionalValue.gramm << " грамм, ";
	}
	else {
		cout << "Порядковый номер блюда в меню и его популярность среди клиентов:\n";
		cout << Restaurant.ratingAndNumber.num << " номер, " << Restaurant.ratingAndNumber.rating << " баллов,\n";
	}

	cout << "Цена: " << Restaurant.price << "рублей\n";
}
void AddRestaruant(int num, char cs)
{
	Restaurant* q = new Restaurant; // Создали новую структуру.
	*q = inpDish(cs); // Заполнили ее информацией.
	if (DataBase == NULL) num = 0;
	if (num)
	{
		Restaurant* p = DataBase; // Ищем указатель
		while (p->Next != NULL && -num) // на предыдущую структуру.
			p = p->Next;
		q->Next = p->Next; p->Next = q;
	}
	else { q->Next = DataBase; DataBase = q; }
}
void DeleteRestaurant(int num) // Удаляем структуру
{
	Restaurant* q;
	if (DataBase == NULL) return;
	if (num)
	{
		Restaurant* p = DataBase;
		while (p->Next != NULL && -num) p = p->Next;
		if ((q = p->Next) != NULL) { p->Next = q->Next; delete q; }
	}
	else {
		q = DataBase;
		DataBase = q->Next;
		delete q;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Restaurant* p;

	int i, j;

	while (true) {
		cout << " Управление базой данных ресторана:\n"
			<< "1. Ввести данные.\n"
			<< "2. Вывести всю информацию.\n"
			<< "3. Удалить информацию о блюде.\n"
			<< "4. Удалить всю информацию из базы данных.\n"
			<< "5. Закончить работу.\n"
			<< ">";
		cin >> i;

		switch (i) {
		case 1:
			cout << "Номер блюда в базе данных: "; cin >> i;
			cout << "Информация(1-Пищевая ценность, 2-Номер блюда в меню и его рейтинг среди посетителей): "; cin >> j;
			AddRestaruant(i, j);
			break;
		case 2:
			p = DataBase;
			i = 0;
			while (p != NULL) {
				i += 1;
				cout << "Номер блюда в базе данных: " << i << endl;
				outPutDish(*p);
				p = p->Next;
			}
			break;
		case 3:
			cout << "Блюдо под #: ";
			cin >> i;
			DeleteRestaurant(i);
			break;
		case 4:
			while (DataBase != NULL) {
				p = DataBase;
				DataBase = p->Next;
				delete p;
			}
		case 5:
			return 0;
		default: cout << "Повторите !\n";
		}
	}
}