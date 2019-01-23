
#include "animal.h"
#include <sstream>

#include <iostream>
using namespace std;

Animal::Animal(string nome, int idade)
{
	this->nome = nome;
	this->idade = idade;
	vet = new Veterinario ("", -1);

	if (idade < maisJovem)
		maisJovem = idade;
}

int Animal::maisJovem = 10000;

Cao::Cao(string nome, int idade, string raca) : Animal(nome, idade), raca(raca)
{ }

Voador::Voador(int vmax, int amax)
{
	velocidade_max = vmax;
	altura_max = amax;
}

Morcego::Morcego(string nome, int idade, int vmax, int amax) : Animal(nome, idade), Voador(vmax, amax)
{ }

int Animal::getMaisJovem()
{
	return maisJovem;
}

string Animal::getNome() const
{
	return nome;
}

int Animal::getIdade() const
{
	return idade;
}

string Animal::getInformacao() const
{

	ostringstream convert;
	convert << nome << ", " << idade;

	if (vet->getcodOrdem() != -1 )
		{
		convert << ", " << vet->getInformacao();
		}

		return convert.str();
}

Veterinario* Animal::getVet() const
{
	return vet;
}

bool Cao::eJovem()const
{
	if (idade < 5)
		return true;
	return false;
}

string Cao::getInformacao() const
{

	return Animal::getInformacao() + ", " + raca;
}

bool Morcego::eJovem()const
{
	if (idade < 4)
		return true;
	return false;
}

string Voador::getInformacao() const
{
	ostringstream convert;
	convert << ", " << velocidade_max << ", " << altura_max;

	return convert.str();
}

string Morcego::getInformacao() const
{

	return Animal::getInformacao() + Voador::getInformacao();
}

void Animal::setVet(Veterinario *veterinario)
{
	vet = veterinario;
}

