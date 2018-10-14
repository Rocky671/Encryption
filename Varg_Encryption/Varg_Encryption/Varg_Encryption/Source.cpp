/*
Rocky Vargas
RSA Encryption
12/12/2017
*/

#include <iostream>
#include "Encryption.h"

using namespace std;

int main()
{
	RSA randomGen;
	unsigned long long userNumber;

	cout << "Enter a number to encrypt, and then to decrypt" << endl;

	cin >> userNumber;

	unsigned int encrypted = randomGen.messageEncryptor(userNumber);

	cout << "This is the encrypted number" << endl << encrypted << endl;
	cout << "This is the decrypted number" << endl << randomGen.messageDecryptor(encrypted) << endl;






	system("pause");
	return 0;
}