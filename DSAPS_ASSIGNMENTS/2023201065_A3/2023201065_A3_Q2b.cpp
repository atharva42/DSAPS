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

    bool insert(const T1 &key, const T2 &value)
    {
        size_t index = hash(key);
        Node *current = table[index];
        while (current)
        {
            if (current->key == key)
            {
                current->value = value;
                return false;
            }
            current = current->next;
        }
        Node *newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
        return true;
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
    bool empty() const
    {
        return size == 0;
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

    size_t getSize() const
    {
        return size;
    }
    bool erase(const T1 &key)
    {
        size_t index = hash(key);
        Node *current = table[index];
        Node *prev = nullptr;
        while (current)
        {
            if (current->key == key)
            {
                if (prev)
                {
                    prev->next = current->next;
                }
                else
                {
                    table[index] = current->next;
                }
                delete current;
                size--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
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

    ~UnorderedMap()
    {
        clear();
        delete[] table;
    }
};

int main()
{
    int k, n;
    cin >> n >> k;
    UnorderedMap<int, int> myMap;
    int sum = 0;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        sum += num;
        if (sum == k)
        {
            count++;
        }
        if (myMap.contains(sum - k))
        {
            count += myMap[sum - k];
        }
        myMap[sum]++;
    }
    cout << count << endl;
    return 0;
}