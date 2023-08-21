// Data Structures Spring 2023
// CS 2413
// Mason Cacurak

#include <iostream> 
#include <time.h> // for experiments

using namespace std;

// Insertion sort method for sorting elements in array (couldn't get merge sort to work)
void sort(int arr[], int length) {
    int curr, x;
    for (int i = 1; i < length; i++) {
        curr = arr[i];
        x = i - 1;

        while (x >= 0 && arr[x] > curr) {
            arr[x + 1] = arr[x];
            x = x - 1;
        }
        arr[x + 1] = curr;
    }
}

// Binary search method for searching an array begining in the center of the data structure and then 
// dividing it in half until it finds the desired element (only for sorted arrays)
int binarySearch(int arr[], int lo, int hi, int x) {
      if (hi >= lo) {
            int middle = lo + (hi - lo) / 2;
 
            if (arr[middle] == x)
                  return middle;
 
            if (arr[middle] > x)
                  return binarySearch(arr, lo, middle - 1, x);
 
            return binarySearch(arr, middle + 1, hi, x);
    }
    return -1;
}

// Linear search method for searching through every element in the array sequentially, by iterating through 
// the read in array and comparing it to the target value
int linearSearch(int arr[], int length, int x) {
    for (int j = 0; j < length; j++)
        if (arr[j] == x)
            return j;
    return -1;
}

// Finds two elements in array that are the sum of a predetermined value
void sumNums(int arr[], int length, int x) {
    for (int i = 0; i < length; i++) {
        for (int k = i + 1; k < length; k++) {
            if (arr[i] + arr[k] == x) {
                cout << x << endl;
                cout << " = " << arr[i] << " + " << arr[k] << endl;
                return;
            }
        }
    }
    cout << x << endl;
    return;
}

// Removes predetermined value from array if it exists
int *removeB(int arr[], int length, int x) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == x) {
            for (int j = i; j < length; j++) {
                arr[j] = arr[j + 1];
            }
            cout << "Removing " << x << " at " << i << " in " << "B" << endl;
            return arr;
        }
    }
    cout << "Element " << x << "  not found in B" << endl;
    return arr;
}

// Removes predetermined value from array if it exists
int *removeA(int arr[], int length, int x) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == x) {
            for (int j = i; j < length; j++) {
                arr[j] = arr[j + 1];
            }
            cout << "Removing " << x << " at " << i << " in " << "A" << endl;
            return arr;
        }
    }
    cout << "Element " << x << "  not found in A" << endl;
    return arr;
}

// Inserts an element into array in sorted order
int *insertionB(int arr[], int length, int x) {
      cout << "Inserting " << x << " in B" << endl;
      int i;
      for (i = length - 1; (i >= 0 && arr[i] > x); i--) 
            arr[i + 1] = arr[i];
            arr[i + 1] = x;
        
      return arr;
}

// Inserts an element at the end of the array
int *insertionA(int arr[], int length, int x) {
    cout << "Inserting " << x << " in A" << endl;
    arr[length] = x;
    return arr;
}

// Method to print out array 
void printArr(int arr[], int length) {
    for (int j = 0; j < length; j++) {
        cout << arr[j] << " ";
    }
    cout << endl;
}

