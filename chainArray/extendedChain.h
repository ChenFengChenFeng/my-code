#ifndef extendedChain_
#define extendedChain_

#include <iostream>
#include <sstream>
#include <string>
#include "extendedLinearList.h"
#include "chainWithIterator.h"
// #include "myChain.h"

using namespace std;
// template<class T> class extendedChain;
// template<class T> void meld(extendedChain<T>& a, extendedChain<T>& b);
// template<class T> void merge(const extendedChain<T>& a, const extendedChain<T>& b);
// template<class T> void split(const extendedChain<T>& a, const extendedChain<T>& b);

template<class T>
class extendedChain: public extendedLinearList<T>, public myChain<T> {
    template<class C>
    friend void meld(extendedChain<C>& a, extendedChain<C>& b);
    template<class C>
    friend void merge(extendedChain<C>& a, extendedChain<C>& b, extendedChain<C>& c);
    template<class C>
    friend void split(extendedChain<C>& a, extendedChain<C>& b, const extendedChain<C>& c);

    public:
        // constructor and copy constructor
        extendedChain(int initialCapacity = 10): myChain<T>(initialCapacity), lastNode(NULL) {}
        extendedChain(const extendedChain<T>& c): myChain<T>(c) {}
        ~extendedChain() {}

    // ADT methods
    bool empty() const override { return this -> listSize == 0;}
    int size() const override { return this -> listSize;}
    T& get(int theIndex) const override { return myChain<T>::get(theIndex);}

    /*
        return this->get(theIndex);这句话报错了
        分析下上述操作报错的原因：Segmentation fault (core dumped)
        因为在这里你使用的是this->get(theIndex)，而你是在get(theIndex)中使用的这个函数
        那么就会因为递归调用这个函数而产生错误!!!也就是上述的报错信息。
        方法2使用using，在你的public中首先声明
        using mychain<T>::get;
        return mychain<T>::get(theIndex);
        方法2是可以的。
        方法3，直接调用mychain<T>::get(theIndex);
        但是请注意，不用方法2，3直接调用get(theIndex)是错误的!!!为什么是这样的
        
        这里分析一下:
        1.Parsing of a template. This phase occurs when a template definition is first seen 
        by a compiler (point of definition [3]). During this phase, the lookup is completed
        only for nondependent names.
        2.Template instantiation. It happens when a template is instantiated, with template 
        parameters substituted by the actual template arguments (point of instantiation). 
        It is during this phase when the dependent names are looked up. 
        上述是关于模板类的两阶段查找名字的过程。用中文描述就是:
        1.模板定义阶段:刚被定义时，只有模板中独立的名字（可以理解为和模板参数无关的名字）参加查找
        2.模板实例化阶段：实例化模板代码时，非独立的名字才参加查找
        这个举个例子来说明一下:
        #include<iostream>
        using namespace std;

        template<typename T>
        class A
        {
            public:    
            void f() {   
                cout << "A::f()" << endl;    
            }
        };
        template<typename T>
        class B:public A<T>
        {
            public:   
            void  g()
            { 
                f();//报错，这样写的话
                this->f();//A::f()
                A<T>::f();//A::f()
            } 
        };
        int main(){
            B<int> b;
            b.g();
        }
        首先进入B的模板定义阶段，此时B的基类A<T>依赖于模板参数T，所以是一个非
        独立的名字。所以在这个阶段，对于B来说A<T>这个名字是不存在的，于是A<T>::f()
        也不存在。但此时这段代码仍旧是合法的，因为此时编译器可以认为f是一个非成员函数。
        当稍晚些时候进入B的模板实例化时，编译器已经坚持认为f是非成员函数，纵使此时
        已经可以查到A<T>::f()，编译器也不会去这么做。编译器会认为查找非成员函数没必要
        去基类里面查找，所以这个时候就会找不到f了。于是就会报错。找不到f(no delcaration)。
        那我们回过头来看this->f():
        1.模板定义阶段:尽管没法查到A<T>::f()，但明晃晃的this->告诉编译器，f是一个成员函数
        不是B类里，就是在B类的基类里，于是编译器记住了。
        2.模板实例化阶段：此时编译器查找的对象是一个成员函数，首先在B中查找，没有找到
        ；然后在基类里查找，于是成功找到A<T>::f()。所以不会报错了
        此分析来自:https://www.zhihu.com/question/31797003

    */

