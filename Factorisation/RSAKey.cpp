#include "RSAKey.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <thread>
#include <cstdlib>
#include <ctime>
using namespace NTL;


RSAKey::RSAKey(int bits)
{
	this->bits = bits;
	genererCle();
}



void RSAKey::genererCle()
{
	ZZ seed;
	std::srand(std::time(0));
	seed = std::rand();
	SetSeed(seed);
	GenPrime(p,bits/2);
	GenPrime(q,bits/2);
	n = p * q;
	phi = (p-1) * (q-1);
	RandomBits(a,bits/2);
	ZZ un;
	un = 1;
	while(b >= phi || InvModStatus(b,a,phi) == 1 || a >= n || GCD(n,a) != un)
	{
		RandomBits(a,bits/2);
	}
}

ZZ RSAKey::getP()
{
	return p;
}

ZZ RSAKey::getQ()
{
	return q;
}

ZZ RSAKey::getA()
{
	return a;
}

ZZ RSAKey::getB()
{
	return b;
}

ZZ RSAKey::getN()
{
	return n;
}

ZZ RSAKey::getPhi()
{
	return phi;
}

void RSAKey::show() const
{
	std::cout<<"p: "<<p<<std::endl;
	std::cout<<"q: "<<q<<std::endl;
	std::cout<<"a: "<<a<<std::endl;
	std::cout<<"b: "<<b<<std::endl;
	std::cout<<"n: "<<n<<std::endl;
}

ZZ RSAKey::RSA(const ZZ& x, bool mode)
{
	ZZ c;
	if(!mode)
	{
		PowerMod(c,x,a,n);
	}
	else
	{
		PowerMod(c,x,b,n);
	}
	return c;
}

ZZ RSAKey::RSACrypt(const std::string& msg_)
{
	unsigned char* msg =(unsigned char*) msg_.c_str();
	ZZ x;
	long size = strlen((char*)msg);
	if(size > NumBytes(n))
	{
		size = NumBytes(n);
	}
	ZZFromBytes(x,msg,size);
	ZZ c;
	c = RSA(x,false);
	return c;
}

std::string RSAKey::RSADecrypt(const ZZ& x)
{
	ZZ c;
	c = RSA(x,true);
	char* msg = (char*)malloc(sizeof(char)*NumBytes(c)+1);
	BytesFromZZ((unsigned char*)msg,c,NumBytes(c));
	std::string msgFinal = std::string((const char*)msg);
	return msgFinal;
}

ZZ divisions_successives(ZZ& n)
{
	std::clock_t t;
	double duree;
	t = std::clock();
	ZZ racine = SqrRoot(n);
	ZZ p;
	p = 2;
	while(p < racine)
	{
		if(n % p == 0)
		{
			duree =( std::clock() - t ) / (double)CLOCKS_PER_SEC;
			std::cout<<"Temps d'exécutions(divisions successives) "<<duree<<" s"<<std::endl;
			return p;
		}
		p++;
		p = NextPrime(p);
	}
	return p;
}

ZZ fermat(ZZ& n)
{
	std::clock_t t;
	double duree;
	t = std::clock();
	ZZ a = SqrRoot(n);
	ZZ a2;
	a2 = a*a;
	while(a < n)
	{
		if(a2 >= n && (a2-n) % SqrRoot(a2-n) == 0)
		{
			duree =( std::clock() - t ) / (double)CLOCKS_PER_SEC;
			std::cout<<"Temps d'exécutions(méthode de Fermat) "<<duree<<" s"<<std::endl;
			return a - SqrRoot(a2-n);
		}
		a2 += 2*a + 1;
		a++;
	}
	return n;
}

ZZ pMoinsUn(ZZ& n)
{
	std::clock_t t;
	double duree;
	t = std::clock();
	ZZ B;
	B = SqrRoot(n);
	ZZ a;
	a = 2;
	ZZ p;
	p = 2;
	ZZ d;
	int i;
	while(a <= B)
	{
		i = 0;
		while(i < 64)
		{
			p *=a;
			if(p >= n)
			{
				p = p % n;
			}
			d = GCD(p-1,n);
			if(d > 1 && d < n)
			{
				duree =( std::clock() - t ) / (double)CLOCKS_PER_SEC;
				std::cout<<"Temps d'exécutions(p-1) "<<duree<<" s"<<std::endl;
				return d;
			}
			if(d == n)
			{
				i = 16;
			}
			else
			{
				i++;
			}
		}
		a++;
		a = NextPrime(a);
		p = a;
	}
	return n;
}

ZZ aleatoire(ZZ& n)
{
	std::clock_t t;
	double duree;
	t = std::clock();
	ZZ racine;
	racine = SqrRoot(n);
	ZZ seed;
	std::srand(std::time(0));
	seed = std::rand();
	ZZ p;
	p = RandomBnd(racine);
	bool b = true;
	while(b)
	{
		if(p > 1)
		{
			if(n % p == 0)
			{
				b = false;
			}
			else
			{
				p = RandomBnd(racine);
			}
		}
		else
		{
			p = RandomBnd(racine);
		}
	}
	duree =( std::clock() - t ) / (double)CLOCKS_PER_SEC;
	std::cout<<"Temps d'exécutions(aleatoire) "<<duree<<" s"<<std::endl;
	return p;
}


ZZ rho(ZZ& n)
{
	std::clock_t t;
	double duree;
	t = std::clock();
	ZZ a;
	a = SqrRoot(n);
	ZZ b;
	ZZ c;
	b = a;
	c = 1;
	ZZ d;
	while(1)
	{
		a = (a*a + c)%n;
		b = (b*b + c)%n;
		b = (b*b + c)%n;
		d = GCD(abs(a-b),n);
		if(d > 1 && d < n)
		{
			duree =( std::clock() - t ) / (double)CLOCKS_PER_SEC;
			std::cout<<"Temps d'exécutions(rho) "<<duree<<" s"<<std::endl;
			return d;
		}
	}
	return n;
}

ZZ ecm(ZZ& n)
{
	std::clock_t t;
	double duree;
	t = std::clock();

	ZZ seed;
	std::srand(std::time(0));
	seed = std::rand();
	ZZ x;
	ZZ y;
	ZZ a;
	ZZ B;
	ZZ b;
	ZZ d;
	ZZ p;
	ZZ pe;
	ZZ gcd_x;
	ZZ gcd_y;
	B = 1000;

	while(1)
	{
		x = RandomBnd(n);
		y = RandomBnd(n);
		a = RandomBnd(n);

		
		b = (y*y - x*x*x - a*x)%n;
		d = GCD(4*a*a*a - 27*b*b,n);
		if(d >1 && d < n)
		{
			duree =( std::clock() - t ) / (double)CLOCKS_PER_SEC;
			std::cout<<"Temps d'exécutions(ECM) "<<duree<<" s"<<std::endl;
			return d;
		}
		p = 2;
		while(p < 5)
		{
			pe = p;
			while(pe < B)
			{
				pe *=p;
			}
			pe = pe/p;
			x = (pe*x)%n;
			y = (pe*y)%n; 
			gcd_x = GCD(x,n);
			gcd_y = GCD(y,n);
			if(gcd_x == 1 && gcd_y == 1)
			{
				p++;
				p = NextPrime(p);
			}
			else
			{
				duree =( std::clock() - t ) / (double)CLOCKS_PER_SEC;
				std::cout<<"Temps d'exécutions(ECM) "<<duree<<" s"<<std::endl;
				if(gcd_y > 1)
				{
					return gcd_y;;
				}
				return gcd_x;
			}
		}
	}
	return n;
}
