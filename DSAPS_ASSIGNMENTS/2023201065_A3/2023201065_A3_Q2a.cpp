#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2>
class UnorderedMap
{
private:
    struct Node
    {
        T1 key;
        T2 value;
        Node *next;
        Node(const T1 &k, const T2 &v) : key(k), value(v), next(nullptr) {}
    };

    Node **table;
    size_t capacity;
    size_t size;

    size_t customStringHash(const std::string &str) const
    {
        size_t hash = 0;
        for (char c : str)
        {
            size_t asciiValue = static_cast<size_t>(c);
            hash = (hash * 31) + asciiValue;
        }
        return hash;
    }

    size_t customHash(const T1 &key) const
    {
        size_t hash = 0;
        const char *keyPtr = reinterpret_cast<const char *>(&key);
        for (size_t i = 0; i < sizeof(T1); i++)
        {
            hash = (hash * 31) + static_cast<size_t>(keyPtr[i]);
        }
        return hash;
    }

    size_t hash(const T1 &key) const
    {
        if constexpr (std::is_same<T1, std::string>::value)
        {
            return customStringHash(key) % capacity;
        }
        else
        {
            return customHash(key) % capacity;
        }
    }

public:
    UnorderedMap(size_t initialCapacity = 1000000) : capacity(initialCapacity), size(0)
    {
        table = new Node *[capacity];
        for (size_t i = 0; i < capacity; i++)
        {
            table[i] = nullptr;
        }
    }
bool contains(const T1 &key) const
    {
        size_t index = hash(key);
        Node *current = table[index];
        while (current)
        {
            if (current->key == key)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    size_t getSize() const
    {
        return size;
    }
    
    bool erase(const T1 &key)
    {
        size_t index = hash(key);
        Node *present = table[index];
        Node *prev = nullptr;
        while (present)
        {
            if (present->key == key)
            {
                if (prev)
                {
                    prev->next = present->next;
                }
                else
                {
                    table[index] = present->next;
                }
                delete present;
                size--;
                return true;
            }
            prev = present;
            present = present->next;
        }
        return false;
    }


    T2 &operator[](const T1 &key)
    {
        size_t index = hash(key);
        Node *current = table[index];
        while (current)
        {
            if (current->key == key)
            {
                return current->value;
            }
            current = current->next;
        }
        T2 default_value{};
        insert(key, default_value);
        return table[index]->value;
    }
    void keys() const
    {
        for (size_t i = 0; i < capacity; i++)
        {
            Node *current = table[i];
            while (current)
            {
                cout << current->key << endl;
                current = current->next;
            }
        }
    }

    void clear()
    {
        for (size_t i = 0; i < capacity; i++)
        {
            Node *current = table[i];
            while (current)
            {
                Node *temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        size = 0;
    }


    bool empty() const
    {
        return size == 0;
    }
    bool insert(const T1 &key, const T2 &value)
    {
        size_t index = hash(key);
        Node *present = table[index];
        while (present)
        {
            if (present->key == key)
            {
                present->value=value;
                return false;
            }
            present = present->next;
        }
        Node *newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
        return true;
    }

    

    ~UnorderedMap()
    {
        clear();
        delete[] table;
    }
};

int main()
{
    UnorderedMap<string, string> map;
    int q;
    cin >> q;
    while (q)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            string key;
            string value;
            cin >> key >> value;
            cin.ignore();
            bool result = map.insert(key, value);
            cout << (result ? "true" : "false") << endl;
        }
        else if (type == 2)
        {
            string key;
            cin >> key;
            bool result = map.erase(key);
            cout << (result ? "true" : "false") << endl;
        }
        else if (type == 3)
        {
            string key;
            cin >> key;
            bool result = map.contains(key);
            cout << (result ? "true" : "false") << endl;
        }
        else if (type == 4)
        {
            string key;
            cin >> key;
            cout << map[key] << endl;
        }
        else if (type == 5)
        {
            map.clear();
        }
        else if (type == 6)
        {
            cout << map.getSize() << endl;
        }
        else if (type == 7)
        {
            cout << (map.empty() ? "true" : "false") << endl;
        }
        else if (type == 8)
        {
            map.keys();
        }
        q--;
    }

    return 0;
}
