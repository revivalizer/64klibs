#pragma once

// Based on this idea by ryg
// http://stackoverflow.com/questions/4235981/elegant-implementation-of-circular-singly-linked-list-in-c
// Basically, on initialization the list head is a pointer to the list itself (which, conveniently has a next pointer in the correct position)

template <class T>
class zlistnode : public align16
{
public:
	zlistnode(T value)
		: next(nullptr)
		, value(value)
	{
	}

	zlistnode<T>* next;
	T value;
};

template <class T>
class zlist : public align16
{
public:
	zlist()
	{
		head = get_sentinel();
	}

	~zlist()
	{
		// iterate over list, delete nodes?
	}

	zlistnode<T>* head;

	zlistnode<T>* get_sentinel()
	{
		return (zlistnode<T>*)(this);
	}

	zlistnode<T>* create_node(T element)
	{
		zlistnode<T>* n = new zlistnode<T>(element);
		return n;
	}

	void push_front(T element)
	{
		auto n = create_node(element);
		n->next = head;
		head = n;
	}

	void push_back(T element)
	{
		zlistnode<T>* current = head, * sentinel = get_sentinel();

		// search for end
		while (current->next != sentinel)
			current = current->next;

		// insert
		auto n = create_node(element);
		n->next = sentinel;
		current->next = n;
	}

	void remove(T element)
	{
		zlistnode<T>** prevnext, * sentinel = get_sentinel();
		prevnext = &head; // ptr to next pointer of previous node
		while (*prevnext != sentinel) {
			auto current = *prevnext;
			if (current->value == element) {
				*prevnext = current->next; // remove current from list
				delete current; // and free it
				break; // we're done!
			}
			prevnext = &current->next;
		}
	}
};