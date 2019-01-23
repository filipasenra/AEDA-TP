#include "zoo.h"

#include <fstream>
#include <algorithm>

#include <iostream>
using namespace std;

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1)
{
	animais.push_back(a1);
}

string Zoo::getInformacao() const
{
	string informacao;

	for (std::vector<int>::size_type i = 0; i != animais.size(); i++)
	{
		informacao = informacao + animais[i]->getInformacao();
	}

	cout << informacao << endl;

	return informacao;
}

vector<Animal *> Zoo::getAnimais() const
{
	return animais;
}

bool Zoo::animalJovem(string nomeA)
{
	bool existe = false;

	for (std::vector<int>::size_type i = 0; i != animais.size(); i++)
	{
		if (animais[i]->getNome() == nomeA)
		{
			existe = animais[i]->eJovem();
			break;
		}
	}

	return existe;
}

void Zoo::alocaVeterinarios(istream &isV)
{
	string nome, codS;

		while(!isV.eof())
		{
			getline(isV,nome);
			getline(isV,codS);

			long num = atoi(codS.c_str());

			Veterinario *tmp=new Veterinario(nome, num);
			veterinarios.push_back(tmp);
		}

		for(unsigned int i = 0; i < animais.size(); i++)
			animais[i]->setVet( veterinarios[i%veterinarios.size()] );

}

bool Zoo::removeVeterinario (string nomeV)
{
	for(unsigned int i = 0; i < veterinarios.size(); i++)
	{
		if( veterinarios[i]->getNome() == nomeV )
		{
			//Procura animais tratados por Veterinario nomeV
			for(unsigned int j = 0; j < animais.size(); j++)
			{
				if( animais[j]->getVet() == veterinarios[i] )
					//substitui pelo Veterinario seguinte no vector de veterinarios
					animais[j]->setVet( veterinarios[(i + 1)%veterinarios.size()] );
			}
			veterinarios.erase( veterinarios.begin() + i );

			return true;
		}
	}
	return false;
}

bool Zoo::operator < (Zoo& zoo2) const
{
	int idade1 = 0, idade2 = 0;

	for (std::vector<int>::size_type i = 0; i != animais.size(); i++)
		idade1 = idade1 + animais[i]->getIdade();

	for (std::vector<int>::size_type i = 0; i != zoo2.getAnimais().size(); i++)
		idade2 = idade2 + zoo2.getAnimais()[i]->getIdade();

	return idade1 < idade2;
}


