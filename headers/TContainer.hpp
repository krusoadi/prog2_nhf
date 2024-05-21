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
    T *vars; // Stored variables
    int num; // Number of variables

    void delPtr(); // Deletes this->vars, if it isn't nullptr.
    void makePtr(int n); // Creates, an n long array-pointer and assigns to vars
    void checkIndex(int i) const; // Checks if the given index is valid, throws Exception if not.
    void resize(int n); // Resizes this->var, and puts back the old values.

public:
    // Constructors, Destructors

    TContainer();
    [[maybe_unused]] explicit TContainer(T first);
    TContainer(const TContainer<T> &other);
    ~TContainer();

    // Add and Pop methods

    void add_back(T newVar); // Adds a new element to the back of the array.
    [[maybe_unused]] void add_front(T newVar); // Adds a new element to the front of the array
    [[maybe_unused]] void add_index(T newVar, int n); // Inserts element to a given index.

    [[maybe_unused]] T pop_back(); // Gets the last element from vars, (also deletes)
    [[maybe_unused]] T pop_front(); // Gets the first element from vars, (also deletes)
    T pop_index(int n); // Gets the given indexed element from vars, (also deletes)

    // Operator Overloads
    T &operator[](int n) const;

    TContainer<T> &operator=(const TContainer<T> &other);

    // Status Check methods
    [[nodiscard]] bool isEmpty() const; // Checks if the vars is empty (nullptr)

    // Getters

    [[nodiscard]] int size() const; // returns this->num (size of the vars)

    // Other methods

    [[maybe_unused]] void clear(); // Clears the array and frees memory
    [[maybe_unused]] void swap(int n, int m); // Swaps two elements by the given index

    //Search by an independent identity, throws compile time error, if wrongly used.

    template<class Y> // Needed due to object-type independence (Share-OwnedShare comparison)
    int search(Y identity) const;

    // Iterator (BidirectionalIterator is more than enough)

    struct Iterator;

    // Iterator methods

    Iterator begin(); // Returns an iterator to the first element
    Iterator end(); // Returns an iterator to the last+1 element

    [[maybe_unused]] Iterator rbegin(); // Reversed begin
    [[maybe_unused]] Iterator rend(); // Reversed end

    // Const Iterator
    struct ConstIterator;

    [[maybe_unused]] ConstIterator cbegin() const; // Constant Iterator begin
    [[maybe_unused]] ConstIterator cend() const; // Constant Iterator end

    ConstIterator begin() const;
    ConstIterator end() const;

};

