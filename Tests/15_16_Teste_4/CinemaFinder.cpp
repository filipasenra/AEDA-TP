/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() {
}

CinemaFinder::~CinemaFinder() {
}

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1) {
	cinemas.push(c1);
}

tabHFilm CinemaFinder::getFilms() const {
	return films;
}

priority_queue<Cinema> CinemaFinder::getCinemas() const {
	return cinemas;
}

// TODO

//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
	list<string> res;

	for (tabHFilm::const_iterator it = films.begin(); it != films.end(); it++) {
		list<string> tmp = it->film->getActors();

		for (list<string>::const_iterator it2 = tmp.begin(); it2 != tmp.end();
				it2++) {

			if (actorName == (*it2))
				res.push_back(it->film->getTitle());
		}
	}

	return res;
}

//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {

	for (tabHFilm::const_iterator it = films.begin(); it != films.end(); it++) {

		if (it->film->getTitle() == filmTitle) {
			it->film->addActor(actorName);
			return;
		}
	}

	Film *f1 = new Film(filmTitle);
	f1->addActor(actorName);
	FilmPtr fptr;
	fptr.film = f1;
	films.insert(fptr);

}

//c1
string CinemaFinder::nearestCinema(string service1) const {

	priority_queue<Cinema> tmp = cinemas;

	while (!tmp.empty()) {
		Cinema a = tmp.top();
		list<string> services = a.getServices();

		for (list<string>::const_iterator it2 = services.begin(); it2 != services.end();
				it2++) {

			if (*it2 == service1)
				return a.getName();
		}

		tmp.pop();
	}

	return "";
}

//c2
void CinemaFinder::addServiceToNearestCinema(string service1,
		unsigned maxDistance) {

	if(cinemas.empty())
		throw(CinemaNotFound());

	if(cinemas.top().getDistance() >= maxDistance)
		throw(CinemaNotFound());

	Cinema a = cinemas.top();
	cinemas.pop();
	a.addService(service1);
	cinemas.push(a);

}
