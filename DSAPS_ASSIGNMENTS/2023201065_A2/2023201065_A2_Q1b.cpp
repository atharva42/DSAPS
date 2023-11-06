#include<iostream>
using namespace std;    

class MaxHeap{
    private:
        int* p_que;
        int current_size;
        int capacity;
    
    public:
        MaxHeap(){
            capacity=100000;
            p_que = new int[100000];
            current_size=0;
        }

        int size(){
            return current_size;
        }

        void resize(int size){
            int twice=size*2;
            int* sp_que = new int[twice];
            for(int i=0; i<=current_size; i++){
                sp_que[i]=p_que[i];
            }
            delete [] p_que;
            p_que=sp_que;
            capacity=twice;
        }

        void maxHeapifyTheTree(int root_index){
            int left_child=2*root_index+1;
            int right_child=2*root_index+2;
            int max_el=root_index;
            static int count=1;
            if(left_child<current_size && p_que[left_child]>p_que[max_el]){
                max_el=left_child;
            }
            if(right_child<current_size && p_que[right_child]>p_que[max_el]){
                max_el=right_child;
            }
            if(max_el!=root_index){
                int temp=p_que[max_el];
                p_que[max_el]=p_que[root_index];
                p_que[root_index]=temp;
                maxHeapifyTheTree(max_el);
            }
        }
        int curr(){
            return current_size;
        }
        void push(int el){
            if(current_size==(capacity+1)){
                resize(capacity);
            }
            p_que[current_size]=el;
            current_size++;  //probably remove it later
            int start_index=(current_size/2)-1;
                for(int i=start_index; i>=0; i--){
                    maxHeapifyTheTree(i);
                }
        }

        void pop(){
            if(current_size!=0){
            p_que[0]=p_que[current_size-1];
            current_size--;
            int start_index=(current_size/2)-1;
            maxHeapifyTheTree(0);
        }
        else{
            cout<<"No elements in the queue"<<endl;
        }
        }
        int top(){
            if(current_size==0){
                return 0;
            }
            return p_que[0];
        }
};

class MinHeap{
    private:
        int* p_que;
        int current_size;
        int capacity;
    
    public:
        MinHeap(){
            capacity=100000;
            p_que = new int[100000];
            current_size=0;
        }

        int size(){
            return current_size;
        }

        void resize(int size){
            int twice=size*2;
            int* sp_que = new int[twice];
            for(int i=0; i<=current_size; i++){
                sp_que[i]=p_que[i];
            }
            delete [] p_que;
            p_que=sp_que;
            capacity=twice;
        }

        void minHeapifyTheTree(int root_index){
            int left_child=2*root_index+1;
            int right_child=2*root_index+2;
            int min_el=root_index;
            static int count=1;
            if(left_child<current_size && p_que[left_child]<p_que[min_el]){
                min_el=left_child;
            }
            if(right_child<current_size && p_que[right_child]<p_que[min_el]){
                min_el=right_child;
            }
            if(min_el!=root_index){
                int temp=p_que[min_el];
                p_que[min_el]=p_que[root_index];
                p_que[root_index]=temp;
                minHeapifyTheTree(min_el);
            }
        }
        int curr(){
            return current_size;
        }
        void push(int el){
            if(current_size==(capacity+1)){
                resize(capacity);
            }
            p_que[current_size]=el;
            current_size++;  //probably remove it later
            int start_index=(current_size/2)-1;
                for(int i=start_index; i>=0; i--){
                    minHeapifyTheTree(i);
                }
        }
        void pop(){
            if(current_size!=0){
            p_que[0]=p_que[current_size-1];
            current_size--;
            int start_index=(current_size/2)-1;
            minHeapifyTheTree(0);
        }
        else{
            cout<<"No elements in the queue"<<endl;
        }
        }
        int top(){
            if(current_size==0){
                return 0;
            }
            return p_que[0];
        }
};

int main(){
    MaxHeap set1, set2;
    MinHeap obj1, obj2;

    int n, d;
    int start=0, balance=0;
    int element, freeMaggi=0;
    cin>>n>>d;
    int end=d;
    float med[n];
    int sales[n];
    for(int i=0;i<n;i++){
        cin>>sales[i];
    }
   float median=sales[0];
    set1.push(sales[0]);
    for(int i=1;i<n;i++){
        float x=sales[i];
        if(set1.size()>obj1.size()){
            if(x<median){
                obj1.push(set1.top());
                set1.pop();
                set1.push(x);
            }
            else
                obj1.push(x);
            median=(set1.top()+obj1.top())/2.0;
        }
        else if(set1.size()==obj1.size()){
            if(x<median){
                set1.push(x);
                median=(double)set1.top();
            }
            else{
                obj1.push(x);
                median=(double)obj1.top();
            }
        }
        else{
            if(x>median){
                set1.push(obj1.top());
                obj1.pop();
                obj1.push(x);
            }
            else
                set1.push(x);
            median=(set1.top()+obj1.top())/2.0;
        }
        // cout<<median<<endl;
        if(x>median){
            freeMaggi++;
        }
    }
    freeMaggi;
    cout<<freeMaggi;
}