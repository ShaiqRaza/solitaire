#include<iostream>
using namespace std;

/////////////////////////////////// cards and its initializations ////////////////////////////
class card {
	char suit;// h or s or c or d
	char color; //r or b
	const char* rank;
public:
	//constructor
	card(): suit('\0'), color('\0'), rank("") {}

	void setCard(char ch1, char ch2, const char* ch3) {
		suit = ch1;
		color = ch2;
		rank = ch3;
	}

	friend card* initializeCards();
};
card* initializeCards() {
	const char* rankArray[] = { "A","2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	card* cardArray = new card[52];//hardcode as there only exists 52 cards

	int j = 0;
	for (int i = 0; i < 52; i++) {
		if (i < 13)
			cardArray[i].setCard('h', 'r', rankArray[j]);
		else if (i < 26)
			cardArray[i].setCard('s', 'b', rankArray[j]);
		else if (i < 39)
			cardArray[i].setCard('c', 'b', rankArray[j]);
		else
			cardArray[i].setCard('d', 'r', rankArray[j]);
		if (j == 12)
			j = 0;
		else
			j++;
	}

	return cardArray;
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

	void print() {
		node* temp = head->next;
		while (temp->next) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
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
	int maxSize;
public:
	//constructor
	stack(): maxSize(-1) {}
	stack(int n): maxSize(n) {}

	void push(T d) {
		if (maxSize != -1 && s.getSize() >= maxSize)
			s.insertAtEnd(d);
		else
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

	void print() {
		s.print();
	}
};

//////////////////////////////  the overall globl game functions ////////////////////////////
void startTheGame() {
	card* cardArray = nullptr;
	cardArray = initializeCards();

	//stackPile & wastePile
}

/////////////////////////////////////// main function ///////////////////////////////////////
int main() 
{
	startTheGame();
	return 0;
}