template<class T>
TContainer<T> &TContainer<T>::operator=(const TContainer<T> &other) {
    if (this != &other) {
        delPtr();

        num = other.num;
        makePtr(num);
        for (int i = 0; i < num; ++i) {
            vars[i] = other.vars[i];
        }
    }
    return *this;
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
void TContainer<T>::resize(int n) {
    T *temp = new T[n];

    for (int i = 0; i < std::min(n, num); ++i) {
        temp[i] = this->vars[i];
    }
    delPtr();
    this->vars = temp;
    this->num = n;
}

template<class T>
void TContainer<T>::checkIndex(int i) const {
    if (i > num) {
        throw Exceptions(OverIndex, "Over indexed TContainer, when adding a new element.");
    }
    if (i < 0) {
        throw Exceptions(NegativeIndex, "Negative Indexed when adding new element");
    }
}

template<class T>
TContainer<T>::TContainer(): vars(nullptr), num(0) {}

template<class T>
[[maybe_unused]] TContainer<T>::TContainer(T first): num(1) {
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
    resize(this->num + 1);
    this->vars[num - 1] = newVar;
}

template<class T>
[[maybe_unused]] void TContainer<T>::add_front(T newVar) {
    T *temp = new T[num + 1];
    temp[0] = newVar;

    for (int i = 0; i < num; ++i) {
        temp[i + 1] = this->vars[i];
    }
    num++;
    delPtr();
    this->vars = temp;

}

template<class T>
[[maybe_unused]] void TContainer<T>::add_index(T newVar, int n) {
    checkIndex(n);

    T *temp = new T[++num];

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
[[maybe_unused]] T TContainer<T>::pop_back() {
    if (isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot pop from an empty container (back).");
    }

    T retVal = this->vars[num - 1];
    resize(num - 1);
    return retVal;
}

template<class T>
[[maybe_unused]] T TContainer<T>::pop_front() {
    if (isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot pop from an empty container (front).");
    }

    T retVal = this->vars[0];
    T *temp = new T[--num];

    for (int i = 0; i < num; ++i) {
        temp[i] = this->vars[i + 1];
    }
    delPtr();
    this->vars = temp;
    return retVal;
}

template<class T>
T TContainer<T>::pop_index(int n) {
    if (isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot pop from an empty container (index).");
    }
    checkIndex(n);

    T retVal = this->vars[n];
    T *temp = new T[num - 1];

    bool reached_n = false;

    for (int i = 0; i < num; ++i) {
        if (n == i) {
            reached_n = true;
        } else if (!reached_n) {
            temp[i] = this->vars[i];
        } else {
            temp[i - 1] = this->vars[i];
        }
    }

    delPtr();
    this->vars = temp;
    num--;

    return retVal;
}

template<class T>
T &TContainer<T>::operator[](int n) const {
    if (isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot get an indexed item from an empty container.");
    }
    checkIndex(n);
    return this->vars[n];
}

template<class T>
bool TContainer<T>::isEmpty() const {
    return this->vars == nullptr;
}

template<class T>
int TContainer<T>::size() const {
    return this->num;
}

template<class T>
[[maybe_unused]] void TContainer<T>::clear() {
    delPtr();
    this->num = 0;
}

template<class T>
[[maybe_unused]] void TContainer<T>::swap(int n, int m) {
    checkIndex(n);
    checkIndex(m);
    if (n == m) {
        return;
    }

    T temp = this->vars[n];
    this->vars[n] = this->vars[m];
    this->vars[m] = temp;
}

template<class T>
template<class Y>
int TContainer<T>::search(const Y identity) const {
    if (this->isEmpty()) {
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

template<class T>
struct TContainer<T>::Iterator {
    using iterator_category = std::bidirectional_iterator_tag; // Iterator type
    using difference_tag = std::ptrdiff_t; // Difference of two iterator
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    explicit Iterator(pointer ptr) : it_ptr(ptr) {}

    // Returns the index where the iterator is
    difference_tag distance(Iterator other) { return std::distance(this->it_ptr, other.it_ptr); }

    reference operator*() const { return *it_ptr; }

    pointer operator->() { return it_ptr; }

    Iterator &operator++() {
        it_ptr++;
        return *this;
    }

    Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    Iterator &operator--() {
        it_ptr--;
        return *this;
    }

    Iterator operator--(int) {
        Iterator temp = *this;
        --(*this);
        return temp;
    }

    friend bool operator==(const Iterator &a, const Iterator &b) { return a.it_ptr == b.it_ptr; }

    friend bool operator!=(const Iterator &a, const Iterator &b) { return a.it_ptr != b.it_ptr; }

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
[[maybe_unused]] typename TContainer<T>::Iterator TContainer<T>::rbegin() {
    if (this->isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot use iterator on an empty TContainer");
    }
    return TContainer::Iterator(&vars[num - 1]);
}

template<class T>
[[maybe_unused]] typename TContainer<T>::Iterator TContainer<T>::rend() {
    if (this->isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot use iterator on an empty TContainer");
    }
    return TContainer::Iterator(&vars[-1]);
}

template<class T>
struct TContainer<T>::ConstIterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_tag = std::ptrdiff_t;
    using value_type = T;
    using pointer = const T *;
    using reference = const T &;

    explicit ConstIterator(pointer ptr) : it_ptr(ptr) {};

    difference_tag distance(ConstIterator other) { return std::distance(this->it_ptr, other.it_ptr); }

    reference operator*() const { return *it_ptr; }

    pointer operator->() const { return it_ptr; }

    ConstIterator &operator++() {
        it_ptr++;
        return *this;
    }

    ConstIterator operator++(int) {
        ConstIterator temp = *this;
        ++(*this);
        return temp;
    }

    ConstIterator &operator--() {
        it_ptr--;
        return *this;
    }

    ConstIterator operator--(int) {
        ConstIterator temp = *this;
        --(*this);
        return temp;
    }

    friend bool operator==(const ConstIterator &a, const ConstIterator &b) { return a.it_ptr == b.it_ptr; }

    friend bool operator!=(const ConstIterator &a, const ConstIterator &b) { return a.it_ptr != b.it_ptr; }

private:
    pointer it_ptr;
};

template<class T>
[[maybe_unused]] typename TContainer<T>::ConstIterator TContainer<T>::cbegin() const {
    if (this->isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot use const iterator on an empty TContainer");
    }
    return TContainer::ConstIterator(&vars[0]);
}

template<class T>
[[maybe_unused]] typename TContainer<T>::ConstIterator TContainer<T>::cend() const {
    if (this->isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot use const iterator on an empty TContainer");
    }
    return TContainer::ConstIterator(&vars[this->num]);
}

template<class T>
typename TContainer<T>::ConstIterator TContainer<T>::begin() const {
    if (this->isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot use const iterator on an empty TContainer");
    }
    return TContainer::ConstIterator(&vars[0]);
}

template<class T>
typename TContainer<T>::ConstIterator TContainer<T>::end() const {
    if (this->isEmpty()) {
        throw Exceptions(EmptyContainer, "Cannot use const iterator on an empty TContainer");
    }
    return TContainer::ConstIterator(&vars[this->num]);
}

template<class T>
std::ostream &operator<<(std::ostream &stream, TContainer<T> &in) {
    for (int i = 0; i < in.size(); ++i) {
        stream << in[i] << "\n";
    }
    return stream;
}


#endif //PROG2_NHF_TCONTAINER_HPP
