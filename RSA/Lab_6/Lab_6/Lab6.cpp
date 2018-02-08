#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;

int power(int x, unsigned int y, int p)
{
	int res = 1;      // Initialize result

	x = x % p;  // Update x if it is more than or 
				// equal to p

	while (y > 0)
	{
		// If y is odd, multiply x with result
		if (y & 1)
			res = (res*x) % p;

		// y must be even now
		y = y >> 1; // y = y/2
		x = (x*x) % p;
	}
	return res;
}

int lcm(int n1, int n2)
{
	int max = (n1 > n2) ? n1 : n2;

	do
	{
		if (max % n1 == 0 && max % n2 == 0)
		{
			return max;
			break;
		}
		else
			++max;
	} while (true);

	return 0;
}

int gcdExtended(int a, int b, int *x, int *y)
{
	// Base Case
	if (a == 0)
	{
		*x = 0, *y = 1;
		return b;
	}

	int x1, y1; // To store results of recursive call
	int gcd = gcdExtended(b%a, a, &x1, &y1);

	// Update x and y using results of recursive
	// call
	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}

int modInverse(int a, int m)
{
	int x, y;
	int g = gcdExtended(a, m, &x, &y);
	if (g != 1)
		cout << "Inverse doesn't exist";
	else
	{
		// m is added to handle negative x
		int res = (x%m + m) % m;
		//cout << "Modular multiplicative inverse is " << res;
		return res;
	}
}

int main() {
	
	int p = 61;
	int q = 53;
	int n = p*q;
	int phi_n = lcm(p-1,q-1);
	int e = 17;
	int d = modInverse(e,phi_n);//e^-1 mod phi_n;
	int public_key [] = { e, n };
	int secret_key[] = { d, n };
	char myMessage[255]; //= "Hello, my name is Dima!";
	cin >> myMessage;
	//int length = myMessage.length();
	int len = strlen(myMessage);
	string my_Decrypted_Message ;
	string my_Encrypted_Message ;
	string ShifrDigitalSignature;
	string RozshifrDigitalSignature;


		;
	int ascChar;
	unsigned long long Shifr[255];
	unsigned long long Rozshifr[255];
	unsigned long long num;
	for (int i = 0; i<len; i++)
	{
		ascChar = myMessage[i];
		Shifr[i] = power(ascChar, e, n);
		my_Decrypted_Message += to_string(Shifr[i]);
	}
	
	for (int i = 0; i<len; i++)
	{		 
		Rozshifr[i] = power(Shifr[i],d,n);
		my_Encrypted_Message += char(Rozshifr[i]);
	}

	//Цифровий підпис

	for (int i = 0; i<len; i++)
	{
		ascChar = myMessage[i];
		Shifr[i] = power(ascChar, d, n);
		ShifrDigitalSignature += to_string(Shifr[i]);

	}

	string Message_Digital_Signature[] = { myMessage, ShifrDigitalSignature };

	for (int i = 0; i<len; i++)
	{
		Rozshifr[i] = power(Shifr[i], e, n);
		RozshifrDigitalSignature += char(Rozshifr[i]);
	}

	//string Message_Digital_Signature[] = { myMessage, RozshifrDigitalSignature };

	cout << "Public key = " << public_key[0]<< "," << public_key[1] << endl;
	cout << "Secret key = " << secret_key[0]<< "," << secret_key[1] << endl;
	cout << "Message = " << myMessage << endl;
	cout << "Shfrotext = " << my_Decrypted_Message << endl;
	cout << "Rozshifr = " << my_Encrypted_Message << endl;
	cout << "DigitalSignature = " << ShifrDigitalSignature << endl;
	cout << "Chek of DigitalSignature = " << RozshifrDigitalSignature << endl;
	system("pause");
}