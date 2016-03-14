#include <iostream>
#include <string.h>

using namespace std;

class Automobile {
private:
	char *brand;
	int registration[5];
	int speed;	
public:
	Automobile() {};
	Automobile(const char *brand, int registration[], int speed) {
		int size = strlen(brand) + 1;
		this->brand = new char[size];
		strcpy_s(this->brand, size, brand);
		for (int i = 0; i < 5; i++) {
			this->registration[i] = registration[i];
		}
		this->speed = speed;
	}
	bool operator==(const Automobile &a) {
		for (int i = 0; i < 5; i++) {
			if (registration[i] != a.registration[i]) {
				return false;
			}
		}
		return true;
	}
	bool operator==(int n) {
		for (int i = 0; i < 5; i++) {
			if (speed==n) {
				return true;
			}
		}
		return false;
	}
	friend ostream &operator<<(ostream &output, const Automobile &a) {
		output << "Marka:\t" << a.brand << "\tRegistracija[ ";
		for (int i = 0; i < 5; i++) {
			output << a.registration[i] << " ";
		}
		output << "]" << endl;
		return output;
	}
	~Automobile()
	{
		delete [] brand;
	}
};

class RentACar {
private:
	char name[100];
	Automobile *automobiles;
	int nAutomobiles;
	int tAutomobiles;
public:
	RentACar() {};
	RentACar(const char *name) {
		int size = strlen(name) + 1;
		strcpy_s(this->name, size, name);
		nAutomobiles = 0;
		tAutomobiles = 0;
	}
	void operator+=(const Automobile &a) {
		if (nAutomobiles == tAutomobiles) {
			Automobile *temp = automobiles;
			automobiles = new Automobile[nAutomobiles * 2];
			for (int i = 0; i < nAutomobiles; i++) {
				automobiles[i] = temp[i];
			}
			nAutomobiles *= 2;
			//delete[] temp;
		}
		automobiles[nAutomobiles++] = a;

	}
	void operator-=(const Automobile &a) {
		for (int i = 0; i < nAutomobiles; i++) {
			if (automobiles[i] == a) {
				nAutomobiles--;
				for (int j = i; j < nAutomobiles; j++) {
					automobiles[j] = automobiles[j + 1];
				}
			}
		}
	}
	void pecatiNadBrzina(int n) {
		cout << "FINKI - Car" << endl;
		for (int i = 0; i < nAutomobiles; i++) {
			if (automobiles[i] == n) {
				cout << automobiles[i];
			}
		}
	}
	~RentACar()
	{
		//delete[] automobiles;
		//delete[] name;
	}
};

int main() {
	RentACar agencija("FINKI-Car");
	int n;
	cin >> n;

	for (int i = 0;i<n;i++)
	{
		char marka[100];
		int regisracija[5];
		int maximumBrzina;

		cin >> marka;

		for (int i = 0;i<5;i++)
			cin >> regisracija[i];

		cin >> maximumBrzina;

		Automobile nov = Automobile(marka, regisracija, maximumBrzina);
		//dodavanje na avtomobil
		agencija += nov;

	}
	//se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
	char marka[100];
	int regisracija[5];
	int maximumBrzina;
	cin >> marka;
	for (int i = 0;i<5;i++)
		cin >> regisracija[i];
	cin >> maximumBrzina;

	Automobile greshka = Automobile(marka, regisracija, maximumBrzina);

	//brishenje na avtomobil
	agencija -= greshka;

	agencija.pecatiNadBrzina(150);

	return 0;
}