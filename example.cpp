#include<iostream>
#include<fstream>

using namespace std;

float ary[100][100]; 
int completed[100], n;
float cost = 0;

void takeInput()
{
	int i, j;

	//std::ifstream file("data.txt");

	cin >> n;

	n += 1;

	float** dots = new float*[n];

	for (i = 0; i < n-1; i++)
	{
		dots[i] = new float[2];
		cin >> dots[i][0] >> dots[i][1];
	}

	for (i = 0; i < n-1; i++)
		for (j = 0; j < n-1; j++)
			ary[i][j] = sqrtf((dots[i][0] - dots[j][0]) * (dots[i][0] - dots[j][0]) + (dots[i][1] - dots[j][1]) * (dots[i][1] - dots[j][1]));
	ary[n][0] = 0;
	ary[0][n] = 0;
	ary[n][1] = 0;
	ary[1][n] = 0;

	for (i = 2; i < n; i++)
	{
		ary[n][i] = 999;
		ary[i][n] = 999;
	}
			
}

int least(int c)
{
	int i, nc = 999;
	float min = 999, kmin;

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

	if (min != 999)
		cost += kmin;

	return nc;
}

void mincost(int city)
{
	int i, ncity;

	completed[city] = 1;

	ncity = least(city);

	if (ncity == 999)
	{
		ncity = 0;
		cost += ary[city][ncity];

		return;
	}

	mincost(ncity);
}

int main()
{
	takeInput();
	mincost(0);

	cout << cost - ary[1][2];

	return 0;
}