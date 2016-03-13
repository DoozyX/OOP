#include <iostream>
#include <cstring>

using namespace std;

class Potpisuvac {
	//vasiot kod ovde
private:
	char name[20];
	char surname[20];
	char ID[15];
public:
	Potpisuvac() {};
	Potpisuvac(char *name, char *surname, char *ID) {
		strcpy_s(this->name, 20, name);
		strcpy_s(this->surname, 20, surname);
		strcpy_s(this->ID, 15, ID);
	};
	char *getID() {
		return ID;
	}
	~Potpisuvac() {};
};

class Dogovor {
	//vasiot kod ovde
private:
	int num;
	char category[50];
	Potpisuvac signer[3];
public:
	Dogovor() {}
	Dogovor(int num, const char *category, const Potpisuvac signer[]) {
		this->num = num;
		strcpy_s(this->category, 50, category);
		this->signer[0] = signer[0];
		this->signer[1] = signer[1];
		this->signer[2] = signer[2];
	};
	bool proverka() {
		if (!strcmp(signer[0].getID(), signer[1].getID())) {
			return true;
		}
		if (!strcmp(signer[0].getID(), signer[2].getID())) {
			return true;
		}
		if (!strcmp(signer[1].getID(), signer[2].getID())) {
			return true;
		}
		return false;
	}
	~Dogovor() {};
};


int main() {
	char embg[14], ime[20], prezime[20], kategorija[20];
	int broj, n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> embg >> ime >> prezime;
		Potpisuvac p1(ime, prezime, embg);
		cin >> embg >> ime >> prezime;
		Potpisuvac p2(ime, prezime, embg);
		cin >> embg >> ime >> prezime;
		Potpisuvac p3(ime, prezime, embg);
		cin >> broj >> kategorija;
		Potpisuvac p[3];
		p[0] = p1; p[1] = p2; p[2] = p3;
		Dogovor d(broj, kategorija, p);
		cout << "Dogovor " << i + 1 << ":" << endl;
		if (d.proverka() == true)
			cout << "Postojat potpishuvaci so ist EMBG" << endl;
		else
			cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
	}
	return 0;
}
