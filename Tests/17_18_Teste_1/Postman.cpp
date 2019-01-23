/*
 * Postman.cpp
 */
#include "Postman.h"

#include "numberDifferent.h"

Postman::Postman(): id(0) {}

Postman::Postman(string name)
{
	static unsigned int n = 0;
	n++;
	id = n;
	this->name = name;

}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator< (const Postman & c) const
{
	vector <string> zip1, zip2;

	for (std::vector<int>::size_type i = 0; i != myMail.size(); i++)
		zip1.push_back(myMail[i]->getZipCode());

	vector<Mail*> otherPostmanMail = c.getMail();

	for(unsigned int i=0 ; i<otherPostmanMail.size() ; i++)
		zip2.push_back(otherPostmanMail.at(i)->getZipCode());

	return (numberDifferent(zip1) < numberDifferent(zip2));

}





