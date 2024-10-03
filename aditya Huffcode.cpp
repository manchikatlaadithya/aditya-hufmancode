#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Node structure for the Huffman Tree
struct HuffmanNode {
    char data; // character
    int freq;  // frequency of the character
    HuffmanNode *left, *right; // left and right child pointers

    // Constructor for creating a new node
    HuffmanNode(char data, int freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// Compare function for the priority queue (min-heap)
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->freq > r->freq); // Min-heap based on frequency
    }
};

// Recursive function to print Huffman codes in preorder traversal
void printCodes(HuffmanNode* root, string str, unordered_map<char, string>& huffmanCodes) {
    if (!root)
        return;

    // If this is a leaf node, store the code for the character
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = str;
        cout << "Character: " << root->data << ", Huffman Code: " << str << endl;
    }

    // Preorder traversal: root -> left -> right
    printCodes(root->left, str + "0", huffmanCodes);
    printCodes(root->right, str + "1", huffmanCodes);
}

// Function to build the Huffman Tree and print the codes
void buildHuffmanTree(string S, vector<int> freq) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    // Step 1: Create a leaf node for each character and add it to the min-heap
    for (int i = 0; i < S.size(); ++i) {
        minHeap.push(new HuffmanNode(S[i], freq[i]));
    }

    // Step 2: Build the Huffman Tree
    while (minHeap.size() != 1) {
        // Extract the two nodes with the smallest frequency
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency equal to the sum of the two nodes' frequencies
        HuffmanNode* top = new HuffmanNode('$', left->freq + right->freq);

        // Make the extracted nodes as the children of the new node
        top->left = left;
        top->right = right;

        // Add the new node to the min-heap
        minHeap.push(top);
    }

    // Step 3: The remaining node is the root of the Huffman Tree
    HuffmanNode* root = minHeap.top();

    // Step 4: Traverse the Huffman Tree and print the codes using preorder traversal
    unordered_map<char, string> huffmanCodes;
    printCodes(root, "", huffmanCodes);
}

int main() {
    string S = "abcdef";
    vector<int> freq = {5, 9, 12, 13, 16, 45};

    cout << "Building Huffman Tree and printing detailed Huffman Codes:\n" << endl;
    buildHuffmanTree(S, freq);
    
    return 0;
}
