#include <iostream>
using namespace std;

void slowprint(int num)
{
	for (int j = 0; j < 100; j++)
	{
		if (j < num)
			cout << "*";
		else
			cout << ".";
	}
}

void main()
{
	const int count = 5;
	float percent[count];

	for (int i = 0; i < count; ++i)
	{
		float speed;
		cin >> speed;

		float duration;
		cin >> duration;

		float length;
		cin >> length;

		cout << speed << " " << duration << " " << length << endl;

		float pathTODO = length - duration * speed;
		cout << pathTODO << endl;

		if (pathTODO < 0)
		{
			cout << "Kolesar je mimo cilja." << endl;
		}

		percent[i] = (duration * speed) / length;
	}


	cout << "Vnesi stevilo vrstic: ";
	int lines;
	cin >> lines;

	for (int i = 0; i < count; i++)
	{
		cout << "Tekmovalec " << (i + 1) << " (" << percent[i] << "%)" << endl;
		int p = (int)(percent[i]);
		for (int j = 0; j < lines; j++)
		{
			slowprint(p);
			cout << endl;
		}
	}
}