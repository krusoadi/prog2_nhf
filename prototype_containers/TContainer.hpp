#ifndef PROG2_NHF_TCONTAINER_HPP
#define PROG2_NHF_TCONTAINER_HPP

#include "../headers/Exceptions.hpp"
#include <iostream>

template<class T>

class TContainer {
private:
    T* vars;
    int num;

    void delPtr();

public:
    // Constructors, Destructors

    TContainer();
    explicit TContainer(T first);
    TContainer(const TContainer<T>& other);
    ~TContainer();

    // Add and Pop methods

    void add_back(T newVar);
    void add_front(T newVar);
    void add_index(T newVar, int n);

    T pop_back();
    T pop_front();
    T pop_index(int n);

    // Operator Overloads

    T operator[](int n);

    // Status Check methods
    bool isEmpty();

    // Getters

    int getNum() const;

};

template<class T>
void TContainer<T>::delPtr() {
    if (!isEmpty()) {
        delete[] this->vars;
        this->vars = nullptr;
    }
}

template<class T>
TContainer<T>::TContainer(): vars(nullptr), num(0)  {}

template<class T>
TContainer<T>::TContainer(T first): num(1) {
    this->vars = new T[num];
    this->vars = first;
}

template<class T>
TContainer<T>::TContainer(const TContainer<T> &other): num(other.num) {
    delPtr();
    this->vars = new T[num];
    for (int i = 0; i < num; i++) {
        this->vars[i] = other.vars[i];
    }
}

template<class T>
TContainer<T>::~TContainer() {
    delPtr();
}

template<class T>
void TContainer<T>::add_back(T newVar) {
    T* temp = new T[num + 1];

    int i;
    for (i = 0; i < num; i++) {
        temp[i] = this->vars[i];
    }
    temp[i] = newVar;
    ++num;
    delPtr();
    this->vars = temp;
}

template<class T>
void TContainer<T>::add_front(T newVar) {
    T* temp = new T[num + 1];
    temp[0] = newVar;

    for (int i = 0; i < num; i++) {
        temp[i + 1] = this->vars[i];
    }
    num++;
    delPtr();
    this->vars = temp;
}

template<class T>
void TContainer<T>::add_index(T newVar, int n) {
    if (num < n) {
        throw Exceptions(EmptyContainer, "Over indexed TContainer, when adding a new element.");
    }
    if (n < 0) {
        throw Exceptions(NegativeIndex, "Negative Indexed when adding new element");
    }

    T* temp = new T[++num];

    bool reached_n = false;

    for (int i = 0; i < num; i++) {
        if (i == n) {
            temp[i] = newVar;
            reached_n = true;
        } else if (!reached_n) {
            temp[i] = this->vars[i];
        } else {
            temp[i] = this->vars[i - 1];
        }
    }

    delPtr();
    this->vars = temp;
}

template<class T>
T TContainer<T>::pop_back() {
    if(isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot pop from an empty container (back).");
    }

    T retVal = this->vars[--num];

    T* temp = new T[num];

    for (int i = 0; i < num; i++) {
        temp[i] = this->vars[i];
    }
    delPtr();
    this->vars = temp;
    return retVal;
}

template<class T>
T TContainer<T>::pop_front() {
    if(isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot pop from an empty container (front).");
    }

    T retVal = this->vars[0];
    T* temp = new T[--num];

    for (int i = 0; i < num; i++) {
        temp[i] = this->vars[i + 1];
    }
    delPtr();
    this->vars = temp;
    return retVal;
}

template<class T>
T TContainer<T>::pop_index(int n) {
    if(isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot pop from an empty container (index).");
    }
    if (n < 0) {
        throw Exceptions(NegativeIndex, "Negative Indexed when adding new element");
    }
    if (n >= num) {
        throw Exceptions(OverIndex, "Over indexed TContainer, when popping. (index)");
    }


    T retVal = this->vars[n];

    T* temp = new T[num - 1];

    bool reached_n = false;

    for (int i = 0; i < num; i++) {
        if(n == i) {
            reached_n = true;
        } else if (!reached_n) {
            temp[i] = this->vars[i];
        } else {
            temp[i-1] =this->vars[i];
        }
    }

    delPtr();
    this->vars = temp;
    num--;

    return retVal;
}

template<class T>
T TContainer<T>::operator[](int n) {
    if(isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot get an indexed item from an empty container.");
    }
    if (this->num <= n) {
        throw Exceptions(OverIndex, "TContainer was over indexed.");
    }
    return this->vars[n];
}

template<class T>
bool TContainer<T>::isEmpty() {
    return this->vars == nullptr;
}

template<class T>
int TContainer<T>::getNum() const {
    return this->num;
}

template<class T>
std::ostream& operator<<(std::ostream& stream, const TContainer<T> &in) {
    for (int i = 0; i < in.getNum(); ++i) {
        stream << in[i] << "\n";
    }
    return stream;
}

#endif //PROG2_NHF_TCONTAINER_HPP
