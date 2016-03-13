#include <iostream>

using namespace std;

// your code here
class Table {
private:
	int width;
	int height;
public:
	Table() {};
	Table(int width, int height) {
		this->width = width;
		this->height = height;
	}
	void print() {
		cout << "Table: " << width << " " << height << " " << endl;
	}
	~Table() {};
};

class Room {
private:
	Table table;
	int length;
	int width;
public:
	Room() {};
	Room(int width, int lenght, Table t1) {
		this->width = width;
		this->length = lenght;
		this->table = t1;
	}
	void print() {
		cout << "Room: " << width << " " << length << " ";
		table.print();
	};
	~Room() {};
};

class House {
private:
	Room room;
	char adress[50];
public:
	House() {};
	House(Room room, char *adress) {
		this->room = room;
		strcpy_s(this->adress, 50, adress);
	}
	void print() {
		cout << "Address: " << adress << " ";
		room.print();
	}
	~House() {};
};

int main() {
	int n;
	cin >> n;
	for (int i = 0;i<n;i++) {
		int tableWidth, tableHeight;
		cin >> tableWidth;
		cin >> tableHeight;
		Table t(tableWidth, tableHeight);
		int rw, rl;
		cin >> rw;
		cin >> rl;
		Room r(rw, rl, t);
		char adresa[30];
		cin >> adresa;
		House h(r, adresa);
		h.print();
	}

	return 0;
}