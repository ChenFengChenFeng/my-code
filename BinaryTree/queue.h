// abstract class queue
// abstract data type specification for queue data structure
// all methods are pure virtual functions

#ifndef queue_
#define queue_

using namespace std;
template<class T>
class queue {
    public:
        virtual ~queue() {}
        virtual bool empty() const = 0;
        virtual int size() const = 0;
        virtual T& front() = 0;
        virtual T& back() = 0;

        // remove the front element
        virtual void pop() = 0;

        // add the element at the back of the queue
        virtual void push(const T& theElement) = 0;
};

#endif