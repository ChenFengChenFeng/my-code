#include <iostream>
#include "chainNode.h"
#include "linearList.h"
#include "chain.h"
#include "extendedChain.h"

using namespace std;

int main() {
    // test constructor
    linearList<double> *x = new chain<double>;
    chain<int>y, z;
    // chain<double> *fc = new chain<double>;

    // test size
    cout << "Initial size of x, y, and z = "
            << x->size() << ", "
            << y.size() << ", "
            << z.size() << endl;

    // test empty
    if (x->empty()) cout << "x is empty" << endl;
    else cout << "x is not empty" << endl;
    delete x;

    if (y.empty()) cout << "y is empty" << endl;
    else cout << "y is not empty" << endl;

    // test insert
    y.insert(0, 2);
    y.insert(1, 6);
    y.insert(0, 1);
    y.insert(2, 4);
    y.insert(3, 5);
    y.insert(2, 3);
    cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
    cout << "Size of y = " << y.size() << endl;
    if (y.empty()) cout << "y is empty" << endl;
    else cout << "y is not empty" << endl;
    y.output(cout);
    cout << endl << "Testing overloaded <<" << endl;
    cout << y << endl;

    // test idnexOf
    int index = y.indexOf(4);
    if (index < 0) cout << "4 not found" << endl;
    else cout << "The index of 4 is" << index << endl;

    index = y.indexOf(7);
    if (index < 0) cout << "7 not found" << endl;
    else cout << "The index of 7 is" << index << endl;

    // test get
    cout << "Element with index 0 is " << y.get(0) << endl;
    cout << "Element with index 3 is " << y.get(3) << endl;

    // test erase
    y.erase(1);
    cout << "Element 1 erased" << endl;
    cout << "The list is" << y << endl;
    y.erase(2);
    cout << "Element 2 erased" << endl;
    cout << "The list is" << y << endl;
    y.erase(0);
    cout << "Element 0 erased" << endl;
    cout << "The list is" << y << endl;

    cout << "Size of y = " << y.size() << endl;
    if (y.empty()) cout << "y is empty" << endl;
    else cout << "y is not empty" << endl;

    // try {y.insert(-3, 0);}
    // catch (illegalIndex e)
    // {
    //     cout << "Illegal index exception" << endl;
    //     cout << "Insert index must be between 0 and list size" << endl;
    //     e.outputMessage();
    // }

    // test copy constructor
    chain<int> w(y);
    y.erase(0);
    y.erase(0);
    cout << "w should be old y, new y has first 2 elements removed" << endl;
    cout << "w is " << w << endl;
    cout << "y is " << y << endl;
    
    // a few more inserts, just for fun
    y.insert(0, 4);
    y.insert(0, 5);
    y.insert(0, 6);
    y.insert(0, 7);
    cout << "y is " << y << "\n" << endl;
    
    cout << "test function" << "\n" << endl;
    // test shiftoperation
    chain<int> fc;
    cout << "fc = " << &fc << "\n" << endl;
    fc.insert(0, 1);
    fc.insert(0, 2);
    fc.insert(0, 3);
    fc.insert(0, 4);
    fc.insert(0, 5);
    cout << "fc.size() = " << fc.size() << "\n" << endl;
    fc.output(cout);
    // cout << fc << endl;
    fc.shiftLeft(2);

    cout << "after shift2, new fc = " << fc << "\n" << endl;

    fc.insert(0, 10);
    fc.insert(0, 9);
    fc.shiftLeft(0);
    cout << "\n";
    cout << "after shift0, new fc = " << fc << "\n" << endl;
    cout << "\n";
    fc.shiftLeft(4);
    cout << "after shift4, new fc = " << fc << "\n" << endl;

    cout << "\n";

    // test remove from range
    chain<int> fc1;
    fc1.insert(0, 1);
    fc1.insert(0, 2);
    fc1.insert(0, 3);
    fc1.insert(0, 4);
    fc1.insert(0, 5);
    cout << "fc1 = " << fc1 << "\n";
    fc1.removeRange(0, 1);
    cout << "removeRange(0, 1) = " << fc1 << "\n";
    fc1.insert(0, 4);
    fc1.insert(0, 5);
    cout << "fc1 = " << fc1 << "\n";
    fc1.removeRange(1, 4);
    cout << "removeRange(1, 4) = " << fc1 << "\n";

    cout << "\n";
    // test setTheElement
    chain<int> fc2;
    fc2.insert(0, 1);
    fc2.insert(0, 2);
    fc2.insert(0, 3);
    fc2.insert(0, 4);
    fc2.insert(0, 5);
    // fc2.set(5, 100);
    fc2.set(0, 100);
    cout << "fc2 = " << fc2 << "\n";



    cout << "\n";
    // test lastIndexOf
    chain<int> fc3;
    fc3.insert(0, 2);
    fc3.insert(0, 2);
    fc3.insert(0, 3);
    fc3.insert(0, 4);
    fc3.insert(0, 5);
    cout << "fc3 = " << fc3 << "\n";
    int lastIndex = fc3.lastIndexOf(5);
    cout << "fc3LastIndexOf = " << lastIndex << "\n";

    int lastIndex2 = fc3.lastIndexOf(2);
    cout << "fc3LastIndexOf2 = " << lastIndex2 << "\n";


    cout << "\n";
    // test operator[]
    chain<int> fcOperator;
    fcOperator.insert(0, 2);
    fcOperator.insert(0, 2);
    fcOperator.insert(0, 3);
    fcOperator.insert(0, 4);
    fcOperator.insert(0, 5);
    cout << "fcOperator[3] = " << fcOperator[3] << "\n";
    cout << "fc3LastIndexOf[0] = " << fcOperator[0] << "\n";


    cout << "\n";
    // test operator[]
    chain<int> fcOperator2;
    fcOperator2.insert(0, 2);
    fcOperator2.insert(0, 2);
    fcOperator2.insert(0, 3);
    fcOperator2.insert(0, 4);
    fcOperator2.insert(0, 5);

    chain<int> fcOperator1;
    fcOperator1.insert(0, 3);
    fcOperator1.insert(0, 4);
    fcOperator1.insert(0, 5);
    fcOperator1.insert(0, 6);
    fcOperator1.insert(0, 7);

    cout << "fcOperator2 == fcOperator1: " << boolalpha;
    cout << (fcOperator2 == fcOperator1) << "\n";

    cout << "fcOperator2 != fcOperator1: " << boolalpha;
    cout << (fcOperator2 != fcOperator1) << "\n";

    chain<int> fcOperator3;
    fcOperator3.insert(0, 3);
    fcOperator3.insert(0, 2);
    fcOperator3.insert(0, 1);
    fcOperator3.insert(0, 4);
    fcOperator3.insert(0, 5);

    cout << "fcOperator1: " << fcOperator1 << "\n";
    cout << "fcOperator2: " << fcOperator2 << "\n";
    cout << "fcOperator3: " << fcOperator3 << "\n";

    cout << "fcOperator2 < fcOperator3: " << boolalpha;
    cout << (fcOperator2 < fcOperator3) << "\n";

    cout << "fcOperator2 < fcOperator1: " << boolalpha;
    cout << (fcOperator2 < fcOperator1) << "\n";

    cout << "\n";
    chain<int> fc5;
    fc5.insert(0, 3);
    fc5.insert(0, 2);
    fc5.insert(0, 1);
    fc5.insert(0, 4);
    fc5.insert(0, 5);
    cout << "fc5: " << fc5 << "\n";

    chain<int> fc4;
    fc4.insert(0, 1);
    fc4.insert(0, 3);
    fc4.insert(0, 4);
    fc4.insert(0, 5);
    fc4.insert(0, 6);
    cout << "fc4: " << fc4 << "\n";

    fc5.swap(fc4);
    cout << "afterSwap, fc5: " << fc5 << "\n";
    cout << "afterSwap, fc4: " << fc4 << "\n";

    cout << "----------test reverse----------" << "\n";
    chain<int> fc6;
    // fc6.insert(0, 1);
    // fc6.insert(0, 3);
    // fc6.insert(0, 4);
    fc6.insert(0, 5);
    fc6.insert(0, 6);
    fc6.insert(0, 8);
    fc6.insert(0, 7);
    cout << "fc6: " << fc6 << "\n";
    fc6.reverse();
    cout << "after reverse fc6: " << fc6 << "\n";

    cout << "----------test extendedChain----------" << "\n";
    extendedChain<int> fcExtendeda;
    extendedChain<int> fcExtendedb;
    extendedChain<int> fcExtendedc;
    
    fcExtendeda.insert(0, 1);
    fcExtendeda.insert(0, 3);
    fcExtendeda.insert(0, 4);
    cout << "fcExtendeda: " << fcExtendeda << "\n";

    fcExtendedb.insert(0, 7);
    fcExtendedb.insert(0, 6);
    fcExtendedb.insert(0, 5);
    cout << "fcExtendedb: " << fcExtendedb << "\n";

    meld(fcExtendeda, fcExtendedb);
    cout << "after meld, fcExtendeda: " << fcExtendeda << "\n";

    // fcExtendedc.insert(0, 20);
    // fcExtendedc.insert(0, 19);
    // fcExtendedc.insert(0, 18);
    fcExtendedc.push_back(17);
    cout << "fcExtendedc: " << fcExtendedc << "\n";
    meld(fcExtendedc, fcExtendedb);
    cout << "after meld, fcExtendedc: " << fcExtendedc << "\n";


    cout << "----------this.meld----------" << "\n";
    cout << "----------test extendedChain.meld----------" << "\n";
    extendedChain<int> fcExtendedd;
    extendedChain<int> fcExtendede;
    extendedChain<int> fcExtendedf;
    fcExtendedd.insert(0, 200);
    fcExtendedd.insert(0, 190);
    fcExtendedd.insert(0, 180);
    fcExtendedd.push_back(170);
    cout << "fcExtendedd: " << fcExtendedd << "\n";

    fcExtendede.push_back(100);
    fcExtendede.push_back(120);

    fcExtendedf.meld(fcExtendedd, fcExtendede);
    cout << "after meld, fcExtendedf: " << fcExtendedf << "\n";

    cout << "----------test extendedChain.merge----------" << "\n";
    extendedChain<int> fcExtendedg;
    extendedChain<int> fcExtendedh;
    extendedChain<int> fcExtendedi;
    fcExtendedg.insert(0, 2000);
    fcExtendedg.insert(0, 1900);
    fcExtendedg.insert(0, 1800);
    fcExtendedg.push_back(2100);
    cout << "fcExtendedg: " << fcExtendedg << "\n";

    fcExtendedh.push_back(1000);
    fcExtendedh.push_back(1200);

    merge(fcExtendedg, fcExtendedh, fcExtendedi);
    cout << "after merge, fcExtendedi: " << fcExtendedi << "\n";


    cout << "----------test extendedChain.split----------" << "\n";
    extendedChain<int> fcExtendedj;
    extendedChain<int> fcExtendedk;
    extendedChain<int> fcExtendedl;
    fcExtendedl.insert(0, 30);
    fcExtendedl.insert(0, 50);
    fcExtendedl.insert(0, 40);
    fcExtendedl.push_back(60);
    fcExtendedl.push_back(80);
    fcExtendedl.push_back(70);
    cout << "fcExtendedl: " << fcExtendedl << "\n";

    split(fcExtendedj, fcExtendedk, fcExtendedl);
    cout << "after merge, fcExtendedj: " << fcExtendedj << "\n";
    cout << "after merge, fcExtendedk: " << fcExtendedk << "\n";


    cout << "----------test extendedChain.circularShift----------" << "\n";
    extendedChain<int> fcExtendedm;
    fcExtendedm.insert(0, 30);
    fcExtendedm.insert(0, 50);
    fcExtendedm.insert(0, 40);
    fcExtendedm.push_back(60);
    fcExtendedm.push_back(80);
    fcExtendedm.push_back(70);
    cout << "fcExtendedm: " << fcExtendedm << "\n";

    fcExtendedm.circularShift(2);
    cout << "after merge, fcExtendedm: " << fcExtendedm << "\n";

    
    return 0;
}