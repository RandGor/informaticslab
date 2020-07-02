#pragma once

#include <stdio.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const char k_base_symbols[] = "0123456789ABCDEFGHIJKLMNOPQRASUVWXYZ";
//Returns char (0..9,A..Z)
char inttochar(int a) {
	return k_base_symbols[a];
}
//Returns char (0..36)
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

	while (ans[iterator - 1] == '0')
		iterator--;

	ans[iterator] = '\0';
	return ans;
}

string bintohex(string bin) {
	string hex;
	float num = fromRto10(bin, 2);
	hex = from10toR(num, 16);
	return hex;
}

string hextobin(string hex) {
	string bin;
	float dec = fromRto10(hex, 16);
	int c = 8;
	while (c != 0)
	{
		bin.append((dec >= c) ? "1" : "0");
		if (dec >= c)
			dec -= c;
		c /= 2;
	}
	return bin;
}

string getbinorder(double num, int bites) {
	int power = 0;
	int i = 0;

	int dota = 0;
	int end = 0;
	string m = from10toR(abs(num), 2);

	while (m[i] != '\0' && m[i] != '.')
		i++;
	dota = i;
	while (m[i] != '\0')
		i++;
	end = i;

	power = dota - 1;
	float order = power + (pow(2, bites - 1) - 1);

	string binorder = from10toR(order, 2);

	return binorder;
}

string getbinmantis(double num, int bites) {
	string m = from10toR(abs(num), 2);

	char s[100];
	int i = 1;
	int iterator = 0;

	for (int j = 0; j < bites; j++)
	{
		s[j] = '0';
	}
	s[bites] = '\0';

	while (m[i] != '\0')
	{
		if (m[i] != '.')
			s[iterator++] = m[i];
		i++;
	}
	return s;
}

string getbinfloat(double num) {
	int powerbites = 8;
	int mantissabites = 23;

	string binfloat;

	bool signb = num < 0;
	string sign = signb ? "1" : "0";
	string binorder = getbinorder(num, powerbites);
	string binmantis = getbinmantis(num, mantissabites);

	binfloat.append(sign);
	binfloat.append(binorder);
	binfloat.append(binmantis);
	return binfloat;
}

string getbindouble(double num) {
	int powerbites = 11;
	int mantissabites = 52;

	string bindouble;

	bool signb = num < 0;
	string sign = signb ? "1" : "0";
	string binorder = getbinorder(num, powerbites);
	string binmantis = getbinmantis(num, mantissabites);

	bindouble.append(sign);
	bindouble.append(binorder);
	bindouble.append(binmantis);
	return bindouble;
}

string gethexfloat(double num) {
	string hexfloat;
	string binfloat = getbinfloat(num);
	for (int i = 0; i < 32; i = i + 4)
	{
		float p1 = fromRto10(binfloat.substr(i, 4), 2);
		string p2 = from10toR(p1, 16);
		hexfloat.append(p2);
	}
	return hexfloat;
}

string gethexdouble(double num) {
	string hexdouble;
	string bindouble = getbindouble(num);
	for (int i = 0; i < 64; i = i + 4)
	{
		hexdouble.append(bintohex(bindouble.substr(i, 4)));
	}
	return hexdouble;
}

string getbinhex(string hex) {
	string bin;
	int i = 0;
	while (hex[i] != '\0')
	{
		bin.append(hextobin(hex.substr(i, 1)));
		i++;
	}
	return bin;
}

float getfloatbin(string bins) {
	int powerbites = 8;
	int mantissabites = 23;

	bool sign;
	string order;
	string mantis = "1.";

	int power;
	float ans = 0;
	sign = bins[0] == '1';
	order = bins.substr(1, powerbites);
	mantis.append(bins.substr(powerbites + 1, mantissabites));

	power = fromRto10(order, 2) - pow(2, powerbites - 1) + 1;

	ans = fromRto10(mantis, 2) * pow(2, power) * (sign == 1 ? -1 : 1);

	return ans;
}

double getdoublebin(string bins) {
	int powerbites = 11;
	int mantissabites = 52;

	bool sign;
	string order;
	string mantis = "1.";

	int power;
	double ans = 0;
	sign = bins[0] == '1';
	order = bins.substr(1, powerbites);
	mantis.append(bins.substr(powerbites + 1, mantissabites));

	power = fromRto10(order, 2) - pow(2, powerbites - 1) + 1;

	ans = fromRto10(mantis, 2) * pow(2, power) * (sign == 1 ? -1 : 1);

	return ans;
}


double getallhex(string hex) {
	string bins = getbinhex(hex);

	double num = 0;
	if (bins.size() == 32)
		num = getfloatbin(bins);
	else if (bins.size() == 64)
		num = getdoublebin(bins);
	return num;
}