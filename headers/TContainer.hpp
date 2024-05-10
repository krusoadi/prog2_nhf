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
    void makePtr(int n);
    void checkIndex(int i);
    void resize(int n);

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

    [[nodiscard]] int size() const;

    // Other methods

    void clear();
    void swap(int n, int m);

    //Search by an independent identity, throws compile time error, if wrongly used.

    template<class Y> // Needed due to object-type independence (Share-OwnedShare comparison)
            int search(Y identity);

    // Iterator TODO RandomAccessIterator, BidirectionalIterator or ForwardIterator suits better?

    struct Iterator;

    // Iterator methods

    Iterator begin();
    Iterator end();

    Iterator rbegin();
    Iterator rend();

};

template<class T>
void TContainer<T>::resize(int n) {
    T* temp = new T[n];

    for (int i = 0; i < std::min(n, num); ++i) {
        temp[i] = this->vars[i];
    }
    delPtr();
    this->vars = temp;
    this->num = n;
}

template<class T>
void TContainer<T>::checkIndex(int i) {
    if (i > num) {
        throw Exceptions(EmptyContainer, "Over indexed TContainer, when adding a new element.");
    }
    if (i < 0) {
        throw Exceptions(NegativeIndex, "Negative Indexed when adding new element");
    }
}

template<class T>
void TContainer<T>::delPtr() {
    if (!isEmpty()) {
        delete[] this->vars;
        this->vars = nullptr;
    }
}

template<class T>
void TContainer<T>::makePtr(int n) {
    this->vars = new T[n];
}

template<class T>
TContainer<T>::TContainer(): vars(nullptr), num(0)  {}

template<class T>
TContainer<T>::TContainer(T first): num(1) {
    try {
        makePtr(num);
        this->vars[0] = first;
    } catch (std::bad_alloc &e) {
        std::cerr << e.what();
    }

}

template<class T>
TContainer<T>::TContainer(const TContainer<T> &other): num(other.num) {

    try {
        makePtr(num);
        for (int i = 0; i < num; ++i) {
            this->vars[i] = other.vars[i];
        }
    } catch (Exceptions &e) {
        delPtr();
        std::cerr << e.what();
    }
}

template<class T>
TContainer<T>::~TContainer() {
    delPtr();
}

template<class T>
void TContainer<T>::add_back(T newVar) {
    try {
        resize(this->num + 1);
        this->vars[num-1] = newVar;
    } catch (Exceptions &e) {
        delPtr();
        std::cerr << e.what();
    }
}

template<class T>
void TContainer<T>::add_front(T newVar) { // Maybe use resize, but that would be 2 loop.
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
    checkIndex(n);

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
    T retVal = this->vars[num-1];
    resize(num-1);
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
    checkIndex(n);

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
    checkIndex(n);
    return this->vars[n];
}

template<class T>
bool TContainer<T>::isEmpty() {
    return this->vars == nullptr;
}

template<class T>
int TContainer<T>::size() const {
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
template<class Y>
int TContainer<T>::search(Y identity) {
    if(this->isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot search in an empty Container.");
    }

    for (int i = 0; i < this->num; ++i) {
        if (this->vars[i] == identity) {
            return i;
        }
    }
    return -1; // Non-organic return value, means error.
}

// Iterator, and its functions

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

template<class T>
std::ostream& operator<<(std::ostream& stream, TContainer<T> &in) {
    for (int i = 0; i < in.size(); ++i) {
        stream << in[i] << "\n";
    }
    return stream;
}



#endif //PROG2_NHF_TCONTAINER_HPP
