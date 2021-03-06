#include "RSAKey.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout<<"Taille de la clé attendu en paramètre"<<endl;
		exit(EXIT_FAILURE);
	}
	int bit = atoi(argv[1]);
	RSAKey k(bit);
	k.show();
	ZZ n;
	n = k.getN();
	ZZ p;
	/*
	cout<<"Tentatives de factorisation de "<<n<<" par divisions successives"<<endl;
	p = divisions_successives(n);
	cout<<"Facteur obtenu: "<<p<<endl;

	cout<<"Tentatives de factorisation de "<<n<<" par la méthode de Fermat"<<endl;
	p = fermat(n);
	cout<<"Facteur obtenu: "<<p<<endl;

	cout<<"Tentatives de factorisation de "<<n<<" par p-1"<<endl;
	p = pMoinsUn(n);
	cout<<"Facteur obtenu: "<<p<<endl;

	cout<<"Tentatives de factorisation de "<<n<<" par rho"<<endl;
	p = rho(n);
	cout<<"Facteur obtenu: "<<p<<endl;

	cout<<"Tentatives de factorisation de "<<n<<" par ecm"<<endl;
	p = ecm(n);
	cout<<"Facteur obtenu: "<<p<<endl;

	cout<<"Tentatives de factorisation de "<<n<<" par essais aléatoires"<<endl;
	p = aleatoire(n);
	cout<<"Facteur obtenu: "<<p<<endl;
	cout<<"Tentatives de factorisation de "<<n<<" par ECM allégé"<<endl;
	p = ecm_min(n);
	cout<<"Facteur obtenu: "<<p<<endl;
	*/
	test_execution(rho);
	

}
