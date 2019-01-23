/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name)
{
	vector <Mail *> tmp;

	for (std::vector<int>::size_type i = 0; i != postmen.size(); i++)
	{
		if (postmen[i].getName() == name)
		{
			tmp = postmen[i].getMail();
			postmen.erase(postmen.begin() + i);
			break;
		}
	}

	return tmp;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance)
{
	balance = 0;
	vector<Mail *> vec;

	for(std::vector<int>::size_type i = 0; i != mailToSend.size(); i++)
	{
		balance += mailToSend[i]->getPrice();

		if (mailToSend[i]->getZipCode() <= lastZipCode && mailToSend[i]->getZipCode() >= firstZipCode)
			addMailToDeliver(mailToSend[i]);
		else
			vec.push_back(mailToSend[i]);
	}

	mailToSend.clear();

	return vec;

}

Postman PostOffice::addMailToPostman(Mail *m, string name)
{
	for (std::vector<int>::size_type i = 0; i != mailToSend.size(); i++)
	{
		if (postmen[i].getName() == name)
			{
			postmen[i].addMail(m);
			return postmen[i];
			}
	}

	throw (NoPostmanException(name));
}

