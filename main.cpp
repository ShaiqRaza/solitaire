#include<iostream>
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
	card(): suit(""), color(""), rank(""), hide(false) {}

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
	const char* rankArray[] = { "A","2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	cardArray = new card* [52];//hardcode as there only exists 52 cards

	int j = 0;
	for (int i = 0; i < 52; i++) {
		if (i < 13) {
			cardArray[i] = new card();
			cardArray[i]-> setCard("heart", "red", rankArray[j]);
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
ostream& operator<<(ostream& out, card* d){
	if (d == nullptr)
		cout << "[ empty ]";
	else {
		if (d->hide == false) {
			out << "[" << d->suit << " ";
			out << d->color << " ";
			out << d->rank << "]";
		}
		else {
			cout << "[   ]";
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
				return false;
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
	private:
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
	};

	node* begin() {
		return head->next;
	}

	node* end() {
		return tail;
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
		cout << "Stock\t\tWaste\t\t\t\t\t" << "Foundation 1\tFoundation 2\tFoundation 3\tFoundation 4" << endl;
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
	void forFoundationsDestination(string source, string dest, int number) {
		if (source != "c1" && source != "c2" && source != "c3" && source != "c4" && source != "c5" && source != "c6" && source != "c7" && source != "w") {
			cout << "---------------------" << endl;
			cout << "Source not exists" << endl;
			cout << "---------------------" << endl;
			return;
		}
		if (number > 1) {
			cout << "---------------------" << endl;
			cout << "Cannot move cards" << endl;
			cout << "---------------------" << endl;
			return;
		}
		if (dest == "f1") {
			card* f = f1.top();
			if (source == "c1") {
				card* c = columnLists[0].getTail();
				if (conditionsForCardsInFoundations(f, c)) {
					f1.push(c);
					columnLists[0].pop();
				}
			}
			else if (source == "c2") {

			}
			else if (source == "c3") {

			}
			else if (source == "c4") {

			}
			else if (source == "c5") {

			}
			else if (source == "c6") {

			}
			else if (source == "c7") {

			}
		}
		else if (dest == "f2") {
			if (source == "c1") {

			}
			else if (source == "c2") {

			}
			else if (source == "c3") {

			}
			else if (source == "c4") {

			}
			else if (source == "c5") {

			}
			else if (source == "c6") {

			}
			else if (source == "c7") {

			}
		}
		else if (dest == "f3") {
			if (source == "c1") {

			}
			else if (source == "c2") {

			}
			else if (source == "c3") {

			}
			else if (source == "c4") {

			}
			else if (source == "c5") {

			}
			else if (source == "c6") {

			}
			else if (source == "c7") {

			}
		}
		else if (dest == "f4") {
			if (source == "c1") {

			}
			else if (source == "c2") {

			}
			else if (source == "c3") {

			}
			else if (source == "c4") {

			}
			else if (source == "c5") {

			}
			else if (source == "c6") {

			}
			else if (source == "c7") {

			}
		}
		else {
			cout << "---------------------" << endl;
			cout << "Foundation not exists" << endl;
			cout << "---------------------" << endl;
		}
	}
	void runCommand() {
		if (command == "s" && stackPile.size() > 0) {
			wastePile.push(stackPile.top());
			stackPile.pop();
		}
		else if (command == "s" && stackPile.size() == 0){
			for (int i = 23; i >= 0; i--) {
				stackPile.push(wastePile.top());
				wastePile.pop();
			}
		}
		else {

			stringstream ss(command);
			char action;
			string source, dest;
			int number;

			ss >> action >> source >> dest >> number;

			forFoundationsDestination(source, dest, number);
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
