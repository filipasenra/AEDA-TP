/*
 * Empacotador.cpp
 */
#include <sstream>
#include "MaquinaEmpacotar.h"

MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas) :
		capacidadeCaixas(capCaixas) {
}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}

/* a implementar pelos estudantes */

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
	unsigned int n = 0;
	for (vector<Objeto>::iterator it = objs.begin(); it != objs.end(); it++) {
		if ((*it).getPeso() <= capacidadeCaixas) {
			objetos.push(*it);
			objs.erase(it);
			it--;
			n++;
		}

	}

	return n;
}

Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {

	//estrutura temporaria para guardar caixas retiradas da fila
	vector<Caixa> temp;

	//procura caixa mais cheia, ainda com espaco para obj
	while (!caixas.empty()) {
		Caixa cx = caixas.top();
		caixas.pop();
		if (cx.getCargaLivre() >= obj.getPeso()) {

			for (unsigned i = 0; i < temp.size(); i++) //repoe na fila de caixas as caixas retiradas da frente.
				caixas.push(temp[i]);
			return cx;
		} else
			temp.push_back(cx); //coloca as caixas nao utilizadas num vetor temporario
	}
	for (unsigned i = 0; i < temp.size(); i++) //repoe as caixas nao utilizadas de volta, caso nenhuma sirva
		caixas.push(temp[i]);

	return Caixa(capacidadeCaixas); //e retorna uma nova caixa
}

unsigned MaquinaEmpacotar::empacotaObjetos() {

	while (objetos.size() != 0) {
		Objeto o1 = objetos.top();
		objetos.pop();
		Caixa c1 = procuraCaixa(o1);
		c1.addObjeto(o1);
		//a caixa retornada nao se encontra na heap
		caixas.push(c1);
	}

	return caixas.size();
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {

	stringstream tmp;

	if (objetos.size() == 0)
		tmp << "Nao ha objetos!\n";
	else
	{
		HEAP_OBJS buffer = objetos;

		while (buffer.size() != 0)
		{
			Objeto o1 = buffer.top();
			buffer.pop();

			tmp << o1 << "\n";
		}
	}

	return tmp.str();
}

Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	Caixa cx;
	unsigned int a = 0;

	if (caixas.size() == 0)
		throw (MaquinaEmpacotar());

	HEAP_CAIXAS buffer = caixas;

	while (!buffer.empty())
	{
		if(buffer.top().getSize() >= a)
		{
			cx = buffer.top();
			a = cx.getSize();
		}
	}

	return cx;
}

