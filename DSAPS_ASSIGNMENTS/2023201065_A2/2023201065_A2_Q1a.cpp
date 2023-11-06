#include<iostream>
using namespace std;
int mode;

class PriorityQueue{
    private:
        int* p_que;
        int current_size;
        int capacity;
    
    public:
        // int* p_que;
        // int current_size;
        // int capacity;
        PriorityQueue(int x){
            capacity=x;
            p_que = new int[x];
            current_size=0;
            // cout<<capacity<<endl;
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
            current_size++;
            cout<<current_size<<" is the size"<<endl;   //probably remove it later
            int start_index=(current_size/2)-1;
            if(mode){
            if(current_size>1){
                for(int i=start_index; i>=0; i--){
                    maxHeapifyTheTree(i);
                }
            }
            }
            else{
                if(current_size>1){
                for(int i=start_index; i>=0; i--){
                    minHeapifyTheTree(i);
                }
            }
            }
            for(int i=0;i<current_size;i++){
                cout<<p_que[i]<<" ";
            }
            cout<<endl;

        }

        void pop(){
            if(current_size!=0){
            p_que[0]=p_que[current_size-1];
            current_size--;
            int start_index=(current_size/2)-1;
            if(mode){
                    maxHeapifyTheTree(0);
            }
            else{
                    minHeapifyTheTree(0);
            }
            for(int i=0;i<current_size;i++){
                cout<<p_que[i]<<" ";
            }
            cout<<endl;
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
        bool empty(){
            if(current_size==0){
                return true;
            }
            return false;
        }

};


int main(){
    int x, y, input;
    cin>>x;
    PriorityQueue pq(x);
    cout<<"MAX or MIN Queue: ";
    cin>>mode;
    while(true){
        cout<<"choose a case: ";
        cin>>input;
        // cout<<endl;
        switch (input)
        {
        case 1: {
            //will see later
            break;
        }
        case 2: {
            cout<<pq.size()<<endl;
            break;
        }
        case 3: {
            cin>>y;
            pq.push(y);
            break;
        }
        case 4: {
            int x=pq.top();
            cout<<x<<endl;
            break;
        }
        case 5: {
            pq.pop();
            break;
        }
        case 6: {
            if(pq.empty()){
                cout<<"True"<<endl;
            }
            else{
                cout<<"False"<<endl;
            }
            break;
        }
        
        default:
            break;
        }
    }
    return 0;
}