    int indexOf(const T& theElement) const override { return myChain<T>::indexOf(theElement);}
    void erase(int theIndex) override;
    void insert(int theIndex, const T& theElement) override;
    void clear() override {  // virtual 
        // Delete all nodes in myChain.
        while (this -> firstNode != NULL) {
            // delete firstNode
            chainNode<T>* nextNode = this -> firstNode -> next;
            delete this -> firstNode;
            this -> firstNode = nextNode;
        }
        this->listSize = 0;
        lastNode = NULL;
    }
    void push_back(const T& theElement);  // virtual
    void output(ostream& out) const { myChain<T>::output(out);}

    // additional method
    void zero() { this -> firstNode = NULL; this -> listSize = 0;}
    
    // friend void meld<>(extendedChain<T>& a, extendedChain<T>& b);
    void meld(extendedChain<T>& a, extendedChain<T>& b);
    void circularShift(int shiftCount);

    protected:
        chainNode<T>* lastNode;  // pointer to last node in myChain
};

template<class T>
void extendedChain<T>::erase(int theIndex) {
    // Delete the element whose index is theIndex.
    // Throw illegalIndex exception if no such element.
    this -> checkIndex(theIndex);

    // valid index, locate node with element to delete
    chainNode<T>* deleteNode;
    if (theIndex == 0) {
        // remove first node from myChain
        deleteNode = this -> firstNode;
        this -> firstNode = this -> firstNode -> next;
    }
    else {
        // use p to get to predecessor of desired node
        chainNode<T>* p = this -> firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
    
        deleteNode = p->next;
        p->next = p->next->next;  // remove deleteNode from myChain
        if (deleteNode == lastNode)
            lastNode = p;
    }
    this->listSize--;
    delete deleteNode;
}

template<class T>
void extendedChain<T>::insert(int theIndex, const T& theElement) { 
    // Insert theElement so that its index is theIndex.
    if (theIndex < 0 || theIndex > this -> listSize) {
        // invalid index
        ostringstream s;
        s << "index = " << theIndex << " size = " << this -> listSize;
        throw invalid_argument("invalid index");
    }

    if (theIndex == 0) {
        // insert at front
        this -> firstNode = new chainNode<T>(theElement, this -> firstNode);
        if (this->listSize == 0)
            lastNode = this -> firstNode;
    }
    else {
        // find predecessor of new element
        chainNode<T>* p = this -> firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
    
        // insert after p
        p->next = new chainNode<T>(theElement, p->next);
        if (this -> listSize == theIndex)
            lastNode = p -> next;
    }
    this->listSize++;
}

template<class T>
void extendedChain<T>::push_back(const T& theElement) {
    // Insert theElement at the end of the myChain.
    chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
    if (this -> firstNode == NULL)
        // myChain is empty
        this -> firstNode = lastNode = newNode;
    else {
        // attach next to lastNode
        lastNode -> next = newNode;
        lastNode = newNode;
    }
    this->listSize++;
}

template<class T>
void meld(extendedChain<T>& a, extendedChain<T>& b) {
    chainNode<T>* pa = a.myChain<T>::firstNode;
    chainNode<T>* pb = b.myChain<T>::firstNode;
    chainNode<T>* tempALastNode = nullptr;

    while (pa != NULL && pb != NULL) {
        pa -> next = new chainNode<T>(pb -> element, pa -> next);
        pb = pb -> next;
        pa = pa -> next;  // new pa
        tempALastNode = pa;
        a.myChain<T>::listSize++;
        
        pa = pa -> next;
    }  // 遍历a

    while (pb != NULL) {  // 遍历完a
        tempALastNode -> next = new chainNode<T>(pb -> element, tempALastNode -> next);
        pb = pb -> next;
        tempALastNode = tempALastNode -> next;
        a.lastNode = tempALastNode;
        a.myChain<T>::listSize++;
    }
    // delete tempALastNode;
}

