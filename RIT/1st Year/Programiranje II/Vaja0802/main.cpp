#include "VerifiedAccount.h"
#include "MyJSON.h"
#include <iostream>
#include <vector>

using namespace std;


void izpis(vector<MyJSON*>& jsonObjects)
{
	size_t length = 0;
	for (size_t i = 0; i < jsonObjects.size(); i++)
	{
		std::string buffer = jsonObjects[i]->toJSON();
		cout << buffer << endl;
		length += buffer.length();
	}

	cout << endl << endl << "Length: " << length << endl;
}

int main()
{
	vector<MyJSON*> vect;
	vect.push_back(new VerifiedAccount("timi", 20, "timiimit", "pass123", Date(1998, 3, 29), VerificationType::email, "Verification successful", Date(2016, 4, 20)));
	vect.push_back(new VerifiedAccount(*(VerifiedAccount*)vect[0]));

	izpis(vect);
	system("pause");
	return 0;
}