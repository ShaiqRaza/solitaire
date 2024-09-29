#include<iostream>
#include<cstdlib>
using namespace std;

/////////////////////////////////// cards and its initializations ////////////////////////////
class card {
	const char* suit;// h or s or c or d
	const char* color; //r or b
	const char* rank;
public:
	//constructor
	card(): suit(""), color(""), rank("") {}

	void setCard(const char* ch1, const char* ch2, const char* ch3) {
		suit = ch1;
		color = ch2;
		rank = ch3;
	}

	friend void initializeCards(card**& cardArray);

	friend ostream& operator<<(ostream& out, card*& d);
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
ostream& operator<<(ostream& out, card*& d) {
	out << d->suit << " ";
	out << d->color << " ";
	out << d->rank << endl;

	return out;
}

///////////////////////////////////// list implementations //////////////////////////////////
template<class T>
class list {

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
			throw runtime_error("Stack is empty!");
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
	stack<card*> stackPile;
	stack<card*> wastePile;
	stack<card*> f1;
	stack<card*> f2;
	stack<card*> f3;
	stack<card*> f4;
	list<card*>* columnLists;
public:
	//constructor
	solitaire(): cardArray(nullptr), columnLists(nullptr){}

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
};

/////////////////////////////////////// main function ///////////////////////////////////////
int main() 
{
	return 0;
}