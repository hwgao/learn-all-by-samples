#include <iostream>

// Diamond inheritance
// Refer to https://en.wikipedia.org/wiki/Virtual_inheritance
//                Base
//      Derive1         Derive2
//              Derive12
// To declare Derive1 and Derive2 as virtual inheritanced from Base:
// The inheritance structure becomes to Derive12 inheritanced from Base, Derive1 and Derive2
// And Base class will be constructed when instancing Derive12.

class Base {
protected:
    int data = 0;
public:
    // No default constructor anymore
    // Base(int d) : data{d} {}
    Base(int a) {
        std::cout << __FUNCTION__ << " is called\n";
        data = a;
    }
    virtual int read() { return data; }
    virtual void write(int d) { data = d; }
    virtual ~Base() {}
};

class Derive1 : public virtual Base {
public:
    // Calling Base class constructor will be skipped by compiler
    Derive1() : Base{10} {
        std::cout << __FUNCTION__ << " is called\n";
    }
    // as base class doesn't have default constructor,
    // must define a constructor here
    // Derive1() : Base{10} {}
    int read() {
        std::cout << "Derive1:read" << " is called" << "\n";
        return data;
    }
};

class Derive2 : public virtual Base {
public:
    // Calling Base class constructor will be skipped by compiler
    Derive2() : Base{20} {
        std::cout << __FUNCTION__ << " is called\n";
    }
    void write(int d) {
        std::cout << "Derive2:write" << " is called" << "\n";
        // Derive1::read is called
        read();
        data = d;
    }
};

// If Derive1 and Derive2 are not virtual inheritanted from Base,
// Derive12 will be an abstract class if Base is abstract
class Derive12 : public Derive1, public Derive2 {
public:
    Derive12() : Base{30} {
        std::cout << __FUNCTION__ << " is called\n";
    }
};

int main() {
    Derive12 drv12;
    // If Base isn't abstract and Derive1 and Derive2 are not virtual
    // inheritanted from Base, following error is reported.
    // Error: member 'write' found in multiple base classes of different types
    std::cout << drv12.read() << "\n";
    drv12.write(40);
    std::cout << drv12.read() << "\n";


    return 0;
}
