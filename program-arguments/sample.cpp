#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Arguments number with program name is " << argc << "\n";
    for (int i = 0; i < argc; ++i) {
        cout << "argv[" << i << "] is " << argv[i] << "\n";
    }

    return 0;
}
