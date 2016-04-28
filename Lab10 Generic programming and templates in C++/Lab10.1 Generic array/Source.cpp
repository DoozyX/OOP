#include <iostream>
#include <cmath>
#include <cstdlib>
#include <exception>

using namespace std;

class wrongRequest : public exception {
public:
	const char* what() const throw () {
		return "Wrong request!";
	}
};


template <typename T>
class Array {
private:
	T *elements;
	int nElements;
	void init(const Array<T> &ar) {
		nElements = ar.nElements;
		elements = new T[ar.nElements];
		for (int i = 0; i < nElements; ++i) {
			elements[i] = ar.elements[i];
		}
	}
public:
	Array<T>(int _nElements = 1) {
		nElements = _nElements;
		elements = new T[_nElements];
	}
	Array<T>(const Array<T> &ar) {
		init(ar);
	}
	void operator=(const Array<T> &ar) {
		delete[] elements;
		init(ar);

	}
	void Erase() {
		delete[] elements;
		elements = new T[nElements];
	}
	T &operator[](int i) {
		if (i >= 0 && i < nElements) {
			return elements[i];
		} else {
			throw wrongRequest();
		}
	}
	int getLength() {
		return nElements;
	}
	friend ostream& operator<<(ostream &output, const Array<T> &ar) {
		for (int i = 0; i < ar.nElements - 1; ++i) {
			output << "Array[" << i << "] = " << ar.elements[i] << ", ";
		}
		output << "Array[" << ar.nElements - 1 << "] = " << ar.elements[ar.nElements - 1];
		return output;
	}
	template <typename A, typename M> friend bool Equal(Array<A> &, Array<M> &);
	template <typename A> friend bool Equal(Array <A> &, Array<double> &);
	~Array() {
		delete[] elements;
	}
};

template <typename T>
void BubbleSort(Array<T> &ar) {
	bool flag = true;
	T temp;
	int numLength = ar.getLength();
	for (int i = 1; (i <= numLength) && flag; ++i) {
		flag = false;
		for (int j = 0; j < (numLength - 1); ++j) {
			if (ar[j + 1] < ar[j]) {
				temp = ar[j];
				ar[j] = ar[j + 1];
				ar[j + 1] = temp;
				flag = true;
			}
		}
	}
}

template <typename T>
T Sum(Array<T> &ar) {
	T sum = 0;
	int len = ar.getLength();
	for (int i = 0; i < len; ++i) {
		sum += ar[i];
	}
	return sum;
}

template <typename T>
T Average(Array<T> &ar) {
	return Sum(ar) / ar.getLength();
}

template <typename T, typename M>
bool Equal(Array<T> &ar1, Array<M> &ar2) {
	int len1 = ar1.getLength(), len2 = ar2.getLength();
	if (len1 == len2) {
		for (int i = 0; i < len1; ++i) {
			if (ar1.elements[i] != ar2.elements[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}

template <typename T>
bool Equal(Array <T> &ar1, Array<double> &ar2) {
	int len1 = ar1.getLength(), len2 = ar2.getLength();
	if (len1 == len2) {
		for (int i = 0; i < len1; ++i) {
			double diff = ar1.elements[i] - ar2.elements[i];
			if (diff < -0.1 || diff > 0.1) {
				return false;
			}
		}
		if (Average(ar1) - Average(ar2) > 0.5 || Average(ar1) - Average(ar2) < -0.5) {
			return false;
		}
		return true;
	}
	return false;
}


int main() {
	int n;
	double r;

	cin >> r;
	cin >> n;

	Array<int> anArray(n);
	Array<double> adArray(n);
	Array<int> intArray2(n);

	for (int nCount = 0; nCount < n; nCount++) {
		cin >> anArray[nCount];
		adArray[nCount] = anArray[nCount] + r;
	}

	BubbleSort(anArray);

	intArray2 = anArray;

	cout << "The arrays: " << endl;
	cout << anArray;
	cout << endl << "and " << endl;
	cout << intArray2 << endl;
	cout << ((Equal(anArray, intArray2)) ? " ARE" : " ARE NOT") << " same!" << endl;
	cout << "The Average of the array adArray is: " << Average(adArray) << endl;

	cout << "The arrays: " << endl;
	cout << anArray;
	cout << endl << "and " << endl;
	cout << adArray << endl;
	cout << ((Equal(anArray, adArray)) ? " ARE" : " ARE NOT") << " same!";


	return 0;
}
