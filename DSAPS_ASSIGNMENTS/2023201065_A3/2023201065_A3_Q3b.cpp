#include <iostream>
#include<vector>
#include <utility> 
using namespace std;

template <typename T1, typename T2>
class Ordered_map {
private:
    struct Node {
        T1 key;
        T2 value;
        Node* left;
        Node* right;
        int height;

        Node(T1 k, T2 v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int getHeight(Node* node) {
        return (node ? node->height : 0);
    }

    int getBalance(Node* node) {
        return (node ? getHeight(node->left) - getHeight(node->right) : 0);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* temp = x->right;

        x->right = y;
        y->left = temp;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* temp = y->left;

        y->left = x;
        x->right = temp;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, T1 key, T2 value) {
        if (!node) {
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            // Key already exists, update value if needed.
            node->value = value;
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1) {
            if (key < node->left->key) {
                return rotateRight(node);
            } else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        if (balance < -1) {
            if (key > node->right->key) {
                return rotateLeft(node);
            } else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    Node* findMin(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    Node* erase(Node* node, T1 key) {
        if (!node) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = erase(node->left, key);
        } else if (key > node->key) {
            node->right = erase(node->right, key);
        } else {
            // Key found, perform deletion
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = findMin(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = erase(node->right, temp->key);
            }
        }

        if (!node) {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1) {
            if (getBalance(node->left) >= 0) {
                return rotateRight(node);
            } else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        if (balance < -1) {
            if (getBalance(node->right) <= 0) {
                return rotateLeft(node);
            } else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    void inorder(Node* node) {
        if (!node) return;

        inorder(node->left);
        cout << node->key << " " << node->value << endl;
        inorder(node->right);
    }

public:
    Ordered_map() : root(nullptr) {}

    bool empty() {
        return !root;
    }
void clear() {
        while (root) {
            erase(root->key);
        }
    }
    T2& operator[](T1 key) {
        Node* present = root;
        while (present) {
            if (key == present->key) {
                return present->value;
            } else if (key < present->key) {
                present = present->left;
            } else {
                present = present->right;
            }
        }
        root = insert(root, key, T2());
        present = root;
        while (present->key != key) {
            if (key < present->key) {
                present = present->left;
            } else {
                present = present->right;
            }
        }
        return present->value;
    }

    bool contains(T1 key) {
        Node* present = root;
        while (present) {
            if (key == present->key) {
                return true;
            } else if (key < present->key) {
                present = present->left;
            } else {
                present = present->right;
            }
        }
        return false;
    }

    bool erase(T1 key) {
        root = erase(root, key);
        return true;
    }
bool insert(T1 key, T2 value) {
        root = insert(root, key, value);
        return true;
    }


    std::vector<T1> keys() {
        vector<T1> result;
        inorder(root);
        return result;
    }

    std::pair<bool, T1> lower_bound(T1 key) {
        Node* present = root;
        Node* lb = nullptr;
        while (present) {
            if (key == present->key) {
                return make_pair(true, present->key);
            } else if (key < present->key) {
                lb = present;
                present = present->left;
            } else {
                present = present->right;
            }
        }
        return make_pair(false, lb ? lb->key : T1());
    }

    pair<bool, T1> upper_bound(T1 key) {
        Node* present = root;
        Node* ub = nullptr;
        while (present) {
            if (key < present->key) {
                ub = present;
                present = present->left;
            } else {
                present = present->right;
            }
        }
        return make_pair(false, ub ? ub->key : T1());
    }
};

int main() {
    int N;
    cin >> N;

    Ordered_map<pair<int, int>, int> omap;
    int ans = 0;

    for (int i = 0; i < N; ++i) {
        int top_view, bottom_view;
        cin >> top_view >> bottom_view;
        if (top_view > bottom_view) {
            swap(top_view, bottom_view);
        }

        pair<int, int> token = make_pair(top_view, bottom_view);

        // Checking in Ordered_map and updating 'ans' variable
        if (omap.contains(token)) {
            ans += omap[token];
        }

        // Updation of Ordered_map based on small value first and large value second
        omap[token]++;
    }

    cout << ans << endl;

    return 0;
}