#include <iostream>
#include <fstream>

using namespace std;

template<class T>
void PrintArray(T* arr, int count)
{
	for (int i = 0; i < count; i++)
	{
		cout << arr[i] << " ";
	}
}

void PrintIndicesKMP(const char* substr, const char* str)
{
	int sublen = strlen(substr);
	int len = strlen(str);

	int* kmpNext = new int[sublen];

#pragma region fill kmpNext
	kmpNext[0] = 0; // nerabis met tu -1 ker se 'i' v search loop-u na koncu vedno poveca za 1
	//kmpNext[1] = 0;
	int count = 0;
	for (int i = 1; i < sublen; i++)
	{
		if (substr[i] == substr[count])
		{
			count++;
			kmpNext[i] = count;
		}
		else
		{
			count = 0;
			kmpNext[i] = count;
		}
	}

	cout << "kmpNext = {";
	PrintArray(kmpNext, sublen);
	cout << '}' << endl;
#pragma endregion

	for (int i = 0; i < len - sublen; i++)
	{
		for (int j = 0; j < sublen && i < len - sublen; j++)
		{
			if (str[i + j] != substr[j])
			{
				if (j > 0)
					i += j - kmpNext[j - 1]; //  premaknemo na naslednji znak z najmanj ponovitvenim primerjanjem
				else
					i++; // ce je razlika pri prvem znaku se premaknemo za en znak naprej

				j = -1; // resetamo index za primerjat (na zacetku loopa bo 0)
			}
			else if (j == sublen - 1) // ce sta enaka in je index na zadnem znaku
			{
				cout << i << " "; // potem smo nasli zadetek
			}
		}
	}

	cout << endl;

	delete[] kmpNext;
}

char* AllocLoadString(const char* filename)
{
	ifstream file(filename);
	if (!file.is_open())
		return nullptr;

	file.seekg(0, ifstream::end);
	int len = file.tellg();
	file.seekg(0, ifstream::beg);
	char* ret = new char[len + 1];
	file.read(ret, len);
	return ret;
}

void main(int argc, const char** argv)
{
	const char* substr = argv[1];
	const char* filename = argv[2];

	char* filestring = AllocLoadString(filename);

	PrintIndicesKMP(substr, filestring);

	delete[] filestring;

	system("pause");
}