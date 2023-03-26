#ifndef moveLeftAndRightOnChain_
#define moveLeftAndRightOnChain_

#include <iostream>
#include "chainNode.h"
#include "linearList.h"
#include "extendedLinearList.h"
#include "extendedChain.h"

using namespace std;

template<class T>
class moveLeftAndRightOnChain : public linearList<T>, public chain<T> {
    public: 
        moveLeftAndRightOnChain(int initialCapacity = 10);  // chain<T>(initialCapacity);
        moveLeftAndRightOnChain(const moveLeftAndRightOnChain<T>& theList);
        ~moveLeftAndRightOnChain() {};

        void moveRight();
        void moveLeft();
        T& currentElement() const;
        T& previousElement() const;
    private:
        chainNode<T>* p;  // l -> next
        chainNode<T>* l;

};

template<class T>
moveLeftAndRightOnChain<T>::moveLeftAndRightOnChain(int initialCapacity = 10) {
    chain<T>(initialCapacity);
    p = this -> firstNode;
    l = nullptr;
}

template<class T>
moveLeftAndRightOnChain<T>::moveLeftAndRightOnChain(const moveLeftAndRightOnChain<T>& theList) {
    chain<T>(theList);
}

template<class T>
void moveLeftAndRightOnChain<T>::moveRight() {
    l = p;
    p = p -> next;
}

template<class T>
void moveLeftAndRightOnChain<T>::moveLeft() {
    p = l;
    chainNode<T>* temp = this -> firstNode;
    while (temp != NULL && temp -> next -> element != previousElement()) {
        temp = temp -> next;
    }
    l = temp;
}

template<class T>
T& moveLeftAndRightOnChain<T>::currentElement() const {
    return p -> element;
}

template<class T>
T& moveLeftAndRightOnChain<T>::previousElement() const {
    return l -> element;
}
#endif
