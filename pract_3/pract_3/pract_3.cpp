#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

struct Date {
	unsigned short day;
	unsigned short month;
	unsigned short year;
};

struct Record
{
	char transportType[5];
	char route[5];
	double lengthRoute;
	char timeMin[5];
	struct Date date;
};

struct node {
	Record data;
	struct node* next;
};
struct node* myHead;
int countItem = 0;

void myCentr(string s, int wLine) {

	int w = s.length();
	int delta = (wLine - w) / 2;
	cout << left;
	cout.width(delta); cout << " ";
	cout << s;
	cout.width(delta + 1); cout << " ";

}

void printDate(unsigned short day, unsigned short month, unsigned short year, int wLine) {
	int w = 10;
	int delta = (wLine - w) / 2 - 1;
	cout << left;
	cout.width(delta); cout << " ";
	if (day > 9) {
		cout << day;
	}
	else {
		cout << "0" << day;
	}
	cout << ".";
	if (month > 9) {
		cout << month;
	}
	else {
		cout << "0" << month;
	}
	cout << ".";
	cout << year;
	cout.width(delta); cout << " ";
}

void printWhithZero(int num, int width) {
	if (num > 999 and num < 10000) {
		cout.width(width + 1);
		cout << right << "00" << num;
	}
	if (num > 9999 and num < 100000) {
		cout.width(width);
		cout << right << "0" << num;
	}
}

void Draw(struct Record* records) {
	int width = 78 + 16;
	cout << endl;	cout.width(width + 1); cout.fill('-'); cout << "-" << endl;
	cout.fill(' '); cout.width(width);  cout << left << "|Ведомость общественного транспорта"; cout << "|" << endl;
	cout.width(width + 1); cout.fill('-'); cout << "-" << endl;
	cout.fill(' ');
	cout << left << "| Вид транспорта ";
	cout << left << "| маршрута";
	cout << left << "| Протяженность маршрута (км)";
	cout << left << "| Время в дороге (мин)";
	cout << left << " |     Дата     |" << endl;
	cout.width(width + 1); cout.fill('-'); cout << "-" << endl;
	cout.fill(' ');
	for (int i = 0; i < 3; i++) {
		cout << left << "|";  cout << left; myCentr(records[i].transportType, 16);
		cout << left << "| ";  cout << left; myCentr(records[i].route, 8);
		cout.precision(3);
		cout << left << "|           "; cout << left << fixed << records[i].lengthRoute;
		cout << left << "           ";
		cout << left << "|"; cout.width(20); cout << left; myCentr(records[i].timeMin, 22);
		cout << left << "|";
		printDate(records[i].date.day, records[i].date.month, records[i].date.year, 16);
		cout << "|" << endl;
	}
	cout.width(width + 1); cout.fill('-'); cout << "-" << endl;
	cout.fill(' '); cout.width(width);  cout << left << "|Примечание: Тр - трамвай, Тс - троллейбус, А - автобус"; cout << "|" << endl;
	cout.width(width + 1); cout.fill('-'); cout << "-" << endl;
}

vector<int> getMinMonthDate(struct Record* records) {
	vector<int> indexes;
	int minMonth = 13;
	for (int i = 0; i < 10; i++) {
		if (records[i].date.month < minMonth) {
			minMonth = records[i].date.month;
		}
	}
	for (int i = 0; i < 10; i++) {
		if (minMonth == records[i].date.month) {
			indexes.push_back(i);
		}
	}
	return indexes;
}

vector<int> getMaxMonthDate(struct Record* records) {
	vector<int> indexes;
	int maxMonth = 0;
	for (int i = 0; i < 10; i++) {
		if ((maxMonth < records[i].date.month) and (records[i].date.month < 13)) {
			maxMonth = records[i].date.month;
		}
	}
	for (int i = 0; i < 10; i++) {
		if (maxMonth == records[i].date.month) {
			indexes.push_back(i);
		}
	}
	return indexes;
}

