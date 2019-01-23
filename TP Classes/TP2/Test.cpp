#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Frota.h"


void test_a_CriarVeiculos() {
	Automovel a1("Fiat",5,2017,"gasolina",1200);
	Camiao c1("Ford",3,2016,"gasolina",1400,1000);
	Automovel a2("Renault",9,2017,"gasoleo",1300);
	Bicicleta b1("XX",4,2018,"TodoTerreno");
	ASSERT_EQUAL("gasolina", c1.getCombustivel());
	ASSERT_EQUAL("Fiat", a1.getMarca());
	ASSERT_EQUAL("Ford", c1.getMarca());
}

void test_b_CriarFrota() {
 	Frota f;
 	ASSERT_EQUAL(0, f.numVeiculos());
 	ASSERT_EQUAL(0, f.menorAno());
 	Veiculo *v1 =new Automovel("Fiat",5,1997,"gasolina",1200);
 	Veiculo *v2= new Camiao("Ford",3,1999,"gasolina",1400,1000);
 	Veiculo *v3=new Automovel("Renault",9,1997,"gasoleo",1300);
 	Veiculo *v4=new Bicicleta("XX",4,2002,"TodoTerreno");
 	f.adicionaVeiculo(v1);
 	f.adicionaVeiculo(v2);
 	f.adicionaVeiculo(v3);
 	f.adicionaVeiculo(v4);
 	ASSERT_EQUAL(4, f.numVeiculos());
 	ASSERT_EQUAL(1997, f.menorAno());
}

 void test_c_InfoVeiculo() {
	Automovel a1("Fiat",5,1997,"gasolina",1200);
	Camiao c1("Ford",3,1999,"gasolina",1400,1000);
	Bicicleta b1("XX",4,2002,"TodoTerreno");
	ASSERT_EQUAL(5, a1.info());
	ASSERT_EQUAL(6,c1.info());
	ASSERT_EQUAL(4,b1.info());
}

void test_d_InfoFrota() {
	Veiculo *v1 =new Automovel("Fiat",5,2016,"gasolina",1200);
 	Veiculo *v2= new Camiao("Ford",3,2017,"gasolina",1400,1000);
 	Veiculo *v3=new Bicicleta("XX",4,2018,"TodoTerreno");
 	Frota f;
 	f.adicionaVeiculo(v1);
 	f.adicionaVeiculo(v2);
 	f.adicionaVeiculo(v3);
 	ASSERTM("Este teste nunca falha! VERIFICAR informação escrita no monitor", true);
 	cout << f;
}

void test_e_OperadorMenor() {
	Automovel a1("Fiat",3,2017,"gasolina",1200);
	Camiao c1("Ford",5,2017,"gasolina",1400,1000);
	Bicicleta b1("XX",4,2018,"TodoTerreno");
	ASSERT_EQUAL(true, a1<c1);
	ASSERT_EQUAL(false,b1<c1);
	ASSERT_EQUAL(true,a1<b1);
}

void test_f_OperadorFuncao() {
	Frota f;
	Veiculo *v1 =new Automovel("Fiat",5,2016,"gasolina",1200);
	Veiculo *v2= new Camiao("Ford",3,2017,"gasolina",1400,1000);
	Veiculo *v3=new Automovel("Renault",9,2016,"gasoleo",1300);
	Veiculo *v4=new Automovel("Renault",9,2010,"gasoleo",1300);
	Veiculo *v5=new Bicicleta("XX",4,2018,"TodoTerreno");
	f.adicionaVeiculo(v1);
	f.adicionaVeiculo(v2);
	f.adicionaVeiculo(v3);
	f.adicionaVeiculo(v4);
	f.adicionaVeiculo(v5);
	ASSERT_EQUAL(5, f.numVeiculos());
	vector<Veiculo*> v;
	v = f(2016);
	ASSERT_EQUAL(2, v.size());
	v = f(2015);
	ASSERT_EQUAL(0, v.size());
	v = f(2010);
	ASSERT_EQUAL(1, v.size());
	ASSERT_EQUAL("Renault", v[0]->getMarca());
}

void test_g_ImpostoVeiculo() {
	Automovel a1("Fiat",5,1997,"gasolina",1200);
	Camiao c1("Ford",3,1999,"gasolina",1400,1000);
	Bicicleta b1("XX",4,2002,"TodoTerreno");
	ASSERT_EQUAL_DELTA(29.06, a1.calcImposto(),0.001);
	ASSERT_EQUAL_DELTA(45.15,c1.calcImposto(),0.001);
	ASSERT_EQUAL_DELTA(0,b1.calcImposto(),0.001);
}

void test_h_ImpostoFrota() {
	Veiculo *v1 =new Automovel("Fiat",5,1997,"gasolina",1200);
	Veiculo *v2= new Camiao("Ford",3,1999,"gasolina",1400,1000);
	Veiculo *v3=new Bicicleta("XX",4,2002,"TodoTerreno");
	Frota f;
	f.adicionaVeiculo(v1);
	f.adicionaVeiculo(v2);
	f.adicionaVeiculo(v3);
	ASSERT_EQUAL_DELTA(74.21, f.totalImposto(),0.001);
}


void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_a_CriarVeiculos));
	s.push_back(CUTE(test_b_CriarFrota));
	s.push_back(CUTE(test_c_InfoVeiculo));
	s.push_back(CUTE(test_d_InfoFrota));
	s.push_back(CUTE(test_e_OperadorMenor));
	s.push_back(CUTE(test_f_OperadorFuncao));
	s.push_back(CUTE(test_g_ImpostoVeiculo));
	s.push_back(CUTE(test_h_ImpostoFrota));

	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA 2018/2019 - Aula Pratica 2");
}

int main(){
    runSuite();
}

ostream & operator<<(ostream & o, const Frota & f)
{

	for (std::vector<int>::size_type i = 0; i != f.veiculos.size(); i++)
	{
		o << f.veiculos[i]->info() << endl;
	}

	return o;
}
