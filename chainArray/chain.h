#ifndef chain_
#define chain_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "chainNode.h"
#include "linearList.h"

using namespace std;
template<class T> class chain;
template<class T> bool operator==(const chain<T>& left, const chain<T>& right);
template<class T> bool operator!=(const chain<T>& left, const chain<T>& right);
template<class T> bool operator<(const chain<T>& left, const chain<T>& right);

template<class T>
class chain: public linearList<T> {
    public:
        chain(int initialCapacity = 10);
        chain(const chain<T>&);
        ~chain();

        // ADT
        bool empty() const { return listSize == 0; }
        int size() const { return listSize; }
        T& get(int theIndex) const;
        int indexOf(const T& theElement) const;
        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);
        void output(ostream& out) const;
        void shiftLeft(int shiftNum);
        void removeRange(int fromIndex, int toIndex);
        void set(int theIndex, int theElement);
        int lastIndexOf(int theElement);

        T& operator[](int index) const;
        // template<class U>
        friend bool operator==<>(const chain<T>& left, const chain<T>& right);
        friend bool operator!=<>(const chain<T>& left, const chain<T>& right);
        friend bool operator< <>(const chain<T>& left, const chain<T>& right);

        void swap(chain<T>& myList);
        // void chainToArray(const chain<T>& myList);
        // chainNode<T>* reverse(chainNode<T>* head);
        chainNode<T>* firstNode;
        void reverse();

    protected:
        void checkIndex(int theIndex) const;
        // chainNode<T>* firstNode;
        int listSize;
};


template<class T>
chain<T>::chain(int initialCapacity) {
    // 构造
    if (initialCapacity == 0) {
        ostringstream s;
        s << "initialCapacity = " << initialCapacity << "Must be > 0";
    }
    firstNode = NULL;
    listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T>& theList) {
    // copy constructor
    listSize = theList.listSize;
    if (listSize == 0) {
        firstNode = NULL;
    }

    // non-empty list
    chainNode<T>* sourceNode = theList.firstNode;

    // node in theList to copy from
    firstNode = new chainNode<T>(sourceNode -> element);

    // copy first element of theList
    sourceNode = sourceNode -> next;
    chainNode<T>* targetNode = firstNode;

    // current last node in *this
    while (sourceNode != NULL) {   
        // copy remaining elements
        targetNode->next = new chainNode<T>(sourceNode -> element);
        targetNode = targetNode -> next;
        sourceNode = sourceNode -> next;
    }
    targetNode->next = NULL;  // end the chain
}

