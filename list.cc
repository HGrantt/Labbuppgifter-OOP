#include <iostream>

#include "list.h"


list::list():first(nullptr)
{}

list::~list()
{
    delete first;
}

void list::pop(int const x)
{
    element* popper{first};
    element* prev{nullptr};

    while(popper != nullptr)
    {
	if(popper -> x == x)
	{
	    if(prev == nullptr)
	    {
		first = popper->next;
	    }
	    else
	    {
		prev->next = popper->next;
	    }
	    popper->next = nullptr;
	    delete popper;
	    return;
	}
	prev = popper;
	popper = popper->next;
    }
}

void list::insert_element(int const x)
{
    insert_element(x, first);
}

void list::insert_element(int const x,  element* &check)
{
    if ( check == nullptr || x <= check->x)
    {
	element* tmp = new element(x);
	tmp->next = check;
	check = tmp;
    }
    else
    {
	insert_element(x, check->next);
    }
}

void list::print_all() const
{
    list::element* current_element = first;
    while(current_element != nullptr)
    {
	current_element->print_x();
	std::cout << ',';
	current_element = current_element->next;
    }
    std::cout << std::endl;
}

bool list::is_empty() const
{
    return first == nullptr;
}

list::list(list const& copy)
    :list()
{
    if (copy.is_empty())
    {
	return;
    }
    element* check = copy.first->next;
    first = new element(copy.first->x);
    element* next_ptr = first;
    while( check != nullptr )
    {
	int _x = check->x;
	next_ptr->next = new element(_x);
	check = check->next;
	next_ptr = next_ptr -> next;
    }
}

list& list::operator=(list const& rhs)
{
    if( this != &rhs )
    {
	list copy(rhs);
	std::swap(copy.first, first);
    }
    return* this;
}

list::element& list::element::operator=(element const& rhs)
{
    if(this != &rhs)
    {
	element copy(rhs);
	std::swap(copy.x, x);
	std::swap(copy.next, next);
    }
    return *this;
}

list::element::element(element const& copy): x(copy.x), next(nullptr)
{}

list::element::element(int _x, element* _next) : x(_x), next(_next)
{}

list::element::~element()
{
    delete next;
}

void list::element::print_x()
{
    std::cout << this->x;
}
