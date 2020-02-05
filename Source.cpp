#define MAXIMUM 500
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>  
#include <iostream>
#include <locale.h>
#include <windows.h>
#include <string>
#include <math.h>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
double delt;
double raz;
map <char, int> ab;
void Sort(int* arr, int size)
{
	int tmp, i, j;
	for (i = 0; i < size - 1; ++i)
	{
		for (j = 0; j < size - 1; ++j)
		{
			if (arr[j + 1] < arr[j])
			{
				tmp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}
double delta(map <char, int> alf, int strl)
{
	double pi = 0;
	std::map<char, int>::iterator it;
	double sum = 0;
	double i = 1;
	raz = 1;
	for (it = alf.begin(); it != alf.end(); it++)
	{
		pi = it->second / (double)strl;
		sum += pi * pi;
	}
	while (1)
	{

		if (sum * i < 1)
			i *= 10;
		else break;
	}
	raz /= i;
	return sum;
}
void hash1(char* data, map <char, int> alf, int a, int b, int m)
{
	int j = 0;
	int q = 0;
	int k = strlen(data);
	int r = 0;
	std::map<char, int>::iterator it;
	for (int i = 0; i < k; i++)
	{
		q = distance(alf.begin(), alf.find(data[i]));
		j = fmod(a * q + b, m);
		it = alf.begin();
		while (r < j)
		{
			it++;
			r++;
		}
		r = 0;
		data[i] = it->first;
	}

}
void hash2(char* data, map <char, int> alf, int* key, int m, int keylen)
{
	int i = 0;
	int k = strlen(data);
	int modul = fmod(k, keylen);
	std::map<char, int>::iterator it;
	int q = 0;
	int o = 0;
	int md;
	int r = 0;
	int mas[20]; memset(mas, 0, 20);
	while (i < k)
	{
		if (i + modul == k && modul != 0)
		{
			for (int j = 0; j < modul; j++)
			{
				q = distance(alf.begin(), alf.find(data[i + j]));
				o = fmod(q + key[j], m);
				it = alf.begin();
				r = 0;
				while (r < o)
				{
					it++;
					r++;
				}
				r = 0;
				data[i + j] = it->first;
			}
			break;
		}
		for (int j = i; j < i + keylen; j++)
		{
			q = distance(alf.begin(), alf.find(data[j]));
			md = fmod(j, keylen);
			mas[md] = q;

		}
		for (int j = i; j < i + keylen; j++)
		{
			md = fmod(j, keylen);
			o = fmod(mas[md] + key[md], m);
			it = alf.begin();

			while (r < o)
			{
				it++;
				r++;
			}
			r = 0;
			data[j] = it->first;

		}
		i += keylen;
	}
}
int evkl(int a, int b)
{
	int p = 1, q = 0, r = 0, s = 1, x, y;
	while (a && b) {
		if (a >= b) {
			a = a - b;
			p = p - r;
			q = q - s;
		}
		else
		{
			b = b - a;
			r = r - p;
			s = s - q;
		}
	}
	if (a) {
		x = p;
		y = q;
	}
	else
	{
		x = r;
		y = s;
	}
	return x;
}
char* decrypt1(char* data, char* decrypt, map <char, int> alf, int a, int b, int m)
{
	int a1;
	if (a < 0)
		a1 = evkl(m + a, m);
	else a1 = evkl(a, m);
	int j = 0;
	int q = 0;
	int k = strlen(data);
	int r = 0;
	std::map<char, int>::iterator it;
	for (int i = 0; i < k; i++)
	{
		q = distance(alf.begin(), alf.find(data[i]));
		j = fmod((q - b) * a1, m);
		if (j < 0)
		{
			j = j + m;
		}
		it = alf.begin();
		while (r < j)
		{
			it++;
			r++;
		}
		r = 0;
		//	data[i] = ch[j][0];
		decrypt[i] = it->first;
	}
	return decrypt;
}
char* decrypt2(char* data, map <char, int> alf, int* key, int m, int keylen)
{
	int i = 0;
	int k = strlen(data);
	int modul = fmod(k, keylen);
	std::map<char, int>::iterator it;
	int q = 0;
	int o = 0;
	int md;
	int r = 0;
	int mas[20]; memset(mas, 0, 20);
	while (i < k)
	{
		if (i + modul == k && modul != 0)
		{
			for (int j = 0; j < modul; j++)
			{
				q = distance(alf.begin(), alf.find(data[i + j]));
				o = fmod(q - key[j], m);
				it = alf.begin();

				while (r < o)
				{
					it++;
					r++;
				}
				r = 0;
				data[i + j] = it->first;
			}
			break;
		}
		for (int j = i; j < i + keylen; j++)
		{
			q = distance(alf.begin(), alf.find(data[j]));
			md = fmod(j, keylen);
			mas[md] = q;

		}
		for (int j = i; j < i + keylen; j++)
		{
			md = fmod(j, keylen);
			o = fmod(mas[md] - key[md], m);
			if (o < 0)
				o = m + o;
			it = alf.begin();

			while (r < o)
			{
				it++;
				r++;
			}
			r = 0;
			data[j] = it->first;

		}
		i += keylen;
	}
	return data;
}
int NOD(int a, int b)
{
	while (a > 0 && b > 0)
		if (a > b)
			a %= b;

		else
			b %= a;

	return a + b;
}
int countRep(std::string text, std::string sub) {
	int count = 0;
	int pos = 0;
	while (true) {
		pos = text.find(sub, pos);
		if (pos != -1) {
			count++;
			pos++;
		}
		else {
			break;
		}
	}
	return count;
}
int resh(int x1, int y1, int x2, int y2, int* a, int* b, int m)
{
	for (int i = 2; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (((m + fmod(x1 * i + j, m) == y1) || (fmod(x1 * i + j, m) == y1)) && ((m + fmod(x2 * i + j, m) == y2) || (fmod(x2 * i + j, m) == y2)))
			{
				if (ab[i] != j&& NOD(i,m)==1)
				{
					ab[i] = j;
					*a = i;
					*b = j;
					return 0;
				}
			}
		}
	}
	return -1;

}
char* freq(char* data, map <char, int> fr, int m)
{
	std::map<char, int>::iterator itt;
	std::map<char, int>::iterator it;
	std::map<char, int>::iterator i1;
	std::map<char, int>::iterator i2;

	std::map<char, int>::iterator it1;
	std::map<char, int>::iterator it2;
	std::map<int, int>::iterator ite;
	int fl1 = 0;
	int fl3 = 0;
	int a = 0, b = 0;
	int x, y;
	int str = -1;
	char err[] = { "max <2" };
	int maxFr1 = 0;
	int u = 0;
	
	char* decryptdata = new char[strlen(data)];
	map <int, int> fre;
	map <int, int> fre1;
	map <char, int> fr1;
	int q1 = -1, q2 = -1, q3 = -1, q4 = -1;
	int max = 0;
	int j = 1;
	int col = 0;
	for (itt = fr.begin(); itt != fr.end(); itt++)
	{
		fr1[itt->first] = 0;
	}
	for (int i = 0; i < strlen(data); i++)
	{
		fr1[data[i]]++;
	}
	for (it = fr.begin(); it != fr.end(); it++)
		fre[it->second]++;
	for (it = fr1.begin(); it != fr1.end(); it++)
		fre1[it->second]++;
	while (col < 10)
	{
		for (ite = fre.begin(); ite != fre.end(); ite++)
		{
			if (ite->second == j && fre1.find(ite->first) != fre1.end())
			{
				if (fre1[ite->first] == j)
				{
					for (it = fr.begin(); it != fr.end(); it++)
					{
						if (it->second == ite->first)
						{
							if (q1 == -1)
							{
								q1 = distance(fr.begin(), fr.find(it->first));
								i1 = it;
							}
							else if (q3 == -1)
							{
								q3 = distance(fr.begin(), fr.find(it->first));
								i2 = it;
							}
							if(q1!=-1 && q3!=-1)
							{ 
								for (it1 = fr1.begin(); it1 != fr1.end(); it1++)
								{
									if (it1->second == i1->second )
									{
										fl1 = 1;
										q2 = distance(fr1.begin(), fr1.find(it1->first));

										for (it2 = fr1.begin(); it2 != fr1.end(); it2++)
										{
											if (it2->second == i2->second )
											{
												fl3 = 1;
												q4 = distance(fr1.begin(), fr1.find(it2->first));
												if (q1 == 0)
													q1 += m;
												if (q2 == 0)
													q2 += m;
												if (q3 == 0)
													q3 += m;
												if (q4 == 0)
													q4 += m;
												if (!resh(q1, q2, q3, q4, &a, &b, fr.size()))
												{
													cout << "a=" << fmod(a, m) << "b=" << fmod(b, m) << '\n' << endl;
													decrypt1(data, decryptdata, fr1, fmod(a, m), fmod(b, m), m);
													decryptdata[strlen(data)] = '\0';
													std::ofstream decr1("freqdecryp.bin", std::ofstream::binary);
													std::string affin;
													affin.assign(decryptdata, strlen(decryptdata));
													decr1 << affin;
													decr1.close();
													cout << "Please, write 0 or 1" << endl;
													cin >> str;
													if (str == 1)
														return decryptdata;
													col++;
													if (col > 9)
														return decryptdata;
												}
											}
										}
									}
								}
								
								if (!fl1)
									q1 = -1;
								else if (!fl3)
									q3 = -1;
								fl1 = 0;
								fl3 = 0;

							}
						}
					}
				}
			}
		}
		j++;
	}
	return decryptdata;
}
std::map<char, double>::iterator iter(std::map<char, double>::iterator it, int o)
{
	int r = 0;
	while (r < o)
	{
		it++;
		r++;
	}
	return it;
}
char* sdvig(char* data, int key, map<char, int> A)
{
	char* cryptdata = new char[strlen(data) + 1];
	int m = A.size();
	int q = 0;

	std::map<char, int>::iterator it;
	int r = 0;
	int j = 0;
	for (int i = 0; i < strlen(data); i++)
	{
		q = distance(A.begin(), A.find(data[i]));
		j = fmod(q + key, m);
		it = A.begin();
		while (r < j)
		{
			it++;
			r++;
		}
		r = 0;
		cryptdata[i] = it->first;
	}
	return cryptdata;
}
double MIc(map <char, int> Fi, map <char, int> Fi1, int n, int n1)
{
	int sum = 0;
	std::map<char, int>::iterator it;
	std::map<char, int>::iterator it1;
	for (it = Fi.begin(); it != Fi.end(); it++)
		sum += it->second * (Fi1[it->first]);
	double MI = sum / (double)(n * n1);
	return MI;
}

int freqForfridman(map <char, int> fr, char* data)
{
	map <char, int> fr1;
	int col = 0;
	int j = 1;
	int q, q1,k1;
	int flag;
	std::map<char, int>::iterator it;
	std::map<char, int>::iterator it1;
	std::map<int, int>::iterator ite;
	std::map<int, int>::iterator i1;
	std::map<int, int>::iterator i2;
	int nokey = -1;
	map <int, int> fre;
	map <int, int> fre1;
	for (int i = 0; i < strlen(data); i++)
		fr1[data[i]] = 0;
	for (int i = 0; i < strlen(data); i++)
		fr1[data[i]]++;
	for (it = fr.begin(); it != fr.end(); it++)
		fre[it->second]++;
	for (it = fr1.begin(); it != fr1.end(); it++)
		fre1[it->second]++;
	while (col < 10&&j<fr.size())
	{
		for (ite = fre.begin(); ite != fre.end(); ite++)
		{
			if (ite->second == j && fre1.find(ite->first) != fre1.end())
			{
				if (fre1[ite->first] == j)
				{
					for (it = fr.begin(); it != fr.end(); it++)
					{
						if (it->second == ite->first)
						{
							q = distance(fr.begin(), fr.find(it->first));
							for (it1 = fr1.begin(); it1 != fr1.end(); it1++)
							{
								if (it1->second == ite->first)
								{
									q1 = distance(fr1.begin(), fr1.find(it1->first));
									if (q1 < q)
										k1 = fr.size() + q1 - q;
									else k1 = q1 - q;
									printf("\nk1 == %d?", k1);
									cin >> flag;
									if (flag)
										return k1;
								}
							}
						}
					}
					
					
					
				}
			}
		}
		j++;
	}

	return nokey;

}
int fridmanKey(char* data, char*text, int keylen, map <char, int> fr, int* key)
{
	//int* key= new int[keylen];
	map <char, int> frequ;
	int h = 0;
	int e = 0;
	while (h+ e < strlen(text))
	{
		frequ[text[h+e]]++;
		e += keylen;
	}
	int d = keylen;
	int j = 0;
	map <char, int> Fi;
	map <char, int> Fi1;
	int flag = 0;
	int strlen1 = 0;
	double MI = 0;
	double maxMI = 0;
	int strlen2 = 0;
	int err = 0;
	int* sdx = new int[keylen];
	std::map<char, int>::iterator it;
	char* Yi = new char[strlen(data)];
	char* Yj = new char[strlen(data)];
	char* Yjj = new char[strlen(data)];
	double min = 0;
	for (int i = 0; i < strlen(data); i++)
	{
		Fi[data[i]] = 0;
		Fi1[data[i]] = 0;
	}
	int k = 0;


	while (k + j < strlen(data))
	{
		Yi[strlen1] = data[k + j];
		Fi[data[k + j]]++;
		j += keylen;
		strlen1++;

	}
	Yi[strlen1] = '\0';
	j = 0;
	for (int i = 1; i < d; i++)
	{

		strlen2 = 0;
		while (i + j < strlen(data))
		{
			Yj[strlen2] = data[i + j];
			j += keylen;
			strlen2++;
		}
		Yj[strlen2] = '\0';
		for (int y = 0; y < fr.size(); y++)
		{
			Yjj = sdvig(Yj, y, fr);
			Yjj[strlen2] = '\0';
			for (int o = 0; o < strlen(Yjj); o++)
				Fi1[Yjj[o]]++;
			MI = MIc(Fi, Fi1, strlen1, strlen2);
			
			if (pow(MI - delt, 2) >
				pow(raz, 2))
			{
				if (MI > delt)
				{
					err = 1;
					sdx[i] = y;
				}
			}
			else
			{
				err = 1;
				sdx[i] = y;
			}

			for (it = Fi1.begin(); it != Fi1.end(); it++)
				it->second = 0;
		}
		if (err == 0)
			return 0;
		else err = 0;
		j = 0;




	}
	int ke = freqForfridman(frequ, Yi);
	if (ke != -1)
	{
		key[0] = ke;
		for (int p = 1; p < keylen; p++)
		{
			printf("%d", sdx[p]);
			key[p] = fr.size() - sdx[p] + key[0];
		}
	}
	else
	{
		int z = 1;
		for (int p = 1; p < fr.size(); p++)
		{
			printf("\n%d. {%d,", p, p);
			while (z < keylen - 1)
			{
				printf("%d,", fr.size() - sdx[z] + p); 
				z++;
			}
			printf("%d}\n", fr.size() - sdx[z] + p);
			z = 1;
		}
		printf("k1 == ?\n");
		cin >> key[0];
		for (int p = 1; p < keylen; p++)
		{
			printf("%d", sdx[p]);
			key[p] = fr.size() - sdx[p] + key[0];
		}

	}


	return 1;
}
double Ic(map<char, int> Fi, int k)
{
	double I;
	int sum = 0;
	std::map<char, int>::iterator it;
	for (it = Fi.begin(); it != Fi.end(); it++)
		sum += it->second * (it->second - 1);
	I = sum / (double)(k * (k - 1));
	return I;
}
int fridmanLen(char* data)
{
	int d = 2;
	int nd = 0;
	map <char, int> Fi;
	double I[MAXIMUM];
	int modul = 0;
	int k = strlen(data);
	int mod = 0;
	int j = 0;
	int l = 0;
	int cout = 0;
	int flag = 0;
	double min = 0;
	for (int i = 0; i < k; i++)
	{
		Fi[data[i]] = 0;
	}
	while (d < 20)
	{
		for (int i = 0; i < d; i++)
		{
			while (i + j < strlen(data))
			{
				Fi[data[i + j]]++;
				j += d;
				l++;
			}
			I[cout] = Ic(Fi, l);

			l = 0;
			j = 0;
			for (int i = 0; i < strlen(data); i++)
			{
				Fi[data[i]] = 0;
			}
			cout++;

		}
		for (int y = 0; y < cout; y++)
		{
			if (pow(I[y] - delt, 2) >
				pow(raz, 2))
			{
				if (I[y] < delt)
					flag = 1;
			}
		}
		memset(I, 0, MAXIMUM);
		cout = 0;
		j = 0;
		if (flag)
		{
			d++;
			flag = 0;
			min = 0;
		}
		else return d;
	}
	return -1;
}
int kazistki(char* data)
{

	map <char, double>alf;
	int k = strlen(data);
	for (int i = 0; i < strlen(data); i++)
	{
		alf[data[i]] = 0;
	}
	for (int i = 0; i < strlen(data); i++)
	{
		alf[data[i]]++;
	}
	std::map<char, double>::iterator it;
	std::map<char, double>::iterator it1;

	int max = 0;
	char str[100] = { 0 };
	char maxStr[100] = { 0 };
std:string nGr, strin;
	int cout;
	int* rasst = new int[strlen(data) / 2];
	strin.assign(data, strlen(data));
	int colofrast = 0;
	int prev = 0;
	int next = 0;
	int maxNod = 0;
	int nod = 0;
	for (it = alf.begin(); it != alf.end(); it++)
	{
		for (it1 = alf.begin(); it1 != alf.end(); it1++)
		{
			if (((it1->second > 2) && (it->first == it1->first)) || ((it1->second > 1) && (it->first != it1->first)))
			{
				str[0] = it->first;
				str[1] = it1->first;

				nGr.assign(str, 2);
				cout = countRep(strin, nGr);
				if (cout > 1 && cout > max)
				{
					for (int i = 0; i < strlen(data); i++)
					{
						if (data[i] == str[0])
							if (data[i + 1] == str[1] && (i + 1) < strlen(data))
								if (colofrast > 0)
								{
									next = i;
									rasst[colofrast - 1] = next - prev;
									prev = next;
									colofrast++;
								}
								else
								{
									prev = i;
									colofrast++;
								}

					}
					if (colofrast - 1 > 1)
					{
						nod = NOD(rasst[0], rasst[1]);
						for (int i = 2; i < colofrast - 1; i++)
						{
							nod = NOD(rasst[i], nod);
						}
						if (nod > 1 && nod > maxNod)
							maxNod = nod;
					}

					colofrast = 0;
					strcpy(maxStr, str);
					max = cout;

				}
			}
		}
	}
	return maxNod;
	system("pause");

}
float ato(char* str)
{
	float a = 0;
	float q = 0;
	int f = 10;
	int i = 0;
	for (int k = 2; k < strlen(str); k++)
	{
		i = str[k] - '0';
		q = i / (float)f;
		a += q;
		f *= 10;
	}
	return a;
}
int main(void)
{
	setlocale(LC_ALL, "Russian");

	FILE* stream;
	char list[1];
	int mode = 0;
	int flag = 0;
	int cout = 0;
	char* mas = new char[2];
	char* mas1 = new char[2];
	int i = 0;
	char filename[100];	memset(filename, 0, 100);
	char outfile[100]; memset(outfile, 0, 100);
	printf("Please write the mode 1 or 2\n");
	cin >> mode;
	if (mode == 1)
	{
		//1 part
		map <char, int> frequency;
		printf("Please write filename\n");
		cin >> filename;
		std::ifstream file;
		file.open(filename, std::ios::binary);
		std::string rawText = std::string((std::istreambuf_iterator<char>(file)),
			(std::istreambuf_iterator<char>()));
		int size = rawText.length();
		char* data = new char[rawText.length() + 1];
		char* data1 = new char[rawText.length() + 1];

		strcpy(data, rawText.c_str());
		strcpy(data1, rawText.c_str());
		for (int i = 0; i < strlen(data); i++)
		{
				frequency[data[i]] = 0;
		}
		for (int i = 0; i < strlen(data); i++)
		{
				frequency[data[i]]++;

		}
		std::map<char, int>::iterator it;

		file.close();


		//write in out.txt
		std::ofstream ofs("output.txt", std::ofstream::out);
		std::string str;
		char output[2] = { 0 };
		output[1] = '-';

		for (it = frequency.begin(); it != frequency.end(); it++)
		{
			output[0] = it->first;
			str.assign(output, 2);
			ofs << str;
			ofs << it->second;
			ofs << "\n";
			cout++;
		}
		ofs.close();
		char* vizener = data;



		//affin
		int a=0;
		int flm1 = 0;
		//key
		if (cout <= 2)
		{
			printf("Key may be only 1\n");
			printf("Key 1 (write 1 or 0)\n");
			cin >> flm1;
			if (flm1 == 0)
				return 0;
			else
				a = 1;

		}
		int b = rand() % cout;
		srand(time(NULL));
		while (!flm1)
		{

			a = rand() % cout;
			if (a < 2)
				continue;
			else 
			{
				if (NOD(a, cout) == 1)
					break;
			}
		}
		printf("a=%d   b=%d\n", a, b);
		hash1(data, frequency, a, b, cout);
		std::ofstream hash1("affin.bin", std::ofstream::binary);
		std::string affin;
		affin.assign(data, strlen(data));
		hash1 << affin;
		//hash1 << affin;
		hash1.close();

		//vizener
		int key[4] = { 2,10,7,13 };
		hash2(data1, frequency, key, cout, 4);
		std::ofstream hash2("vizener.bin", std::ofstream::binary);
		std::string vizene;
		vizene.assign(data1, strlen(data1));
		hash2 << vizene;
		hash2.close();
	}
	else if (mode == 2)
	{
		//2 part
		char input[100]; memset(input, 0, 100);
		char inputSh1[100]; memset(inputSh1, 0, 100);
		char inputSh2[100]; memset(inputSh2, 0, 100);
		char text[100]; memset(text, 0, 100);


		std::ifstream file;
		printf("Please write filename (frequency)\n");
		cin >> input;
		printf("Please write filename (Affin)\n");
		cin >> inputSh1;
		printf("Please write filename (Vizener)\n");
		cin >> inputSh2;
		printf("Please write filename (text)\n");
		cin >> text;



		//2.1
		file.open(input, std::ios::binary);
		std::string rawText = std::string((std::istreambuf_iterator<char>(file)),
			(std::istreambuf_iterator<char>()));
		int size = rawText.length();
		char* data = new char[rawText.length() + 1];
		strcpy(data, rawText.c_str());
		file.close();
		map <char, int>frequency;
		char st[10] = { 0 };
		int p = 0;
		int m = 0;
		int e = 0;
		int t = 0;
		double ft = 0;

		std::map<char, int>::iterator it;
		float c;
		int b;
		char cc = '\0';

		int h = 0;
		int md = 1;
		while (data[p] != '\0')
		{

			while (data[p] != '-'&& data[p]!='\0')
				p++;
			if (data[p + 1] == '-')
				p++;
			if (data[p] == '\0')
				break;
			frequency[data[p-1]] = 0;
			h = p + 1;
			while (data[h] >= '0' && data[h] <= '9')
			{
				frequency[data[p-1]] *= 10;
				frequency[data[p-1]] += (data[h] - '0');
				h++;
			}
			p++;
		
		}

		file.open(inputSh1, std::ios::binary);
		rawText = std::string((std::istreambuf_iterator<char>(file)),
			(std::istreambuf_iterator<char>()));
		int sizeAff = rawText.length();
		char* sh1 = new char[rawText.length() + 1];
		strcpy(sh1, rawText.c_str());
		file.close();

		freq(sh1, frequency, frequency.size());


		//2.2
		file.open(inputSh2, std::ios::binary);
		rawText = std::string((std::istreambuf_iterator<char>(file)),
			(std::istreambuf_iterator<char>()));
		int sizeViz = rawText.length();
		char* sh2 = new char[rawText.length() + 1];
		char* decryptdata = new char[rawText.length() + 1];
		strcpy(sh2, rawText.c_str());
		file.close();

		
		int fl = 0;
		int keyl = 0;
		
		delt = delta(frequency, strlen(sh2));
		printf("\ndelta == %f\n", delt);
		int lenKaz = kazistki(sh2);
		printf("\nlen kazistki == %d\n", lenKaz);
		int lenFrid = fridmanLen(sh2);
		printf("\nlen fridman == %d\n", lenFrid);
		printf("Please write number of key 1 or 2\n");
		cin >> fl;
		if (fl == 1)
			keyl = lenKaz;
		else if (fl == 2) keyl = lenFrid;
		else {
			printf("Sorry, keylen is not found(((");
			return 0;
		}
		int* key = new int[keyl];
		file.open(text, std::ios::binary);
		rawText = std::string((std::istreambuf_iterator<char>(file)),
			(std::istreambuf_iterator<char>()));
		char* txt = new char[rawText.length() + 1];
		strcpy(txt, rawText.c_str());
		file.close();
		if (!fridmanKey(sh2,txt, keyl, frequency, key))
		{
			printf("Sorry, key is not found(((");
			return 0;
		}
		printf("\n KEY\n");
		printf("\n{");
		for (int u = 0; u < keyl; u++)
			printf("%d ", key[u]);
		printf("}");
		decryptdata = decrypt2(sh2, frequency, key, frequency.size(), keyl);
		std::ofstream decr2("friddecryp.bin", std::ofstream::binary);
		std::string frid;
		frid.assign(decryptdata, strlen(decryptdata));
		decr2 << frid;
		decr2.close();
	}
	return 0;
}