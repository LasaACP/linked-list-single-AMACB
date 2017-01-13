#include <iostream>
#include <stdexcept>
 
template <typename T> class LinkedList {
	class Node {
	public:
		T value;
		void setNext(Node* n) {
			next = n;
		}
		void setPrev(Node* n) {
			prev = n;
		}
		Node* next;
		Node* prev;
	};
public:
	LinkedList() { // Initial empty list conditions
		head = nullptr;
		tail = nullptr;
		length = 0;
	}
	~LinkedList() { // Removes each Node
		while (head != nullptr && tail != nullptr) pop(); // Pop each value to clear memory
	}
 
	unsigned int size() { // Returns the size of the list
		return length;
	}
 
	T &operator[](unsigned int index) { // Returns the value at the given index
		Node* node = head;
		for (int i = 0; i < index; ++i) {
			node = node->next;
			if (node == nullptr) {
				std::string error("Offset of "+std::to_string(index)+" out of range");
				throw std::range_error(std::string(error));
			}
		}
		return node->value;
	}
 
	void add(T val) { // Adds a value to the beginning of the list
		Node* newNode = new Node();
		newNode->value = val;
		if (head != nullptr) {
			head->setPrev(newNode);
		}
		newNode->next = head;
		newNode->prev =	nullptr;
		head = newNode;
		if (length == 0) {
			tail = newNode;
		}
 
		length++;
	}
	void push(T val) { // Pushes a value to the end of the list
		Node* newNode = new Node();
		newNode->value = val;
		if (tail != nullptr) {
			tail->setNext(newNode);
		}
		newNode->prev = tail;
		newNode->next =	nullptr;
		tail = newNode;
		if (length == 0) {
			head = newNode;
		}
 
		length++;
	}
	void insert(int index, T val) { // Inserts a value at index in the list
		if (index == length-1) {
			this->push(val);
			return;
		}
		Node* newNode = new Node();
		newNode->value = val;
		Node* before = this->nodeAt(index);
		Node* after = before->next;
 
		newNode->next = after;
		newNode->prev = before;
		before->next = newNode;
		after->prev = newNode;
		length++;
	}
 
	T pop() { // Pops a value from the beginning and returns it
		if (head == nullptr || tail == nullptr) {
			std::string error("Cannot pop empty list");
			throw std::range_error(error);
		}
		Node* n = head;
		T ret = n->value;
		head = head->next;
		if (head != nullptr) {
			head->prev = nullptr;
		}
		delete n;
 
		length--;
		return ret;
	}
	T shift() { // Shifts a value from the end and returns it
		if (head == nullptr || tail == nullptr) {
			std::string error("Cannot shift empty list");
			throw std::range_error(error);
		}
		Node* n = tail;
		T ret = n->value;
		tail = tail->prev;
		if (tail != nullptr) {
			tail->next = nullptr;
		}
		delete n;
 
		length--;
		return ret;
	}
	T remove(int index) {
		if (index == 0) {
			return this->pop();
		}
		if (index == length-1) {
			return this->shift();
		}
		Node* n = this->nodeAt(index);
		T ret = n->value;
		Node* before = n->prev;
		Node* after = n->next;
		before->next = after;
		after->prev = before;
		delete n;
 
		length--;
		return ret;
	}
 
private:
	Node* nodeAt(int index) {
		Node* node = head;
		for (int i = 0; i < index; ++i) {
			node = node->next;
			if (node == nullptr) {
				std::string error("Offset of "+std::to_string(index)+" out of range");
				throw 1;
			}
		}
		return node;
	}
 
	Node* head;
	Node* tail;
	int length;
};