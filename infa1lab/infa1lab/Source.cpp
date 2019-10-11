#include <stdio.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const char k_base_symbols[] = "0123456789ABCDEFGHIJKLMNOPQRASUVWXYZ";

char inttochar(int a) {
	return k_base_symbols[a];
}

int chartoint(char a) {
	int i = 0;
	while (k_base_symbols[i] != a)
		i++;
	return i;
}

double fromRto10(string num, int r) {
	double ans = 0;
	int c = 0;
	int end = 0;
	while (num[c] != '\0' && num[c] != '.')
		c++;

	end = c;
	while (num[end] != '\0')
		end++;

	for (int i = 0; i < c; i++)
		ans += chartoint(num[c - 1 - i]) * powf(r, i);

	for (int i = -1; i > c - end; i--)
		ans += chartoint(num[c - i]) * powf(r, i);
	return ans;
}

string from10toR(double num, int r) {
	if (num == 0)
		return "0";
	char ans[220];
	int int_num = num;
	double frac_num = num - floor(num);
	int shift = 108;
	int i = shift;
	int j;
	int iterator = 0;

	while (int_num - powf(r, i) < 0)
		i--;

	while (i >= 0)
	{
		j = r - 1;
		while (j >= 0 && int_num - j * powf(r, i) < 0)
			j--;

		int_num -= j * powf(r, i);
		ans[iterator++] = inttochar(j);
		i--;
	}

	if (frac_num == 0) {
		ans[iterator] = '\0';
		return ans;
	}

	if (iterator == 0)
		ans[iterator++] = '0';

	ans[iterator++] = '.';
	i = -1;



	while (i >= -shift)
	{
		j = r - 1;
		while (j >= 0 && frac_num - j * powf(r, i) < 0)
			j--;

		frac_num -= j * powf(r, i);
		ans[iterator++] = inttochar(j);
		i--;
	}

	while (ans[iterator-1] == '0')
		iterator--;

	ans[iterator] = '\0';
	return ans;
}

void f1() {
	ifstream f;
	f.open("input1.txt");
	if ((!f.is_open()) || (f.peek() == EOF)) return;

	string nums;
	double num;
	int r1, r2;
	while (!f.eof())
	{
		f >> nums;
		f >> r1;
		f >> r2;
		num = fromRto10(nums, r1);
		printf_s("num %d\t%s\n", r1, nums.c_str());
		string numR = from10toR(num, r2);
		printf("num %d\t%s\n\n", r2, numR.c_str());
	}

}

void f2() {
	ifstream f;
	f.open("input2.txt");
	if ((!f.is_open()) || (f.peek() == EOF)) return;
	string num1, num2;
	double n1, n2, res;
	string Res;
	int r;
	char symb;
	while (!f.eof())
	{
		res = -1;
		f >> num1;
		f >> symb;
		f >> num2;
		f >> r;
		printf_s("Input = \t%s %c %s\n", num1.c_str(), symb, num2.c_str());
		n1 = fromRto10(num1, r);
		n2 = fromRto10(num2, r);
		switch (symb)
		{
		case '+':
			res = n1 + n2;
			break;
		case '-':
			res = n1 - n2;
			break;
		case '*':
			res = n1 * n2;
			break;
		case '/':
			if (n2 != 0) res = n1 / n2;
			else printf_s("wrong number(possibly zero)");
			break;
		}
		Res = from10toR(res, r);
		printf_s("Result = \t%s\n\n", Res.c_str());
	}
}

void main() {
	f1();
	f2();
	_getch();
}
