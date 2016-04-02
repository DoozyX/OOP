#include <iostream>
#include <cstring>

using namespace std;

//Vasiot kod ovde
class Ekipa {
protected:
	char name[15];
	int win;
	int lose;
public:
	Ekipa(const char* ime = "unknown", int pob = 0, int por = 0) {
		strcpy(name, ime);
		win = pob;
		lose = por;
	}
	void print() {
		cout << "Ime: " << name << " Pobedi: " << win << " Porazi: " << lose;
	}
	~Ekipa() {}
};

class FudbalskaEkipa : public Ekipa {
private:
	int redCard;
	int yellowCard;
	int tie;
public:
	FudbalskaEkipa(const char* ime = "unknown", int pob = 0, int por = 0, int ck = 0, int zk = 0, int ner = 0) :Ekipa(ime, pob, por) {
		redCard = ck;
		yellowCard = zk;
		tie = ner;
	}
	int points() {
		return win * 3 + tie;
	}
	void print() {
		Ekipa::print();
		cout << " Nereseni: " << tie << " Poeni: " << points();
	}
	~FudbalskaEkipa() {}
};

int main() {
	char ime[15];
	int pob, por, ck, zk, ner;
	cin >> ime >> pob >> por >> ck >> zk >> ner;
	FudbalskaEkipa f1(ime, pob, por, ck, zk, ner);
	f1.print();
	return 0;
}