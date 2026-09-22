// Part 2 - Handling Dangling Pointers in Strings with OOP Recap

#include <iostream>
#include <string>
using namespace std;

class StringPool {
private:
    string* stringPool;   
    int currentSize;
    int maxSize;
    bool* removedFlags;  
public:
    // constructor - sets everything up and allocates our dynamic memory
    StringPool() {
        maxSize = 5;
        currentSize = 0;
        stringPool = new string[maxSize];
        removedFlags = new bool[maxSize];

        for (int i = 0; i < maxSize; i++) {
            removedFlags[i] = false;
        }
    }

    // destructor - free the memory we allocated in the constructor
    // (if we forgot this, the stringPool and removedFlags arrays would leak)
    ~StringPool() {
        delete[] stringPool;
        delete[] removedFlags;
        cout << "(StringPool destroyed, its arrays have been freed)" << endl;
    }

    // adds a string to the pool, if there is room left
    void addString(string s) {
        if (currentSize >= maxSize) {
            cout << "Pool is full! Can't add \"" << s << "\"." << endl;
            return;
        }
        stringPool[currentSize] = s;
        removedFlags[currentSize] = false;
        currentSize++;
        cout << "Added \"" << s << "\" to the pool." << endl;
    }
    void removeString(int index) {
        if (index < 0 || index >= currentSize) {
            cout << "That index doesn't exist in the pool." << endl;
            return;
        }
        if (removedFlags[index]) {
            cout << "That string was already removed." << endl;
            return;
        }

        cout << "Removed \"" << stringPool[index] << "\" from the pool, "
             << "but its memory is still hanging around..." << endl;
        removedFlags[index] = true;
    }
    void fixLeaks() {
        cout << "\nScanning the pool for leaked strings..." << endl;
        bool foundAny = false;

        for (int i = 0; i < currentSize; i++) {
            if (removedFlags[i]) {
                cout << "  -> freeing memory used by \"" << stringPool[i] << "\"" << endl;
                stringPool[i].clear();   // actually releases the string's memory
                foundAny = true;
            }
        }

        if (!foundAny) {
            cout << "  No leaked strings found." << endl;
        }
        cout << "Done fixing leaks.\n" << endl;
    }
    void showStatus() {
        cout << "\n----- Pool Status -----" << endl;
        for (int i = 0; i < currentSize; i++) {
            cout << "[" << i << "] ";
            if (removedFlags[i]) {
                cout << "(removed, leftover content = \"" << stringPool[i] << "\")";
            } else {
                cout << "\"" << stringPool[i] << "\"";
            }
            cout << endl;
        }
        cout << "------------------------\n" << endl;
    }
};
int main() {
    StringPool pool;

    // step 1: add a bunch of strings to the pool
    pool.addString("Hello");
    pool.addString("World");
    pool.addString("CS250");
    pool.addString("DataStructures");

    pool.showStatus();

    // step 2: remove a couple of strings WITHOUT freeing their memory
    pool.removeString(1);
    pool.removeString(2);

    pool.showStatus();

    // step 3: detect and fix the leak
    pool.fixLeaks();

    pool.showStatus();

    return 0;
}