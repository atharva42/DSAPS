#include <iostream>

using namespace std;

// Struct for Node in Linked List
template <typename T>
struct Node {
    int row, col;
    T value;
    Node* next;
};

// Class for Linked List-Based Sparse Matrix
template <typename T>
class SparseMatrixLinkedList {
private:
    Node<T>* head;
    int rows, cols;

public:
    SparseMatrixLinkedList(int n, int m) { 
        rows = n;
        cols = m;
        head = nullptr;
    }

    // Insert function
    void insert(int row, int col, T value) {
        if (row < 1 || row > rows || col < 1 || col > cols) {
            cerr << "Rows and columns do not match" << endl;
            exit(1);
        }
        if (value != 0) {
            Node<T>* newNode = new Node<T>;
            newNode->row = row;
            newNode->col = col;
            newNode->value = value;
            newNode->next = nullptr;

            if (!head || row < head->row || (row == head->row && col < head->col)) {
                newNode->next = head;
                head = newNode;
            } else {
                Node<T>* current = head;
                while (current->next && (row > current->next->row || (row == current->next->row && col > current->next->col))) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
        }
    }

    // Transpose function
    SparseMatrixLinkedList<T> transpose() {
        SparseMatrixLinkedList<T> result(cols, rows);

        Node<T>* current = head;
        while (current != nullptr) {
            result.insert(current->col, current->row, current->value);
            current = current->next;
        }

        return result;
    }

    // Function to perform matrix addition
    SparseMatrixLinkedList<T> add(const SparseMatrixLinkedList<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            cerr << "Matrix dimensions are not compatible for addition." << endl;
            exit(1);
        }

        SparseMatrixLinkedList<T> result(rows, cols);

        Node<T>* current1 = head;
        Node<T>* current2 = other.head;

        while (current1 != nullptr || current2 != nullptr) {
            int row1 = (current1 != nullptr) ? current1->row : rows;
            int row2 = (current2 != nullptr) ? current2->row : rows;
            int col1 = (current1 != nullptr) ? current1->col : cols;
            int col2 = (current2 != nullptr) ? current2->col : cols;

            if (row1 == row2 && col1 == col2) {
                result.insert(row1, col1, (current1->value) + (current2->value));
                current1 = current1->next;
                current2 = current2->next;
            } else if (row1 < row2 || (row1 == row2 && col1 < col2)) {
                result.insert(row1, col1, current1->value);
                current1 = current1->next;
            } else if (row1 > row2 || (row1 == row2 && col1 > col2)) {
                result.insert(row2, col2, current2->value);
                current2 = current2->next;
            }
        }

        return result;
    }

    // Function to perform matrix multiplication
    SparseMatrixLinkedList<T> multiply(const SparseMatrixLinkedList<T>& other) const {
        if (cols != other.rows) {
            cerr << "Matrix dimensions are not compatible for multiplication." << endl;
            exit(1);
        }

        SparseMatrixLinkedList<T> result(rows, other.cols);
        if(head==nullptr || other.head==nullptr){
            return result;
        }
        Node<T>* current1 = head;
        while (current1 != nullptr) {
            Node<T>* current2 = other.head;
            while (current2 != nullptr) {
                if (current1->col == current2->row) {
                   T value= current1->value * current2->value;
                    result.insert(current1->row, current2->col, value);
                }
                current2 = current2->next;
            }
            
            // cout<<"Hey"<<endl;
            current1 = current1->next;
            // cout<<"Hey1"<<endl;
        }

        Node<T>* prev = result.head;
        Node<T>* current = prev->next;
        while(current->next){
            cout<<current->row<<" "<<current->col<<endl;
            if(prev->row==current->row && prev->col==current->col){
                prev->value+=current->value;
                current=current->next;
                delete prev->next;
                prev->next=current;
            }
            else{
            prev=current;
            current=current->next;
            }
        }
        if(prev->row==current->row && prev->col==current->col){
                prev->value+=current->value;
                delete prev->next;
            }
        return result;
    }

