#include "Jogo.h"
#include <sstream>

BinaryTree<Circulo> & Jogo::getJogo() {
	return jogo;
}

ostream &operator <<(ostream &os, Circulo &c1) {
	os << c1.getPontuacao() << "-";

	if (c1.getEstado())
		os << "true" << "-";
	else
		os << "false" << "-";

	os << c1.getNVisitas() << "\n";

	return os;
}

//recursividade
BinaryTree<Circulo> Jogo::iniciaJogo(int pos, int niv, vector<int> &pontos,
		vector<bool> &estados) {
	Circulo c1(pontos[pos], estados[pos]);

	if (niv == 0)
		return BinaryTree<Circulo>(c1);

	//avança para o lado esquerdo da arvore
	BinaryTree<Circulo> filhoEsq = iniciaJogo(2 * pos + 1, niv - 1, pontos,
			estados);

	//avança para o lado direito da arvore
	BinaryTree<Circulo> filhoDir = iniciaJogo(2 * pos + 2, niv - 1, pontos,
			estados);

	//retorna a arvore formada após ter havido a recursividade no filho Esq e no Filho direito
	//raiz da arvore e o circulo com os elementos de indice 0 dos vetores
	return BinaryTree<Circulo>(c1, filhoEsq, filhoDir);
}

Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados) {
	jogo = iniciaJogo(0, niv, pontos, estados);
}

string Jogo::escreveJogo() {
	stringstream a;

	//arvore percorrida por nivel: BTItrLevel
	//iterator para para a arvore jogo por nivel
	BTItrLevel<Circulo> it(jogo);

	while (!it.isAtEnd()) {
		a << it.retrieve();
		it.advance();
	}

	return a.str();
}

int Jogo::jogada() {
	//começa no nivel 1 e com pontos negativos pois quer dizer que ocorreu um erro (a arvore esta fazia)
	int pos = 0;
	int pontos = -1;

	BTItrLevel<Circulo> it(jogo);

	while (!it.isAtEnd()) {
		Circulo &c1 = it.retrieve();
		bool estado = c1.getEstado();

		pontos = c1.getPontuacao();
		c1.changeEstado();
		c1.incVisitas();

		int nova_posicao;
		//ir para a esquerda
		if (!estado)
			nova_posicao = 2*pos + 1;
		else
			nova_posicao = 2*pos + 2;

		for(int i = pos; i<nova_posicao && !it.isAtEnd(); i++) {
			it.advance();        // avanca p/ filho esquerdo ou direito
			pos++;
		}
	}

	return pontos;
}

int Jogo::maisVisitado() {

	int mais_visitado = 0;

	BTItrLevel<Circulo> it(jogo);

	if (it.isAtEnd())
		return -1;

	it.advance();

	for (; !it.isAtEnd(); it.advance())
	{
		if (mais_visitado < it.retrieve().getNVisitas())
			mais_visitado = it.retrieve().getNVisitas();
	}

	return mais_visitado;
}

