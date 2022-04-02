#include <iostream>
using namespace std;

/*
다항식의 덧셈 -> 계수(coefficient)와 지수(exponent)로 나누어 판단 및 계산
*/

class linked_term {
public:
    // setter
    linked_term(const float &coef, const int &exp, linked_term* link) {
        this->coef = coef;
        this->exp = exp;
        this->link = link;
    }
    void set_coef(const float &coef) {
        this->coef = coef;
    }
    void set_exp(const int &exp) {
        this->exp = exp;
    }
    void set_link(linked_term* link) {
        this->link = link;
    }

    // getter 
    float get_coef() {
        return this->coef;
    }
    int get_exp() {
        return this->exp;
    }
    linked_term* get_link() {
        return this->link;
    }

    friend void linked_term_insert(const float &coef, const int &exp, linked_term* &head_ptr);

    // add operator function
    friend linked_term* add(linked_term* op1, linked_term* op2) {
        linked_term* result = new linked_term(0,0,NULL);
        
        while ( op1->link && op2->link ) { // 둘 다 남아있을 때 
            // 같은 지수항일 경우
            if ( op1->exp == op2->exp ) {
                result->exp = op1->exp;
                if ( op1->coef + op2->coef ) { // 더해서 0이면 그 다음으로 ... 
                    result->coef = op1->coef + op2->coef;
                    op1 = op1->link;
                    op2 = op2->link;
                } else {
                    op1 = op1->link; op2 = op2->link;
                    continue;
                }
                
            } else if ( op1->exp > op2->exp ) { // op1의 항이 더 클 경우 
                result->exp = op1->exp;
                result->coef = op1->coef;
                op1 = op1->link;

            } else { // op2의 항이 더 클 경우
                result->exp = op2->exp;
                result->coef = op2->coef;
                op2 = op2->link;
            }

            cout << result->get_coef() << "x^" << result->get_exp() << " "; 

            // 다음 result 노드 추가
            result->link = new linked_term(0,0,result);
            result = result->link;
        }

        while ( op1->link || op2->link ) {
            if ( op1->link ) {
                result->exp = op1->exp;
                result->coef = op1->coef;
                op1 = op1->link;

            } else {
                result->exp = op2->exp;
                result->coef = op2->coef;
                op2 = op2->link;
            }

            cout << result->get_coef() << "x^" << result->get_exp() << " "; 

            // 추가 후 result 노드 추가
            result = new linked_term(0,0,result);
            result = result->link;
        }

        // 마지막 항 
            if ( op1 && op2 ) {
                result->exp = op1->exp;
                result->coef = op1->coef + op2->coef;
            } else {
                if ( op1 ) {
                result->exp = op1->exp;
                result->coef = op1->coef;
            } 
                if ( op2 ) {
                result->exp = op2->exp;
                result->coef = op2->coef;
            }
            }
            
            cout << result->get_coef() << "x^" << result->get_exp() << " "; 
        
        return result;
    }

private:
    float coef;
    int exp;
    linked_term *link; // link field
};

void linked_term_insert( const float &coef, const int &exp, linked_term* &previous_ptr ) {
    linked_term *insert_ptr = new linked_term(coef, exp, previous_ptr->link);
    previous_ptr -> set_link(insert_ptr); // 추가된 노드의 주소로 link
    previous_ptr = previous_ptr->get_link();
}


class term {
public: 
    term(const float &coef, const int &expk) {
        this->coef = coef;
        this->exp = exp;
    }

    // setter 
    void set_coef(const float &coef) {
        this->coef = coef;
    }
    void set_exp(const int &exp) {
        this->exp = exp;
    }

    // getter 
    float get_coef() {
        return this->coef;
    }
    int get_exp() {
        return this->exp;
    }

    // add operator function
    friend term* add(term* op1, term* op2) {
        if ( sizeof(op1) != sizeof(op2) ) {

        }
        return op1;
    }


private:    
    float coef;
    int exp;
};


int main(void) {
    linked_term* op1 = NULL; // head
    linked_term* op2 = NULL; // head 
    linked_term* tail1 = NULL;
    linked_term* tail2 = NULL;

    term* op1_arr = NULL;
    term* op2_arr = NULL;

    // -3x^3 +5x^2 -7x +9 
    op1 = new linked_term(-3, 3, op1);
    tail1 = op1;
    linked_term_insert(5, 2, tail1);
    linked_term_insert(-7, 1, tail1);
    linked_term_insert(9, 0, tail1);
    cout << endl;

    // 2x^2 +7x -4
    op2 = new linked_term(2, 2, op2);
    tail2 = op2;
    linked_term_insert(7, 1, tail2);
    linked_term_insert(-4, 0, tail2);
    cout << endl;

    linked_term* result = add(op1, op2);

    return 0;
}