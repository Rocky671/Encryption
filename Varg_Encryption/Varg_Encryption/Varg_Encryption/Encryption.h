#pragma once
#include <random>
#include <ctime>
#include <boost\multiprecision\miller_rabin.hpp>
#include <boost\random\mersenne_twister.hpp>

using namespace std;
using namespace boost::random;
using namespace boost::multiprecision;

class RSA
{
public:
	RSA()
	{
		srand(time(0));	
		randomNumberGenny();

		pqGenerator();

		// generates the n
		n = p * q;

		totient = (p - 1) * (q - 1);

		eGenerator();
		dGenerator();
	}

	// encrypts the message
	unsigned long long messageEncryptor(unsigned int message)
	{
		// initializes the Emessage
		unsigned long long encryptedMessage = 1;

		// loops through "public key times"
		for (unsigned long long i = 0; i < e; i++)
		{
			// starts with 1, multiplies the message, then modulus n
			encryptedMessage = encryptedMessage * message;
			encryptedMessage = encryptedMessage % n;
		}
		
		// returns the encrypted message
		return encryptedMessage;
	}
	
	// message decoder
	unsigned int messageDecryptor(unsigned long long encryptedMessage)
	{
		// initializes at 1
		unsigned long long decryptedMessage = 1;

		// loops through "private key times"
		for (unsigned long long i = 0; i < d; i++)
		{
			// starts with 1, multiplies the message, then modulus n
			decryptedMessage = decryptedMessage * encryptedMessage;
			decryptedMessage = decryptedMessage % n;
		}

		return decryptedMessage;
	}

private:
	// p is a prime number
	unsigned long long p;
	// q is a prime number
	unsigned long long q;
	// n is p * q
	unsigned long long n;
	// totient is p - 1 * q - 1 
	unsigned long long totient;
	// e is the public key
	// e will be greater than 1, but less than the totient
	// the greatest common divisor of e and the totient is 1 (co prime)
	unsigned long long e;
	// d is the private key
	// d * e is equal to 1 + k * the totient
	unsigned long long d;


	mt11213b randomNumberGenny;

	void pqGenerator()
	{
		// generates the p's
		p = generator();
		// generates the q's
		q = generator();
	}

	// finds the E a.k.a public key
	void eGenerator()
	{
		e = generator();
		// while the GCD isn't equal to 1
		while(greatestCommonDivisor(e, totient) != 1)
		{
			// while e is greater than or equal to the totient, or less than or equal to 1
			while (e >= totient || e <= 1)
			{
				// generate a new prime number
				e = generator();
			}
		}
	}

	// generates the private key
	void dGenerator()
	{	
		// finds the number that's perfectly divisible by e, meaning no remainder because the remainder will mess up the encryption
		unsigned long long number = totient + 1;

		// ensures that the private key won't be equal to the public key
		while (number % e != 0 || number / e == e)
		{
			number = number + totient;
		}

		d = number / e;
	}

	// this function courtesy of stack overflow
	unsigned long long greatestCommonDivisor(unsigned long long a, unsigned long long b)
	{
		return b == 0 ? a : greatestCommonDivisor(b, a % b);
	}

	// generates random numbers
	unsigned long long generator()
	{
		unsigned long long random;

		// super simple for loop
		for (;;)
		{
			// generates random number between 0 and 65535
			random = rand() % UINT16_MAX;

			// performs miller rabin test on random number with 525 trials to check if it's a prime number
			if (miller_rabin_test(random, 525, randomNumberGenny))
			{
				return random;
			}
		}
	}
};