#include <iostream>
using namespace std;

// ICP-ISP 테이블 함수
int isp(char ch) {
    switch ( ch ) {
        case '^':   
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        case '(':
            return 0;
        case '#':
            return -1;
        default:
            return ch;
    }
}

int icp(char ch) {
    switch ( ch ) {
        case '^':   
            return 4;
        case '*':
        case '/': 
            return 2;
        case '+':
        case '-':
            return 1;
        case '(':
            return 4;
        default:
            return ch;
    }
}

// stack 자료형 구현
// include <stack> 해도 되지만 ... 공부 겸 직접 구현해보자 
class Stack {
    int size=0, top=-1;
    char* stack; // char 배열로 스택 구현

public:
    Stack(int size) {
        this->stack = new char[size+1];
        this->top = -1;
        this->size = size;
    }

    bool isFull() {
        return top == size;
    }

    bool isEmpty() {
        return top == -1;
    }

    char pop() {
        if ( !isEmpty() ) { 
            return stack[top--];
        } else {
            cout << "Stack is Empty!!" << endl;
            return ' ';
        }
    }

    void push(char element) {
        if ( !isFull() ) {
            top ++;
            stack[top] = element;
        } else {
            cout << "Stack is Full!!" << endl;
        }
    }

    char top_element() {
        return stack[top];
    }
};

// infix -> postfix 변환
string inToPost(string infix_exp) {
    Stack s( infix_exp.length() );
    string postfix_exp = "";
    
    s.push('#');

    for( int i=0 ; i<infix_exp.length() ; i++ ) {
        char a = infix_exp[i];
        
        if ( a>='0' && a<='9' ) {
            postfix_exp += a;
            continue; // 반복 지점으로 ...

        } else { // operator or 괄호 
            if ( a == ')' ) { // 왼쪽 괄호인 경우 -> 이제 우선 연산 필요 
                char tmp;
                while (  (tmp=s.pop()) != '(' ) {
                    postfix_exp += tmp;
                }

            } else { // 일반 operator or 괄호 
                while ( true ) {    
                    if ( isp( s.top_element() ) >= icp(a)  ){
                        postfix_exp += s.pop();

                    } else {
                        s.push(a);
                        break;
                    }
                }
            }
            continue;
        }
    }

    // 모든 infix expression 문자열 scan 완료 
    while ( s.top_element() != '#' ) {
        postfix_exp += s.pop();
    }

    return postfix_exp;
}

// postfix 연산
double evalPostFix(string exp) {
    // 근데 operand가 10의 자리 넘어가면 ... 어카지 ... 하
    // 1 . add #
    Stack s( exp.length() );
    s.push('#');

    // 2. scan 
    for (int i=0 ; i < exp.length() ; i++ ) {
        char a = exp[i];
        if ( a>='0' && a<='9' ) { // operand
            s.push(a);

        } else { // operator
            int op2 = int(s.pop())-48;
            int op1 = int(s.pop())-48;
            int tmp;

            char result;
            // 연산자 선택 후 연산
            switch ( a ) {
                case '*' : 
                    result = (char)((op1*op2)+'0'); // 숫자를 char로 만들기 위해 +48 ( 아스키코드 )
                    break;  
                case '/' : 
                    result = (char)((double(op1)/op2)+'0');
                    break; 

                case '^' : 
                    tmp = op1;
                    for ( int i=1 ; i < op2 ; i++ ) {
                        tmp *= op1;
                    }
                    result = (char)((tmp)+'0');
                    break; 

                case '+':
                    result = (char)((op1+op2)+'0');
                    break;  

                case '-':
                    result = (char)((op1-op2)+'0');
                    break;  
            } // end switch

            s.push(result); 
        }
    }

    // 결과 값
    return s.pop()-48;
}

int main(void) {
    string infix = "(1+3)*2/(6-4)^2";
    string postfix = inToPost(infix);
    cout << postfix << " = " << evalPostFix(postfix);

    return 0;
}