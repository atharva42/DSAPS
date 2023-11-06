#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

const int stack_size=110;
string num_stack[stack_size];
char op_stack[stack_size];
int top=-1;
int top_op=-1;


//Division function beneath


string division(const string& dividend, const string& raw_divisor ){
    long long int divisor= stoi(raw_divisor);
    long long int index=0;
    long long int number=dividend[index]-'0';
    long long int size=dividend.size();
    string result;
    while(size>index){
        if(number<divisor && index<size-1){
        number=number*10+(dividend[++index]-'0');
        result+=0+'0';
        }
        else{
        result+=(number/divisor)+'0';
        // if(number%divisor==0){
        //     result+=0+'0';
        // }
        number=(number%divisor)*10+dividend[++index]-'0';
        }
    }
    int i=0;
    while(result[i]==0){
        i++;
    }
    string r_result=result.substr(i);
    return r_result;
}


//Multiplication function beneath

string multiply(const string& multiplcand, const string& multiplier){
    long long int len1= multiplcand.size();
    long long int len2=multiplier.size();
    long long int product;
    long long int carry;
    long long int tracker=0;
    string result((len1+len2), '0');
    for(int i=len1-1; i>=0;i--){
        carry=0;
        for(int j=len2-1; j>=0; j--){
            product=(multiplcand[i]-'0')*(multiplier[j]-'0')+(result[i+j+1]-'0')+carry;
            carry=product/10;
            result[i+j+1]=product%10+'0';
        }
        result[i]=(carry+result[i]-'0')+'0';
    }
    while(result[tracker]=='0'){
        tracker++;
    }
    return result.substr(tracker, (len1+len2)-tracker);
    }



//addition function beneath

string addition(const string& num1, const string& num2){
    int len1=num1.size();
    int len2=num2.size();
    int carry=0;
    int d1, d2, sum;
    int i=len1-1;
    int j=len2-1;
    string result;
    string temp;
    if(len1!=len2){         //If statement to add two numbers of unequal size
        if(len1>len2){      //If statement to add two numbers when first number has more digits compared to second
        while(j>=0){
        d1 = num1[i]-'0';
        d2 = num2[j]-'0';
        sum = d1 + d2 + carry;
        carry = sum / 10;
        result = to_string(sum % 10) + result;

        if (i >= 0) i--;
        if (j >= 0) j--;
        }
        if(carry!=0){       // If statement to check carry. This if is present inside other two if statements
            while(carry!=0 && i>=0){
                d1=num1[i]-'0';
                sum=d1+carry;
                carry=sum/10;
                result = to_string(sum % 10) + result;
                i--;
            }
            if(carry!=0 && i<0){ // meant to handle cases like 999+1
                result=to_string(carry)+result;
            }
        }
        if(carry==0 || i>=0){ //meant to handle cases like 100+80
                result=num1.substr(0, i+1)+result;
            }
        }
    }
    else{
    while(i>=0){
        int d1 = num1[i]-'0';
        int d2 = num2[j]-'0';
        int sum = d1 + d2 + carry;
        carry = sum / 10;
        result = to_string(sum % 10)+ result;

        if (i >= 0) i--;
        if (j >= 0) j--;
    }
    if(carry!=0){       // If statement to check carry. This if is present inside other two if statements meant to handle cases like 90+10
            while(carry!=0 && i>=0){
                d1=num1[i]-'0';
                sum=d1+carry;
                carry=sum/10;
                result = to_string(sum % 10) + result;
                i--;
            }
            if(carry!=0 && i<0){ // meant to handle cases like 9999+9999
                result=to_string(carry)+result;
            }
        }
    }
    return result;
}


// Subtraction function beneath

string subtract(const string& num1, const string& num2){
    int len1=num1.size();
    int len2=num2.size();
    int tracker=0;
    int borrow=0;
    int diff;
    int d1, d2;
    int i=len1-1;
    int j=len2-1;
    string result;
    if(num1==num2){
        return "0";
    }
    if(len1>len2){
        while(j>=0){
        d1 = num1[i] - '0';
        d2 = num2[j] - '0';
        diff=d1-d2-borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result = to_string(diff) + result;
        if (i >= 0) i--;
        if (j >= 0) j--;
    }   
    if(borrow!=0 && i>=0){      // meant to handle cases like 1000-99 of continous borrowing
        while(i>=0){
        d1 = num1[i] - '0';
        diff=d1-borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result = to_string(diff) + result;
        i--;
    } 
    }
        if(borrow==0 || i>=0){ //meant to handle cases like 9999-1
                result=num1.substr(0, i+1)+result;
            }
    }
    else{
    while(i>=0 || j>=0){
        d1 = num1[i] - '0';
        d2 = num2[j] - '0';
        int diff=d1-d2-borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result = to_string(diff) + result;

        if (i >= 0) i--;
        if (j >= 0) j--;
    }
    }
    while(result[tracker]=='0'){
        tracker++;
    }
    return result.substr(tracker, (len1+len2)-tracker);
}


//Exponent function beneath

string exponent(const string& base, const string& raw_power){
    int power= stoi(raw_power);
    string result="1";
    string curr_base=base;
    while(power>0){
        if(power%2==1){
            result=multiply(result, curr_base);
        }
        curr_base=multiply(curr_base, curr_base);
        power/=2;
    }
   return result;
}


//GCD function is implemented below that also uses moduluss function

