#include "Frota.h"
#include <string>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1)
{
	veiculos.push_back(v1);
}

int Frota::numVeiculos() const
{
	return size(veiculos);
}

int Frota::menorAno() const
{
	if (size(veiculos) == 0)
		return 0;

	int temp = veiculos[0]->getAno();

	for (std::vector<int>::size_type i = 1; i != veiculos.size(); i++)
	{
		if (veiculos[i]->getAno() < temp)
			temp = veiculos[i]->getAno();
	}

	return temp;
}

vector<Veiculo *> Frota::operator () (int anoM) const
{
	vector <Veiculo *> temp;

	for (std::vector<int>::size_type i = 0; i != veiculos.size(); i++)
	{
		if (veiculos[i]->getAno() == anoM)
			temp.push_back(veiculos[i]);
	}

	return temp;
}

float Frota::totalImposto() const
{
	float totalImposto = 0;

	for (std::vector<int>::size_type i = 0; i != veiculos.size(); i++)
	{
		totalImposto = totalImposto + veiculos[i]->calcImposto();
	}

	return totalImposto;

}
