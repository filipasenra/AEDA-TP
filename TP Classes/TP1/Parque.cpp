#include "Parque.h"
#include <vector>
#include <algorithm>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) :lotacao(lot), numMaximoClientes(nMaxCli)
{
	vagas = lot;
}

unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const
{
	return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const
{
	for (std::vector<int>::size_type i = 0; i != clientes.size(); i++)
	{
		if (clientes[i].nome == nome)
			return i;
	}

	return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
	InfoCartao f1;

	if (size(clientes) < numMaximoClientes)
	{
		f1.nome = nome;
		f1.presente = false;
		clientes.push_back(f1);
		return true;
	}

	return false;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	//Parque completo
	if (vagas <= 0)
		return false;


	if (posicaoCliente(nome) == -1)
		// O cliente nao esta registado
		return false;
	else
		if (clientes[posicaoCliente(nome)].presente)
			//O Cliente ja tem o caso no parque
			return false;
		else
		{
			vagas--;
			clientes[posicaoCliente(nome)].presente = true;
			return true;
		}
}

bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	if (clientes[posicaoCliente(nome)].presente)
		return false;

	clientes.erase (clientes.begin()+posicaoCliente(nome));
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	if (posicaoCliente(nome) == -1)
			// O cliente nao esta registado
			return false;
	else
		if (!clientes[posicaoCliente(nome)].presente)
			//O cliente nao se encontra no parque
			return false;
		else
		{
			clientes[posicaoCliente(nome)].presente = false;
			vagas++;
			return true;
		}

}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao - vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const
{
	return size(clientes);
}
