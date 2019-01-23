#include "Veiculo.h"
#include <iostream>

using namespace std;


Veiculo::Veiculo (string mc, int m, int a)
{
	marca = mc;
	mes = m;
	ano = a;
}

Motorizado::Motorizado(string mc, int m, int a, string c, int cil) : Veiculo (mc, m, a), combustivel(c), cilindrada(cil)
{ }

Automovel::Automovel(string mc, int m, int a,string c, int cil) : Motorizado (mc, m, a, c, cil)
{ }

Camiao::Camiao(string mc, int m, int a,string c, int cil,int cm) : Motorizado (mc, m, a, c, cil), carga_maxima(cm)
{ }

Bicicleta::Bicicleta(string mc, int m, int a,string t) : Veiculo (mc, m, a), tipo (t)
{ }

string Motorizado::getCombustivel() const
{
	return combustivel;
}

string Veiculo::getMarca() const
{
	return marca;
}

int Veiculo::getAno() const
{
	return ano;
}

int Veiculo::info() const
{
	cout << "Marca: " << marca << endl;
	cout << "Mes: " << mes << endl;
	cout << "Ano: " << ano << endl;
	return 3;
}

int Motorizado::info() const
{
	Veiculo::info();
	cout << "Combustivel: " << combustivel << endl;
	cout << "Cilindridada: " << cilindrada << endl;
	return 5;
}

int Automovel::info() const
{
	return Motorizado::info();
}

int Camiao::info() const
{
	Motorizado::info();
	cout << "Carga Maxima" << carga_maxima << endl;
	return 6;
}

int Bicicleta::info() const
{
	Veiculo::info();
	cout << "Tipo: " << tipo << endl;

	return 4;
}

bool Veiculo::operator < (const Veiculo & v) const
{
	if (ano < v.ano)
		return true;
	else if (ano == v.ano)
		{
		if (mes < v.mes)
			return true;
		else
			return false;
		}
	else
		return false;

}

float Motorizado::calcImposto() const
{
	if (combustivel == "gasolina")
	{
		if (ano > 1995)
		{
			if (cilindrada <= 1000)
				return 14.56;

			if (cilindrada <= 1300)
				return 29.06;

			if (cilindrada <= 1750)
				return 45.15;

			if (cilindrada <= 2600)
				return 113.98;

			if (cilindrada <= 3500)
				return 181.17;

			return 320.89;
		}

	//<=1995
	if (cilindrada <= 1000)
		return 8.10;

	if (cilindrada <= 1300)
		return 14.56;

	if (cilindrada <= 1750)
		return 22.65;

	if (cilindrada <= 2600)
		return 54.89;

	if (cilindrada <= 3500)
		return 87.13;

	return 148.37;

	}

//outro

if (ano > 1995)
{
	if (cilindrada <= 1000)
		return 14.56;

	if (cilindrada <= 2000)
		return 29.06;

	if (cilindrada <= 3000)
		return 45.15;

	return 113.98;
}

//<=1995

if (cilindrada <= 1000)
	return 8.10;

if (cilindrada <= 2000)
	return 14.56;

if (cilindrada <= 3000)
	return 22.65;

return 54.89;

}

float Bicicleta::calcImposto() const
{
	return 0;
}
