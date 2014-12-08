#ifndef _LIST_H_
#define _LIST_H_

class list
{
public:
  list();
  list(list const&);
  list& operator=(list const&);
  list& operator=(list&&)=delete;
  ~list();

  void insert_element(int const x);
  void pop(int const x);
  void print_all() const;
  bool is_empty() const;

private:
  class element
  {
  public:
    element& operator=(element const&);
    element(int x, element* next=nullptr);
    element(element const&);
    element& operator=(element&&) = delete;
    ~element();

    void print_x();
    int x;
    element* next;
  };

  element* first;
  void insert_element(int x, element*& check);
};

#endif
