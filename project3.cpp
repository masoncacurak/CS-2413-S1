// Project 3 
// CS 2413 Data Structures
// Spring 2023
// Mason Cacurak

#include <iostream>
#include <vector> 
#include <list> 

using namespace std;

class transaction {

int tID; // Transaction ID
int fromID; // Source ID
int toID; // Target ID
int tAmount; // How much is being transfered
string timeStamp; // Time of the transaction read from the input file

public:
// * Default constructor
transaction() {} 

// * Non default constructor
transaction(int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp) {
    tID = temptID;
    fromID = tempfromID;
    toID = temptoID;
    tAmount = temptAmount;
    timeStamp = temptimeStamp;
}

// * Getters
int getTransactionID() { return tID; }

int getFromID() { return fromID; }

int getTargetID() { return toID; }

int getTransactionAmount() { return tAmount; }

string getTimeStamp() { return timeStamp; }

};

class block {

int blockNumber; // Block number of the current block
int currentNumTransactions; // How many transactions are currently in the block
int maxNumTransactions; // How many maximum transactions can be in the block
vector<transaction> bTransactions; // Vector of transaction objects

public:
// * Default constructor
block() {}

// * Non default constructor
block(int bNumber, int maxTransactions) {
    blockNumber = bNumber;
    currentNumTransactions = 0;
    maxNumTransactions = maxTransactions;
    bTransactions = vector<transaction>(maxTransactions);
    cout << "Adding block #" << bNumber << endl;
}

// * Insert method to insert a new transaction into the vector bTransactions
void insert(transaction newTransaction) {
    if (currentNumTransactions < maxNumTransactions) {
        bTransactions[currentNumTransactions] = newTransaction;
        currentNumTransactions++;
    }
}

// * Getters
int getCurrentNumTransactions() { return currentNumTransactions; }

int getMaxNumTransactions() { return maxNumTransactions; }

vector<transaction> getTransactions() { return bTransactions; }

int getBlockNumber() { return blockNumber; }

};

class blockChain {
    
int currentNumBlocks; // Maintain the size of the list/block chain list
list<block> bChain; // Blockchain as a linked list
int numTransactionsPerBlock; // Number of transactions per block

public: 
// * Default constructor
blockChain() {}

// * Non default constructor
blockChain(int tPerB) {
    currentNumBlocks = 1;
    numTransactionsPerBlock = tPerB;
    block* b = new block(currentNumBlocks, tPerB);
    bChain.push_front(*b);
}

// * Insert method to insert new transaction into the block chain - add new block if existing block is full
void insertTransaction(transaction transactions) {
    if (bChain.front().getCurrentNumTransactions() == bChain.front().getMaxNumTransactions()) {
        block* newBlock = new block(currentNumBlocks + 1, numTransactionsPerBlock);
        newBlock->insert(transactions);
        bChain.push_front(*newBlock);
        currentNumBlocks++;
        cout << "Inserting transaction to block #" << currentNumBlocks << endl;
    }
    else {
        bChain.front().insert(transactions);
        cout << "Inserting transaction to block #" << currentNumBlocks << endl;
    }
}

// * Display method outputs current number of blocks, block number, number of transactions, and the transactions in each block
void display() {
    cout << "Current number of blocks: " << currentNumBlocks << endl;

    for (auto it = bChain.rbegin(); it != bChain.rend(); it++) {
        block currentBlock = *it;
        cout << "Block number: " << currentBlock.getBlockNumber() << " -- Number of Transaction: " << currentBlock.getCurrentNumTransactions() << endl;
        vector<transaction> transactions = currentBlock.getTransactions();

        for (int i = 0; i < currentBlock.getCurrentNumTransactions(); i++) {
            transaction currentTransaction = transactions[i];
            cout << currentTransaction.getTransactionID() << " " << currentTransaction.getFromID() << " " << currentTransaction.getTargetID() 
            << " " << currentTransaction.getTransactionAmount() << " " << currentTransaction.getTimeStamp() << endl;
        }
    }
}

};

int main() {

int numTransactionsPerBlock; // Max transactions per block
cin >> numTransactionsPerBlock;
cout << "Number of transactions per block: " << numTransactionsPerBlock << endl;

int totalNumTransactions; // Total transactions to be read from the input file
cin >> totalNumTransactions;
cout << "Total number of transactions: " << totalNumTransactions << endl;

// * Object of block chain
blockChain* b1 = new blockChain(numTransactionsPerBlock);

// * Insert transactions into the blockchain
int temptID;
int tempfromID;
int temptoID;
int temptAmount;
string temptimeStamp;

for (int i = 0; i < totalNumTransactions; ++i) {
    cin >> temptID;
    cin >> tempfromID;
    cin >> temptoID;
    cin >> temptAmount;
    cin >> temptimeStamp;
    transaction* t = new transaction(temptID, tempfromID, temptoID, temptAmount, temptimeStamp);
    b1->insertTransaction(*t);
}

// * Calls display method
b1->display();

return 0;

}

