#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <random>
#include "Espantapajaros.h"
using namespace std;
enum Colorl { RED, BLACK };
struct Node
{
    float data;
    int height;
    Colorl color;
    Node* parent;
    Node* left;
    Node* right;
    Node()
    {
        data = 0;
        height = 0;
        left = NULL;
        right = NULL;
    }
    Node(float _data)
    {
        data = _data;
        height = 0;
        left = NULL;
        right = NULL;
    }
};

struct TreeH
{
    int cost;
    int grow;
    int speed;
    int fruit;
    int X;
    int Y;
    int buff;
    int plague;
    bool estado = false;
    int miss = 0;
    float totalMoney = 0;
    int sold = 0;
    ALLEGRO_BITMAP* ABImagen = al_load_bitmap("ArbolHeap.png");
    vector<Node*> heap;
    TreeH(int x, int y)
    {
        cost = 130;
        grow = 150;
        speed = 35;
        fruit = 0;
        X = x-10;
        Y = y-3;
        buff = 1;
        plague = 0;
       
        bool estado = false;
    }
    // Function to get the parent index of a node
    int parent(int index)
    {
        return (index - 1) / 2;
    }

    // Function to get the left child index of a node
    int leftChild(int index)
    {
        return (2 * index) + 1;
    }

    // Function to get the right child index of a node
    int rightChild(int index)
    {
        return (2 * index) + 2;
    }

