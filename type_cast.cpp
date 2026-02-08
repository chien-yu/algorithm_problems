#include <iostream>

using namespace std;

int main()
{
    const int a = 5;
    const int* p = &a;
    int* ptr;
    ptr = const_cast<int*>(p);
    // int* p = const_cast<
    cout << *p << endl;
    return 0;
}