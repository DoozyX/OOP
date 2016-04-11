#include<iostream>

using namespace std;

// your code here
class Vehicle {
protected:
	float mass;
	int width;
	int height;
public:
	Vehicle(float m = 0, int w = 0, int h = 0) {
		mass = m;
		width = w;
		height = h;
	}
	virtual int dailyPrice() {
		return 0;
	}
	float getMass() {
		return mass;
	}
	int getWidth() {
		return width;
	}
};

class Automobile : public Vehicle {
private:
	int nDoors;
public:
	Automobile(float m, int w, int h, int n) : Vehicle(m, w, h) {
		nDoors = n;
	}
	int dailyPrice() {
		if (nDoors < 5) {
			return 100;
		}
		return 130;
	}
};

class Bus : public Vehicle {
private:
	int nPassengers;
public:
	Bus(float m, int w, int h, int n) : Vehicle(m, w, h) {
		nPassengers = n;
	}
	int dailyPrice() {
		return nPassengers * 5;
	}
};

class Truck : public Vehicle {
private:
	float maxWeight;
public:
	Truck(float m, int w, int h, float mW) : Vehicle(m, w, h) {
		maxWeight = mW;
	}
	float getMaxWeight() {
		return maxWeight;
	}
	int dailyPrice() {
		return (mass + maxWeight) * 0.02;
	}
};

class Parking {
private:
	Vehicle **vehicles;
	int nVehicles;
public:
	Parking() {
		nVehicles = 0;
		vehicles = NULL;
	}
	Parking &operator+=(Vehicle *v) {
		Vehicle **temp = vehicles;
		vehicles = new Vehicle*[nVehicles + 1];
		for (int i = 0; i < nVehicles; ++i) {
			vehicles[i] = temp[i];
		}
		vehicles[nVehicles] = v;
		++nVehicles;
		delete[] temp;
		return *this;
	}
	void print() {
		int autos = 0, buses = 0, trucks = 0;
		for (int i = 0; i < nVehicles; ++i) {
			Automobile *tAuto = dynamic_cast <Automobile *> (vehicles[i]);
			if (tAuto) {
				++autos;
				continue;
			}
			Bus *tBus = dynamic_cast <Bus *> (vehicles[i]);
			if (tBus) {
				++buses;
				continue;
			}
			Truck *tTruck = dynamic_cast <Truck *> (vehicles[i]);
			if (tTruck) {
				++trucks;
			}
		}
		cout << "Automobiles: " << autos << endl
			<< "Busses: " << buses << endl
			<< "Trucks: " << trucks << endl;
	}
	int dailyProfit() {
		int profit = 0;
		for (int i = 0; i < nVehicles; ++i) {
			profit += vehicles[i]->dailyPrice();
		}
		return profit;
	}
	float totallMass() {
		float tMass = 0;
		for (int i = 0; i < nVehicles; ++i) {
			tMass += vehicles[i]->getMass();
		}
		return tMass;
	}
	int vehiclesWiderThan(int width) {
		int count = 0;
		for (int i = 0; i < nVehicles; ++i) {
			if (vehicles[i]->getWidth() > width) {
				++count;
			}
		}
		return count;
	}
	int greaterMaxWeightThan(Vehicle &v) {
		int count = 0;
		for (int i = 0; i < nVehicles; ++i) {
			Truck *tTruck = dynamic_cast <Truck *> (vehicles[i]);
			if (tTruck) {
				if (tTruck->getMaxWeight() > v.getMass()) {
					count++;
				}
			}

		}
		return count;
	}
	~Parking() {
		delete[] vehicles;
	}
};

int main() {
	Parking p;
	int n;
	cin >> n;
	int width, height, broj;
	float mass, max_weight;
	for (int i = 0; i < n; i++) {
		int type;
		cin >> type;
		if (type == 1) {
			cin >> mass >> width >> height >> broj;
			Automobile *a = new Automobile(mass, width, height, broj);
			p += a;
		}
		if (type == 2) {
			cin >> mass >> width >> height >> broj;
			p += new Bus(mass, width, height, broj);
		}
		if (type == 3) {
			cin >> mass >> width >> height >> max_weight;
			p += new Truck(mass, width, height, max_weight);
		}
	}
	p.print();
	cout << "\nDaily profit: " << p.dailyProfit() << endl;
	cout << "Total mass: " << p.totallMass() << endl;
	cout << "Number wider then 5 is: " << p.vehiclesWiderThan(5) << endl;
	Automobile a(1200, 4, 3, 5);
	cout << "Number of trucks with max weight larger then the automobile is: " << p.greaterMaxWeightThan(a) << endl;
	return 0;
}
