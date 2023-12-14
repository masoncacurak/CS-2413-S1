// Spring 2023
// Data Structures
// Project 2
// Mason Cacurak

#include <iostream>
#include <string>
#include <fstream> 

using namespace std;

class tableClass {

protected:
string** myTable; // 2D string array to store all values (strings and numbers)
string* DTarray; // 1D array to store the data types of each column
int noRows, noCols; // Number of rows and columns

public:
// * Constructor
tableClass() {}

// * Constructor
tableClass(int rows, int cols) {
    noRows = rows;
    noCols = cols;
    // Allocating memory to DTarray
    DTarray = new string[noCols];
    for (int i = 0; i < noCols; i++) {
        DTarray[i] = "";
    }
    // Allocating memory to myTable array
    myTable = new string* [noRows];
    for (int i = 0; i < noRows; i++) {
        myTable[i] = new string[noCols];
    }
}

// * Overload method
// Overload the [] operator to access a row in myTable
string* operator[] (int i) {
    return myTable[i];
}

// * File reading method 
// readCSV method iterates through each line in the file, parses commas and 
// stores parsed lines in the 2D array myTable as rows
void readCSV(string filename) {
    fstream file;
    file.open(filename);
    string line;
    string delim = ",";
    int noRows = 0;
    int noCols = 0;

    if (!file.is_open()) {
        cout << "Error opeing file" << endl;
    }
    if (file.is_open()) {
        while (getline(file, line)) {
            size_t index;
            string word;
            while ((index = line.find(delim, 0)) != string::npos) {
                word = line.substr(0, index);
                line.erase(0, index + delim.length());
                myTable[noRows][noCols] = word;
                noCols++;
            }
            myTable[noRows][noCols] = line;
            noCols = 0;
            noRows++;
        }
    }
}

// * DTarray copy method
void copyDTarray(string* arr) {
    for (int i = 0; i < noCols; i++) {
        DTarray[i] = arr[i];
    }
}

// * Display method 
// Prints out the data types stored in DTarray and then prints out myTable array in a table
void display() {
    for (int i = 0; i < noCols; i++) {
        cout << DTarray[i] << "\t";
    }
    cout << endl;
    for (int i = 0; i < noRows; i++) {
        for (int j = 0; j < noCols; j++) {
            cout << myTable[i][j] << "\t";
        }
        cout << endl;
    }
}

// * Sort the table
// Selection sort algorithm to sort myTable row wise based off of the column of index[0]
void sortTable() {
    string temp;
    for (int i = 0; i < noRows - 1; i++) {
        for (int j = i + 1; j < noRows; j++) {
            if (myTable[i][0] > myTable[j][0]) {
                for (int k = 0; k < noCols; k++) {
                    temp = myTable[i][k];
                    myTable[i][k] = myTable[j][k];
                    myTable[j][k] = temp;
                }
            }
        }
    }
}

// * Search record (str will be from the first column)
// Linear seearch algorithm to to search myTable at column index[0] and prints the whole row if querie value was found
string* searchRecord(string str) {
    for (int i = 0; i < noRows; i++) {
        if (myTable[i][0] == str) {
            cout << "Record found:" << endl;
            for (int j = 0; j < noCols; j++) {
                cout << myTable[i][j] << "\t";
            }
            cout << endl;
        }
    }
    return nullptr;
    cout << "Record not found" << endl;
}

// * Search value from table
// Search algorithm iterates through every row and column, and if the given value is found, it prints out 
// the index of rows and columns in which it was found 
void searchValue(string str) {
    bool found = false;
    double target = stod(str); 
    cout << "Searching for " << target << endl;
    for (int r = 0; r < noRows; r++) {
        for (int c = 0; c < noCols; c++) {
            double value;
            try {
                value = stod(myTable[r][c]); 
            } catch (invalid_argument e) {
                continue; 
            }
            if (value == target) {
                cout << "found in (" << r << ", " << c << ")" << endl;
                found = true;
            }
        }
    }
    if (!found) {
        cout << "Value not found" << endl;
    }
}

// * Returns the number of rows
int getNumberRows() {
  return noRows;
}

// * Returns the number of columns
int getNumberCols() {
  return noCols;
}

// * Prints and returns a tableClass object with a subset of columns from colLeft to colRight indices and all rows
tableClass* getColumns(int colLeft, int colRight) {
    int numCols = colRight - colLeft + 1;
    tableClass *cols = new tableClass(noRows, numCols);

    for (int i = colLeft; i < colRight; i++) {
        cols->DTarray[i] = DTarray[i + colLeft]; 
        cout << DTarray[i] << "\t"; 
    }
    cout << endl;

    for (int r = 0; r < noRows; r++) { 
        for (int c = colLeft; c < colRight; c++) {
            cols->myTable[r][c - colLeft] = myTable[r][c];
            cout << myTable[r][c] << "\t";
        }
        cout << endl;
    }
    return cols;
}

// * Prints and returns a tableClass with a subset of rows from rowTop to rowBottom indices and all columns
tableClass* getRows(int rowTop, int rowBottom) {
    int numRows = rowBottom - rowTop + 1;
    tableClass *rows = new tableClass(numRows, noCols);

    for (int i = 0; i < noCols; i++) {
        rows->DTarray[i] = DTarray[i]; 
        cout << DTarray[i] << "\t"; 
    }
    cout << endl;

    for (int r = rowTop; r < rowBottom; r++) {
        for (int c = 0; c < noCols; c++) {
        rows->myTable[r - rowTop][c] = myTable[r][c];
        cout << myTable[r][c] << "\t";
        }
        cout << endl;
    }
    return rows;
}

// * Finds and returns a tableClass with the data between the cols and rows given
// ! Somehow prints wrong col value for first 3 rows, but last 2 rows are correct
tableClass* getRowsCols(int colLeft, int colRight, int rowTop, int rowBottom) {
    int numRows = rowBottom - rowTop + 1;
    int numCols = colRight - colLeft + 1;
    tableClass *rowcol = new tableClass(numRows, numCols);

    for (int i = colLeft; i < colRight; i++) {
        rowcol->DTarray[i - colLeft] = DTarray[i]; 
        cout << DTarray[i] << "\t"; 
    }
    cout << endl;
    for (int r = rowTop; r < rowBottom; r++) {
        for (int c = colLeft; c < colRight; c++) {
            rowcol->myTable[r - rowTop][c - colLeft] = myTable[r][c];
            cout << myTable[r][c] << "\t";
        }
        cout << endl;
    }
    return rowcol;
}

// * Finds and returns the minVal of the given column
// findMin method iterates through a given column, begining with minVal set to maxVal, and then going 
// down the column and comparing minVal to the current val in the column
double findMin(int colNumber) {
    if (colNumber > noCols) {
        cout << "Column Number " << colNumber << " out of bounds" << endl;
    }
    double minVal = 9999;
    for (int r = 0; r < noRows; r++) {
        double val = stod(myTable[r][colNumber]);
        if (val < minVal) {
            minVal = val;
        }
    }
    cout << "Min of " << colNumber << " is " << minVal;
    cout << endl;
    return minVal;
}

// * Destructor
// Deallocating memory
~tableClass() {
    delete[] DTarray;
    
    for (int i = 0; i < noRows; i++) {
        delete[] myTable[i];
    }
    delete[] myTable;
}
};

