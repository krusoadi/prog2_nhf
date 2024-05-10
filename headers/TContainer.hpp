#ifndef PROG2_NHF_TCONTAINER_HPP
#define PROG2_NHF_TCONTAINER_HPP

#include "Exceptions.hpp"
#include <iostream>
#include <iterator>
#include <cstddef>

// Every method in the class are listed down below in declaration order

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

    T& operator[](int n);

    // Status Check methods
    bool isEmpty();

    // Getters

    [[nodiscard]] int getNum() const;

    // Other methods

    void clear();
    void swap(int n, int m);

    // Iterator TODO RandomAccessIterator, BidirectionalIterator or ForwardIterator suits better?

    struct Iterator;

    // Iterator methods

    Iterator begin();
    Iterator end();

    Iterator rbegin();
    Iterator rend();

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
    this->vars[0] = first;
}

template<class T>
TContainer<T>::TContainer(const TContainer<T> &other): num(other.num) {
    this->vars = new T[num];
    for (int i = 0; i < num; ++i) {
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
    for (i = 0; i < num; ++i) {
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

    for (int i = 0; i < num; ++i) {
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

    for (int i = 0; i < num; ++i) {
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

    for (int i = 0; i < num; ++i) {
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

    for (int i = 0; i < num; ++i) {
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

    for (int i = 0; i < num; ++i) {
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
T& TContainer<T>::operator[](int n) {
    if(isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot get an indexed item from an empty container.");
    }
    if (this->num <= n) {
        throw Exceptions(OverIndex, "TContainer was over indexed.");
    }
    if (n < 0) {
        throw Exceptions(NegativeIndex, "Negative Indexed when adding new element");
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
void TContainer<T>::clear() {
    delPtr();
    this->num = 0;
}

template<class T>
void TContainer<T>::swap(int n, int m) {
    if (n >= num || m >= num) {
        throw Exceptions(OverIndex, "Over indexed, when swapping.");
    } if (n < 0 || m < 0) {
        throw Exceptions(NegativeIndex, "Negative index was given when swapping.");
    } if(n == m) {
        return;
    }

    T temp = this->vars[n];
    this->vars[n] = this->vars[m];
    this->vars[m] =temp;
}

template<class T>
std::ostream& operator<<(std::ostream& stream, TContainer<T> &in) {
    for (int i = 0; i < in.getNum(); ++i) {
        stream << in[i] << "\n";
    }
    return stream;
}

// Iterator, adn its functions

template <class T> struct TContainer<T>::Iterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_tag = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    explicit Iterator(pointer ptr) : it_ptr(ptr) {}

    reference operator*() const {return *it_ptr;}
    pointer operator->() {return it_ptr;}

    Iterator& operator++() {it_ptr++; return *this;}
    Iterator operator++(int) {Iterator temp = *this; ++(*this); return temp;}

    Iterator& operator--() {it_ptr--; return *this;}
    Iterator operator--(int) {Iterator temp = *this; --(*this); return temp;}

    friend bool operator==(const Iterator& a, const Iterator& b) {return a.it_ptr == b.it_ptr;}
    friend bool operator !=(const Iterator& a, const Iterator& b) {return a.it_ptr != b.it_ptr;}

private:
    pointer it_ptr;
};

template<class T>
typename TContainer<T>::Iterator TContainer<T>::begin() {
    if (this->isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot use iterator on an empty TContainer");
    }
    return TContainer::Iterator(&vars[0]);
}

template<class T>
typename TContainer<T>::Iterator TContainer<T>::end() {
    if (this->isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot use iterator on an empty TContainer");
    }
    return TContainer::Iterator(&vars[this->num]);
}

template<class T>
typename TContainer<T>::Iterator TContainer<T>::rbegin() {
    if (this->isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot use iterator on an empty TContainer");
    }
    return TContainer::Iterator(&vars[num - 1]);
}

template<class T>
typename TContainer<T>::Iterator TContainer<T>::rend() {
    if (this->isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot use iterator on an empty TContainer");
    }
    return TContainer::Iterator(&vars[-1]); // BRUH??????
}




#endif //PROG2_NHF_TCONTAINER_HPP
