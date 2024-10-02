#include<iostream>
#include<iomanip>
#include<cstdlib>
#include <cstring>
#include <sstream>
using namespace std;

/////////////////////////////////// cards and its initializations ////////////////////////////
class card {
	const char* suit;// h or s or c or d
	const char* color; //r or b
	const char* rank;
	bool hide;
public:
	//constructor
	card() : suit(""), color(""), rank(""), hide(false) {}

	bool getHide() {
		return hide;
	}

	void setCard(const char* ch1, const char* ch2, const char* ch3) {
		suit = ch1;
		color = ch2;
		rank = ch3;
	}

	void toggleHide() {
		hide = !hide;
	}

	friend void initializeCards(card**& cardArray);

	friend ostream& operator<<(ostream& out, card* d);

	friend bool conditionsForCardsInFoundations(card* f, card* c);
};
void initializeCards(card**& cardArray) {
	const char* rankArray[] = { "A","2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	cardArray = new card * [52];//hardcode as there only exists 52 cards

	int j = 0;
	for (int i = 0; i < 52; i++) {
		if (i < 13) {
			cardArray[i] = new card();
			cardArray[i]->setCard("heart", "red", rankArray[j]);
		}
		else if (i < 26) {
			cardArray[i] = new card();
			cardArray[i]->setCard("spade", "black", rankArray[j]);
		}
		else if (i < 39) {
			cardArray[i] = new card();
			cardArray[i]->setCard("club", "black", rankArray[j]);
		}
		else {
			cardArray[i] = new card();
			cardArray[i]->setCard("diamond", "red", rankArray[j]);
		}
		if (j == 12)
			j = 0;
		else
			j++;
	}
}
ostream& operator<<(ostream& out, card* d) {
	if (d == nullptr)
		out << "[    empty    ]";
	else {
		if (d->hide == false) {
			out << "[" << d->suit << " ";
			out << d->color << " ";
			out << setw(2) << d->rank << "]";
		}
		else {
			out << "[   ]";
		}
	}

	return out;
}
bool conditionsForCardsInFoundations(card* f, card* c) {
	const char* rankArray[] = { "A","2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	if (f && c) {
		if (f->suit == c->suit && f->color == c->color) {
			for (int i = 0; i < 13; i++) {
				if (rankArray[i] == f->rank && rankArray[i + 1] == c->rank) {
					return true;
				}
			}
		}
	}
	else if (c && !f) {
		if (c->rank == "A")
			return true;
		return false;
	}

	return false;
}
bool conditionsForCardsInLists(card* c, card* s) {

}

///////////////////////////////////// list implementations //////////////////////////////////
template<class T>
class list
{
	class node {

	public:
		T data;
		node* next;
		node* prev;

		//constructor
		node(T d) : data(d), next(nullptr), prev(nullptr) {}

	};

	node* head;
	node* tail;
	int size;

public:
	//constructor
	list() {

		//we made dumb nodes of head and tail in doubly linked list
		head = new node(T());
		tail = new node(T());

		head->next = tail;
		tail->prev = head;

		size = 0;
	}

	class iterator {
		node* currentNode;

	public:
		iterator(node* n = nullptr) : currentNode(n) {}

		iterator& operator=(node* n) {
			currentNode = n;
			return *this;
		}

		iterator& operator=(iterator& rhs) {
			if (this->currentNode != rhs.currentNode) {
				currentNode = rhs.currentNode;
			}
			return *this;
		}

		T& operator*() {
			return currentNode->data;
		}

		iterator& operator++() {
			if (currentNode) {
				currentNode = currentNode->next;
			}
			return *this;
		}

		iterator& operator++(int) {
			iterator temp = *this;
			if (currentNode) {
				currentNode = currentNode->next;
			}
			return temp;
		}

		iterator& operator--() {
			if (currentNode) {
				currentNode = currentNode->prev;
			}
			return *this;
		}

		iterator& operator--(int) {
			iterator temp = *this;
			if (currentNode) {
				currentNode = currentNode->prev;
			}
			return temp;
		}

		bool operator!=(const iterator& other) {
			return currentNode != other.currentNode;
		}

		void moveNodesToAnotherList(list<T>& dest, list<T>& source, int& n) {
			currentNode->prev->next = source.tail;
			node* temp = currentNode->prev;
			currentNode->prev = dest.tail->prev;
			dest.tail->prev->next = currentNode;
			source.tail->prev = temp;
			source.size = source.size - n;
			dest.size = dest.size + n;
		}
	};

	node* begin() {
		return head;
	}

	node* end() {
		return tail-prev;
	}

	//remove from end not delete
	void pop() {
		if (size) {
			node* temp = tail->prev;
			tail->prev = tail->prev->prev;
			tail->prev->next = tail;
			size--;
		}
	}

	void insertAtStart(T d) {
		node* t = new node(d);
		t->next = head->next;
		t->prev = head;
		head->next->prev = t;
		head->next = t;
		size++;
	}

	void insertAtEnd(T d) {
		node* t = new node(d);
		t->prev = tail->prev;
		t->next = tail;
		tail->prev->next = t;
		tail->prev = t;
		size++;
	}

	bool deleteStart() {
		if (size) {
			node* temp = head->next;
			head->next = head->next->next;
			head->next->prev = head;
			delete temp;
			size--;
			return true;
		}
		return false;
	}

	bool deleteEnd() {
		if (size) {
			node* temp = tail->prev;
			tail->prev = tail->prev->prev;
			tail->prev->next = tail;
			delete temp;
			size--;
			return true;
		}
		return false;
	}

	void print() {
		node* temp = head->next;
		while (temp->next) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	node* findElement(T val) {
		node* temp = head->next;
		while (temp->next) {
			if (temp->data == val) {
				return temp;
			}
			temp = temp->next;
		}
		return nullptr;
	}

	bool deleteElement(T val) {
		node* temp = findElement(val);
		if (temp) {
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			size--;
			return true;
		}
		return false;
	}

	int getSize() {
		return size;
	}

	T getTail() {
		return tail->prev->data;
	}

	T gethead() {
		return head->next->data;
	}
};

///////////////////////////////////// stack implementations /////////////////////////////////
template<class T>
class stack {
	list<T> s;
public:
	//constructor
	stack() {}

	void push(T d) {
		s.insertAtEnd(d);
	}

	bool pop() {
		if (s.deleteEnd())
			return true;
		return false;
	}

	bool isEmpty() {
		if (s.getSize())
			return false;
		return true;
	}

	T top() {
		if (isEmpty())
			return T();// will return nullptr
		else
			return s.getTail();
	}

	int size() {
		return s.getSize();
	}

	void print() {
		s.print();
	}
};

class solitaire {
	card** cardArray;
	string command;
	stack<card*> stackPile;
	stack<card*> wastePile;
	stack<card*> f1;
	stack<card*> f2;
	stack<card*> f3;
	stack<card*> f4;
	list<card*>* columnLists;
	stack<string> commands;
public:
	//constructor
	solitaire() : cardArray(nullptr), columnLists(nullptr) {}

	//////////////////////////////  the overall globl game functions ////////////////////////////
	void initializeStackPile() {
		for (int i = 0; i < 24; i++) {
			stackPile.push(cardArray[i]);
		}
	}
	void initializeColumnLists() {
		columnLists = new list<card*>[7];
		int j = 24;//after stack pile remaining cards
		for (int i = 0; i < 7; i++) {
			for (int k = 0; k <= i; k++) {
				columnLists[i].insertAtStart(cardArray[j]);
				if (k)
					columnLists[i].gethead()->toggleHide();
				j++;
			}
		}
	}
	void shuffleCards() {
		srand(time(0));
		card* temp = nullptr;
		for (int i = 0; i < 25; i++) {
			int j = rand() % 52;
			//random swapping
			temp = cardArray[i];
			cardArray[i] = cardArray[j];
			cardArray[j] = temp;
		}
	}
	void initialization() {
		initializeCards(cardArray);
		shuffleCards();
		initializeStackPile();
		initializeColumnLists();
	}
	void display() {
		system("cls");
		cout << "Stock\t\tWaste\t\t\t\t\t" << "\tFoundation 1\t\tFoundation 2\t\tFoundation 3\t\tFoundation 4" << endl;
		cout << "[   ]\t\t";
		cout << wastePile.top() << "\t\t\t\t";
		cout << f1.top() << "  \t";
		cout << f2.top() << "  \t";
		cout << f3.top() << "  \t";
		cout << f4.top() << "  \t" << endl;
		cout << stackPile.size() << " cards \t " << wastePile.size() << " cards" << endl << endl;

		for (int i = 0; i < 7; i++) {
			list<card*> ::iterator it = columnLists[i].begin();
			list<card*> ::iterator end = columnLists[i].end();
			cout << "Column " << i + 1 << ": ";
			while (it != end) {
				cout << *it;
				it++;
			}
			cout << endl;
		}
	}
	void input() {
		cout << "Enter command: ";
		getline(cin, command);
	}
	void movetoFoundation(stack<card*>& foundation, string source) {
		card* f = foundation.top();
		if (source == "c1") {
			card* c = columnLists[0].getTail();
			if (conditionsForCardsInFoundations(f, c)) {
				foundation.push(c);
				columnLists[0].pop();
				c = columnLists[0].getTail();
				if(c->getHide())
					c->toggleHide();
			}
		}
		else if (source == "c2") {
			card* c = columnLists[1].getTail();
			if (conditionsForCardsInFoundations(f, c)) {
				foundation.push(c);
				columnLists[1].pop();
				c = columnLists[1].getTail();
				if (c->getHide())
					c->toggleHide();
			}
		}
		else if (source == "c3") {
			card* c = columnLists[2].getTail();
			if (conditionsForCardsInFoundations(f, c)) {
				foundation.push(c);
				columnLists[2].pop();
				c = columnLists[2].getTail();
				if (c->getHide())
					c->toggleHide();
			}
		}
		else if (source == "c4") {
			card* c = columnLists[3].getTail();
			if (conditionsForCardsInFoundations(f, c)) {
				foundation.push(c);
				columnLists[3].pop();
				c = columnLists[3].getTail();
				if (c->getHide())
					c->toggleHide();
			}
		}
		else if (source == "c5") {
			card* c = columnLists[4].getTail();
			if (conditionsForCardsInFoundations(f, c)) {
				foundation.push(c);
				columnLists[4].pop();
				c = columnLists[4].getTail();
				if (c->getHide())
					c->toggleHide();
			}
		}
		else if (source == "c6") {
			card* c = columnLists[5].getTail();
			if (conditionsForCardsInFoundations(f, c)) {
				foundation.push(c);
				columnLists[5].pop();
				c = columnLists[5].getTail();
				if (c->getHide())
					c->toggleHide();
			}
		}
		else if (source == "c7") {
			card* c = columnLists[6].getTail();
			if (conditionsForCardsInFoundations(f, c)) {
				foundation.push(c);
				columnLists[6].pop();
				c = columnLists[6].getTail();
				if (c->getHide())
					c->toggleHide();
			}
		}
		else if (source == "w") {
			card* c = wastePile.top();
			if (conditionsForCardsInFoundations(f, c)) {
				foundation.push(c);
				wastePile.pop();
			}
		}
	}
	void forFoundationsDestination(string source, string dest, int number) {
		if (source != "c1" && source != "c2" && source != "c3" && source != "c4" && source != "c5" && source != "c6" && source != "c7" && source != "w") {
			cout << "Source not possible" << endl;
			return;
		}
		if (number > 1) {
			cout << "Cannot move cards" << endl;
			return;
		}
		if (dest == "f1")
			movetoFoundation(f1, source);
		else if (dest == "f2")
			movetoFoundation(f2, source);
		else if (dest == "f3")
			movetoFoundation(f3, source);
		else if (dest == "f4")
			movetoFoundation(f4, source);
		else {
			cout << "Given Destination not exists" << endl;
		}
	}
	void MoveListToList(list<card*>& source, list<card*>& dest, int& number) {
		if (number > source.getSize()) {
			cout << "Invalid Command!" << endl;
			return;
		}
		else {
			list<card*> ::iterator it = source.end();
			for (int i = 1; i < number; i++) {
				if (!conditionsForCardsInLists(*it, *(--it))) {
					cout << "Invalid Command!" << endl;
					return;
				}
			}
			if (!conditionsForCardsInLists(*it, dest.getTail())) {
				cout << "Invalid Command" << endl;
				return;
			}
			//if conditions are true
			it.moveNodesToAnotherList(dest, source, number);
		}
		
	}
	void movetoList(list<card*>& dest, string source, int number) {
		if (source == "c1")
			MoveListToList(columnLists[0], dest, number);
		if (source == "c2")
			MoveListToList(columnLists[1], dest, number);
		if (source == "c3")
			MoveListToList(columnLists[2], dest, number);
		if (source == "c4")
			MoveListToList(columnLists[3], dest, number);
		if (source == "c5")
			MoveListToList(columnLists[4], dest, number);
		if (source == "c6")
			MoveListToList(columnLists[5], dest, number);
		if (source == "c7")
			MoveListToList(columnLists[6], dest, number);
	}
	void forListsDestination(string source, string dest, int number) {
		if (source != "c1" && source != "c2" && source != "c3" && source != "c4" && source != "c5" && source != "c6" && source != "c7" && source != "w" && source != "f1" && source != "f2" && source != "f3" && source != "f4") {
			cout << "Source not possible" << endl;
			return;
		}
		if (source == "w" || source == "f1" || source == "f2" || source == "f3" || source != "f4") {
			if (number > 1) {
				cout << "Cannot move cards" << endl;
				return;
			}
		}
		if (dest == "c1") {
			list<card*> list = columnLists[0];
			movetoList(list, source, number);
		}
		else if (dest == "c2") {
			list<card*> list = columnLists[1];
			movetoList(list, source, number);
		}
		else if (dest == "c3") {
			list<card*> list = columnLists[2];
			movetoList(list, source, number);
		}
		else if (dest == "c4") {
			list<card*> list = columnLists[3];
			movetoList(list, source, number);
		}
		else if (dest == "c5") {
			list<card*> list = columnLists[4];
			movetoList(list, source, number);
		}
		else if (dest == "c6") {
			list<card*> list = columnLists[5];
			movetoList(list, source, number);
		}
		else if (dest == "c7") {
			list<card*> list = columnLists[6];
			movetoList(list, source, number);
		}
	}
	void runCommand() {
		if (command == "s" && stackPile.size() > 0) {
			wastePile.push(stackPile.top());
			stackPile.pop();
		}
		else if (command == "s" && stackPile.size() == 0) {
			for (int i = 23; i >= 0; i--) {
				stackPile.push(wastePile.top());
				wastePile.pop();
			}
		}
		else if (command == "z") {


		}
		else {

			stringstream ss(command);
			char action;
			string source, dest;
			int number;

			ss >> action >> source >> dest >> number;

			if (action == 'm') {
				if (source == dest) {
					cout << "Invalid Command! Source and Destination must be different." << endl;
					return;
				}
				if (dest[0] == 'f')
					forFoundationsDestination(source, dest, number);
				else if (dest[0] == 'c')
					forListsDestination(source, dest, number);
				else
					cout << "Invalid Destination!" << dest << endl;
			}
			else
				cout << action << " Invalid Command!" << endl;
		}
	}
};

/////////////////////////////////////// main function ///////////////////////////////////////
int main()
{
	solitaire game;
	game.initialization();
	game.display();
	for (int i = 1; i <= 27; i++) {
		game.input();
		game.runCommand();
		game.display();
	}
	return 0;
}
