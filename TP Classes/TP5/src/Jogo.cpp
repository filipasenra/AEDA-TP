/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <cstdlib>
#include <ctime>
using namespace std;

unsigned int Jogo::numPalavras(string frase) {
	if (frase.length() == 0)
		return 0;
	int n = 1;
	int pos = frase.find(' ');
	while (pos != -1) {
		frase = frase.substr(pos + 1);
		pos = frase.find(' ');
		n++;
	}
	return n;
}

Jogo::Jogo() {
	this->criancas.clear();
}

Jogo::Jogo(list<Crianca>& lc2) {
	criancas = lc2;
}

void Jogo::insereCrianca(const Crianca &c1) {
	criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const {
	return criancas;
}

string Jogo::escreve() const {
	string res;

	for (list<Crianca>::const_iterator it = criancas.begin();
			it != criancas.end(); it++) {
		res += it->escreve() + "\n";
	}
	return res;
}

Crianca& Jogo::perdeJogo(string frase) {

	list<Crianca> t = this->getCriancasJogo();
	list<Crianca>::const_iterator it = t.begin();

	while (t.size() != 1) {
		unsigned int tamanhoFrase = (this->numPalavras(frase) -1) % t.size();

		for (unsigned int i = 0; i < tamanhoFrase; i++) {
			it++;
		}

		it = t.erase(it);

		if (it == t.end())
			it = t.begin();
	}

	Crianca *c1 = new Crianca( t.front());
		return *c1;
}

list<Crianca>& Jogo::inverte() {

	criancas.reverse();

	return criancas;
}

list<Crianca> Jogo::divide(unsigned id) {

	list<Crianca> l1;
	for (list<Crianca>::const_iterator it = criancas.begin();
			it != criancas.end(); it++)
	{
		if (it->getIdade() > id)
		{
			l1.push_back(*it);
			criancas.erase(it);
			it--;
		}
	}

	return l1;
}

void Jogo::setCriancasJogo(const list<Crianca>& l1) {
	criancas = l1;
}

bool Jogo::operator==(Jogo& j2) {

	if (criancas.size() != j2.criancas.size())
		return false;

	list<Crianca>::const_iterator it = criancas.begin();
	list<Crianca>::const_iterator it1 = j2.criancas.begin();

	while (it != criancas.end())
	{
		if (!(*it == *it1))
			return false;

		it++;
		it1++;
	}

	return true;
}

list<Crianca> Jogo::baralha() const {

	list<Crianca> l1;
	list<Crianca> l = criancas;

	srand(time(NULL) );

	while (l.size() > 0)
	{
		int rPos = rand() % l.size();

		list<Crianca>::iterator it = l.begin();

		for(int i = 0; i < rPos; i++, it++);

		l1.push_back(*it);
		l.erase(it);
	}

	l = l1;

	return l1;
}
