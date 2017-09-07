#include <iostream>
#include <memory>
using namespace std;

class Base {
    int a = 11;
    int b = 22;

protected:
    virtual int getB() {
        return b;
    }

public:
    virtual int getA() {
        return a;
    }

    virtual void printAll() = 0;

    virtual ~Base() {
        cout << "~base() is called" << "\n";
    }
};

class DerivePublic : public Base {
    int c = 33;
public:
    void printAll() {
        cout << "printAll of DerivePublic is called" << "\n";
        // cannot access a and b directly,
        // as they are private members of Base
        cout << "a: " << getA() << "\n";
        cout << "b: " << getB() << "\n";
        cout << "c: " << c << "\n";
    }
};

class DeriveProtected : protected Base {
    int c = 55;
    // getA is protected
    // getB is protected
public:
    void printAll() {
        cout << "printAll of DeriveProtected is called" << "\n";
        cout << "a: " << getA() << "\n";
        cout << "b: " << getB() << "\n";
        cout << "c: " << c << "\n";
    }
};

class DerivePrivate : private Base {
    int c = 77;
    // getA is private
    // getB is private
public:
    void printAll() {
        cout << "printAll of DerivePrivate is called" << "\n";
        cout << "a: " << getA() << "\n";
        cout << "b: " << getB() << "\n";
        cout << "c: " << c << "\n";
    }
};

int main()
{
    /**
     * Inheritance
     */
    {
    DerivePublic dp;
    cout << dp.getA() << "\n";
    // cannot access getB
    dp.printAll();
    // destructor is called here
    }

    {
    DeriveProtected dpp;
    // getA is protected same as getB
    // Can only be called in derviced class
    dpp.printAll();
    }

    {
    DerivePrivate dppp;
    // getA and getB are both private
    dppp.printAll();
    }

    /**
     * Polymorphism
     */
    // Error:
    // cannot cast 'DerivePrivate' to its private base class 'Base'
    // Base *bb = new DerivePrivate();
    // Error:
    // cannot cast 'DeriveProtected' to its protected base class 'Base'
    // Base *bb = new DeriveProtected();
    Base *bb = new DerivePublic();
    // printAll of DerivePublic is called
    bb->printAll();
    // must manually call destructor
    delete bb;

    // Error:
    // auto basePointer = unique_ptr<Base>(new DerivePrivate());
    // auto basePointer = unique_ptr<Base>(new DeriveProtected());
    // A pointer to Base class can only point to the public derived class
    auto basePointer = unique_ptr<Base>(new DerivePublic());
    basePointer->printAll();

    // Error:
    // Base base;
    // Can't instance an abstract class
    // As printAll() is defined as pure virtual function, Base is an abstract
    // class now

    return 0;
}
