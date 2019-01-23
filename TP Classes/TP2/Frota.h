#ifndef FROTA_H_
#define FROTA_H_

#include <vector>
#include "Veiculo.h"

using namespace std;


class Frota {
	vector<Veiculo *> veiculos;
public:
	friend ostream & operator<<(ostream & o, const Frota & f);
	void adicionaVeiculo(Veiculo *v1);
	int numVeiculos() const;
	int menorAno() const;
	vector<Veiculo *> operator () (int anoM) const;
	float totalImposto() const;
};


#endif /*FROTA_H_*/
