#ifndef linearList_
#define linearList_
#include <iostream>

using namespace std;
template<class T>
class linearList
{
    public:
        virtual ~linearList() {};
        // return true if list is empty
        virtual bool empty() const = 0;

        // return number of elements in list
        virtual int size() const = 0;

        // return element whose index is theIndex
        virtual T& get(int theIndex) const = 0;

        // return index of first occurence of the Element
        virtual int indexOf(const T& theElement) const = 0;

        // remove the element whose index is theIndex
        virtual void erase(int theIndex) = 0;

        // insert theElement so that its index is theIndex
        virtual void insert(int theIndex, const T& theElement) = 0;

        // insert list into stream out
        virtual void output(ostream& out) const = 0;
};

#endif