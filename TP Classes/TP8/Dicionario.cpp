#include <iostream>
#include <string>
#include <fstream>
#include "Dicionario.h"
#include "BST.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

//tem que ter isto por causa do insert na arvore
bool PalavraSignificado::operator <(const PalavraSignificado &ps1) const {

	return palavra < ps1.palavra;
}

bool PalavraSignificado::operator ==(const PalavraSignificado &ps1) const {

	return palavra == ps1.palavra;
}

void Dicionario::lerDicionario(ifstream &fich) {
	string pal, sig;

	//check eof flag
	while (!fich.eof()) {
		getline(fich, pal);
		getline(fich, sig);
		PalavraSignificado p1(pal, sig);
		palavras.insert(p1);
	}
}

string Dicionario::consulta(string palavra) const {

	//objeto com a palavra a ser encontrada
	PalavraSignificado p1(palavra, "");

	//retorna o nó na árvore com a palavra
	PalavraSignificado px = palavras.find(p1);

	//Objeto a ser retornado com nao está presente a palavra a procurar
	PalavraSignificado pNotFound("", "");

	//Se nao encontrou
	if (px == pNotFound) {

		//percorrer a arvore toda atraves do it
		//com o objetivo de lançar a excepcao

		BSTItrIn<PalavraSignificado> it(palavras);
		string palAntes = "", signifAntes = "";

		//enquanto o it não chegou ao fim e o objeto para o qual aponta e menor que p1
		//pelo iterator ser em ordem, pesquisa ate o it ser maior que p1
		while (!it.isAtEnd() && it.retrieve() < p1) {
			palAntes = it.retrieve().getPalavra();
			signifAntes = it.retrieve().getSignificado();
			it.advance();
		}

		string palApos = "", signifApos = "";

		//se nao chegou ao fim
		if (!it.isAtEnd()) {
			palApos = it.retrieve().getPalavra();
			signifApos = it.retrieve().getSignificado();
		}

		//lança excepcao com palavra antes e excepcao com palavra depois
		throw PalavraNaoExiste(palAntes, signifAntes, palApos, signifApos);

	}

	return px.getSignificado();
}

bool Dicionario::corrige(string palavra, string significado) {

	//objeto com a palavra a ser encontrada
	PalavraSignificado p1(palavra, significado);

	//retorna o nó na árvore com a palavra
	PalavraSignificado px = palavras.find(p1);

	//Objeto a ser retornado com nao está presente a palavra a procurar
	PalavraSignificado pNotFound("", "");

	if (px == pNotFound)
	{
		palavras.insert(p1);
		return false;
	}

	palavras.remove(p1);
	palavras.insert(p1);
	return true;
}

void Dicionario::imprime() const {

	//iterator em ordem para imprimir as palavras por ordem alfabetica
	BSTItrIn<PalavraSignificado> it(palavras);

	//enquanto o it nao chegou ao fim
	while (!it.isAtEnd()) {
		cout << it.retrieve().getPalavra() << endl
				<< it.retrieve().getSignificado() << endl;

		//avança para o proximo elemento
		it.advance();
	}
}
