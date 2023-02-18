#ifndef _H
#define _H

using namespace std;

#define ARRAY_SIZE 100 // This is max length of token array, Do not worry about longer case. 
class Token{
    public:
        string symbol; // To store character or symbol
        string code;   // To store encoded version of symbol
        int count=0;   // To store frequency of symbol
};

class Node{
    public:
        Token token;
        Node *left;
        Node *right;
        Node *next;
};

class PriorityQueue{
    public:
        Node * head;
        void push(Node*);
        int token_count;
        PriorityQueue();
        Node *pop();
        void print_queue();
};

class HuffmanBinaryTree{
    public:
        Node * root;
        HuffmanBinaryTree();
        Node *merge(Node*,Node*);
        void print_binary_tree(Node *,int);
        void delete_postorder_traversal(Node *);
        ~HuffmanBinaryTree();
};


class Huffman{
    public:
        int token_count=0;
        Token token_array[ARRAY_SIZE];
        Node *priority_queue_head;
        PriorityQueue priority_queue;
        HuffmanBinaryTree huffman_binary_tree;
        void find_frequencies();
        void print_frequencies_and_codes();
        void get_priority_queue();
        void get_huffman_tree();
        void get_codes(Node*,string);
        double calculate_compression_ratio();
        string return_code(string);
    
    private:
        int findindex(Token *,string);                  // It returns the index of given string parameter in Token array
};
#endif