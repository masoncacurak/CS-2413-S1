// Project 4
// CS 2413 Data Structures
// Spring 2023
// Mason Cacurak

#include <iostream>
#include <vector> // For array of transactions and array of blockChains
#include <list> // For blockchain

using namespace std;

class transaction {

    int tID; // Transaction id
    int fromID; // Source ID
    int fromValue; // P4: how much funds does the source ID person have? If first time, then initialize with 100 coins 
    int toID; // Target ID
    int toValue; // P4: how much funds does the source ID person have? If first time, then initialize with 100 coins 
    int tAmount; // How much is being transfered
    string timeStamp; // Time of the transaction read from the input file

public:
// Default constructor
transaction() {}
    
// Non-default constructor - P4: default 100 for from and to values
transaction(int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp);

// Getters
int getTransactionID() { return tID; }
int getFromID() { return fromID; }
int getTargetID() { return toID; }
int getTransactionAmount() { return tAmount; }
string getTimeStamp() { return timeStamp; }
int getFromValue() { return fromValue; } 
int getToValue() { return toValue; } 
int getTAmount() { return tAmount;} 

// Display transaction method
void displayTransaction();

};

transaction::transaction(int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp) {
    tID = temptID;
    fromID = tempfromID;
    toID = temptoID;
    tAmount = temptAmount;
    timeStamp = temptimeStamp;
    fromValue = 100;
    toValue = 100;
}

// Display method for transaction class (outputs transactions in each block)
void transaction::displayTransaction() {
    cout << tID << " " << fromID << " " << fromValue << " " << toID << " " << toValue << " " << tAmount << " " << timeStamp << endl;
}

// * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class block {

    int blockNumber; // Block number of the current block
    int currentNumTransactions; // How many transactions are currently in the block 
    int maxNumTransactions; // How many maximum transactions can be in the block
    vector<transaction> bTransactions; // Vector of transaction objects

public:
// Default constructor
block() {}

// Non-default constructor
block(int bNumber, int maxTransactions) {
    blockNumber = bNumber;
    currentNumTransactions = 0;
    maxNumTransactions = maxTransactions;
    bTransactions = vector<transaction> (maxTransactions);
}

// Insert method to insert a new transaction
void insert(transaction transaction) {
    if (currentNumTransactions < maxNumTransactions) {
        bTransactions[currentNumTransactions] = transaction;
        currentNumTransactions++;
    }
}

// TODO: P4: search for an ID in the bTransaction vector
void searchTransactions() {}

// Getters
int getCurrentNumTransactions() { return currentNumTransactions; }
int getMaxNumTransactions() { return maxNumTransactions; }
vector<transaction> getTransactions() { return bTransactions; }
int getBlockNumber() { return blockNumber; }

};

// * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class blockChain {

    int currentNumBlocks; // Maintain the size of the list/block chain list
    list<block> bChain; // Blockchain as a linked list
    int numTransactionsPerBlock; // Number of transactions per block

public:
// Default constructor
blockChain() {}

// Non-default constructor
blockChain(int tPerB) {
    currentNumBlocks = 1;
    numTransactionsPerBlock = tPerB;
    block* b = new block(currentNumBlocks, tPerB);
    bChain.push_front(*b);
}

// Insert method to insert new transaction into the block chain - add new block if existing block is full
void insertTransaction(transaction transaction) {
    if (bChain.front().getCurrentNumTransactions() == bChain.front().getMaxNumTransactions()) {
        block* newBlock = new block(currentNumBlocks + 1, numTransactionsPerBlock);
        newBlock->insert(transaction);
        bChain.push_front(*newBlock);
        currentNumBlocks++;
        cout << "Inserting transaction to block #" << currentNumBlocks;
    }
    else {
        bChain.front().insert(transaction);
        cout << "Inserting transaction to block #" << currentNumBlocks;
    }
}

// Display method outputs current number of blocks, block number, and number of transactions (calls display method in transaction class)
void displayBlockChain() {
    cout << "Current number of blocks: " << currentNumBlocks << endl;

    for (auto it = bChain.rbegin(); it != bChain.rend(); it++) {
        block currentBlock = *it;
        cout << "Block number: " << currentBlock.getBlockNumber() << " -- Number of Transaction: " << currentBlock.getCurrentNumTransactions() << endl;
        vector<transaction> transactions = currentBlock.getTransactions();

        for (int i = 0; i < currentBlock.getCurrentNumTransactions(); i++) {
            transaction currentTransaction = transactions[i];
            currentTransaction.displayTransaction();
        }
    }
}

// TODO: P4: search for an ID across all blocks in bChain
void searchBlocks() {}

// Getters
list<block> getBlockChain() { return bChain; }

};

// * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class blockNetwork {

    int numNodes; // Maintain the number of nodes in the network
    vector<blockChain> allNodes; // Vector of all the blockChains in the network
    vector<int> u; // Edge list u node
    vector<int> v; // Edge list v node
    int numEdges;
    int numNodesInNetwork;

public:
// Default constructor
blockNetwork() {}

// Non-default constructor
blockNetwork(int numberOfNodes) {
    int numNodes = numberOfNodes;
    allNodes = vector<blockChain>(numberOfNodes);
    cin >> numEdges;
    u = vector<int> (numEdges);
    v = vector<int> (numEdges); 

    for (int i = 0; i < numEdges; i++) {
        cin >> u[i];
        cin >> v[i];
    }
}

// Insert method to insert new transaction into the block chain in a specific node
void insertNode(transaction transaction, int node) {
    allNodes[node].insertTransaction(transaction);
    cout << " in node " << node << endl;
}

// Insert method to insert blocks into allNodes vector 
void insertBlockChain(blockChain b) {
    for (int i = 0; i < allNodes.size(); i++) {
        allNodes[i] = b;
    }
}

// Display method for blockNetwork class (calls displayBlockChain)
void displayBlockNetwork(int node) {
    for (int i = 0; i <= node; i++) {
        cout << "~~~ Node " << i << ":" << endl;
        allNodes[i].displayBlockChain();
    }
}

};

// * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {

int numNodesInNetwork; // Number of nodes in the network
cin >> numNodesInNetwork;
cout << "Number of nodes: " << numNodesInNetwork << endl;

int numTransactionsPerBlock; // Max transactions per block
cin >> numTransactionsPerBlock;
cout << "Number of transactions per block: " << numTransactionsPerBlock << endl;

int totalNumTransactions; // Total transactions to be read from the input file
cin >> totalNumTransactions;
cout << "Total number of transactions: " << totalNumTransactions << endl;

// Object of blockNetwork
blockNetwork* n1 = new blockNetwork(numNodesInNetwork);

// Object of blockChain network
blockChain* b1 = new blockChain(numTransactionsPerBlock);

// Calls insertBlockChain method 
for (int i = 0; i < numNodesInNetwork  ; i++) {
    n1->insertBlockChain(*b1);
}

// Inputs the transaction information and inserts to blockNetwork object n1
int temptID;
int tempfromID;
int temptoID;
int temptAmount;
string temptimeStamp;
int node;
for (int i = 0; i < totalNumTransactions; i++) {
    cin >> node;
    cin >> temptID;
    cin >> tempfromID;
    cin >> temptoID;
    cin >> temptAmount;
    cin >> temptimeStamp;
    transaction* t = new transaction(temptID, tempfromID, temptoID, temptAmount, temptimeStamp);
    n1->insertNode(*t, node);
}

// Calls display method in blockNetwork class
n1->displayBlockNetwork(node);

return 0;

}