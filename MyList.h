#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <fstream>

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
class MyList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t list_size;

public:
    MyList() : head(nullptr), tail(nullptr), list_size(0) {}
    ~MyList();

    bool empty() const { return list_size == 0; }
    size_t size() const { return list_size; }
    void push_back(T val);
    void push_front(T val);
    void pop_back();
    void pop_front();
    void print() const;
    void reverse();
    void merge(MyList<T>& other);
    void remove_duplicates();
    T sum() const;
    void save_to_file(const std::string& filename) const;
    void load_from_file(const std::string& filename);
    void print(const std::string& format) const;
};

#include "MyList.tpp"

#endif // MYLIST_H
