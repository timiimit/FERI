#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define ARRAYSIZE(x) sizeof(x) / sizeof(*x)
typedef unsigned int uint;

int main()
{
	srand((uint)time(0));

	const char* adj[] = { "fast", "sharp", "strong", "flashy", "best", "junkie", "chosen", "happy", "sad", "unlucky" };
	const uint adjlen = ARRAYSIZE(adj);

	const char* dog[] = { "george", "rusty", "storm", "flash", "maximus", "diva", "chelsea", "joey", "ace", "mickey" };
	const uint doglen = ARRAYSIZE(dog);

	const char* sep[] = { "", ".", "_" };
	const uint seplen = ARRAYSIZE(sep);

	const uint maxnum = 100;

	cout << "Generating 10 random usernames..." << endl;
	for (uint i = 0; i < 10; ++i)
	{
		cout << "Username " << i << ": ";

		uint iadj = rand() % adjlen;
		uint isep = rand() % seplen;
		uint idog = rand() % doglen;
		bool addnum = rand() % 2;

		cout << adj[iadj];
		cout << sep[isep];
		cout << dog[idog];
		if (addnum)
		{
			uint rnum = rand() % (maxnum + 10); // +10 allows zero padded numbers
			if (rnum >= maxnum)
			{
				rnum -= maxnum;
				if (rnum < 10)
				{
					cout << 0;
				}
			}
			cout << rnum;
		}
		cout << endl;
	}

	system("pause");
	return 0;
}