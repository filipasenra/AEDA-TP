
#include "veterinario.h"
#include <sstream>
#include <iostream>
using namespace std;

Veterinario::Veterinario(string nome, int cod)
{
	this->nome=nome;
	codOrdem = cod;
}

string Veterinario::getNome() const
{
	return nome;
}

long Veterinario::getcodOrdem() const
{
	return codOrdem;
}

string Veterinario::getInformacao() const
{
	ostringstream ordem;
	ordem << codOrdem;
	return (nome + ", " + ordem.str());
}

