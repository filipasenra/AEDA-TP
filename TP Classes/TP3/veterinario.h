
#ifndef SRC_VETERINARIO_H_
#define SRC_VETERINARIO_H_

#include <string>
using namespace std;

class Veterinario {
	string nome;
	long codOrdem;
public:
	Veterinario(string nome, int cod);
	string getNome() const;
	long getcodOrdem() const;
	string getInformacao() const;
	//completar
};



#endif /* SRC_VETERINARIO_H_ */
