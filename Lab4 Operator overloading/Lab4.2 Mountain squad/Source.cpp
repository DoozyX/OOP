#include <iostream>
#include <string.h>

using namespace std;

class MSquad {
private:
	char *name;
	int tours;
	int members;
public:
	MSquad() {
		tours = 0;
		members = 0;
		name = new char[0];
	};
	MSquad(const char *name, int tours, int members) {
		int size = strlen(name) + 1;
		this->name = new char[size];
		strcpy_s(this->name, size, name);
		this->tours = tours;
		this->members = members;
	}
	MSquad(const MSquad &ms) {
		int size = strlen(ms.name) + 1;
		name = new char[size];
		strcpy_s(name, size, name);
		tours = ms.tours;
		members = ms.members;
	}
	friend ostream &operator<<(ostream &output, const MSquad &ms) {
		output << "Ime: " << ms.name << " Turi: " << ms.tours << " Clenovi: " << ms.members << endl;
		return output;
	}
	MSquad &operator=(const MSquad &ms) {
		int size = strlen(ms.name) + 1;
		name = new char[size];
		strcpy_s(name, size, name);
		tours = ms.tours;
		members = ms.members;
		return *this;
	}
	MSquad operator+(const MSquad &ms) {
		MSquad t;
		t.members = members + ms.members;
		if (members > ms.members) {
			t.tours = tours;
			int size = strlen(name) + 1;
			t.name = new char[size];
			strcpy_s(t.name, size, ms.name);
		}
		else {
			t.tours = ms.tours;
			int size = strlen(ms.name) + 1;
			t.name = new char[size];
			strcpy_s(t.name, size, ms.name);
		}
		return t;
	}
	bool operator>(const MSquad &ms) {
		if (members > ms.members) {
			return true;
		}
		return false;
	}
	bool operator<(const MSquad &ms) {
		if (members < ms.members) {
			return true;
		}
		return false;
	}
	~MSquad() {
		delete[] name;
	}
};

void mostMemebers(MSquad *ms, int n) {
	MSquad max;
	max = ms[0];
	for (int i = 1; i < n; i++) {
		if (ms[i] > max) {
			max = ms[i];
		}
	}
	cout << "Najmnogu clenovi ima planinarskoto drustvo: ";
	cout << max;
}

int main()
{
	MSquad squads[3];
	MSquad s;
	for (int i = 0;i<3;i++)
	{
		char name[100];
		int tours;
		int members;
		cin >> name;
		cin >> tours;
		cin >> members;
		squads[i] = MSquad(name, tours, members);
	}

	s = squads[0] + squads[1];
	cout << s;

	mostMemebers(squads, 3);

	return 0;
}
