#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

class Property {
protected:
	char address[50];
	char city[50];
	float area;
public:
	Property(const char* _address = "unknown", const char* _city = "unknown", float _area = 0) {
		strcpy(address, _address);
		strcpy(city, _city);
		area = _area;
	}
	virtual float cena() const = 0;
	friend ostream& operator<<(ostream &output, const Property &p) {
		output << "Address: " << p.address << endl << "City: " << p.city << endl << p.area << " square meters" << endl;
		return output;
	}
	bool operator<(const Property &p) {
		return cena() < p.cena();
	}
	virtual ~Property() {}
};

class House : public Property {
private:
	int nFloors;
	float areaFloor;
	bool subRoof;
public:
	House(const char *_address = "unkndown", const char* _city = "unknown", float _area = 0, int _nFloors = 0, float _areaFloor = 0, bool _subRoof = false) :
		Property(_address, _city, _area) {
		nFloors = _nFloors;
		areaFloor = _areaFloor;
		subRoof = _subRoof;
	}
	float cena() const {
		return areaFloor*nFloors * 700 + subRoof * 450;
	}
};

class Building : public Property {
private:
	float areaApartment;
	int nApartments;
public:
	Building(const char *_address = "unkndown", const char* _city = "unknown", float _area = 0, float _areaApartment = 0, int _nApartments = 0) :
		Property(_address, _city, _area) {
		areaApartment = _areaApartment;
		nApartments = _nApartments;
	}
	float cena() const {
		return (areaApartment * 800)*nApartments + (nApartments * 500);
	}

};

void mostExpensiveProperty(Property **ps, int n) {
	Property *min = ps[0];
	for (int i = 1; i < n; ++i) {
		if (!(*ps[i] < *min)) {
			min = ps[i];
		}
	}
	cout << *min;
}

int main() {
	int n;
	int tip_nedviznost;

	cin >> n;

	Property **ned = new Property*[n];
	char adresa[100];
	char grad[30];
	float kvadratura;
	for (int i = 0; i < n; ++i) {
		cin >> tip_nedviznost >> adresa >> grad >> kvadratura;
		if (tip_nedviznost == 1) {
			int br_kat;
			float kvadrat_kat;
			bool potkrovje;
			cin >> br_kat >> kvadrat_kat >> potkrovje;
			ned[i] = new House(adresa, grad, kvadratura, br_kat, kvadrat_kat, potkrovje);
		} else if (tip_nedviznost == 2) {
			int br_stanovi;
			float kvadrat_na_stan;
			cin >> br_stanovi >> kvadrat_na_stan;

			ned[i] = new Building(adresa, grad, kvadratura, br_stanovi, kvadrat_na_stan);
		}
	}

	cout << "== PROPERTIES ==" << endl;
	for (int i = 0; i<n; i++) {
		cout << *(ned[i]) << "Price: " << ned[i]->cena() << endl;
	}

	cout << "=== MOST EXPENSIVE PROPERTY ===" << endl;
	mostExpensiveProperty(ned, n);

	return 0;
}