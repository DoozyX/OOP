#include <iostream>

using namespace std;

// your code here
class Matrix {
private:
	float mat[10][10];
	int row;
	int column;
public:
	Matrix() {
		row = 10;
		column = 10;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				mat[i][j]=0;
			}
		}
	};
	Matrix(int row, int column) {
		this->row = row;
		this->column = column;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				mat[i][j] = 0;
			}
		}
	};
	Matrix(const Matrix &m) {
		this->row = m.row;
		this->column = m.column;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				this->mat[i][j] = m.mat[i][j];
			}
		}
	};
	friend istream &operator>>(istream  &input, Matrix &m) {
		input >> m.row >> m.column;
		for (int i = 0; i < m.row; i++) {
			for (int j = 0; j < m.column; j++) {
				input >> m.mat[i][j];
			}
		}
		return input;
	}
	friend ostream &operator<<(ostream  &output, const Matrix &m) {
		for (int i = 0; i < m.row; i++) {
			for (int j = 0; j < m.column; j++) {
				output << m.mat[i][j] << " ";
			}
			cout << endl;
		}
		return output;
	}
	Matrix& operator=(const Matrix &m) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				mat[i][j] = m.mat[i][j];
			}
		}
		return *this;
	}
	Matrix operator+(const int num) {
		Matrix m(row,column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				m.mat[i][j] = mat[i][j]+num;
			}
		}
		return m;
	}
	Matrix operator-(const Matrix &m) {
		Matrix t(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				t.mat[i][j] = this->mat[i][j] - m.mat[i][j];
			}
		}
		return t;
	}
	Matrix operator*(const Matrix &m) {
		Matrix t(row, column);
		for (int i = 0; i < this->row; i++) {
			for (int j = 0; j < m.column; j++) {
				for (int k = 0; k < m.row; k++)
				{
					t.mat[i][j] += this->mat[i][k] * m.mat[k][j];
				}
			}
		}
		return t;
	}
};

int main() {
	Matrix A, B, C;
	cin >> A >> B >> C;
	Matrix D = B * C;
	Matrix R = A - D + 2;
	cout << R;
}