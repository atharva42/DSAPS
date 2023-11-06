#include <iostream>
#include <vector>

template <typename T1, typename T2>
class ordered_map
{
private:
    struct Node
    {
        T1 key;
        T2 value;
        Node *left;
        Node *right;
        int height;

        Node(T1 k, T2 v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node *root;
    int treeSize;

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *temp = x->right;

        x->right = y;
        y->left = temp;

        y->height = 1 + std::max((y->left ? y->left->height: 0), (y->right ? y->right->height : 0));
        x->height = 1 + std::max((x->left ? x->left->height : 0), (x->right ? x->right->height : 0));

        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *temp = y->left;

        y->left = x;
        x->right = temp;

        x->height = 1 + std::max((x->left ? x->left->height : 0), (x->right ? x->right->height : 0));
        y->height = 1 + std::max((y->left ? y->left->height : 0), (y->right ? y->right->height : 0));

        return y;
    }

    int getBalance(Node *node)
    {
        if (node == NULL)
            return 0;
        return (node->left ? node->left->height : 0) - (node->right ? node->right->height : 0);
    }

    Node *balance(Node *node)
    {
        if (node == NULL)
            return node;

        int balance = getBalance(node);

        if (balance > 1)
        {
            if (getBalance(node->left) >= 0)
            {
                return rightRotate(node);
            }
            else
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }

        if (balance < -1)
        {
            if (getBalance(node->right) <= 0)
            {
                return leftRotate(node);
            }
            else
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    Node *insert(Node *node, T1 key, T2 value)
    {
        if (node == NULL)
        {
            Node *newNode = new Node(key, value);
            treeSize++;
            return newNode;
        }

        if (key < node->key)
        {
            node->left = insert(node->left, key, value);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key, value);
        }
        else
        {
            node->value = value;
            return node;
        }

        node->height = 1 + std::max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));

        return balance(node);
    }

    Node *findMin(Node *node)
    {
        while (node->left != NULL)
        {
            node = node->left;
        }
        return node;
    }

    Node *remove(Node *node, T1 key)
    {
        if (node == NULL)
            return node;

        if (key < node->key)
        {
            node->left = remove(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = remove(node->right, key);
        }
        else
        {
            if (node->left == NULL || node->right == NULL)
            {
                Node *temp = node->left ? node->left : node->right;

                if (temp == NULL)
                {
                    temp = node;
                    node = NULL;
                }
                else
                {
                    *node = *temp;
                }

                delete temp;
                treeSize--;
            }
            else
            {
                Node *temp = findMin(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = remove(node->right, temp->key);
            }
        }

        if (node == NULL)
            return node;

        node->height = 1 + std::max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));

        return balance(node);
    }

    bool contains(Node *node, T1 key)
    {
        if (node == NULL)
            return false;

        if (key < node->key)
        {
            return contains(node->left, key);
        }
        else if (key > node->key)
        {
            return contains(node->right, key);
        }
        else
        {
            return true;
        }
    }

    T2 &get(Node *node, T1 key)
    {
        if (node == NULL)
        {
            root = insert(root, key, T2());
            return find(root, key)->value;
        }

        if (key < node->key)
        {
            return get(node->left, key);
        }
        else if (key > node->key)
        {
            return get(node->right, key);
        }
        else
        {
            return node->value;
        }
    }

    Node *find(Node *node, T1 key)
    {
        if (node == NULL)
            return NULL;

        if (key < node->key)
        {
            return find(node->left, key);
        }
        else if (key > node->key)
        {
            return find(node->right, key);
        }
        else
        {
            return node;
        }
    }

    void clear(Node *node)
    {
        if (treeSize > 0)
        {
            treeSize = 0;
        }

        if (node == NULL)
        {
            return;
        }

        clear(node->left);
        clear(node->right);

        delete node;
    }

