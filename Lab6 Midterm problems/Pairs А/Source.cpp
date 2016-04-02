#include <iostream>
#include <cstring>
using namespace std;


// Your code here
class Pair {
private:
	char *key;
	int value;
	void copy(const Pair &p) {
		value = p.value;
		key = new char[strlen(p.key) + 1];
		strcpy(key, p.key);
	}
public:
	Pair(const char* key = "unknown", int value = 0) {
		this->value = value;
		this->key = new char[strlen(key) + 1];
		strcpy(this->key, key);
	}
	Pair(const Pair &p) {
		copy(p);
	}
	char* getKey() {
		return key;
	}
	Pair &operator=(const Pair &p) {
		if (this != &p) {
			delete[] key;
			copy(p);
		}
		return *this;
	}
	friend ostream &operator<<(ostream &output, const Pair &p) {
		output << "('" << p.key << "', " << p.value << ")" << endl;
		return output;
	}
	Pair &operator++() {
		++value;
		return *this;
	}
	Pair operator++(int) {
		Pair t(*this);
		++value;
		return t;
	}
	Pair operator+(const Pair &p) {
		Pair t;
		if (strlen(key) >= strlen(p.key)) {
			t = *this;
			t.value += p.value;
		}
		else {
			t = p;
			t.value += value;
		}
		return t;
	}
	bool operator!=(const Pair &p) {
		if (value == p.value && (!strcmp(key, p.key))) {
			return false;
		}
		return true;
	}
	bool operator==(const Pair &p) {
		if (!strcmp(key, p.key)) {
			return true;
		}
		return false;
	}
	~Pair() {
		delete[] key;
	}
};

class Collection {
private:
	Pair *pairs;
	int length;
	void copy(const Collection &c) {
		length = c.length;
		pairs = new Pair[c.length];
		for (int i = 0; i < length; ++i) {
			pairs[i] = c.pairs[i];
		}
	}
public:
	Collection(Pair *pairs = NULL, int length = 0) {
		this->length = length;
		this->pairs = new Pair[length];
		for (int i = 0; i < length; ++i) {
			this->pairs[i] = pairs[i];
		}
	}
	Collection(const Collection &c) {
		copy(c);
	}
	Collection &operator=(const Collection &c) {
		if (this != &c) {
			delete[] pairs;
			copy(c);
		}
		return *this;
	}
	void operator+=(const Pair &p) {
		Pair *t = pairs;
		pairs = new Pair[length + 1];
		for (int i = 0; i<length; ++i) {
			pairs[i] = t[i];
		}
		pairs[length] = p;
		++length;

		delete[] t;
	}
	friend ostream &operator<<(ostream &output, const Collection &c) {
		output << "Size: " << c.length << endl;
		for (int i = 0; i<c.length; ++i) {
			output << c.pairs[i];
		}
		return output;
	}
	bool operator==(const Collection &p) {
		if (length == p.length) {
			for (int i = 0; i<length; ++i) {
				if (pairs[i] != p.pairs[i]) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
	Pair* find(const char* key) {
		for (int i = 0; i<length; ++i) {
			if (!strcmp(pairs[i].getKey(), key)) {
				return &pairs[i];
			}
		}
		return NULL;
	}
	~Collection() {
		delete[] pairs;
	}
};


void read(char *k, float *v) {
	cin >> k;
	cin >> *v;
}
int main() {
	char key[50];
	float value;
	cout << "----- class Pair -----" << endl;
	read(key, &value);
	cout << "----- constructor -----" << endl;
	Pair p1(key, value);
	read(key, &value);
	Pair p2(key, value);
	Pair p3(p1);
	cout << "----- operator << -----" << endl;
	cout << p1;
	cout << p2;
	cout << "----- operator ++(int) -----" << endl;
	cout << p1++;
	cout << p1;
	cout << "----- operator ++ -----" << endl;
	cout << ++p2;
	cout << "----- operator + -----" << endl;
	Pair p = p1 + p2;
	cout << "----- operator = -----" << endl;
	p3 = p;
	cout << p3;

	cout << "----- class Collection -----" << endl;
	cout << "----- constructor -----" << endl;
	Collection k;
	cout << "----- operator += -----" << endl;
	k += p1;
	k += p2;
	k += p3;
	cout << "----- operator << -----" << endl;
	cout << k;
	cout << "----- copy constructor -----" << endl;
	Collection k2(k);
	cout << "----- operator == -----" << endl;
	if (k == k2) {
		cout << "k == k2" << endl;
	}
	k2 += p1;
	if (k == k2) {
		// not equal
		cout << "k == k2" << endl;
	}
	cout << "----- find -----" << endl;
	Pair* f = k.find(key);
	cout << *f;
	strcat(key, "other");
	f = k.find(key);
	if (f == NULL) {
		cout << key << " not found" << endl;
	}
	return 0;
}
