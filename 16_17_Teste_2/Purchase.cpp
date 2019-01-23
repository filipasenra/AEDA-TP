/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) :
		client(cli) {
}

long Purchase::getClient() const {
	return client;
}

list<stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article *e1 = new Article(client, barCode);
	e1->setPresent(present);
	e1->setDeliverHome(deliverHome);

	return e1;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {

	std::list<std::stack<Article*> >::iterator it = bags.end();
	it--;

	if (it->size() >= BAG_SIZE) {
		stack<Article*> e1;
		e1.push(article);
		bags.push_back(e1);
	} else {
		it->push(article);
	}

}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {

	vector<Article*> presents;
	stack<Article*> tempBag;

	for (std::list<std::stack<Article*> >::iterator it = bags.begin();
			it != bags.end(); it++) {
		stack<Article*> & bag = (*it);

		while (!bag.empty()) {
			if (bag.top()->getPresent())	// Present found!
				presents.push_back(bag.top());
			else
				tempBag.push(bag.top());// Not a present ; goes to the temporary bag

			bag.pop();	// remove it from the bag
		}

		// Reset the bag with the non-presents
		while (!tempBag.empty()) {
			bag.push(tempBag.top());
			tempBag.pop();
		}
	}

	return presents;

}