    // Print function
    void print() const {
        Node<T>* current = head;

        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                if (current != nullptr && current->row == i && current->col == j) {
                    cout << current->value << " ";
                    current = current->next;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
};

//sparse operation using matrix is below

template <typename T>
struct Triplet {
    int row;
    int col;
    T value;
};

template <typename T>
class SparseUsingArray{
    private:
        Triplet<T>* elements;
        int size=1;
        int capacity=10;
        int rows;
        int cols;
    
    public:
        SparseUsingArray(int n, int m) {
        rows=n;
        cols=m;
        elements = new Triplet<T>[capacity];
    }

    void insert(int row, int col, T value) {
        if (size == capacity) {
            // Resize the array
            resizeArray();
        }

        elements[size].row = row;
        elements[size].col = col;
        elements[size].value = value;
        size++;
    }

    void resizeArray() {
        capacity *= 2;
        Triplet<T>* newElements = new Triplet<T>[capacity];
        
        for (int i = 1; i <= size; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

    void transpose() const {
    SparseUsingArray<T> result(cols, rows);

    // Initialize the transposed matrix
    for (int i = 1; i <= size; i++) {
        int newRow = elements[i].col;
        int newCol = elements[i].row;
        T value = elements[i].value;
        // cout<<value<<endl;

        // Add the value to the transposed matrix at the new coordinates
        result.elements[i].row = newRow;
        result.elements[i].col = newCol;
        result.elements[i].value = value;
    }
    for (int i = 1; i <= cols; i++) {
        for (int j = 1; j <= rows; j++) {
            bool found = false;
            for (int k = 1; k <= size; k++) {
                if (result.elements[k].row == i && result.elements[k].col == j) {
                    cout << result.elements[k].value << " ";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

// Function to perform matrix addition
SparseUsingArray<T> add(const SparseUsingArray<T>& other) const {
    if (rows != other.rows || cols != other.cols) {
        cerr << "Matrix dimensions are not compatible for addition." << endl;
        exit(1);
    }

    SparseUsingArray<T> result(rows, cols);

    int i = 0; // Index for this matrix's elements
    int j = 0; // Index for the other matrix's elements

    while (i < size || j < other.size) {
        if (i < size && (j >= other.size || (elements[i].row < other.elements[j].row ||
                                             (elements[i].row == other.elements[j].row && elements[i].col < other.elements[j].col)))) {
            result.insert(elements[i].row, elements[i].col, elements[i].value);
            i++;
        } else if (j < other.size && (i >= size || (elements[i].row > other.elements[j].row ||
                                                   (elements[i].row == other.elements[j].row && elements[i].col > other.elements[j].col)))) {
            result.insert(other.elements[j].row, other.elements[j].col, other.elements[j].value);
            j++;
        } else if (i < size && j < other.size && elements[i].row == other.elements[j].row &&
                   elements[i].col == other.elements[j].col) {
            T sum = elements[i].value + other.elements[j].value;
            result.insert(elements[i].row, elements[i].col, sum);
            i++;
            j++;
        }
    }

    // Handle remaining elements in this matrix
    while (i < size) {
        result.insert(elements[i].row, elements[i].col, elements[i].value);
        i++;
    }

    // Handle remaining elements in the other matrix
    while (j < other.size) {
        result.insert(other.elements[j].row, other.elements[j].col, other.elements[j].value);
        j++;
    }

    return result;
}

// Function to print the result matrix
void printResult(const SparseUsingArray<T>& result) const {
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            bool found = false;
            for (int k = 0; k < result.size; k++) {
                if (result.elements[k].row == i && result.elements[k].col == j) {
                    cout << result.elements[k].value << " ";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

void multiply(const SparseUsingArray<T>& other) const {
    if (cols != other.rows) {
        cerr << "Matrix dimensions are not compatible for multiplication." << endl;
        exit(1);
    }

    SparseUsingArray<T> result(rows, other.cols);

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= other.size; j++) {
            if (elements[i].col == other.elements[j].row) {
                T product = elements[i].value * other.elements[j].value;
                int row = elements[i].row;
                int col = other.elements[j].col;
                result.accumulate(row, col, product);
            }
        }
    }

    result.printResult(result);
}


void accumulate(int row, int col, T value) {
    for (int i = 1; i <= size; i++) {
        if (elements[i].row == row && elements[i].col == col) {
            elements[i].value += value;
        }
    }

    // If no element found, insert a new one with the accumulated value
    if (size == capacity) {
        // Resize the array
        resizeArray();
    }

    elements[size].row = row;
    elements[size].col = col;
    elements[size].value = value;
    size++;
}

    void print() {
    int currentElement = 0;  // Keep track of the current element in the elements array

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            if (currentElement < size && elements[currentElement].row == i && elements[currentElement].col == j) {
                // If the current element matches the row and column, print its value
                cout << elements[currentElement].value << " ";
                currentElement++;
            } else {
                // If no element matches the row and column, print 0
                cout << "0 ";
            }
        }
        cout << endl;  // Move to the next row
    }
}


};

int main() {
    int dataStructureType, operationType;
    int n1, m1, n2, m2;
    cout << "Enter data structure type (1 for Array, 2 for Linked List): ";
    cin >> dataStructureType;
    cout << "Enter operation type (1 for Addition, 2 for Transpose, 3 for Multiplication): ";
    cin >> operationType;
    cout << "Enter matrix 1 details (number of rows and columns): ";
    cin >> n1 >> m1;

    if (dataStructureType == 1) {
        SparseUsingArray<double> matrix1(n1, m1);
        cout << "Enter matrix 1 elements:" << endl;
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= m1; j++) {
                double value;
                cin >> value;
                if (value != 0) {
                    matrix1.insert(i, j, value);
                }
            }
        }
        // matrix1.print();

        if (operationType == 2) {
            cout << "Transpose of matrix 1:" << endl;
            matrix1.transpose();
        } 
        else {
            if (operationType == 1 || operationType == 3) {
                cout << "Enter matrix 2 details (number of rows and columns): ";
                cin >> n2 >> m2;
            }

            SparseUsingArray<double> matrix2(n2, m2);
            if (operationType == 1 || operationType == 3) {
                cout << "Enter matrix 2 elements:" << endl;
                for (int i = 1; i <= n2; i++) {
                    for (int j = 1; j <= m2; j++) {
                        double value;
                        cin >> value;
                        if (value != 0) {
                            matrix2.insert(i, j, value);
                        }
                    }
                }
            }

            if (operationType == 1) {
                SparseUsingArray<double> resultMatrix = matrix1.add(matrix2);

    cout << "Result Matrix:" << endl;
    resultMatrix.printResult(resultMatrix);

            }
             if (operationType == 3) {
                cout << "Matrix 1 * Matrix 2:" << endl;
                matrix1.multiply(matrix2);

            }
        }
    } 
    else if (dataStructureType == 2) {
        SparseMatrixLinkedList<double> matrix1(n1, m1);
        cout << "Enter matrix 1 elements:" << endl;
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= m1; j++) {
                double value;
                cin >> value;
                if (value != 0) {
                    matrix1.insert(i, j, value);
                }
            }
        }

        if (operationType == 2) {
            SparseMatrixLinkedList<double> transposeMatrix = matrix1.transpose();
            transposeMatrix.print();
        } else {
            if (operationType == 1 || operationType == 3) {
                cout << "Enter matrix 2 details (number of rows and columns): ";
                cin >> n2 >> m2;
            }

            SparseMatrixLinkedList<double> matrix2(n2, m2);
            if (operationType == 1 || operationType == 3) {
                cout << "Enter matrix 2 elements:" << endl;
                for (int i = 1; i <= n2; i++) {
                    for (int j = 1; j <= m2; j++) {
                        double value;
                        cin >> value;
                        if (value != 0) {
                            matrix2.insert(i, j, value);
                        }
                    }
                }
            }

            if (operationType == 1) {
                SparseMatrixLinkedList<double> result = matrix1.add(matrix2);
                result.print();
            } else if (operationType == 3) {
                SparseMatrixLinkedList<double> result = matrix1.multiply(matrix2);
                result.print();
            }
        }
    }

    return 0;
}
