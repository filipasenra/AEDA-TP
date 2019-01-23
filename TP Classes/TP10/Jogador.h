#ifndef JOGADOR_H_
#define JOGADOR_H_

#include "Aposta.h"
#include <string>

using namespace std;


//A ALTERAR!!
struct apostaHash
{
	//funcao hash
	int operator() (const Aposta & ap) const
	{
		return ap.somaNumeros();
	}
	
	//funcao de igualdade
	bool operator() (const Aposta & ap1, const Aposta & ap2) const
	{
		if (ap1.getNumeros().size() != ap2.getNumeros().size())
			return false;

		unsigned int n = ap1.calculaCertos(ap2.getNumeros());
		if (n != ap1.getNumeros().size())
			return false;

		return true;
	}
};

typedef unordered_set<Aposta, apostaHash, apostaHash> tabHAposta;


class Jogador
{
	tabHAposta apostas;
	string nome;
public:
	Jogador(string nm="anonimo") { nome=nm; }
	void adicionaAposta(const Aposta & ap);
	unsigned apostasNoNumero(unsigned num) const;
	tabHAposta apostasPremiadas(const tabHInt & sorteio) const;
	unsigned getNumApostas() const { return apostas.size(); }
};

#endif /*JOGADOR1_H_*/