// template<class T>
// void extendedChain<T>::meld(extendedChain<T>& a, extendedChain<T>& b) {
//     this -> clear();
//     int tempSize = std::min(a.size(), b.size()), i = 0;
//     chainNode<T>* pa = a.myChain<T>::firstNode;
//     chainNode<T>* pb = b.myChain<T>::firstNode;

//     this -> firstNode = new chainNode<T>(pa -> element);
//     chainNode<T>* p = this -> firstNode;
//     p -> next = new chainNode<T>(pb -> element);
//     p = p -> next;  // new head

//     pa = pa -> next;  // new head
//     pb = pb -> next;
    
//     while (i++ < (tempSize - 1)) {
//         cout << i << "\n";
//         p -> next = new chainNode<T>(pa -> element);
//         p = p -> next;
//         p -> next = new chainNode<T>(pb -> element);
//         p = p -> next;

//         pa = pa -> next;
//         pb = pb -> next;
//     }

//     while (pa != NULL) {
//         p -> next = new chainNode<T>(pa -> element);
//         p = p -> next;
//         pa = pa -> next;
//     }

//     while (pb != NULL) {
//         p -> next = new chainNode<T>(pb -> element);
//         p = p -> next;
//         pb = pb -> next;
//     }
    
//     this -> listSize = a.size() + b.size();
//     this -> lastNode = p;
//     p -> next = NULL;
//     a.myChain<T>::firstNode = NULL;
//     b.myChain<T>::firstNode = NULL;
//     a.myChain<T>::listSize = b.myChain<T>::listSize = 0;
// }


template<class T>
void extendedChain<T>::meld(extendedChain<T>& a, extendedChain<T>& b) {  // 使用a, b的节点空间
    // cout << "++++++++++++++++++";
    int tempSize = std::min(a.size(), b.size()), i = 0;
    this -> clear();

    // chainNode<T>* pa = a.myChain<T>::firstNode;
    // chainNode<T>* pb = b.myChain<T>::firstNode;

    // this -> firstNode = a.myChain<T>::firstNode;
    // chainNode<T>* p = this -> firstNode;  // pa
    // p -> next = b.myChain<T>::firstNode;
    // p = p -> next;

    // pa = pa -> next;
    // cout << "pa -> element: " << pa -> element;
    // pb = pb -> next;

    this -> firstNode = a.myChain<T>::firstNode;
    chainNode<T> *p = this -> firstNode;  // 让p指向本对象的firstNode
    // 然后让本地的firstNode指向a的第一个节点
    // pa和pb都指向a和b的头结点的下一个位置，为的是让可以让别人找到这个节点
    chainNode<T>* pa = a.myChain<T>::firstNode -> next;
    chainNode<T>* pb = b.myChain<T>::firstNode -> next;
    p -> next = b.myChain<T>::firstNode;  // 到这一步，已经进行了两个节点的合并了
    p = p -> next;  // 合并完了

    // while (i++ != (tempSize - 1)) {
    //     cout << "I am in";
    //     p -> next = pa;
    //     p = p -> next;
    //     p -> next = pb;
    //     p = p -> next;

    //     pa = pa -> next;
    //     pb = pb -> next;
    // }

    while (i++ != (tempSize - 1)) {
        std::cout << "\n 进入了while循环中" << "\n";
        a.myChain<T>::firstNode = pa;  // 得到最新的头结点
        b.myChain<T>::firstNode = pb;
        
        pa = pa -> next;  // 保留好下一个节点的位置
        pb = pb -> next;

        // 将两个链表当前的头结点进行合并
        p -> next = a.myChain<T>::firstNode;
        p = p -> next;
        p -> next = b.myChain<T>::firstNode;
        p = p -> next;
    }

    while (pa != NULL) {
        p -> next = pa;
        p = p -> next;
        pa = pa -> next;
    }

    while (pb != NULL) {
        p -> next = pb;
        p = p -> next;
        pb = pb -> next;
    }

    this -> listSize = a.myChain<T>::listSize + b.myChain<T>::listSize;
    a.myChain<T>::firstNode = NULL;
    b.myChain<T>::firstNode = NULL;
    a.myChain<T>::listSize = b.myChain<T>::listSize = 0;
}

