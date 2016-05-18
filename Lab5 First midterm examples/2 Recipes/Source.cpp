#include<iostream>
#include<cstring>
using namespace std;

// your code here
class Recipe {
private:
	int ingredients;
	char name[100];
	char *contents;
	void cpy(const Recipe &r) {
		this->ingredients = r.ingredients;
		strcpy(this->name, r.name);
		this->contents = new char[strlen(r.contents) + 1];
		strcpy(this->contents, r.contents);
	}
public:
	Recipe(int ingredients = 0, const char name[] = "unknown", const char *contents = "unknown") {
		this->ingredients = ingredients;
		strcpy(this->name, name);
		this->contents = new char[strlen(contents) + 1];
		strcpy(this->contents, contents);
	}
	Recipe(const Recipe &r) {
		cpy(r);
	}
	void set_num_ing(int i) {
		ingredients = i;
	}
	void set_name(const char *name) {
		strcpy(this->name, name);
	}
	void set_contents(char *contents) {
		this->contents = new char[strlen(contents) + 1];
		strcpy(this->contents, contents);
	}
	Recipe &operator=(const Recipe &r) {
		if (this != &r) {
			delete[] contents;
			cpy(r);
		}
		return *this;
	}
	friend ostream &operator<<(ostream &output, const Recipe &r) {
		output << r.ingredients << endl << r.name << endl << r.contents << endl;
		return output;
	}
	bool operator==(const Recipe &r) {
		if (strcmp(name, r.name))
			return false;
		return true;
	}
	Recipe &operator++() {
		++ingredients;
		return *this;
	}
	Recipe operator++(int) {
		Recipe r(*this);
		++ingredients;
		return r;
	}
	int getIngredients() {
		return ingredients;
	}
	~Recipe() {
		delete[] contents;
	}
};

class RecipesBook {
private:
	char name[100];
	Recipe *recipes;
	int num;
	void cpy(const RecipesBook &rb) {
		strcpy(name, rb.name);
		num = rb.num;
		recipes = new Recipe[rb.num + 1];
		for (int i = 0; i < rb.num; ++i) {
			recipes[i] = rb.recipes[i];
		}
	}
public:
	RecipesBook(const char *name = "unknown") {
		strcpy(this->name, name);
		recipes = NULL;
		num = 0;
	}
	RecipesBook(const RecipesBook &rb) {
		cpy(rb);
	}
	RecipesBook &operator=(const RecipesBook &rb) {
		if (this != &rb) {
			delete[] recipes;
			cpy(rb);
		}
		return *this;
	}
	bool notSameRecie(const Recipe &r) {
		for (int i = 0; i < num; ++i) {
			if (recipes[i] == r) {
				return false;
			}
		}
		return true;
	}
	RecipesBook &operator+=(const Recipe &r) {
		if (notSameRecie(r)) {
			Recipe *rp = recipes;
			recipes = new Recipe[num + 1];
			for (int i = 0; i < num; ++i) {
				recipes[i] = rp[i];
			}
			recipes[num] = r;
			++num;
		}
		return *this;
	}
	friend ostream &operator<<(ostream &output, const RecipesBook &rb) {
		output << rb.name << endl;
		for (int i = 0; i < rb.num; ++i) {
			output << rb.recipes[i] << endl;
		}
		return output;
	}

	RecipesBook newBook(Recipe &r) {
		RecipesBook nb(name);
		for (int i = 0; i < num; ++i) {
			if (recipes[i].getIngredients() < r.getIngredients()) {
				Recipe rec = recipes[i];
				++rec;
				nb += rec;
			}
		}
		return nb;
	}

};

int main() {
	Recipe rec;
	int n;
	char name[100], contents[200];
	int num_ing;
	cin >> name >> n;
	RecipesBook b1(name);
	Recipe last;
	for (int i = 0; i < n; i++) {
		cin >> num_ing >> name >> contents;
		Recipe r(num_ing, name, contents);
		b1 += r;
		last = r;
	}
	cout << b1;
	cin >> num_ing >> name >> contents;
	rec.set_num_ing(num_ing);
	rec.set_name(name);
	rec.set_contents(contents);
	b1 += rec;
	cout << b1;
	RecipesBook b2 = b1.newBook(rec);
	cout << b2;
	// testing copy constructor
	cout << "b2 copy" << endl;
	RecipesBook rb = b2;
	last.set_name("changed-name");
	rb += last;
	cout << rb;
	cout << "original" << endl;
	cout << b2;
	return 0;
}