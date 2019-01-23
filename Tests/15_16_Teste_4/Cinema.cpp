/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr) :
		name(nm), distance(d), numberOfRooms(nr), timetable(
				FilmTime(0, NULL, 0)) {
}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls) :
		name(nm), distance(d), numberOfRooms(nr), services(ls), timetable(
				FilmTime(0, NULL, 0)) {
}

Cinema::~Cinema() {
}

string Cinema::getName() const {
	return name;
}

unsigned Cinema::getDistance() const {
	return distance;
}

list<string> Cinema::getServices() const {
	return services;
}

BST<FilmTime> Cinema::getTimetable() const {
	return timetable;
}

void Cinema::addService(string service1) {
	services.push_back(service1);
}

void Cinema::addFilmTime(const FilmTime &ft1) {
	timetable.insert(ft1);
}

// TODO

bool Cinema::operator<(const Cinema & cr) const {
	if (distance == cr.distance) {
		return (services.size() > cr.services.size());
	} else {
		return (distance > cr.distance);
	}
}

//a1
Film *Cinema::filmAtHour(unsigned &h1) const {

	if (timetable.isEmpty()) {
		return NULL;
	}

	BSTItrIn<FilmTime> it(timetable);

	unsigned int num_analised = 0;

	while (!it.isAtEnd()) {

		num_analised++;

		if (it.retrieve().getHour() == h1)
			return it.retrieve().getFilm();
		else if (it.retrieve().getHour() > h1)
			{
			//elemento imediatamente atrás
			num_analised--;
			break;
			}

		it.advance();
	}

	if (num_analised == 0)
		return NULL;

	BSTItrIn<FilmTime> it2(timetable);

	for (unsigned int i = 1; i < num_analised; i++) {
		it2.advance();
	}

	h1 = it2.retrieve().getHour();
	return it2.retrieve().getFilm();
}

//a2
bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {

	bool old_hour = false;
	bool new_hour = false;

	if (timetable.isEmpty()) {
		return NULL;
	}

	if (h1 == h2)
		return true;

	BSTItrIn<FilmTime> it(timetable);
	//just to inicialize it
	static FilmTime temp(0, NULL, 0);

	while (!it.isAtEnd()) {

		if (it.retrieve().getHour() == h1
				&& it.retrieve().getRoomID() == room1) {
			old_hour = true;
			temp = it.retrieve();
		}

		if (it.retrieve().getHour() == h2 && it.retrieve().getRoomID() == room1)
			new_hour = true;

		it.advance();
	}

	if (!old_hour || new_hour)
		return false;

	// Make the change
	timetable.remove(temp);
	temp.setHour(h2);
	timetable.insert(temp);

	return true;
}

//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {

	bool found;

	//percorrer as salas todas ordem [1, numberOfRooms]
	for (unsigned id = 1; id <= numberOfRooms; id++) {

		found = false;

		BSTItrIn<FilmTime> it(timetable);

		while (!it.isAtEnd()) {
			if (it.retrieve().getRoomID() == id
					&& it.retrieve().getHour() == h1) {
				found = true;
				break;
			}
			//remember timetable is organized by hour
			else if (it.retrieve().getHour() > h1)
				break;

			it.advance();
		}

		//se a sala a que se esta a procurar, não tem o horario preenchido
		if (!found) {
			timetable.insert(FilmTime(h1, f1, id));
			return id;
		}
	}

	return 0;
}

