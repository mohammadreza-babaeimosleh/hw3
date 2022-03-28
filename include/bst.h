#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>
#include <iomanip>
#include<vector>
#include<compare>

class BST
{
public:
    class Node;
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    BST(Node _root);
    BST& operator++();
    BST operator++(int);
    ~BST();
    BST();
    BST(const BST& bst);
    BST& operator=(const BST& bst);
    BST& operator=(BST&& bst);
    BST(BST&& bst);
   



    
private:
    Node* root;
};


class BST::Node
{
public:
    Node(int value, Node* left = nullptr , Node* right = nullptr)
    {
        //std::cout << "normal constructor" << std::endl;
        this->value = value;
        this->left = left;
        this->right = right;
    }


    Node()
        : Node(0, nullptr , nullptr)
    {
        //std::cout << "defualt constructor" << std::endl;
    }


    Node(const Node& node)
        : value{ node.value } 
        , left{ node.left }
        , right{ node.right }
    {
        //std::cout << " copy constructor " << std::endl;
    }

    std::partial_ordering operator<=>(const Node& node) {return value <=> node.value; }
    bool operator==(const Node& node) { return value == node.value; }
    
    std::partial_ordering operator<=>(const int& num) {return value <=> num; }
    bool operator==(const int& num) { return value == num; }

    int value;
    Node* left;
    Node* right;
};

std::ostream& operator<<(std::ostream& os, BST::Node node);

std::ostream& operator<<(std::ostream& os, BST bst);


#endif //BST_H