int main() {
      int maxValues; // max number of values to store / length of the arrays
      int currentValues; // as we add, the number of values in the arrays
      int tempVal; // variable used to read the number 
      cin >> maxValues; // read the maximum number of values from the redirected input file

      // Display length of array
      cout << "Length of the array: " << maxValues << endl;

      // Create dynamic array A of size maxValues and display the values in array A
      cout << "Array A: ";
      int *A = new int[maxValues];
      for (int i = 0; i < maxValues; i++) {
           cin >> tempVal; 
           A[i] = tempVal;
           cout << A[i] << " ";
      }
      cout << endl;

      // Create dynamic array B of size maxValues and store it in A
      int *B = new int[maxValues];
      for (int i = 0; i < maxValues; i++) {
            B[i] = A[i];
      }

      // Sort array B using insertion sort and display its values
      sort(B, maxValues);
      cout << "Array B: ";
      for (int i = 0; i < maxValues; i++) {
            cout << B[i] << " ";
      }
      cout << endl;
      cout << endl;

      // Find elements in array B by implementing the binary search method
      // and then display if the value was found and at what index
      cout << "Find:" << endl;
      cin.ignore(3);
      int length;
      cin >> length;
      int *findB = new int[length];
      for (int i = 0; i < length; i++) {
            cin >> tempVal;
            findB[i] = tempVal;
            if((binarySearch(B, 0, maxValues, tempVal)) != -1) {
                  cout << "Element " << tempVal << " found at " << binarySearch(B, 0, maxValues, tempVal) << " in B" << endl;
            }
            else {
                  cout << "Element " << tempVal << " not found in B" << endl;
            }
      }
      cout << endl;

      // Find elements in array A by implementing linear search method and then 
      // display if the values were found and at what index
      int *findA = new int[length];
      for (int i = 0; i < length; i++) {
            findA[i] = findB[i];
            tempVal = findA[i];
            if ((linearSearch(A, maxValues, tempVal)) != -1) {
                  cout << "Element " << tempVal << " found at " << linearSearch(A, maxValues, tempVal) << " in A" << endl;
            }
            else {
                  cout << "Element " << tempVal << " not found in A" << endl;
            }
      }
      cout << endl;

      // Find sumPairs of B by iterating through the dynamic array 
      // sumPairsB and calling the sumNums method 
      cout << "SumPairs:" << endl;
      cout << "B: " << endl;
      cin.ignore(3);
      int sumLength;
      cin >> sumLength;

      int *sumPairsB = new int[sumLength];
      for (int i = 0; i < sumLength; i++) {
            cin >> tempVal;
            sumPairsB[i] = tempVal;
            sumNums(B, maxValues, tempVal);
      }
      cout << endl;
      cout << endl;

      // Find sumPairs of A by iterating through the dynamic array 
      // sumPairsA and calling the sumNums method 
      cout << "A: " << endl;
      int *sumPairsA = new int[sumLength];
      for (int i = 0; i < sumLength; i++) {
            sumPairsA[i] = sumPairsB[i];
            tempVal = sumPairsA[i];
            sumNums(A, maxValues, tempVal);
      }
      cout << endl;
      cout << endl;
      
      // Remove elements from array B iterating through the dynamic array remB 
      // and calling the removeB method
      cout << "Remove:" << endl;
      int remLength;
      cin.ignore(3);
      cin >> remLength;

      int *remB = new int[remLength];
      for (int i = 0; i < remLength; i++) {
            cin >> tempVal;
            remB[i] = tempVal;
            removeB(B, maxValues, tempVal);
      }
      cout << endl;

      // Remove elements from array A by iterating through the dynamic array remA and calling 
      // the removeA method
      int *remA = new int[remLength];
      for (int i = 0; i < remLength; i++) {
            remA[i] = remB[i];
            tempVal = remA[i];
            removeA(A, maxValues, tempVal);
      }
      cout << endl;

      // Display the arrays values after removal of elements by calling printArr method
      maxValues = maxValues - remLength + 1;
      cout << "After removal Array A: ";
      printArr(A, maxValues);

      cout << "After removal Array B: ";
      printArr(B, maxValues);
      cout << endl;

      // Insert elements into array B by interating through the insertB dynamic array and 
      // calling the insertionB method
      cout << "Insert: " << endl;
      int insLength;
      cin.ignore(3);
      cin >> insLength;

      int *insertB = new int[insLength];
      length = maxValues;
      for (int i = 0; i < insLength; i++) {
            length++;
            cin >> tempVal;
            insertB[i] = tempVal;
            insertionB(B, length - 1, tempVal);
      }
      cout << endl;

      // Insert elements into array A by interating through the dynamic array insertA and
      // and calling the insertionA method
      int *insertA = new int[insLength];
      length = maxValues;
      for (int i = 0; i < insLength; i++) {
            insertA[i] = insertB[i];
            tempVal = insertA[i];
            insertionA(A, length, tempVal);
            length++;
      }
      cout << endl;

      // Display the arrays values after insertion of elements by calling the printArr method
      maxValues = maxValues + insLength;
      cout << "After insertions Array A: ";
      printArr(A, maxValues);

      cout << "After insertions Array B: ";
      printArr(B, maxValues);

      cout << endl;

      return 0;
}