int main() {

    int numRows, numCols;
    string fileName;
    char option;

    cin >> numRows >> numCols >> fileName;
    cout << "NumRows: " << numRows << endl;
    cout << "NumCols: " << numCols << endl;
    cout << "FileName: " << fileName << endl;

    tableClass* d = new tableClass(numRows, numCols);

    // * Read the file input name and call readCSV()
    d->readCSV("fileInput1.csv");

    d->sortTable();

    // * Read the data types and store in DTarray of d
    string* DTarray = new string[numCols];
    for (int i = 0; i < numCols; i++) {
        cin >> DTarray[i];
        d->copyDTarray(DTarray);
    }

    // * Start reading the options till the end of the file
    while(!cin.eof()) {
        string line;
        string str;
        string content;

        getline(cin, line);
        content += line + '\n';
        if (!line.empty()) {
            
            if (line[0] == 'D') { //// * Call display method
                d->display();
            }
            if (line[0] == 'F') {  // * Find and record row of query value
                d->searchRecord(line.substr(2));
            }
            // ! Incomplete... can't find 124.9 in myTable array
            if (line[0] == 'V') {  // * Call searchValue method
                string str = line.substr(2, line.length());
                d->searchValue(str);
            }
            if (line[0] == 'I') {  // * Call findMin method
                d->findMin(stod(line.substr(2)));
            }
            if (line[0] == 'C') {  // * Call getColumns method
                int colLeft = line.length();
                int colRight = line.length();
                colLeft = (stoi(line.substr(2)));
                colRight = (stoi(line.substr(4)));
                d->getColumns(colLeft, colRight);
            }
            if (line[0] == 'R') {  // * Call getRows method
                int rowBottom = line.length();
                int rowTop = line.length();
                rowBottom = (stoi(line.substr(4)));
                rowTop = (stoi(line.substr(2)));
                d->getRows(rowTop, rowBottom);
            }
            if (line[0] == 'S') {  // * Call getRowsCol method
                int colLeft = line.length();
                int colRight = line.length(); 
                int rowTop = line.length();
                int rowBottom = line.length();
                colLeft = (stoi(line.substr(2)));
                colRight = (stoi(line.substr(4)));
                rowTop = (stoi(line.substr(6)));
                rowBottom = (stoi(line.substr(8)));
                d->getRowsCols(colLeft, colRight, rowTop, rowBottom);
            }
        }
    }
    return 0;
}
