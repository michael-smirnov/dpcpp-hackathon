#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

double ary[1000][1000]; 
int completed[1000], n;

void takeInput()
{
	int i, j;

	//std::ifstream file("data.txt");

	cin >> n;

	n += 1;

	double** dots = new double*[n];

	for (i = 0; i < n-1; i++)
	{
		dots[i] = new double[2];
		cin >> dots[i][0] >> dots[i][1];
	}

	for (i = 0; i < n-1; i++)
		for (j = 0; j < n-1; j++)
			ary[i][j] = sqrt((dots[i][0] - dots[j][0]) * (dots[i][0] - dots[j][0]) + (dots[i][1] - dots[j][1]) * (dots[i][1] - dots[j][1]));
	ary[n-1][0] = 1;
	ary[0][n-1] = 1;
	ary[n-1][1] = 1;
	ary[1][n-1] = 1;

	for (i = 2; i <= n; i++)
	{
		ary[n-1][i] = 9999;
		ary[i][n-1] = 9999;
	}
			
}

int least(int c)
{
	int i, nc = 9999;
	double min = 9999, kmin;

	for (i = 0; i < n; i++)
	{
		if ((ary[c][i] != 0) && (completed[i] == 0))
			if (ary[c][i] + ary[i][c] < min)
			{
				min = ary[i][0] + ary[c][i];
				kmin = ary[c][i];
				nc = i;
			}
	}

	return nc;
}

void mincost(int city)
{
	int i, ncity;

	completed[city] = 1;
	if (city != 0 && city !=1)
	{
		cout<<city<<",";
	}

	ncity = least(city);

	if (ncity == 9999)
	{
		ncity = 0;
		cout<<"\r";
		return;
	}

	mincost(ncity);
}

int main()
{
	takeInput();
	mincost(0);

	//cout << cost - ary[1][2];

	return 0;
}