#include <iostream>
#include <cstring>
#include <string.h>
#include <exception>

using namespace std;

class BadRegistration : public exception {
public:
	const char* what() const throw () {
		return "Pogresno vnesena registracija";
	}
};

class BadAlcohol : public exception {
public:
	const char* what() const throw () {
		return "Pogresno vnesen procent na alkohol!";
	}
};

class ImaMasa {
public:
	virtual double vratiMasa() = 0;
	virtual void pecati() = 0;
};

class PaketPijalok {
protected:
	double volumenEden;
	int kolicina;
	static double gustina;
	static double masaNaAmbalza;
public:
	PaketPijalok(double vol = 0, int kol = 0) {
		volumenEden = vol;
		kolicina = kol;
	}
	virtual double vratiMasa() {
		return (volumenEden*gustina + masaNaAmbalza) * kolicina;
	}
	virtual void pecati() {
		cout << "kolicina " << kolicina << ", so po " << volumenEden*gustina << " l(dm3)" << endl;
	}
};
class PaketSok : public PaketPijalok, public ImaMasa {
private:
	bool daliGaziran;
public:
	PaketSok(double vol = 0, int kol = 0, bool gaziran = false) : PaketPijalok(vol, kol) {
		daliGaziran = gaziran;
	}
	double vratiMasa() {
		if (daliGaziran) {
			return PaketPijalok::vratiMasa();
		}
		return PaketPijalok::vratiMasa() + 0.1*kolicina;
	}
	void pecati() {
		cout << "Paket sok" << endl;
		PaketPijalok::pecati();
	}
};
class PaketVino : public PaketPijalok, public ImaMasa {
private:
	double procentAlkohol;
public:
	PaketVino(double vol = 0, int kol = 0, double procent = 0) : PaketPijalok(vol, kol) {
		if (procent <= 1 && procent >= 0) {
			procentAlkohol = procent;
		}else {
			procentAlkohol = 0;
			throw BadAlcohol();
		}
	}
	double vratiMasa() {
		return PaketPijalok::vratiMasa() * (0.9 + procentAlkohol);
	}
	void pecati() {
		cout << "Paket vino" << endl;
		cout << "kolicina " << kolicina << ", " << procentAlkohol * 100 << "% alkohol od po " << volumenEden*gustina << " l(dm3)" << endl;
	}
};

class Kamion {
private:
	char *registration;
	char *driver;
	ImaMasa **elements;
	int nElements;
public:
	Kamion(const char *_registration, const char *_driver) {
		driver = new char[strlen(_driver) + 1];
		strcpy_s(driver, strlen(_driver) + 1, _driver);
		nElements = 0;
		elements = NULL;
		int regLen = strlen(_registration);
		if (regLen != 8) throw BadRegistration();
		if (!isalpha(_registration[0]) && !isalpha(_registration[1]) && !isalpha(_registration[6]) && !isalpha(_registration[7])) throw BadRegistration();
		registration = new char[regLen+1];
		strcpy_s(registration, regLen + 1, _registration);

	}
	Kamion(const Kamion &k) {
		registration = new char[strlen(k.registration) + 1];
		strcpy_s(registration, strlen(k.registration) + 1, k.registration);
		driver = new char[strlen(k.driver) + 1];
		strcpy_s(driver, strlen(k.driver) + 1, k.driver);
		nElements = k.nElements;
		elements = new ImaMasa*[nElements];
		for (int i = 0; i < nElements; ++i) {
			elements[i] = k.elements[i];
		}
	}
	void dodadiElement(ImaMasa *im) {
		ImaMasa **temp = elements;
		elements = new ImaMasa*[nElements + 1];
		for (int i = 0; i < nElements; ++i) {
			elements[i] = temp[i];
		}		
		elements[nElements] = im;
		++nElements;
		delete[] temp;
	}
	double vratiVkupnaMasa() {
		double total = 0;
		for (int i = 0; i < nElements; ++i) {
			total += elements[i]->vratiMasa();
		}
		return total;
	}
	void pecati() {
		cout << "Kamion so registracija " << registration << " i vozac " << driver << " prenesuva: " << endl;
		for (int i = 0; i < nElements; ++i) {
			elements[i]->pecati();
		}
	}
	Kamion pretovar(const char* _registration, const char* _driver) {
		Kamion k(_registration, _driver);
		int maxI = -1;
		double maxMasa = 0;
		for (int i = 0; i < nElements; ++i) {
			if (elements[i]->vratiMasa() > maxMasa) {
				maxI = i;
				maxMasa = elements[i]->vratiMasa();
			}
		}
		for (int i = 0; i < nElements; ++i) {
			if (i != maxI) {
				k.dodadiElement(elements[i]);
			}
		}
		return k;
	}
	~Kamion() {
		delete[] registration;
		delete[] driver;
		delete[] elements;
	}
};

double PaketPijalok::gustina = 0.8;
double PaketPijalok::masaNaAmbalza = 0.2;

int main()
{
	char ime[20], reg[9];
	double vol;
	int kol;
	bool g;
	double proc;

	cin >> reg;
	cin >> ime;
	try {
		Kamion A(reg, ime);
		ImaMasa **d = new ImaMasa*[5];
		cin >> vol >> kol;
		cin >> g;
		d[0] = new PaketSok(vol, kol, g);
		cin >> vol >> kol;
		cin >> proc;
		try {
			d[1] = new PaketVino(vol, kol, proc);
		}catch (BadAlcohol &ba) {
			d[1] = new PaketVino(vol, kol, 0);
			cout << ba.what() << endl;
		}		
		cin >> vol >> kol;
		cin >> proc;
		try {
			d[2] = new PaketVino(vol, kol, proc);
		}catch (BadAlcohol &ba) {
			cout << ba.what() << endl;
			d[2] = new PaketVino(vol, kol, 0);
		}
		cin >> vol >> kol;
		cin >> g;
		d[3] = new PaketSok(vol, kol, g);
		cin >> vol >> kol;
		cin >> proc;
		try {
			d[4] = new PaketVino(vol, kol, proc);
		}catch (BadAlcohol &ba) {
			cout << ba.what() << endl;
			d[4] = new PaketVino(vol, kol, 0);
		}

		A.dodadiElement(d[0]);
		A.dodadiElement(d[1]);
		A.dodadiElement(d[2]);
		A.dodadiElement(d[3]);
		A.dodadiElement(d[4]);
		A.pecati();
		cout << "Vkupna masa: " << A.vratiVkupnaMasa() << endl;
		cin >> reg;
		cin >> ime;
		Kamion B = A.pretovar(reg, ime);
		B.pecati();
		cout << "Vkupna masa: " << B.vratiVkupnaMasa() << endl;
	}catch (BadRegistration& br){
		cout << br.what() << endl;
	}

	return 0;
}
