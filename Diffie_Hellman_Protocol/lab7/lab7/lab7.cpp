#include <iostream>
#include <cstdlib>
#include <ctime>
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

void main() {


	srand(time(NULL));
	int OpenSimpleNumberP = std::rand();
	int g = std::rand();
	int secretAliceA = std::rand();
	int secretBobB = std::rand();
	
	int OpenAlicekeyA, OpenBobkeyB;

	OpenAlicekeyA = power(g,secretAliceA, OpenSimpleNumberP);
	OpenBobkeyB = power(g, secretBobB, OpenSimpleNumberP);

	int messageFromBobToAlice = OpenBobkeyB;
	int messageFromAliceToBob= OpenAlicekeyA;

	int AliceSecretKey = power(messageFromBobToAlice,secretAliceA, OpenSimpleNumberP);
	int BobSecretKey = power(messageFromAliceToBob, secretBobB, OpenSimpleNumberP);

	int chek = power(g, secretAliceA*secretBobB, OpenSimpleNumberP);

	cout << "Alice`s number = " << secretAliceA << endl;
	cout << "Bob`s  number = " << secretBobB << endl;
	cout << "Message form Alice to Bob = " << messageFromAliceToBob << endl;
	cout << "Message form Bob to Alice = " << messageFromBobToAlice << endl;
	cout << "Alice`s  secret key = " << AliceSecretKey << endl;
	cout << "Bob`s  secret key= " << BobSecretKey << endl;
	cout << "Chek k = " << chek << endl;

	system("pause");
}