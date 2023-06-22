// binary tree traversal methods

#include <iostream>
#include "binaryTreeNode.h"
#include "linkedQueue.h"

using namespace std;

template <class T>
void visit(binaryTreeNode<T>* x) {
    cout << x -> element << "\n";
}

template <class T>
void preOrder(binaryTreeNode<T>* t) {
    if (t != nullptr) {
        visit(t);
        preOrder(t -> leftChild);
        preOrder(t -> rightChild);
    }
}

template <class T>
void inOrder(binaryTreeNode<T>* t) {
    if (t != nullptr) {
        inOrder(t -> leftChild);
        visit(t);
        inOrder(t -> rightChild);
    }
}

template <class T>
void postOrder(binaryTreeNode<T>* t) {
    if (t != nullptr) {
        postOrder(t -> leftChild);
        postOrder(t -> rightChild);
        visit(t);
    }
}

template <class T>
void levelOrder(binaryTreeNode<T>* t) {
    linkedQueue<binaryTreeNode<T>*> que;
    while (t != nullptr) {
        visit(t);  // visit t

        // put t`s children on queue
        if (t -> leftChild != nullptr) {
            que.push(t -> leftChild);
        }

        if (t -> rightChild != nullptr) {
            que.push(t -> rightChild);
        }

        // get next node to visit
        t = que.front();

        if (que.empty() == 0) {
            return;
        }
        que.pop();
    }
}

int main() {
    
    return 0;
}