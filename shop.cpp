/*
  Copyright 2018 wmik
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#define FILE_NAME "shop.dat"

using namespace std;

class Item {
private:
    char itemCode[20], itemName[20];
    double itemPrice;
public:
    void readItem() {
        cout << endl << "INPUT ITEM DETAILS" << endl;
        cout << "ITEM CODE: ";
        cin.getline(itemCode, 20);
        cout << "ITEM NAME: ";
        cin.getline(itemName, 20);
        cout << "ITEM PRICE: ";
        cin >> itemPrice;
    }
    void displayItem() {
        cout << left << setw(15) << itemCode
             << left << setw(15) << itemName
             << left << setw(15) << setprecision(4) << itemPrice << endl;
    }
    char *getItemCode() { return itemCode; }
};

int writeToFile(Item item, string filename) {
    item.readItem();
    fstream file;
    /// write to file
    file.open(filename, ios::out|ios::binary|ios::app);
    if (!file){
        cout << "Error writing file" << endl;
        return -1;
    }
    file.write((char*)&item,sizeof(item));
    file.close();
    cout << "SAVED..." << endl;
    return 0;
}

int readFromFile(string filename) {
    Item item;
    fstream file;
    file.open(filename,ios::in|ios::binary);
    if (!file){
        cout << "Error opening file" << endl;
        return -1;
    }
    if (file.read((char*)&item,sizeof(item))) {
        cout << endl
             << left << setw(15) << "ITEM CODE"
             << left << setw(15) << "ITEM NAME"
             << left << setw(15) << "ITEM PRICE" << endl;
        while(!file.eof()) {
            item.displayItem();
            file.read((char*)&item,sizeof(item));
        }
    }
    else {
        cout << "Error reading from file" << endl;
        return -1;
    }
    file.close();
    return 0;
}

int searchItemCode(string search, string filename) {
    Item item;
    ifstream file;
    file.open(filename,ios::in);
    if (!file){
        cout << "Error opening file" << endl;
        return -1;
    }
    if (file.read((char*)&item,sizeof(item))) {
        while (!file.eof()) {
            if (item.getItemCode() == search) {
                cout << endl
                     << left << setw(15) << "ITEM CODE"
                     << left << setw(15) << "ITEM NAME"
                     << left << setw(15) << "ITEM PRICE" << endl;
                item.displayItem();
                break;
            }
            file.read((char*)&item, sizeof(item));
        }
    }
    else {
        cout << "Error reading from file" << endl;
        return -1;
    }
    file.close();
    cout << endl;
    return 0;
}

int main()
{
    Item item;
    int menuItem;
    string search;
    cout << "**********SHOP PROGRAM**********" << endl;
    cout << "0: EXIT" << endl;
    cout << "1: ADD ITEM" << endl;
    cout << "2: DISPLAY ALL ITEMS" << endl;
    cout << "3: SEARCH ITEM" << endl;
    while (true) {
        cout << endl << "PLEASE SELECT AN OPTION: ";
        cin >> menuItem;
        switch(menuItem) {
        case 0:
            return 0;
        case 1:
            cin.ignore();
            writeToFile(item, FILE_NAME);
            break;
        case 2:
            readFromFile(FILE_NAME);
            break;
        case 3:
            cout << "\nSearch for item code: ";
            cin >> search;
            searchItemCode(search, FILE_NAME);
            break;
        default:
            cout << "\nERROR: Unknown selection" << endl;
            return 0;
        }
    }
    return 0;
}
