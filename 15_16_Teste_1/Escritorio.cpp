#include "Escritorio.h"
#include <iostream>
#include <algorithm>

//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }

Documento Documento::operator+ (const Documento & d1) const
{
	int numPaginas_novo = d1.numPaginas  + numPaginas;
	float pPreto_novo = (d1.pPreto*d1.numPaginas + pPreto*numPaginas)/numPaginas_novo;
	float pAmarelo_novo = (d1.pAmarelo*d1.numPaginas + pAmarelo*numPaginas)/numPaginas_novo;

	return Documento (numPaginas_novo, pPreto_novo, pAmarelo_novo);
}

//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }


//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }

bool ImpressoraPB::imprime(Documento doc1)
{

	if (numPagImprimir < doc1.getNumPaginas())
		return false;

	numPagImprimir -= doc1.getNumPaginas();
	docsImpressos.push_back(doc1);
	return true;

}

bool ImpressoraPB::bool_tonerBaixo()
{
	return numPagImprimir < 30;
}

//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}

bool ImpressoraCores::imprime(Documento doc1)
{
	if (numPagImprimirPreto < doc1.getPercentagemPreto()*doc1.getNumPaginas())
		return false;

	if (numPagImprimirAmarelo < doc1.getPercentagemAmarelo()*doc1.getNumPaginas())
		return false;

	numPagImprimirPreto -= doc1.getPercentagemPreto()*doc1.getNumPaginas();
	numPagImprimirAmarelo -= doc1.getPercentagemAmarelo()*doc1.getNumPaginas();
	docsImpressos.push_back(doc1);

	return true;
}

bool ImpressoraCores::bool_tonerBaixo()
{
	return (numPagImprimirPreto < 20 || numPagImprimirAmarelo < 20) ;
}


//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }

int Escritorio::numImpressorasSemResponsavel() const
{
	int n = 0;

	for (std::vector<int>::size_type i = 0; i != funcionarios.size(); i++)
	{
		n += funcionarios[i].getImpressoras().size();
	}

	return impressoras.size()-n;
}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1)
{
	vector<Impressora *> tmp;

	for (std::vector<int>::size_type i = 0; i != impressoras.size(); i++)
	{
		if (impressoras[i]->getAno() < ano1)
			{
			tmp.push_back(impressoras[i]);
			impressoras.erase(impressoras.begin() + i);
			i--;
			}
	}

	return tmp;
}

Impressora * Escritorio::imprimeDoc(Documento doc1) const
{
	for (std::vector<int>::size_type i = 0; i != impressoras.size(); i++)
	{
		if (impressoras[i]->imprime(doc1))
			return impressoras[i];
	}

	Impressora * tmp = new ImpressoraPB("inexistente", 0, 0);
	return tmp;
}

vector<Impressora *> Escritorio::tonerBaixo() const
{
	vector<Impressora *> tmp;

	for (std::vector<int>::size_type i = 0; i != impressoras.size(); i++)
	{
		if (impressoras[i]->bool_tonerBaixo())
			tmp.push_back(impressoras[i]);
	}

	return tmp;

}

string Escritorio::operator() (string x) const
{
	for (std::vector<int>::size_type i = 0; i != funcionarios.size(); i++)
	{
		for (std::vector<int>::size_type j = 0; j != funcionarios[i].getImpressoras().size(); j++)
		{
			if (funcionarios[i].getImpressoras()[j]->getCodigo() == x)
				return funcionarios[i].getCodigo();
		}
	}

	return "nulo";
}
