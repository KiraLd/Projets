/**
*@file RSAKey.hpp
*/
#ifndef _RSAKEY_
#define _RSAKEY_
#include <NTL/ZZ.h>
using namespace NTL;

/**
*@class RSAKey
*@brief Représente les clés privé/publique RSA
*/
class RSAKey
{
	private:
		/**
		@brief élément p de la clé privée
		*/
		ZZ p;
		/**
		*@brief élément q de la clé privée
		*/
		ZZ q;
		/**
		*@brief élément b de la clé privée
		*@note inverse multiplicatif de a mod phi
		*/
		ZZ b;
		/**
		*@brief élément n de la clé publique
		*@note n = p*q
		*/
		ZZ n;
		/**
		*@brief élément a de la clé publique
		*/
		ZZ a;
		/**
		*@brief Indicatrice d'Euler sur n
		*@note phi = (p-1)*(q-1)
		*/
		ZZ phi;
		/**
		*@brief le nombre de bits maximum pour coder n
		*/
		int bits;
	public:
		/**
		*@brief Constructeur par initialisation, génére une clé RSA
		*@param le nombre de bits pour coder n
		*@note Génére une clé RSA tel que: p et q premier, a et b < n et b inverse de a mod phi
		*/
		RSAKey(int bits);

		/**
		*@brief Génére une clé RSA aléatoire
		*@note appelée par le 1er constructeur
		*/
		void genererCle();
		/**
		*@brief Getter p
		*@return composante p
		*/
		ZZ getP();
		/**
		*@brief Getter q
		*@return composante q
		*/
		ZZ getQ();
		/**
		*@brief Getter a
		*@return composante a
		*/
		ZZ getA();
		/**
		*@brief Getter b
		*@return composante b
		*/
		ZZ getB();
		/**
		*@brief Getter n
		*@return composante n
		*/
		ZZ getN();
		/**
		*@brief Getter phi
		*@return indicatrice d'Euler sur n
		*/
		ZZ getPhi();
		/**
		@brief Affiche la clé
		*/
		void show() const;
		/**
		*@brief Effectue le chiffrement RSA sur un entier
		*@param x l'entier à chiffré
		*@param mode false pour chiffré, true pour déchiffré
		*@return l'entier chiffré
		*/
		ZZ RSA(const ZZ& x, bool mode); 
		/**
		*@brief Convertit et crypte une chaine de caractère
		*@param msg_ la chaine à chiffrée
		*@return la chaine crypté sous forme d'un entier
		*/
		ZZ RSACrypt(const std::string& msg_);
		/**
		*@brief Décriffre un entier et le convertit en chaine de caractère
		*@param x l'entier à déchiffrer
		*@return la chaine résultante du déchiffrement
		*/
		std::string RSADecrypt(const ZZ& x);
};

ZZ divisions_successives(ZZ& n);
ZZ aleatoire(ZZ& n);
ZZ fermat(ZZ& n);
ZZ pMoinsUn(ZZ& n);
ZZ rho(ZZ& n);
ZZ ecm(ZZ& n);

#endif
