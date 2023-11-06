#include <iostream>
using namespace std;

template <class T>
class Deque
{
private:
    /* data */
    T *deque;
    int front_index;
    int rear_index;
    int current_size;
    int deque_capacity;

    //***************All the functions will start from here************

    // operation 1 beneath

public:
    Deque()
    {
        deque_capacity = 8;
        current_size = 0;
        deque = new T[deque_capacity];
        front_index = -1;
        rear_index = deque_capacity;
    }

    // operation 2 beneath

    Deque(int n)
    {
        deque_capacity = n;
        deque = new T[deque_capacity];
        front_index = -1;
        rear_index = deque_capacity;
        current_size = 0;
        for (int i = 0; i < n; i++)
        {
            deque[i] = T(); // replace front_index with value T. ask someone for T
        }
    }

    // operation 3 beneath

    Deque(int n, T x)
    {
        deque_capacity = n;
        deque = new T[deque_capacity];
        front_index = 0;
        rear_index = deque_capacity-1;
        current_size = n;
        int i;
        for (i = 0; i < deque_capacity; i++)
        {
            deque[i] = x;
        }
    }

    // operation 4 beneath

    bool push_back(T x)
    {
        if (current_size == (deque_capacity + 1))
        {
            resize(current_size * 2);
        }
        rear_index = (rear_index-1) % deque_capacity;
        deque[rear_index] = x;
        current_size += 1;
        return true;
    }

    // operation 5 beneath

    bool pop_back()
    {
        if (current_size == 0)
        {
            front_index = 0;
            rear_index = deque_capacity-1;
            return false;
        }
        rear_index = (deque_capacity+ rear_index - 1) % deque_capacity;
        current_size -= 1;
        return true;
    }

    // operation 6 beneath

    bool push_front(T x)
    {
        if ((deque_capacity+1) == current_size)
        {                             // check if this condition is appropriate
            resize(current_size * 2); // check if resizing needs to be done
            deque_capacity = current_size * 2;
        }
        if(front_index<rear_index){
        front_index = (deque_capacity+ front_index + 1) % deque_capacity;
        deque[front_index] = x;
        current_size++;
        return true;
        }
        return false;
    }

    // operation 7 beneath

    bool pop_front()
    {
        if (current_size == 0)
        {
            return false;
        }
        if(front_index<rear_index){
        front_index = (deque_capacity+front_index -1) % deque_capacity;
        current_size--;
        return true;
        }
        return false;
    }

    // operation 8 beneath

    T front()
    {
        int value;
        if (current_size == 0)
        {
            return T(); // check what exactly is default value T and the replace with 3
        }
        value = deque[front_index];
        return value;
    }

    // operation 9 beneath

    T back()
    {
        int value;
        if (current_size == 0)
        {
            return T(); // check what exactly is default value T and the replace with 3
        }
        value = deque[rear_index];
        return value;
    }

    // operation 10 beneath

    T operator[](int n)
    {
        if (n < 0 || n >= current_size)
        {
            return T();
        }
        return deque[(front_index + n) % deque_capacity];
    }

    // operation 11 beneath

    bool empty()
    {
        if (current_size == 0)
        {
            return true;
        }
        return false;
    }

    // operation 12 beneath

    int size()
    {
        return current_size;
    }

    // operation 13 beneath

    void resize(int n)
{
    if (n <= current_size || n <= 0)
    {
        return; // No need to resize to a smaller size or invalid size.
    }

    T *new_deque = new T[n];

    for (int i = 0; i < current_size; i++)
    {
        new_deque[i] = deque[(front_index + i) % deque_capacity];
    }

    for (int i = current_size; i < n; i++)
    {
        new_deque[i] = T(); // Use default constructor to initialize new elements.
    }

    front_index = 0;
    rear_index = current_size;
    deque_capacity = n;
    delete[] deque;
    deque = new_deque;
}


    // operation 14 beneath

    void resize(int n, int d)
    {
        T *new_deque = new T[n];
        if (n > deque_capacity)
        {
            for (int i = 0; i < current_size; i++)
            {
                new_deque[i] = deque[(front_index + i) % deque_capacity];
            }
            for (int j = current_size; j < n; j++)
            {
                new_deque[j] = d;
            }
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                new_deque[i] = deque[i];
            }
        }
        front_index = 0;
        rear_index = current_size - 1;
        deque_capacity = n;
        current_size = n;
        delete[] deque;
        deque = new_deque;
    }

    // operation 15 beneath

    void reserve(int n)
    {
        if (n > deque_capacity)
        {
            resize(n);
        }
    }

    // operation 16 beneath

    void shrink_to_fit()
    {
        if (current_size < deque_capacity)
            resize(current_size);
    }

    // operation 17 beneath

    void clear()
    {
        int n;
        delete[] deque;
        T *deque = new T[deque_capacity];
        n = deque_capacity;
        front_index = 0;
        rear_index = 0;
        deque_capacity = n;
        current_size = 0;
    }

    // operation 18

    int capacity()
    {
        return deque_capacity;
    }

    // ~Deque(){
    //     delete[] deque;
    // }
};

int main()
{
    Deque<int> de_que;
    // here a variable of diffprinter needs to be declared that will be of
    // any datatype so replece existing values of corresponding function
    int choice;
    while (true)
    {
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            de_que = Deque<int>();
            break;
        }

        case 2:
        {
            int n;
            cin >> n;
            de_que = Deque<int>(n);
            break;
        }

        case 3:
        {
            int n, x;
            cin >> n;
            cin >> x;
            de_que = Deque<int>(n, x);
            break;
        }

        case 4:
        {
            int x;
            cin >> x;
            if(de_que.push_back(x)){
            cout << "true" << endl;
            }
            else{
                cout<<"false"<<endl;
            }
            break;
        }

        case 5:
        {
            if(de_que.pop_back()){
            cout << "true" << endl;
            }
            else{
                cout<<"false"<<endl;
            }
            break;
        }

        case 6:
        {
            int x;
            cin >> x;
            if(de_que.push_front(x)){
            cout << "true" << endl;
            }
            else{
                cout<<"false"<<endl;
            }
            break;
        }

        case 7:
        {
            if(de_que.pop_front()){
            cout << "true" << endl;
            }
            else{
                cout<<"false"<<endl;
            }
            break;
        }

        case 8:
        {
            // need to print the element poped from front here
            cout << de_que.front() << endl;
            break;
        }

        case 9:
        {
            // need to print the element poped from front here
            cout << de_que.back() << endl;
            break;
        }

        case 10:
        {
            int n;
            cin >> n;
            cout << de_que.operator[](n) << endl;
            break;
        }

        case 11:
        {
            if (de_que.empty())
            {
                cout << 1 << endl;
            }
            else
            {
                cout << 0 << endl;
            }
            break;
        }

        case 12:
        {
            cout << de_que.size() << endl;
            break;
        }

        case 13:
        {
            int n;
            cin >> n;
            de_que.resize(n);
            break;
        }

        case 14:
        {
            int n, d;
            cin >> n;
            cin >> d;
            de_que.resize(n, d);
            break;
        }

        case 15:
        {
            int n;
            cin >> n;
            de_que.reserve(n);
            break;
        }

        case 16:
        {
            de_que.shrink_to_fit();
            break;
        }

        case 17:
        {
            de_que.clear();
            break;
        }

        case 18:
        {
            cout << de_que.capacity() << endl;
            break;
        }

        default:
            return 0;
        }

        // use switch to make cases below and enjoy.
        // Delete this after you have implemented the function
    }
}