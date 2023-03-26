#ifndef extendedLinearList_
#define extendedLinearList_

using namespace std;

template<class T>
class extendedLinearList: linearList<T> {
    public:
        virtual ~extendedLinearList() {}

        // empty the list
        virtual void clear() = 0;

        // insert theElement at end of list
        virtual void push_back(const T& theElement) = 0;
};
#endif