    void collectKeys(Node *node, std::vector<T1> &keys)
    {
        if (node == NULL)
            return;

        collectKeys(node->left, keys);
        keys.push_back(node->key);
        collectKeys(node->right, keys);
    }

public:
    ordered_map() : root(NULL), treeSize(0) {}

    ~ordered_map()
    {
        clear(root);
    }

    bool empty()
    {
        return root == NULL;
    }

    int size()
    {
        return treeSize;
    }

    bool contains(T1 key)
    {
        return contains(root, key);
    }

    bool insert(T1 key, T2 value)
    {
        int oldSize = treeSize;
        root = insert(root, key, value);
        return treeSize > oldSize;
    }

    bool erase(T1 key)
    {
        int oldSize = treeSize;
        root = remove(root, key);
        return treeSize < oldSize;
    }

    T2 &operator[](T1 key)
    {
        return get(root, key);
    }

    void clear()
    {
        clear(root);
        root = NULL;
    }

    std::vector<T1> keys()
    {
        std::vector<T1> result;
        if (!empty())
        {
            collectKeys(root, result);
        }
        return result;
    }

    std::pair<bool, T1> lower_bound(T1 key)
    {
        Node *current = root;
        Node *lbNode = NULL;

        while (current != NULL)
        {
            if (key < current->key)
            {
                lbNode = current;
                current = current->left;
            }
            else if (key > current->key)
            {
                current = current->right;
            }
            else
            {
                return std::make_pair(true, current->key);
            }
        }

        if (lbNode)
        {
            return std::make_pair(true, lbNode->key);
        }
        else
        {
            return std::make_pair(false, T1());
        }
    }

    std::pair<bool, T1> upper_bound(T1 key)
    {
        Node *current = root;
        Node *ubNode = NULL;

        while (current != NULL)
        {
            if (key < current->key)
            {
                ubNode = current;
                current = current->left;
            }
            else if (key >= current->key)
            {
                current = current->right;
            }
        }

        if (ubNode)
        {
            return std::make_pair(true, ubNode->key);
        }
        else
        {
            return std::make_pair(false, T1());
        }
    }
};

int main()
{
    ordered_map<int, std::string> omap;

    while (1)
    {
        int input;
        std::cin >> input;

        if (input == 1)
        {
            std::cout << std::boolalpha << omap.empty() << std::endl;
        }
        else if (input == 2)
        {
            std::cout << omap.size() << std::endl;
        }
        else if (input == 3)
        {
            int key;
            std::cin >> key;
            std::cout << std::boolalpha << omap.contains(key) << std::endl;
        }
        else if (input == 4)
        {
            int key;
            std::string value;
            std::cin >> key;
            std::cin >> value;
            std::cout << std::boolalpha << omap.insert(key, value) << std::endl;
        }
        else if (input == 5)
        {
            int key;
            std::cin >> key;
            std::cout << std::boolalpha << omap.erase(key) << std::endl;
        }
        else if (input == 6)
        {
            int key;
            std::cin >> key;
            std::cout << omap[key] << std::endl;
        }
        else if (input == 7)
        {
            omap.clear();
        }
        else if (input == 8)
        {
            if (omap.keys().size() == 0)
            {
                std::cout << std::endl;
            }

            for (auto z : omap.keys())
            {
                std::cout << z << std::endl;
            }
        }
        else if (input == 9)
        {
            int key;
            std::cin >> key;
            std::pair<bool, int> result = omap.lower_bound(key);
            if (result.first)
            {
                std::cout << "true" << std::endl << result.second << std::endl;
            }
            else
            {
                std::cout << "false" << std::endl;
            }
        }
        else if (input == 10)
        {
            int key;
            std::cin >> key;
            std::pair<bool, int> result = omap.upper_bound(key);
            if (result.first)
            {
                std::cout << "true" << std::endl << result.second << std::endl;
            }
            else
            {
                std::cout << "false" << std::endl;
            }
        }
        else if (input == 0)
        {
            break;
        }
    }

    return 0;
}
