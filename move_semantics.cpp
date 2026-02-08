#include <iostream>

#include <cstring>
// #include <algorithm>

class string
{
    char* data;

public:

    string(const char* p)
    {
        std::cout << "Create! lvalue pointer: " << static_cast<const void*>(p) << std::endl;
        size_t size = std::strlen(p) + 1;
        data = new char[size];
        std::memcpy(data, p, size);
    }

        ~string()
    {
        delete[] data;
    }

    string(const string& that)
    {
        std::cout << "Copy! lvalue string pointer: " << static_cast<const void*>(&that) << std::endl;
        size_t size = std::strlen(that.data) + 1;
        data = new char[size];
        std::memcpy(data, that.data, size);
    }

    void dump()
    {
        std::cout << data << std::endl;
    }

    string(string&& that)   // string&& is an rvalue reference to a string
    {
        std::cout << "rvalue pointer: " << &that << std::endl;
        data = that.data;
        that.data = nullptr;
    }
};

string& f()
{
    char y[10] = "gggggg7";
    static string b(y);
    return b;
}

int main()
{
    char x[10] = "abcde10";
    string a(x);
    a.dump();
    string c("cccccc8");
    c.dump();
    string d(f());
    d.dump();
    string e((string&&)string("rrrrrr7"));
    e.dump();
    string f(std::move(string("rrrrrr9")));
    f.dump();
    return 0;
}