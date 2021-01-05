#include <algorithm>
#include <iostream>

using namespace std;
template <class T>
class Node {
public:
	T val;
	Node<T>* next;
	Node() {
		cout << "Konstr Node" << endl;
		next = nullptr;
	}
	Node(T val) {
		cout << "Konstr Node(T)" << endl;
		this->val = val;
	}
	~Node(){ cout << "Destr ~Node" << endl; 
	if (next)
		delete next;
	}
};

template <class T>
class List {
public:
	Node<T>* start;
	Node<T>* last;
	Node<T>* cur_node;
	Node<T>* prev;
	List() {
		cout << "Konstr List" << endl;
		start = new Node<T>();
		last = start;
		prev = last;
		cur_node = start;
	}
	List(const List<T>& l) {
		Node<T>* cur = l.start;
		start = new Node<T>();
		last = start;
		prev = last;
		while (cur->next != l.start) {
			push_back(cur->val);
			if (cur == l.cur_node) cur_node = last;
			cur = cur->next;
		}
	}
	~List() {
		cout << "Destr ~List" << endl;
		if (start)
			delete start;
		if (last)
			delete last;
		if (prev)
			delete prev;
		if (cur_node)
			delete cur_node;
		//if (last != start) {
		//	Node<T>* node = start;
		//	Node<T>* temp_start = start;
		//	while (node->next != temp_start) {
		//		pop();
		//	}
		//	//delete node;
		//	//delete temp_start;
		//}
	}
	void push_back(T val) {
		last->val = val;
		Node<T>* next = new Node<T>();
		next->next = start;
		last->next = next;
		prev = last;
		last = last->next;
	}
	T pop() {
		if (last == start) return last->val;
		else {
			prev->next = start;
			last = prev;
			Node<T>* cur = start;
			while (cur->next != last) {
				cur = cur->next;
			}
			Node<T>* res = cur->next;
			if (cur_node == res) cur_node = cur;
			prev = cur;
			return res->val;
		}
	}

	void print() {
		Node<T>* node = start;
		while (node->next != start) {
			cout << node->val << " ";
			node = node->next;
		}
		cout << endl;
	}

	void sort() {
		int swapped = 0, s = 0;
		Node<T>* cur = start;
		Node<T>* last_sorted = last;
		do {
			swapped = 0;
			cur = start;
			while (cur->next != last_sorted) {
				if (cur->val > cur->next->val) {
					swap_with_next(cur);
					swapped = 1;
					s = 1;
				}
				if (s != 1) cur = cur->next;
				s = 0;
			}
			last_sorted = cur;
		} while (swapped == 1);
	}
	List<T> operator = (List<T> l) {
		this->start = l.start;
		this->last = l.last;
		this->prev = l.prev;
		this->last->next = this->start;

		return *this;
	}
	List<T> operator + (List<T> l) {
		this->last->val = l.start->val;
		this->last->next = l.start->next;
		this->last = l.last;
		this->prev = l.prev;
		this->last->next = start;
		return *this;
	}
	inline friend ostream& operator<<(std::ostream& out, List<T>& list) {
		Node<T>* node = list.start;
		while (node->next != list.start) {
			out << node->val << " ";
			node = node->next;
		}
		out << endl;
		return out;
	}
	T go_next() {
		if (cur_node->next == start) return cur_node->val;
		cur_node = cur_node->next;
		return cur_node->val;
	}
	T go_prev() {
		if (cur_node == start) return cur_node->val;
		Node<T>* cur = start;
		while (cur->next != cur_node) {
			cur = cur->next;
		}
		cur_node = cur;
		return cur_node->val;
	}
	T cur() {
		return cur_node->val;
	}
	void insert(T val) {
		//cout << "HHH" << endl;
		T tmp_val = cur_node->val;

		if (cur_node->next == last) {

			cur_node->val = val;
			push_back(tmp_val);
		}

		Node<T>* new_node = new Node<T>(tmp_val);
		Node<T>* tmp = cur_node->next;
		new_node->next = tmp;
		cur_node->next = new_node;
		cur_node->val = val;
		cur_node = cur_node->next;
	}
private:
	void swap_with_next(Node<T>* node) {
		Node<T>* prev_node = start;
		Node<T>* tmp;
		if (node == start) {
			tmp = node->next->next;
			start = node->next;
			last->next = start;
			node->next->next = node;
			node->next = tmp;
			return;
		}
		while (prev_node->next != node) {
			prev_node = prev_node->next;
		}
		if (node->next == last) {
			prev_node->next = last;
			last->next = node;
			last = node;
			last->next = start;
			return;
		}
		prev_node->next = node->next;
		tmp = node->next->next;
		node->next->next = node;
		node->next = tmp;
	}
};

template <class T>
class ListIterator {
	Node<T>& val;
	List<T>& list;
	ListIterator();
public:
	ListIterator(List<T>& list) {
		this->list = list;
		val = list.start;
	}
	T* operator*() {
		return *this->val;
	}
	ListIterator* operator++() {
		this->val = this->val->next;
		return this;
	}
};