    // Function to swap two elements in the heap
    void swap(Node*& a, Node*& b)
    {
        Node* temp = a;
        a = b;
        b = temp;
    }
    void heapify(int index)
    {
        int largest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        // Compare the value of the current node with its left child
        if (left < heap.size() && heap[left]->data > heap[largest]->data)
            largest = left;

        // Compare the value of the current node with its right child
        if (right < heap.size() && heap[right]->data > heap[largest]->data)
            largest = right;

        // If the largest value is not the current node, swap them and heapify the affected subtree
        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapify(largest);
        }
    }
    void insert(float value)
    {
        Node* newNode = new Node(value);
        heap.push_back(newNode);
        fruit++;
        int index = heap.size() - 1;
        while (index != 0 && heap[parent(index)]->data < heap[index]->data) {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }
    void removeRoot()
    {
        if (heap.empty()) {
            cout << "Heap is empty." << endl;
            return;
        }
        fruit--;
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
    }
    void print()
    {
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i]->data << " ";
        }
    }
    float Hrandgen()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.001, 5.0);
        return floor(dis(gen) * 1000.0) / 1000.0;
    }
    void growHTree()
    {
        //for (int i = 0; i < 200; ++i)
        //{
          //this_thread::sleep_for(std::chrono::seconds(speed * tree->buff));
        insert(Hrandgen());
        cout << "|";
        print();
        cout << "|" << endl;
        //std::this_thread::sleep_for(std::chrono::seconds(3));
       /// this_thread::sleep_for(std::chrono::seconds(20));
   // }


    }
};
struct TreeA
{
    int cost;
    int grow;
    int speed;
    int fruit;
    int X;
    int Y;
    int buff;
    int plague;
    bool estado = false;
    int miss = 0;
    float totalMoney = 0;
    int sold = 0;
    ALLEGRO_BITMAP* ABImagen = al_load_bitmap("ArbolAvl.png");
    Node* root;
    Node* lastNode, * parentOfLastNode;
    TreeA(int x, int y )
    {
        cost = 100;
        grow = 500;
        speed = 60;
        fruit = 0;
        X = x-10;
        Y = y-3;
        buff = 1;
        plague = 0;
        root = NULL;
    }
    int getHeight(Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }
    int getBalance(Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }
    void updateHeight(Node* node)
    {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = std::max(leftHeight, rightHeight) + 1;
    }
    Node* rotateRight(Node* node)
    {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }
    Node* rotateLeft(Node* node)
    {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }
    Node* insertNode(Node* root, float data)
    {
        if (root == nullptr)
        {
            Node* newNode = new Node();
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->height = 1;
            return newNode;
        }
        if (data < root->data)
            root->left = insertNode(root->left, data);
        else if (data > root->data)
            root->right = insertNode(root->right, data);
        else
            return root;
        updateHeight(root);

        int balance = getBalance(root);
        if (balance > 1)
        {
            if (data < root->left->data)
                return rotateRight(root);
            else
            {
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }
        if (balance < -1)
        {
            if (data > root->right->data)
                return rotateLeft(root);
            else
            {
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
        }
        return root;
    }
    void print2(Node* root) {
        if (root != nullptr) {
            print2(root->left);
            std::cout << root->data << " ";
            print2(root->right);
        }
    }
    void insert(float data)
    {
        root = insertNode(root, data);
        fruit++;
    }
    Node* findMin(Node* node)
    {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    int height(Node* root)
    {
        if (root == NULL)
            return 0;

        int lheight = height(root->left) + 1;
        int rheight = height(root->right) + 1;

        return max(lheight, rheight);
    }
    void getLastNodeAndItsParent(Node* root, int level, Node* parent)
    {
        if (root == NULL)
            return;
        if (level == 1)
        {
            lastNode = root;
            parentOfLastNode = parent;
        }
        getLastNodeAndItsParent(root->left, level - 1, root);
        getLastNodeAndItsParent(root->right, level - 1, root);
    }
    void remove2(Node* root)
    {
        int levelOfLastNode = height(root);
        getLastNodeAndItsParent(root, levelOfLastNode, NULL);

        if (lastNode && parentOfLastNode)
        {
            if (parentOfLastNode->right)
                parentOfLastNode->right = NULL;
            else
                parentOfLastNode->left = NULL;
        }
        else
            cout << "Empty Tree\n";
    }
    Node* removeNode(Node* root) {
        remove2(root);
        // Update the height of the current node
        updateHeight(root);
        // Perform rotations if needed to balance the tree
        int balance = getBalance(root);
        if (balance > 1) {
            if (getBalance(root->left) >= 0) {
                // Left-Left case
                return rotateRight(root);
            }
            else {
                // Left-Right case
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }
        if (balance < -1) {
            if (getBalance(root->right) <= 0) {
                // Right-Right case
                return rotateLeft(root);
            }
            else {
                // Right-Left case
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
        }
        return root;
    }
    float Arandgen()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(2, 20);
        return floor(dis(gen) * 1000.0) / 1000.0;
    }
    void print()
    {
        print2(root);
        std::cout << std::endl;
    }
    void remove()
    {
        removeNode(root);
        fruit--;
    }
    void growATree()
    {
        //for (int i = 0; i < 200; ++i)
        //{
          //this_thread::sleep_for(std::chrono::seconds(speed * tree->buff));
        insert(Arandgen());
        cout << "|";
        print();
        cout << "|" << endl;
        //std::this_thread::sleep_for(std::chrono::seconds(3));
       /// this_thread::sleep_for(std::chrono::seconds(20));
   // }


    }
};
struct TreeF
{
    int cost;
    int grow;
    int speed;
    int fruit;
    int X;
    int Y;
    ALLEGRO_BITMAP* ABImagen = al_load_bitmap("ArbolRojinegro.png");
    int buff;
    int plague;
    bool estado = false;
    Node* root;
    int miss = 0;
    float totalMoney = 0;
    int sold = 0;
    Node* lastNode, * parentOfLastNode;
    TreeF(int x, int y)
    {
        cost = 600;
        grow = 500;
        speed = 60;
        fruit = 0;
        X = x-10;
        Y = y-3;
        buff = 1;
        plague = 0;
        root = NULL;
    }
    Node* createNode(float data)
    {
        Node* newNode = new Node(data);
        newNode->data = data;
        newNode->color = RED;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->parent = nullptr;
        return newNode;
    }
    void leftRotate(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }
    void rightRotate(Node* y)
    {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != nullptr)
            x->right->parent = y;

        x->parent = y->parent;

        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        x->right = y;
        y->parent = x;
    }
    void fixInsertion(Node* z)
    {
        while (z->parent != nullptr && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else {
                Node* y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    Node* insertNode(Node* root, Node* z)
    {
        if (root == nullptr)
            return z;

        if (z->data < root->data)
        {
            root->left = insertNode(root->left, z);
            root->left->parent = root;
        }
        else if (z->data > root->data)
        {
            root->right = insertNode(root->right, z);
            root->right->parent = root;
        }
        return root;
    }
    void insert(int data)
    {
        Node* node = createNode(data);
        root = insertNode(root, node);
        fixInsertion(node);
        fruit++;
    }
    void inorderTraversal(Node* root)
    {
        if (root != nullptr) {
            inorderTraversal(root->left);
            std::cout << root->data << " ";
            inorderTraversal(root->right);
        }
    }
    void print()
    {
        inorderTraversal(root);
    }
    Node* findMinimum(Node* node)
    {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
    Node* notNull(Node* node1, Node* node2)
    {
        if (node1 != NULL)
            return node1;
        return node2;
    }
    Node* nod(Node* node)
    {
        if (node == NULL)
            return NULL;
        return notNull(node->left, node->right);
    }
    int getHeight(Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }
    int getBalance(Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }
    void updateHeight(Node* node)
    {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = std::max(leftHeight, rightHeight) + 1;
    }
    Node* rotateRight(Node* node)
    {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }
    Node* rotateLeft(Node* node)
    {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }
    int height(Node* root)
    {
        if (root == NULL)
            return 0;

        int lheight = height(root->left) + 1;
        int rheight = height(root->right) + 1;

        return max(lheight, rheight);
    }
    void getLastNodeAndItsParent(Node* root, int level, Node* parent)
    {
        if (root == NULL)
            return;
        if (level == 1)
        {
            lastNode = root;
            parentOfLastNode = parent;
        }
        getLastNodeAndItsParent(root->left, level - 1, root);
        getLastNodeAndItsParent(root->right, level - 1, root);
    }
    void remove2(Node* root)
    {
        int levelOfLastNode = height(root);
        getLastNodeAndItsParent(root, levelOfLastNode, NULL);

        if (lastNode && parentOfLastNode)
        {
            if (parentOfLastNode->right)
                parentOfLastNode->right = NULL;
            else
                parentOfLastNode->left = NULL;
        }
        else
            cout << "Empty Tree\n";
    }
    Node* removeNode(Node* root) {
        remove2(root);
        // Update the height of the current node
        updateHeight(root);
        // Perform rotations if needed to balance the tree
        int balance = getBalance(root);
        if (balance > 1) {
            if (getBalance(root->left) >= 0) {
                // Left-Left case
                return rotateRight(root);
            }
            else {
                // Left-Right case
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }
        if (balance < -1) {
            if (getBalance(root->right) <= 0) {
                // Right-Right case
                return rotateLeft(root);
            }
            else {
                // Right-Left case
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
        }
        return root;
    }
    float Frandgen()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(5, 50);
        return floor(dis(gen) * 1000.0) / 1000.0;
    }
    void remove()
    {
        removeNode(root);
        fruit--;
    }
    void growFTree()
    {
        //for (int i = 0; i < 200; ++i)
        //{
          //this_thread::sleep_for(std::chrono::seconds(speed * tree->buff));
        insert(Frandgen());
        cout << "|Esto es del rojinegro: ";
        print();
        cout << "|" << endl;
        //std::this_thread::sleep_for(std::chrono::seconds(3));
       /// this_thread::sleep_for(std::chrono::seconds(20));
   // }


    }
};

int randgen()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 100);
    return dis(gen);
}
int randgenC()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 7);
    return dis(gen);
}
struct Crow
{
    int probability;
    int frecuency;
    int speed;
    int buff;
    int X;
    int Y;
    bool active;
    ALLEGRO_BITMAP* crowImage = al_load_bitmap("Crow.png");
    float height = 52;
    float width = 50;
    Crow(int x, int y)
    {
        probability = 40; //appear probability
        frecuency = 120; //when appear
        speed = 90; //how many fruits will eat
        buff = 1;
        X = x;
        Y = y;
        active = false;
    }

};
struct Worm
{
    int probability;
    int frecuency;
    int speed;
    int buff;
    int X;
    int Y;
    bool active;
    ALLEGRO_BITMAP* crowImage = al_load_bitmap("Worm.png");
    float height = 46;
    float width = 45;
    Worm(int x, int y)
    {
        probability = 30; //appear probability
        frecuency = 60; //when appear
        buff = 1;
        X = x;
        Y = y;
        active = false;
    }

};