void addItem(Record data)
{
	struct node* newItem = new node();
	newItem->data = data;
	if (countItem == 0) {
		newItem->next = NULL;
	}
	else
	{
		newItem->next = myHead;
	}
	myHead = newItem;
	countItem++;
}
/// <summary>
/// Вставка элемента в список
/// </summary>
/// <param name="index">индекс после которого вставить</param>
/// <param name="data">значение которое необходимо вставить</param>
void insertItem(int index, Record data) {
	if (not (index >= 0 and index <= countItem and countItem >= 0))
		return;
	if (index == 0) {
		addItem(data);
	}
	else {
		struct node* current = myHead;
		for (int i = 0; i < index - 1; i++) {
			current = current->next;
		}
		struct node* newItem = new node();
		newItem->data = data;
		newItem->next = current->next;
		current->next = newItem;
		countItem++;
	}
}
/// <summary>
/// Изменить элемент списка
/// </summary>
/// <param name="index">индекс изменяемого элемента</param>
/// <param name="data">значение на которое нужно изменить</param>
void editItem(int index, Record data) {
	if (index >= 0 and index < countItem and countItem>0) {
		struct node* current = myHead;
		for (int i = 0; i < index; i++) {
			current = current->next;
			//cout << "+" << current->data;
		}
		current->data = data;
	}
	else {
		cout << endl << "Ошибка индекс не в диапазоне";
	}
}
/// <summary>
/// Функция для удаления элемента из динамического списка
/// </summary>
/// <param name="index">Индекс удаляемого элемента</param>
void deleteItem(int index) {
	if (index >= 0 and index < countItem and countItem>0) {
		struct node* current = myHead;
		struct node* old;
		if (index == 0) {
			old = myHead;
			myHead = current->next;
			delete old;
			countItem--;
		}
		else {
			int i = 0;
			while (current) {
				if (i == index - 1) {
					old = current->next->next;
					delete current->next;
					current->next = old;
					countItem--;
					break;
				}
				i++;
				current = current->next;
			}
		}
	}
}
void printMyList() {
	struct node* current = myHead;
	cout << endl;
	while (current) {
		cout << " " << current->data.transportType;
		current = current->next;
	}
}
void DrawWithList() {
	int width = 78 + 16;
	cout << endl;	cout.width(width + 1); cout.fill('-'); cout << "-" << endl;
	cout.fill(' '); cout.width(width);  cout << left << "|Ведомость общественного транспорта"; cout << "|" << endl;
	cout.width(width + 1); cout.fill('-'); cout << "-" << endl;
	cout.fill(' ');
	cout << left << "| Вид транспорта ";
	cout << left << "| маршрута";
	cout << left << "| Протяженность маршрута (км)";
	cout << left << "| Время в дороге (мин)";
	cout << left << " |     Дата     |" << endl;
	cout.width(width + 1); cout.fill('-'); cout << "-" << endl;
	cout.fill(' ');
	struct node* current = myHead;
	while (current) {
		cout << left << "|"; cout.width(16); cout << left << current->data.transportType;
		cout << left << "|"; cout.width(8 + 1); cout << left << current->data.route;
		cout << left << "|+"; cout.width(22 + 5); cout << left << current->data.lengthRoute;
		std::cout.precision(2);
		cout << left << "|"; cout.width(22); cout << left << fixed << current->data.timeMin;
		cout << left << "|";
		printDate(current->data.date.day, current->data.date.month, current->data.date.year, 16);
		cout << "|" << endl;
		current = current->next;
	}
	cout.width(width + 1); cout.fill('-'); cout << "-" << endl;
	cout.fill(' '); cout.width(width);  cout << left << "|Примечание: Тр - трамвай, Тс - троллейбус, А - автобус"; cout << "|" << endl;
	cout.width(width + 1); cout.fill('-'); cout << "-" << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	struct Record records[10];

	records[0] = { "Тр.", "12 ", 27.550, "75 ", {03,04,2022} };
	records[1] = { "Т-с", "17 ", 13.600, "57 ", {03,04,2020} };
	records[2] = { "А", "12а",  57.300, "117", {04,03,2022} };

	Draw(records);

	vector<int> minIndexes = getMinMonthDate(records);
	vector<int> maxIndexes = getMaxMonthDate(records);
	for (auto i : minIndexes)
		cout << endl << "minIndexes = " << i << ' ';
	for (auto i : maxIndexes)
		cout << endl << "maxIndexes = " << i << ' ';

	cout << endl << "Поменять местами записи(элементы массива структур),";
	cout << endl << "содержащие минимальный и максимальный номер месяца даты" << endl;

	struct Record tmpRecord = records[maxIndexes[0]];
	for (auto i : maxIndexes)
		records[i] = records[minIndexes[0]];
	for (auto i : minIndexes)
		records[i] = tmpRecord;


	Draw(records);
	cout << endl << "Практическая № 2 (Динамические массивы):" << endl;
	Record* A;
	int n = 3;
	A = (Record*)malloc(n * sizeof(Record));
	//A = (Record*)calloc(n, sizeof(Record)); 
	for (int i = 0; i < n; i++) {
		strcpy_s(A[i].transportType, records[i].transportType);
		strcpy_s(A[i].timeMin, records[i].timeMin);
		//A[i].surName = records[i].surName;
		/*A[i].year, records[i].year;*/
		//A[i].surName.assign(records[i].surName.c_str());
		//	*(B[i]) = records[i];
		//basic_string<char>
	}

	Record** B;
	B = (Record**) new Record * [10];
	for (int i = 0; i < 10; i++) {
		B[i] = (Record*) new Record;
		*(B[i]) = records[i];
	}

	//
	A = (Record*)realloc(A, 10 * sizeof(Record));
	// 
	//Record ** B;
	//B = (Record**) new Record * [10];
	//for (int i = 0; i < 10; i++) {
	//	B[i] = (Record*) new Record;
	//	*(B[i]) = A[i];
	//	//B[i].surName = A[i].surName;
	//	//*(B[i])->surName = A[i]->surName;
	//	
	//}

	//адрес а[i], значение a[i]->строковое_поле, адрес в[i], значение в[i]->строковое_поле.
	for (int i = 0; i < 3; i++) {
		cout << endl << "адрес A[i] " << &A[i] << " a[i]->transportType " << A[i].transportType;
		//cout << endl << "адрес B[i] " << &B[i] << " B[i]->surName " << B[i]->surName;
	}

	//for (int i = 0; i < 10; i++) {
	//	delete B[i];
	//}
	//delete[]B;
	//free(A);

	cout << "Практика 3 Динамический список" << endl;
	//system("mspaint");
	addItem(records[0]);
	addItem(records[1]);
	addItem(records[2]);
	DrawWithList();
	struct Record newRecord = { "Тр.", "12", 27.550, "75", {03,04,2022} };
	insertItem(1, newRecord);
	DrawWithList();
	deleteItem(3);
	DrawWithList();
	struct Record editRecord = { "Т-с", "17", 13.600, "57 ", {03,04,2020} };
	editItem(1, editRecord);
	DrawWithList();
}