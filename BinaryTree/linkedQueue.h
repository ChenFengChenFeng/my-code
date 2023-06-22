// linked implementation of a queue
// drives from the ADT queue

#ifndef linkedQueue_
#define linkedQueue_

#include "queue.h"
#include "chainNode.h"
using namespace std;

template<class T>
class linkedQueue: public queue<T> {
    public:
        linkedQueue(int initialCapacity = 10) {
            queueFront = nullptr;
            queueSize = 0;
        }

        ~linkedQueue();

        bool empty() const {
            return queueSize == 0;
        }

        int size() const {
            return queueSize;
        }

        T& front() {
            if (queueSize == 0) {
                throw invalid_argument("invalid index");
            }
            return queueFront -> element;
        }

        T& back() {
            if (queueSize == 0) {
                throw invalid_argument("invalid index");
            }
            return queueBack -> element;
        }

        void pop();

        void push(const T&);
    private:
        chainNode<T>* queueFront;
        chainNode<T>* queueBack;
        int queueSize;
};

template<class T>
linkedQueue<T>::~linkedQueue() {
    while (queueFront != nullptr) {
        chainNode<T>* nextNode = queueFront -> next;
        delete queueFront;
        queueFront = nextNode;
    }
}

template<class T>
void linkedQueue<T>::pop() {
    if (queueFront == nullptr) {
        throw invalid_argument("invalid index");
    }
    
    chainNode<T>* nextNode = queueFront -> next;
    delete queueFront;
    queueFront = nextNode;
    queueSize--;
}

template<class T>
void linkedQueue<T>::push(const T& theElement) {
    chainNode<T>* newNode = new chainNode<T>(theElement, nullptr);
    if (queueSize == 0) {
        queueFront = newNode;  // queue empty
    }
    else {
        queueBack -> next = newNode;  // queue not empty
    }
    queueBack = newNode;
    queueSize++;
}


#endif