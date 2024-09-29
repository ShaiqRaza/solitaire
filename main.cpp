#include<iostream>
using namespace std;

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
};

int main() 
{
	list <int> myList;
	myList.deleteStart();
	return 0;
}