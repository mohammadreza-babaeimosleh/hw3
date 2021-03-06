#include "bst.h"

BST::BST(Node _root)
    : root{ &_root }
{
}

BST::BST()
    : root{ nullptr }
{
}


BST::Node*& BST::get_root()
{
    return root ; 
}


void BST::bfs(std::function<void(Node*& node)> func) 
{
    //defining lambda func for calculate depth(height) of tree
    std::function<size_t(Node*& node)> depth = [&](Node* node)->size_t
    {
        
        if(node == nullptr)
        {
            return 0;
        }
        else
        {
            size_t left_depth{ depth(node->left) };
            size_t right_depth{ depth(node->right) };
            
            if(left_depth > right_depth)
            {
                return left_depth + 1 ;
            }
            else
            {
                return right_depth + 1 ;
            }
        }

    };

    //defining lambda function for applying func to every node 
    std::function<void(size_t current_depth, Node*& node)> apply = [&](size_t current_depth , Node* node)->void
    {

        if(node == nullptr)
        {
            return;
        }

        if(current_depth == 1)
        { 
            func(node);
        }
        else if(current_depth > 1 )
        {
            apply(current_depth - 1 , node->left );
            apply(current_depth - 1 , node->right);
        }

    };

    size_t tree_depth{ depth(root) };

    if(tree_depth == 0)
    {
        return;
    }
    else
    {
        for(size_t current_depth{ 1 } ; current_depth <= tree_depth ; current_depth++)
        {
            apply(current_depth, root);
        }
    }

}


size_t BST::length()
{

    size_t counter{};
    std::function<void(size_t& count, Node*& root)> length_cal = [&](size_t count, Node* root)->void
    {
        if(root != nullptr)
        {
            counter += 1;
        }
        else
        {
            return;
        }

        length_cal(count, root->left);
        length_cal(count, root->right);

    };
    length_cal(counter, root);

    return counter;
}


bool BST::add_node(int value)
{

    Node* node{ new Node{ value } };

    if(root == nullptr) //empty tree
    {
        root = node;
        root->value = value;
        return true;
    }

    std::function<bool(int value, Node*& root)> adder = [&](int value, Node* root)->bool
    {
        
        if(root->value == value)
        {
            std::cout << "this value already exists in the tree" << std::endl;
            return false;
        }
        else if(root->value > value)
        {

            if(root->left == nullptr)
            {

                root->left = node;
                return true;
            }
            else
            {
                adder(value, root->left);
            }

        }
        else if(root->value < value)
        {

            if(root->right == nullptr)
            {
                root->right = node ;
                return true;
            }
            else
            {
                adder(value, root->right);
            }

        }

        return false;

    };

    if(adder(value, root))
    {
        return true;
    }
    else
    {
        return false;
    }

}


BST::Node** BST::find_node(int value)
{

    std::function<Node**(int value, Node** root)> finder = [&](int value, Node** root)->Node**
    {

        if((*root)->value == value)
        {
            std::cout << "value found" << std::endl;
            return root;
        }
        else if((*root)->value > value)
        {

            if((*root)->left == nullptr)
            {
                std::cout << "value does not exist" << std::endl;
                return nullptr;
            }
            else
            {   
                return finder(value,&((*root)->left));
            }

        }
        else if((*root)->value < value)
        {

            if((*root)->right == nullptr)
            {
                std::cout << "value does not exist" << std::endl;
                return nullptr; 
            }
            else
            {
                return finder(value,&((*root)->right));
            }

        }

        return nullptr;

    };
    
    Node** output{finder(value, &root)};
    return output;


}


BST::Node** BST::find_parrent(int value)
{

    if(find_node(value) == nullptr)
    {
        return nullptr;
    }

    std::function<Node**(int value, Node** root)> parrent_finder = [&](int value, Node** root)->Node**
    {

        if((*root) == nullptr)
        {
            return nullptr;
        }

        if((*root)->value == value)
        {
            std::cout << "given valuue is the root and has no parrents" << std::endl;
            return nullptr;
        }
        else if(((*root)->left) !=nullptr && ((*root)->left)->value == value)
        {
            std::cout << "parrent is   " << (*root)->value << std::endl;
            return root;
        }
        else if(((*root)->right) !=nullptr && ((*root)->right)->value == value)
        {
            std::cout << "parrent is   " << (*root)->value << std::endl;
            return root;
        }
        else if((*root)->value > value)
        {
            return parrent_finder(value, &((*root)->left));
        }
        else if((*root)->value < value)
        {
            return parrent_finder(value, &((*root)->left));
        }

        return nullptr;

    };

    Node** parrent{ parrent_finder(value, &root) };
    return parrent;

}


