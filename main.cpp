
#include <iostream>
#include "Search_Tree/Tree.cpp"

using namespace std;

int main() {

    compare(1000);
    compare(10000);
    compare(100000);

    MyTree MyTree1;
    MyTree1.insert(3);
    MyTree1.insert(5);
    MyTree1.insert(2);
    MyTree1.insert(1);

    MyTree MyTree2;
    MyTree2.insert(3);
    MyTree2.insert(11);
    MyTree2.insert(8);
    MyTree2.insert(2);

    cout << "MyTree1: ";
    MyTree1.print();
    std::cout << "MyTree2: ";
    MyTree2.print();

    cout << "Union: ";
    unification(MyTree1, MyTree2).print();

    cout << "Symmetric Difference: ";
    symmetricDifference(MyTree1, MyTree2).print();


    return 0;

}