template<class T>
void merge(extendedChain<T>& a, extendedChain<T>& b, extendedChain<T>& c) {
    c.clear();
    chainNode<T>* pa = a.myChain<T>::firstNode;
    chainNode<T>* pb = b.myChain<T>::firstNode;

    // 注意，对于空的firstNode，千万不能写成这样的
    // chainNode<T> *p = this->firstNode;因为这样的话，p仅仅是和
    // firstNode指向的位置一样，但是p->next = otherP;那么我的firstNode是没改变的
    // 只有firstNode是有值的时候，才是可以的，也就是对于这种合并的，我们
    // 必须先确保this->firstNode是有值的才可以

    if (pa -> element <= pb -> element) {
        c.myChain<T>::firstNode = new chainNode<T>(pa -> element);
        pa = pa -> next;
    }
    else {
        c.myChain<T>::firstNode = new chainNode<T>(pb -> element);
        pb = pb -> next;
    }

    chainNode<T>* pc = c.myChain<T>::firstNode;
    while (pa != NULL && pb != NULL) {
        if (pa -> element <= pb -> element) {
            pc -> next = new chainNode<T>(pa -> element);
            pc = pc -> next;
            pa = pa -> next;
        }
        else {
            pc -> next = new chainNode<T>(pb -> element);
            pc = pc -> next;
            pb = pb -> next;
        }
    }

    while (pa != NULL) {
        pc -> next = new chainNode<T>(pa -> element);
        pc = pc -> next;
        pa = pa -> next;
    }

    while (pb != NULL) {
        pc -> next = new chainNode<T>(pb -> element);
        pc = pc -> next;
        pb = pb -> next;
    }

    c.lastNode = pc;
    c.myChain<T>::listSize = a.size() + b.size();
}

template<class T>
void split(extendedChain<T>& a, extendedChain<T>& b, const extendedChain<T>& c) {
    chainNode<T>* pc = c.myChain<T>::firstNode;

    a.myChain<T>::firstNode = new chainNode<T>(pc -> element);
    pc = pc -> next;
    b.myChain<T>::firstNode = new chainNode<T>(pc -> element);
    pc = pc -> next;

    chainNode<T>* pa = a.myChain<T>::firstNode;
    chainNode<T>* pb = b.myChain<T>::firstNode;

    while (pc != NULL) {
        pa -> next = new chainNode<T>(pc -> element);
        pa = pa -> next;
        pc = pc -> next;
        if (pc != NULL) {
            pb -> next = new chainNode<T>(pc -> element);
            pb = pb -> next;
            pc = pc -> next;
        }
    }
    a.lastNode = pa;
    b.lastNode = pb;
    a.myChain<T>::listSize = (c.myChain<T>::listSize + 1) / 2;
    b.myChain<T>::listSize = (c.myChain<T>::listSize + 1) / 2;
}

template<class T>
void extendedChain<T>::circularShift(int shiftCount) {
    this -> checkIndex(shiftCount);
    chainNode<T>* p = this -> firstNode;
    int i = 0;

    // while (p != NULL && i < shiftCount) {
    //     lastNode -> next = new chainNode<T>(p -> element);
    //     lastNode = lastNode -> next;

    //     p = p -> next;  // new head
    //     i++;
    // }
    // this -> firstNode = p;

    while (p != NULL && i < shiftCount) {
        lastNode -> next = new chainNode<T>(this -> firstNode -> element);
        lastNode = lastNode -> next;  // new lastNode

        p = p -> next;
        this -> firstNode = p;  // new firstNode
        i++;
    }
}

#endif