BST::Node** BST::find_successor(int value)
{
    if(find_node(value) == nullptr) //check for value existance
    {
        return nullptr;
    }
    else
    {

        Node** target_node{ find_node(value) };
        Node** successor{ target_node };
        if((*target_node)->left == nullptr)
        {
            return successor;
        }
        else
        {
            successor = &((*target_node)->left);

            while(true)
            {

                if((*successor)->right != nullptr)
                {
                    successor = &((*successor)->right);
                }
                else
                {
                    return successor;
                }

            }

        }

    }

}


bool BST::delete_node(int value)
{
    Node** target_node{ find_node(value) };

    if(target_node == nullptr)
    {
        return false;
    }

    if((*target_node)->left == nullptr && (*target_node)->right == nullptr)
    {
        (*target_node) = nullptr;
        return true;
    }

    if((*target_node)->left == nullptr && (*target_node)->right != nullptr)
    {
        *target_node = (*target_node)->right;
        return true;
    }

    if((*target_node)->left != nullptr && (*target_node)->right == nullptr)
    {
        *target_node = (*target_node)->left;
        return true;
    }

    Node** successor{ find_successor(value) };
    (*target_node)->value = (*successor)->value;
    *successor = nullptr;
    return true;
    
}


std::ostream& operator<<(std::ostream& os, BST bst)
{
    os << std::string(80, '*') << std::endl;

    std::function<void(BST::Node*& node)> print = [&](BST::Node* node)->void
    {
        os << node << "\t" ; 
        os << "=> value: " << node->value << "\t";
        os << "left :"<< std::left << std::setw(15) << node->left << "\t" << "right: " << node->right << std::endl;
    };
    
    bst.bfs(print);

    os << "binary search tree size: " << bst.length() << std::endl;

    os << std::string(80, '*') << std::endl;
    return os;
}


std::ostream& operator<<(std::ostream& os, BST::Node node)
{
    os << "node adrress: " << &node << "\t";
    os << "node value: " << node.value << "\t";
    os << "left child adrress: " << node.left << "\t";
    os << "right child adrress: " << node.right << "\t";

    return os;
}


BST& BST::operator++()
{
    //ussing lambda function just for using bfs
    std::function<void(Node*& node)> plus_1 = [&](Node* node)->void
    {
        node->value = node->value + 1;
    };
    
    bfs(plus_1);
    
    return *this;
}


BST BST::operator++(int)
{
    BST tmp{ *this };
    ++(*this);
    
    return tmp;
}


BST::~BST()
{
    
 	std::vector<Node*> nodes;
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto& node: nodes)
    {
 		delete node;
    }
}


BST::BST(const BST& bst) // copy constructor
{

    std::function<void(Node*const& root_org, Node** root)> filler = [&](Node*const root_org, Node** root)->void
    {   
        
        if(root_org != nullptr)
        {
            *root = new Node{ (root_org->value) };
        }
        

        if(root_org->left != nullptr)
        {
            filler(root_org->left, &((*root)->left));
        }

        if(root_org->right != nullptr)
        {
            filler(root_org->right, &((*root)->right));
        } 

        return;

    };

    filler(bst.root, &root);
}


BST& BST::operator=(const BST& bst)
{
    if(this == &bst) // bst = bst 
    {
        return *this;
    }

    std::vector<Node*> nodes;
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto& node: nodes)
    {
 		delete node;
    }

    std::function<void(Node*const& root_org, Node** root)> filler = [&](Node*const root_org, Node** root)->void
    {   
        
        if(root_org != nullptr)
        {
            *root = new Node{ (root_org->value) };
        }
        

        if(root_org->left != nullptr)
        {
            filler(root_org->left, &((*root)->left));
        }

        if(root_org->right != nullptr)
        {
            filler(root_org->right, &((*root)->right));
        } 

        return;

    };

    filler(bst.root, &root);
    
    return *this;
    
}


BST& BST::operator=(BST&& bst)
{
    // deleting old nodes
    std::vector<Node*> nodes;
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto& node: nodes)
    {
 		delete node;
    }
    
    // stealing the root pointer
    root = bst.root;
    bst.root = nullptr;

    return *this;

}


BST::BST(BST&& bst)
{
    root = new Node{};
    root = bst.root;
    bst.root = nullptr;
}


BST::BST(std::initializer_list<int> args)
    : root{ nullptr }
{
    for(auto i : args)
    {
        add_node(i);
    }
}

 


