#include <iostream>
using namespace std;

void main()
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
}