template<class T>
chain<T>::~chain() {
    while (firstNode != NULL) {
        chainNode<T>* nextNode = firstNode -> next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class T>
void chain<T>::checkIndex(int theIndex) const {
    // Verify that theIndex is between 0 and listSize - 1.
    if (theIndex < 0 || theIndex >= listSize)
    {   
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw invalid_argument("invalid index");
        // throw illegalIndex(s.str());
    }

}

template<class T>
T& chain<T>::get(int theIndex) const {
    // Return element whose index is theIndex.
    // Throw illegalIndex exception if no such element.
    checkIndex(theIndex);

    // move to desired node
    chainNode<T>* currentNode = firstNode;
    for (int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;

    return currentNode->element;
}

template<class T>
int chain<T>::indexOf(const T& theElement) const {
    // Return index of first occurrence of theElement.
    // Return -1 if theElement not in list.

    // search the chain for theElement
    chainNode<T>* currentNode = firstNode;
    int index = 0;  // index of currentNode
    while (currentNode != NULL && currentNode->element != theElement)
    {
        // move to next node
        currentNode = currentNode->next;
        index++;
    }

    // make sure we found matching element
    if (currentNode == NULL)
        return -1;
    else
        return index;
}

template<class T>
void chain<T>::erase(int theIndex) {
    // Delete the element whose index is theIndex.
    // Throw illegalIndex exception if no such element.
    checkIndex(theIndex);

    // valid index, locate node with element to delete
    chainNode<T>* deleteNode = nullptr;
    if (theIndex == 0)
    {   
        // remove first node from chain
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else 
    {   
        // use p to get to predecessor of desired node
        chainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
    
        deleteNode = p->next;
        p->next = p->next->next; // remove deleteNode from chain
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void chain<T>::insert(int theIndex, const T& theElement) {
    if (theIndex < 0 || theIndex > listSize) {
        // invalid index
        ostringstream s;
        s << "index = " << theIndex << "size = " << listSize;
    }

    if (theIndex == 0) {
        // front
        firstNode = new chainNode<T>(theElement, firstNode);
    }
    else {  // find predecessor of new element
        chainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p -> next;
        }
        
        // insert after p
        p -> next = new chainNode<T>(theElement, p -> next);
    }
    listSize++;
}

template<class T>
void chain<T>::output(ostream& out) const {
    // Put the list into the stream out.
    for (chainNode<T>* currentNode = firstNode;
                        currentNode != NULL;
                        currentNode = currentNode->next)
        out << currentNode->element << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const chain<T>& x)
    { x.output(out); return out; }


template<class T>
void chain<T>::shiftLeft(int shiftNum) {

    if (shiftNum == 0 || shiftNum > listSize) {
        cout << "Error shirtOperation!!!";
    }
    
    for (int i = 0; i < shiftNum; i++) {
        firstNode = firstNode -> next;
    }
    listSize = listSize - shiftNum;
    // return firstNode;
}

template<class T>
void chain<T>::removeRange(int fromIndex, int toIndex) {
    // remove element from fromIndex to toIndex
    checkIndex(fromIndex);
    checkIndex(toIndex);

    chainNode<T>* pre = new chainNode<T>(0, firstNode);  // 申请虚拟头结点
    
    for (int i = -1; i < fromIndex - 1; i++) {
        pre = pre -> next;
    }

    chainNode<T>* p = pre;
    for (int i = 0; i < toIndex - fromIndex + 1; i++) {
        p = p -> next;
    }

    pre -> next = p -> next;
    if (fromIndex == 0)
        firstNode = pre -> next;
    listSize = listSize - (toIndex - fromIndex + 1);
}

template<class T>
void chain<T>::set(int theIndex, int theElement) {
    // set theIndex`s element to theElement
    checkIndex(theIndex);
    chainNode<T>* currentNode = firstNode;
    for (int i = 0; i < theIndex; i++) {
        currentNode = currentNode -> next;
    }
    currentNode -> element = theElement;
}

template<class T>
int chain<T>::lastIndexOf(int theElement) {
    // the index of theElement that last occurs
    int index = -1;
    vector<int> temp;

    chainNode<T>* p = firstNode;
    while (p != NULL) {
        if (p -> element == theElement) {
            temp.push_back(index + 1);
            // cout << "index + 1 = " << index + 1 << "\n";
        }
        p = p -> next;
        index = index + 1;
    }
    return temp.at(temp.size() - 1);
}

template<class T>
T& chain<T>::operator[](int index) const {
    checkIndex(index);
    chainNode<T>* p = firstNode;
    int i = 0;
    while (p != NULL && i < index) {
        p = p -> next;
        i++;
    }
    return p -> element;
}

template<class T>
bool operator==(const chain<T>& left, const chain<T>& right) {
    if (left.listSize != right.listSize) {
        return false;
    }
    chainNode<T>* pleft = left.firstNode;
    chainNode<T>* pright = right.firstNode;

    while (pleft != NULL) {
        if (pleft -> element != pright -> element) {
            return false;
        }
        pleft = pleft -> next;
        pright = pright -> next;
    }
    return true;
}

template<class T>
bool operator!=(const chain<T>& left, const chain<T>& right) {
    if (left.listSize != right.listSize) {
        return true;
    }
    chainNode<T>* pleft = left.firstNode;
    chainNode<T>* pright = right.firstNode;

    while (pleft != NULL) {
        if (pleft -> element != pright -> element) {
            return true;
        }
        pleft = pleft -> next;
        pright = pright -> next;
    }
    return false;
}

template<class T>
bool operator<(const chain<T>& left, const chain<T>& right) {
    chainNode<T>* pleft = left.firstNode;
    chainNode<T>* pright = right.firstNode;

    while (pleft != NULL) {
        if (pleft -> element <= pright -> element) {
            pleft = pleft -> next;
            pright = pright -> next;
        }
        else 
            return false;
    }
    return true;
}

template<class T>
void chain<T>::swap(chain<T>& myList) {
    chainNode<T>* p = firstNode;
    firstNode = myList.firstNode;
    myList.firstNode = p;

    int temp = listSize;
    listSize = myList.listSize;
    myList.listSize = temp;
}

// template<class T>
// void chain<T>::chainToArray(const chain<T>& myList) {
//     chainNode<T>* p = myList.firstNode;

// }

// template<class T>
// chainNode<T>* chain<T>::reverse(chainNode<T>* head) {
//     if (head == NULL || head -> next == NULL) {
//         return head;
//     }

//     chainNode<T>* newHead = reverse(head -> next);
//     cout << "I am in 1" << "\n";
//     head -> next -> next = head;
//     head -> next = nullptr;
//     return newHead;
// }

template<class T>
void chain<T>::reverse() {
    chainNode<T>* pre = nullptr;
    
    while (firstNode != NULL) {
        chainNode<T>* next = firstNode -> next;
        firstNode -> next = pre;
        pre = firstNode;
        firstNode = next;
    }
    firstNode = pre;
}




#endif