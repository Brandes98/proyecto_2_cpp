#pragma once
#include "Arboles.h"

struct TreeO
{
    int cost;
    int grow;
    int speed;
    int quantity = 0;
    int miss = 0;
    float totalMoney = 0;
    int sold = 0;
    int fruit;
    int X = 0;
    int Y = 0;
    int ubication[2] = { X,Y };
    int buff;
    int plague;
    ALLEGRO_BITMAP* ABImagen = al_load_bitmap("ArbolBinario.png");
    bool estado = false;
    Node* root;
    Node* lastNode, * parentOfLastNode;
   // static int contador;
    TreeO(int x, int y)
    {
        cost = 100;
        grow = 200;
        speed = 20;
        fruit = 0;
        X = x - 10;
        Y = y - 3;
        buff = 1;
        plague = 0;
        root = NULL;
        //contador = 0;

    }
    void insert(Node* node, float value)
    {
        if (root == NULL)
        {
            root = new Node(value);
            fruit++;
        }
        else
        {
            float data = node->data;
            if (value < data)
            {
                if (node->left == NULL)
                {
                    node->left = new Node(value);
                    fruit++;
                }
                else
                    insert(node->left, value);
            }
            else if (value > data)
            {
                if (node->right == NULL)
                {
                    node->right = new Node(value);
                    fruit++;
                }
                else
                    insert(node->right, value);
            }
        }
    }
    bool valid(int seconds)
    {
       
        return true;
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
            if (parentOfLastNode->right) {
                
                parentOfLastNode->right = NULL;
            }
            else {
                
                parentOfLastNode->left = NULL;

            }
        }
        else
            cout << "Empty Tree\n";
    }
    void remove()
    {
        totalMoney -= root->data;
        remove2(root);
    }
    int Depth(Node* node)
    {
        if (node == NULL)
        {
            return 0;
        }
        else
        {
            int leftDepth = Depth(node->left);
            int rightDepth = Depth(node->right);

            if (leftDepth > rightDepth)
                return leftDepth + 1;
            else
                return rightDepth + 1;
        }
    }
    void print(Node* node, int level)
    {
        if (node == NULL)
            return;
        else
        {
            if (level == 0)
                cout << node->data;
            else if (level == 1)
            {
                if (node->left != NULL && node->right != NULL)
                    cout << node->left->data << " " << node->right->data << " ";
                else if (node->left != NULL)
                    cout << node->left->data << " ";
                else if (node->right != NULL)
                    cout << node->right->data << " ";
            }
            else
            {
                print(node->left, level - 1);
                print(node->right, level - 1);
            }
        }
    }
    float Orandgen()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.001, 5.0);
        return floor(dis(gen) * 1000.0) / 1000.0;
    }
    void inorder(Node* root)
    {
        if (root == NULL)
            return;

        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
    void growOTree()
    {
        //for (int i = 0; i < 200; ++i)
        //{
          //this_thread::sleep_for(std::chrono::seconds(speed * tree->buff));
        float mone = Orandgen();
        totalMoney += mone;
            insert(root,mone);
            cout << "|";
            inorder(root);
            cout << "|" << endl;
            //std::this_thread::sleep_for(std::chrono::seconds(3));
           /// this_thread::sleep_for(std::chrono::seconds(20));
       // }


    }
};
