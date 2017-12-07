// BIO_lab2_1.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int Score(int* s, string* DNA, int l, int t)
{
	int score = 0;

	for (int i = 0; i < l;i++)
	{
		int A = 0, C = 0, G = 0, T = 0;
		for (int j = 0; j < t; j++)
		{
			if (DNA[j][s[j] + i] == 'A')
				A++;
			if (DNA[j][s[j] + i] == 'C')
				C++;
			if (DNA[j][s[j] + i] == 'G')
				G++;
			if (DNA[j][s[j] + i] == 'T')
				T++;
		}
		score += fmax(fmax(A, C), fmax(G, T));
	}
	return score;
}


string* Motifs(int *bestS, string*DNA, int l, int t)
{
	string* motifs = new string[t];
	for (int i = 0; i < t; i++)
	{
		motifs[i] = new char[l];
	}
	for (int i = 0; i < t; i++)
	{

		motifs[i] = DNA[i].substr(bestS[i], l);

	}
	return motifs;
}

void BruteForceMotifSearch(string* DNA, int t, int n, int l, int i, int* s, int *bestS, int& bestScore)
{

	if (i == 0)
	{
		for (int j = 0; j < n - l + 1; j++)
		{
			s[i] = j;
			if (Score(s, DNA, l, t) > bestScore)
			{
				bestScore = Score(s, DNA, l, t);
				bestS[i] = s[i];
			}
		}
	}
	else
	{
		for (int j = 0; j < n - l + 1; j++)
		{
			s[i] = j;
			int min = bestScore;
			BruteForceMotifSearch(DNA, t, n, l, i - 1, s, bestS, bestScore);
			if (bestScore > min)
			{
				bestS[i] = j;
			}
		}
	}
}


void PrintBestMotifs(string* bestM, int t)
{
	for (int i = 0; i < t; i++)
	{
		cout << bestM[i] << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	else
	{
		string lc;
		string tc;
		getline(fin, lc, ' ');
		getline(fin, tc, '\n');
		int l = atoi(lc.c_str());	// размер шаблона
		int t = atoi(tc.c_str());	// число экземпляров ДНК

		cout << l << endl;
		cout << t << endl;
		string* DNA = new string[t];
		int *s = new int[t];
		for (int i = 0; i < t; i++)
		{
			getline(fin, DNA[i]);
			cout << DNA[i] << endl;
			s[i] = 0;
		}
		int n = strlen(DNA[0].c_str());
		fin.close();
		cout << n << endl;

		string* bestM = new string[t];
		int *bestS = new int[t];
		for (int i = 0; i < t; i++)
		{
			bestS[i] = 0;

		}
		int bestScore = 0;
		for (int i = 0; i < t; i++)
		{
			BruteForceMotifSearch(DNA, t, n, l, i, s, bestS, bestScore);
		}
		bestM = Motifs(bestS, DNA, l, t);
		PrintBestMotifs(bestM, t);
		for (int i = 0; i < t; i++)
		{
			fout << bestM[i] << endl;
		}
		cout << "bestScore = " << bestScore << endl;
		fout.close();
	}
	return 0;
}

