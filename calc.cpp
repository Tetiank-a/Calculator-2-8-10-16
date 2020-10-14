#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

// class for devided string (integer and fractional part)

class DoubleString {
public:
	string integer = "";
	string fractional = "";
	DoubleString(string Number) {
		this->Create(Number);
	}
	void Create(string Number) {    // deviding string on 2 parts
		this->integer = "";
		this->fractional = "";
		int i, j;
		for (i = 0; i < Number.length(); ++i) {
			if (Number[i] == '.') break;
			this->integer += Number[i];
		}
		for (j = i + 1; j < Number.length(); ++j)
			this->fractional += Number[j];
		if (this->fractional == "") this->fractional = "0";
	}
};

// main class for count systems

class SystemX {
private:
	string number = "";
	int digit = 1;
	int systemX = 10;
	double decimal = 0.0;
	string values = "0123456789ABCDEF";
public:
	int Accuracy = 4;
	SystemX(string delta_number, int delta_digit, int delta_systemX);
	SystemX(double delta_decimal, int delta_digit, int delta_systemX);
	void setNumber(string value);
	void setDigit(int value);
	void setSystemX(int value);
	string getNumber();
	int getDigit();
	int getSystemX();
	double getDecimal();
	void ToDecimal();
	double IntToDecimal(string Number, string Check);
	void ToSystemX();
	string ToX(string Number, string Check);
};

// constructor for SystemX class

SystemX::SystemX(string delta_number, int delta_digit, int delta_systemX) {
	this->number = delta_number;
	this->digit = delta_digit;
	this->systemX = delta_systemX;
	this->ToDecimal();    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

SystemX::SystemX(double delta_decimal, int delta_digit, int delta_systemX) {
	this->decimal = delta_decimal;
	this->digit = delta_digit;
	this->systemX = delta_systemX;
	this->ToSystemX();  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

// set and get for digit, systemX, number

void SystemX::setNumber(string value) {
	this->number = value;
}

void SystemX::setDigit(int value) {
	this->digit = value;
}

void SystemX::setSystemX(int value) {
	this->systemX = value;
}

string SystemX::getNumber() {
	return this->number;
}

int SystemX::getDigit() {
	return this->digit;
}

int SystemX::getSystemX() {
	return this->systemX;
}

double SystemX::getDecimal() {
	return this->decimal;
}

// end of set and get

void SystemX::ToDecimal() {
	DoubleString s(this->number);
	decimal = IntToDecimal(s.integer, "Integer") + IntToDecimal(s.fractional, "Fractional");
	decimal *= digit;
}

double SystemX::IntToDecimal(string Number, string Check) {
	double result = 1.0, sum = 0.0;
	if (Check == "Fractional")
		result /= (systemX * 1.0);
	else reverse(Number.begin(), Number.end());
	int x;
	for (int i = 0; i < Number.length(); ++i) {
		if (Number[i] >= '0' && Number[i] <='9')
			x = (Number[i] - '0');
		else
			x = (Number[i] - 'A') + 10;
		sum += x * result;
		if (Check == "Integer")
			result *= (systemX * 1.0);
		else 
			result /= (systemX * 1.0);
	}
	return sum;
}

void SystemX::ToSystemX() {
	this->number = to_string(this->decimal);
	DoubleString s(this->number);
	this->number = ToX(s.integer, "Integer") + '.' + ToX(s.fractional, "Fractional");
}

string SystemX::ToX(string Number, string Check) {
	string ans = "";
	if (Check == "Integer") {
		int n = stoi(Number), x;
		while (n != 0) {
			x = n % systemX;
			ans = values[x] + ans;
			n /= systemX;
		}
		return ans;
	}
	else {
		Number = "0." + Number;
		double n = stod(Number), k;
		int x;
		for (int i = 0; i < Accuracy; i++) {
			k = n * (this->systemX * 1.0);
			x = trunc(k);
			ans += values[x];
			n = k - x * 1.0;
		}
		return ans;
	}
}

double Operation(SystemX a, SystemX b, string operation) {
	if (operation == "+") return (a.getDecimal() + b.getDecimal());
	if (operation == "-") return (a.getDecimal() - b.getDecimal());
	if (operation == "*") return (a.getDecimal() * b.getDecimal());
	if (operation == "/") return (a.getDecimal() / b.getDecimal());
}

int Digit(double n) {
	if (n < 0) return -1;
	return 1;
}

void Programm() {
	string operation, a, b, c;
	int s1, s2, s3;
	double x;
	while (true) {
		cout << "Enter system of A:    ";
		cin >> s1;
		cout << "Enter A:    ";
		cin >> a;

		cout << "Enter system of B:    ";
		cin >> s2;
		cout << "Enter B:    ";
		cin >> b;

		cout << "Enter operation:    ";
		cin >> operation;

		cout << "Enter result system:    ";
		cin >> s3;

		int dig = 1;
		if (a[0] == '-') {
			dig = -1;
			string S = "";
			for (int i = 1; i < a.length(); ++i)
				S += a[i];
			a = S;
		}
		SystemX A(a, dig, s1);
		dig = 1;
		if (b[0] == '-') {
			dig = -1;
			string S = "";
			for (int i = 1; i < b.length(); ++i)
				S += b[i];
			b = S;
		}
		SystemX B(b, dig, s2);
		double x = Operation(A, B, operation);
		SystemX C(abs(x), Digit(x), s3);
		cout << C.getNumber() << '\n';
	}
}

int main() {
	Programm();
}
