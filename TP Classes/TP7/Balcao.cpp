#include <queue>
#include <cstdlib>
#include "Balcao.h"

using namespace std;

Cliente::Cliente() {
	numPresentes = rand() % 5 + 1; //numero aleatorio de 1 a 5
}

int Cliente::getNumPresentes() const {
	return numPresentes;
}

Balcao::Balcao(int te) :
		tempo_embrulho(te) {
	tempo_atual = 0;
	prox_saida = 0;
	prox_chegada = rand() % 20 + 1;
	clientes_atendidos = 0;
}

void Balcao::proximoEvento() {

	if (clientes.size() != 0) {
		if (prox_chegada < prox_saida) {
			tempo_atual = prox_chegada;
			chegada();
		} else if (prox_chegada > prox_saida) {
			tempo_atual = prox_saida;
			saida();
		} else {
			tempo_atual = prox_saida;
			saida();
			chegada();
		}
	} else {
		tempo_atual = prox_chegada;
		chegada();
	}
}

void Balcao::chegada() {
	Cliente e1;

	if (clientes.empty())
		prox_saida = tempo_atual + e1.getNumPresentes() * tempo_embrulho;

	clientes.push(e1);

	prox_chegada = tempo_atual + (rand() % 20) + 1;

	cout << "tempo=" << tempo_atual << "\nchegou novo cliente com "
			<< e1.getNumPresentes() << " presentes\n";

}

void Balcao::saida() {
	cout << "tempo= " << tempo_atual << endl;

	Cliente e1;

	try {
		e1 = getProxCliente();
	} catch (FilaVazia &e) {
		cout << e.getMsg() << endl;
	}

	clientes.pop();

	cout << "cliente atendido: " << e1.getNumPresentes() << " presentes"
			<< endl;
	clientes_atendidos++;

	if (clientes.size() != 0)
		prox_saida = tempo_atual
				+ clientes.front().getNumPresentes() * tempo_embrulho;
	else
		prox_saida = 0;
}

int Balcao::getTempoAtual() const {
	return tempo_atual;
}

int Balcao::getProxChegada() const {
	return prox_chegada;
}

ostream & operator <<(ostream & out, const Balcao & b1) {

	out << "numero de clientes atendidos: " << b1.getClientesAtendidos() << "\n";
	out << "numero de clientes em espera: " << b1.clientes.size() << "\n";
	return out;
}

int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}

int Balcao::getProxSaida() const {
	return prox_saida;
}

int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}

Cliente & Balcao::getProxCliente() {

	if (clientes.size() != 0)
		return clientes.front();

	throw(FilaVazia());
}

