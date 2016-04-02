#include <iostream>
#include <cstring>

using namespace std;

//Your code here
class RealEstate {
protected:
	char* address;
	int area;
	int priceForSqM;
public:
	RealEstate() {
		address = NULL;
		area = 0;
		priceForSqM = 0;
	}
	int price() {
		return area*priceForSqM;
	}
	void print() {
		cout << address << ", Kvadratura: " << area << ", Cena po Kvadrat: " << priceForSqM << endl;
	}
	float estateTax() {
		return price() * 5 / (float)100;
	}
	char* getAddress() {
		return address;
	}
	RealEstate &operator=(const RealEstate &re) {
		if (this != &re) {
			area = re.area;
			priceForSqM = re.priceForSqM;
			delete[] address;
			address = new char[strlen(re.address) + 1];
			strcpy(address, re.address);
		}
		return *this;
	}
	friend istream &operator>>(istream &input, RealEstate &re) {
		RealEstate t;
		t.address = new char[1024];
		input >> t.address >> t.area >> t.priceForSqM;
		re = t;
		return input;
	}
	~RealEstate() {
		delete[] address;
	}
};

class Villa : public RealEstate {
private:
	int luxuryTax;
public:
	Villa() {
		luxuryTax = 0;
	}
	void print() {
		cout << address << ", Kvadratura: " << area << ", Cena po Kvadrat: " << priceForSqM << ", Danok na luksuz: " << luxuryTax << endl;
	}
	float estateTax() {
		return price() * (5 + luxuryTax) / (float)100;
	}
	Villa &operator=(const Villa &v) {
		if (this != &v) {
			area = v.area;
			priceForSqM = v.priceForSqM;
			luxuryTax = v.luxuryTax;
			delete[] address;
			address = new char[strlen(v.address) + 1];
			strcpy(address, v.address);
		}
		return *this;
	}
	friend istream &operator>>(istream &input, Villa &v) {
		Villa t;
		t.address = new char[1024];
		input >> t.address >> t.area >> t.priceForSqM >> t.luxuryTax;
		v = t;
		return input;
	}
	~Villa() {}
};

int main() {
	RealEstate re;
	Villa v;
	cin >> re;
	cin >> v;
	re.print();
	cout << "Danok za: " << re.getAddress() << ", e: " << re.estateTax() << endl;
	v.print();
	cout << "Danok za: " << v.getAddress() << ", e: " << v.estateTax() << endl;
	return 0;
}
