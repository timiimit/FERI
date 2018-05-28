#include "VerifiedAccount.h"
#include <iostream>

using namespace std;

int main()
{
	Account** arr = new Account*[2];
	arr[0] = new VerifiedAccount("timi", 20, "timiimit", "pass123", Date(2018, 3, 29), VerificationType::email, "Verification successful", Date(2016, 4, 20));
	arr[1] = new VerifiedAccount(*arr[0]);

	cout << arr[0]->toString() << endl;
	cout << arr[0]->toStringNV() << endl;
	
	system("pause");
	return 0;
}