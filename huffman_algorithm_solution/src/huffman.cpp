#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include "huffman.h"

using namespace std;

int Huffman::findindex(Token *arr,string elem){
	for(int i=0;i<token_count;i++)
		if (i[arr].symbol == elem ) // a[b] == a+b = b[a]
			return i;
	return -1;
}

void Huffman::find_frequencies()
{
    int index = -1;
    ifstream file_obj; //object to read file
    file_obj.open("../input.txt",ifstream::in);
    char symbol = 0;
    if (!file_obj.is_open()) {
        file_obj.open("input.txt",ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }
    while (file_obj.get(symbol)) 
    {
        string s;
        s.push_back(symbol);
	index=findindex(token_array,s);// find index of element in array
       
	if(index!=-1){		                // increase count			
	    token_array[index].count++;
	}
	else{                               // add array
	    token_array[token_count].symbol = s;
	    token_array[token_count].count=1;					
	    token_count++;
	}
    }
    file_obj.close();
}

PriorityQueue::PriorityQueue()
{
    head = NULL;
    token_count = 0;
}

void PriorityQueue::push(Node *newnode)
{
	if(head==NULL)
	{
		head = newnode;
	}
	else 
	{        
        Node *traversal = head;	
        Node *previous = NULL;
        while (traversal && traversal->token.count < newnode->token.count)
        {
            previous = traversal;
            traversal = traversal->next;
        }
        if (previous==NULL) // we are adding as head 
        {
            newnode->next = traversal;
            head = newnode;
        }
        else //we are adding the newnode between two other nodes or adding to last node
        {
            newnode->next = previous->next;
            previous->next = newnode;
        }    
    }
    token_count++;
}

Node* PriorityQueue::pop()
{
    if(token_count>0)
    {
        Node *target = head;
        head = head ->next;
        token_count--;
        return target;
    }
    else
        return NULL;
}

void PriorityQueue::print_queue()
{
    Node * traversal = head;
    while (traversal)
    {
        cout<<traversal->token.symbol<<"("<<traversal->token.count<<")"<<"-->";
        traversal = traversal->next;
    }
    cout<<endl;
}

HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = NULL;
}

Node * HuffmanBinaryTree::merge(Node *node1, Node *node2)
{
    Node * newnode = new Node();
    newnode->token.symbol = node1->token.symbol + node2->token.symbol;
    newnode->token.count = node1->token.count + node2->token.count; 
    newnode->left = node1;
    newnode->right = node2;
    return newnode;
}

void HuffmanBinaryTree::print_binary_tree(Node *traversal,int level)
{
    cout<<level<<"\t";
    for (int i=0;i<level;i++)
        cout<<"\t"; 
    cout<<traversal->token.symbol<<"("<<traversal->token.count<<")"<<endl;

    if(traversal->left)
    {
        print_binary_tree(traversal->left,level+1);
    }    
    if(traversal->right)
    {
        print_binary_tree(traversal->right,level+1);
    }
}

void HuffmanBinaryTree::delete_postorder_traversal(Node *traversal)
{
    if(traversal!=NULL) 
    {
        delete_postorder_traversal(traversal->left);
        delete_postorder_traversal(traversal->right);
        delete traversal;
    }
}

HuffmanBinaryTree::~HuffmanBinaryTree()
{
    delete_postorder_traversal(root);
    cout<<"Code with no memory leak ;)"<<endl;
    root = NULL;
}

void Huffman::print_frequencies_and_codes()
{
    cout<<"TOKEN"<<"\t"<<"FREQUENCY"<<"\t"<<"CODE"<<endl;
    for(int i=0;i<token_count;i++)
    {
        cout<<setw(2)<<"'"<<token_array[i].symbol<<"'"<<"\t"<<setw(6)<<token_array[i].count<<"\t"<<setw(12)<<token_array[i].code<<endl;
    }
}

void Huffman::get_priority_queue()
{
    for(int i=0;i<token_count;i++)
    {
        Node *newnode = new Node();
        newnode->token = token_array[i];
        newnode->next = NULL;
        newnode->right = NULL;
        newnode->left = NULL;
        priority_queue.push(newnode);
    }
    priority_queue.print_queue();    
}

void Huffman::get_huffman_tree()
{
    Node *node1;
    Node *node2;
    Node *newnode;
    while (priority_queue.token_count>1)
    {
        node1 = priority_queue.pop();
        node2 = priority_queue.pop();
        newnode = huffman_binary_tree.merge(node1,node2);
        priority_queue.push(newnode);
        //priority_queue.print_queue();
        //huffman_binary_tree.print_binary_tree(newnode,0);
    }
    huffman_binary_tree.root = priority_queue.pop(); 
    huffman_binary_tree.print_binary_tree(huffman_binary_tree.root,0);   
}

void Huffman::get_codes(Node *traversal,string codepart)
{    
    if(traversal->left)
    {
        get_codes(traversal->left,codepart + "0");
    }
    else
    {
        int index=findindex(token_array,traversal->token.symbol);
        token_array[index].code = codepart;
    }    
    if(traversal->right)
    {
        get_codes(traversal->right,codepart + "1");
    }
    else 
    {        
        int index=findindex(token_array,traversal->token.symbol);
        token_array[index].code = codepart; 
    }
}

string Huffman::return_code(string target)
{
    int index = findindex(token_array,target);
    return token_array[index].code;
}

double Huffman::calculate_compression_ratio()
{
    double bit_required_before = 0;
    for(int i=0;i<token_count;i++)
        bit_required_before += token_array[i].count * 8;
    double bit_required_after = 0;
    for(int i=0;i<token_count;i++)
        bit_required_after += token_array[i].count * token_array[i].code.length();
    return bit_required_before / bit_required_after;
}
