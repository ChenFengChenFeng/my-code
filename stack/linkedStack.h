// linked implementation of a stack
// derives from the ADT stack

#ifndef linkedStack_
#define linkedStack_

#include "stack.h"
#include "chainNode.h"
#include <iostream>

using namespace std;

template<class T>
class linkedStack : public stack<T> {
    public:
        linkedStack(int initialCapacity = 10) {
            stackTop = nullptr;
            stackSize = 0;
        }

        ~linkedStack();

        bool empty() const {
            return stackSize == 0;
        }

        int size() const {
            return stackSize;
        }

        T& top() {
            if (stackSize == 0) {
                throw invalid_argument("invalid index"); 
            }
            return stackTop->element;
        }

        void pop();

        void push(const T& theElement) {
            stackTop = new chainNode<T>(theElement, stackTop);
            stackSize++;
        }
    private:
        chainNode<T>* stackTop;
        int stackSize;
};

template<class T>
linkedStack<T>::~linkedStack() {
    while (stackTop != nullptr) {
        chainNode<T>* nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
    }
}

template<class T>
void linkedStack<T>::pop() {
    if (stackSize == 0) {
        throw invalid_argument("invalid index");
    }
    chainNode<T>* nextNode = stackTop->next;
    delete stackTop;
    stackTop = nextNode;
    stackSize--;
}

#endif