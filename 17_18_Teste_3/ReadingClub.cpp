/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub() :
		catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books) :
		catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const {
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd()) {
		if (it.retrieve().getTitle() == title
				&& it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(),
					it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if (bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	} else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for (; it1 != it2; it1++) {
		records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for (unsigned int i = 0; i < urs.size(); i++)
		userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}

//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {

	for (unsigned int i = 0; i < books.size(); i++) {
		BookCatalogItem tmp = getCatalogItem(books[i]->getTitle(),
				books[i]->getAuthor());

		if (tmp == BookCatalogItem("", "", 0)) {
			tmp = BookCatalogItem(books[i]->getTitle(), books[i]->getAuthor(),
					books[i]->getYear());
		} else
			catalogItems.remove(tmp);

		tmp.addItems(books[i]);
		catalogItems.insert(tmp);
	}
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;

	BookCatalogItem findAttempt = catalogItems.find(
			BookCatalogItem(book->getTitle(), book->getAuthor(), 0));

	if (!(findAttempt == BookCatalogItem("", "", 0))) {
		temp = findAttempt.getItems();

		for (unsigned int i = 0; i < temp.size(); i++) {
			if (temp[i]->getReader() != NULL) {
				temp.erase(temp.begin() + i);
				i--;
			}
		}
	}

	return temp;

}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	if (book->getReader() != NULL)
		return false;

	vector<Book*> avaiableBooks = getAvailableItems(book);

	if (!avaiableBooks.empty()) {
		reader->addReading(book->getTitle(), book->getAuthor());
		avaiableBooks[0]->setReader(reader);
		return true;
	}

	return false;
}

//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {

	userRecords.insert(user);

}

void ReadingClub::changeUserEMail(User* user, string newEMail) {

	HashTabUserRecord::iterator it = userRecords.find(user);

	if(it == userRecords.end())
		return;

	userRecords.erase(it);
	user->setEMail(newEMail);
	userRecords.insert(user);
}

//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates,
		int min) {

	for(unsigned int i = 0; i < candidates.size(); i++)
	{
		if (candidates[i].numReadings() >= min)
			readerCandidates.push(candidates[0]);
	}

}

int ReadingClub::awardReaderChampion(User& champion) {

	priority_queue<User> buffer = readerCandidates;

	if(buffer.empty())
		return 0;

	User tmp = buffer.top();
	buffer.pop();

	if (buffer.empty() || tmp.numReadings() > buffer.top().numReadings())
	{
		champion = tmp;
		return readerCandidates.size();
	}

	return 0;
}

