/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>

Hospital::Hospital(unsigned trayC) :
		trayCapacity(trayC) {
}

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}

unsigned Hospital::numPatients(string medicalSpecialty) const {
	unsigned int n = 0;

	for (list<Doctor>::const_iterator it = doctors.begin(); it != doctors.end();
			it++) {
		if (it->getMedicalSpecialty() == medicalSpecialty)
			n += it->getPatients().size();
	}

	return n;

}

bool cmp(const Doctor &a, const Doctor &b) {
	if (a.getPatients().size() < b.getPatients().size())
		return true;

	if (a.getPatients().size() > b.getPatients().size())
		return false;

	if (a.getMedicalSpecialty() < b.getMedicalSpecialty())
		return true;

	if (a.getMedicalSpecialty() > b.getMedicalSpecialty())
		return false;

	if (a.getCode() < b.getCode())
		return true;

	return false;
}

void Hospital::sortDoctors() {

	doctors.sort(cmp);

}

bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {

	unsigned int n = 0;

	for (list<Doctor>::const_iterator it = doctors.begin(); it != doctors.end();
			it++) {
		if (it->getMedicalSpecialty() == medicalSpecialty1)
			n++;
	}

	if (n >= 3)
		return false;

	Doctor e1(codM1, medicalSpecialty1);

	addDoctor(e1);

	return true;
}

queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	queue<Patient> p1;

	for (list<Doctor>::const_iterator it = doctors.begin(); it != doctors.end();
			it++) {
		if (it->getCode() == codM1) {
			p1 = it->getPatients();
			doctors.erase(it);
			return p1;
		}
	}

	throw(DoctorInexistent());

}

bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {

	unsigned int sizefila = 10000; //valor arbitário suficientemente grande (?)
	list<Doctor>::iterator e1 = doctors.end();

	for (list<Doctor>::iterator it = doctors.begin(); it != doctors.end();
			it++) {

		unsigned int n = it->getPatients().size();

		if ((it->getMedicalSpecialty() == medicalSpecialty1)
				&& (n < sizefila)) {
			sizefila = it->getPatients().size();
			e1 = it;
		}
	}

	if (e1 == doctors.end())
		return false;

	e1->addPatient(Patient(cod1, medicalSpecialty1));

	return true;
}

void Hospital::processPatient(unsigned codM1) {

	Patient e1(0, "a");
	list<Doctor>::iterator it;

	try {
		for (it = doctors.begin(); it != doctors.end(); it++) {
			if (it->getCode() == codM1) {
				e1 = it->removeNextPatient();
				break;
			}
		}
	} catch (DoctorInexistent &e) {	};

	if (it != doctors.end()) {

		for (list<stack<Patient>>::iterator it = letterTray.begin();
				it != letterTray.end(); it++) {
			if (it->size() < trayCapacity) {
				it->push(e1);
			}
		}
	}

}

unsigned Hospital::removePatients(unsigned codP1) {

	unsigned int n =0;
	for (list<stack<Patient>>::iterator it = letterTray.begin(); it != letterTray.end();
				it++) {

		if (it->top().getCode() == codP1)
		{
			it->pop();
			n++;
		}

		if(it->empty())
		{
			it = letterTray.erase(it);
		}
	}

	return n;

}

