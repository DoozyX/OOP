#include <iostream>
#include <string.h>

using namespace std;

class Worker {
private:
	char firstName[30];
	char lastName[30];
	int salary;
public:
	Worker() {};
	Worker(char *firstName, char *lastName, int salary) {
		strcpy_s(this->firstName, 30, firstName);
		strcpy_s(this->lastName, 30, lastName);
		this->salary = salary;
	}
	int getSalary() {
		return salary;
	}
	void print() {
		cout << firstName << " " << lastName << " " << salary << endl;
	}
	~Worker() {};
};

class Factory {
private:
	Worker workers[100];
	int workersNumber;
public:
	Factory() {};
	Factory(Worker workers[], int workersNumber) {
		this->workersNumber = workersNumber;
		for (int i = 0; i < workersNumber; i++) {
			this->workers[i] = workers[i];
		}
	}
	void printWorkers() {
		cout << "ALL WORKERS:" << endl;
		for (int i = 0; i < workersNumber; i++) {
			workers[i].print();
		}

	}
	void printWithSalary(int salary) {
		cout << "EMPLOYEES WITH SALARY " << salary << ":" << endl;
		for (int i = 0; i < workersNumber; i++) {
			if (workers[i].getSalary()>salary) {
				workers[i].print();
			}
		}
	}

	~Factory() {};
};

int main() {
	int n;
	cin >> n;
	Worker workers[100];
	for (int i = 0; i < n; i++) {
		char name[30], lastName[30];
		int salary;
		cin >> name >> lastName >> salary;
		workers[i] = Worker(name, lastName, salary);
	}
	int salary;
	cin >> salary;
	Factory factory(workers, n);
	factory.printWorkers();
	factory.printWithSalary(salary);
}