string moduluss(const string& dividend, const string& raw_divisor ){
    long long int divisor= stoi(raw_divisor);
    long long int index=0;
    long long int size=dividend.size();
    string noms;
    long long int number=dividend[index]-'0';
    string result;
    while(size>index){
        if(number<divisor && index<size-1){
        number=number*10+(dividend[++index]-'0');
        }
        else{
            if(size-1==index){
                number=(number%divisor);
                return to_string(number);
            }
        result+=(number/divisor)+'0';
        number=(number%divisor)*10+dividend[++index]-'0';
        }
    }
    return to_string(number);
}

string gcd(const string& num1, const string& num2){
    string a = num1;
    string b = num2;
    if(b=="0"){
        return a;
    }
    return gcd(b, moduluss(a,b));

}


//Factorial function beneath


string factorial(const string& number){
    string result;
    if (number == "0" || number == "1") {
         return "1";  
    } 
    else{
        return multiply(number, factorial(subtract(number, "1")));
    }
    return result;
}

//function that determibe precedence of operator is beneath

bool determinePrecedence(char op1, char op2) {
    int precedenceOp1, precedenceOp2;

    if (op1 == '^') precedenceOp1 = 3;
    else if (op1 == '/' || op1 == 'x') precedenceOp1 = 2;
    else if (op1 == '+' || op1 == '-') precedenceOp1 = 1;
    else precedenceOp1 = 0;

    if (op2 == '^') precedenceOp2 = 3;
    else if (op2 == '/' || op2 == 'x') precedenceOp2 = 2;
    else if (op2 == '+' || op2 == '-') precedenceOp2 = 1;
    else precedenceOp2 = 0;

    return precedenceOp1 >= precedenceOp2;
}

//function that push and pop both operand and operator is beneath

string pop_num() {
    string value;
        if (top == -1) {
            cout << "Stack is empty";
            return "";
        } else {
            value = num_stack[top];
            top--;
        }
    return value;
}

char pop_op(){
    char value;
    if (top_op == -1) {
            cout << "Operator Stack is empty";
            return ' ';
        } else {
            value = op_stack[top_op];
            top_op--;
            return value;
        }
}


void push_num(string val) {
        if (top < stack_size - 1) {
            top++;
            num_stack[top] = val;
        } else {
            cout << "Stack is full";
        }
}

void push_op(char c){
        if (top_op < stack_size - 1) {
            top_op++;
            op_stack[top_op] = c;
        } else {
            cout << "Operator Stack is full";
        }
}

//function that call respective function to do their repesctive task.

string performOperation(const string& a, const string& b, char op) {
    if (op == '+') {
        if(a.size()<b.size()){
            return addition(b, a);
        }
        return addition(a, b);
    }
    else if (op == '-') return subtract(a, b);
    else if (op == 'x') return multiply(a, b);
    else if (op == '/') return division(a, b); 
    else if (op == '^') return exponent(a, b);
    return "0";
}

//function that converts infix expression to postfix is implemented beneath

string expressionEvaluate(const string& expr) {
    string postfix;
    for (char c : expr) {
        if (isdigit(c)) {
            postfix += c;
        } else if (c == '/' || c == 'x' || c == '+' || c == '-' || c == '^') {
            postfix += ' ';
            while (top_op >= 0 && op_stack[top_op] != '(' && determinePrecedence(op_stack[top_op], c)) {
                postfix += op_stack[top_op--];
                postfix += ' ';
            }
            push_op(c);
        } else if (c == '(') {
            push_op(c);
            postfix+=' ';
        } else if (c == ')') {
            while (top_op >= 0 && op_stack[top_op] != '(') {
                postfix += op_stack[top_op--];
                postfix += ' ';
            }
            if (top_op>= 0 && op_stack[top_op] == '(') top_op--; // Pop '('
        }
    }

    while (top_op >= 0) {
        postfix += ' ';
        postfix += op_stack[top_op--];
    }
    return postfix;
}

//function that evaluates the postfix expression is beneath

string postfixEvaluate(const string& postfix) {
    top = -1;
    for (size_t i = 0; i < postfix.size(); ++i){
        if (isdigit(postfix[i])) {
            string operand;
            while ((i < postfix.size() && (isdigit(postfix[i]))) || postfix[i] == '.') {
                operand += postfix[i];
                ++i;
            }
            --i;

            push_num(operand);
        }
            else if (postfix[i] == ' ') {
            continue;
        } else { 
            string operand2 = pop_num();
            string operand1 = pop_num();
            char op=postfix[i];
            string result = performOperation(operand1, operand2, op);
            push_num(result);
        }
    }
    string finalResult = pop_num();
    return finalResult;
}



//Main function beneath

int main()
{   int choice, testcase;
    string result_final;
    cin>>testcase;
    cin>>choice;
    for(int i=0;i<testcase;i++){
    switch(choice)
    {
    case 1: {
        string input_expr;
        cin>>input_expr;
        string postfix = expressionEvaluate(input_expr);
        result_final = postfixEvaluate(postfix);
        cout <<result_final << endl;
        break;
    }

    case 2:{
        string base;
        string power;
        string in_put;
        cin>>base;
        cin>>power;
        result_final=exponent(base, power);
        cout<<result_final<<endl;
        break;
        }

    case 3:{
        string num1;
        string num2;
        cin>>num1;
        cin>>num2;
        result_final=gcd(num1, num2);
        cout<<result_final<<endl;
        break;
    }

    case 4:{
        string num;
        cin>>num;
        result_final=factorial(num);
        cout<<result_final<<endl;
        break;
    }
    
    default:
        break;
    }
    }
    return 0;
}