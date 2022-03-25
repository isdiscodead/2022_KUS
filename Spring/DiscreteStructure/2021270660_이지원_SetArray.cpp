#include <iostream>

using namespace std;


class Set {
    char p[26]; // 실제 원소들이 저장될 배열
    int size;   // 원소의 갯수
public:
    Set() { size = 0; }
    Set(const char *s);
    friend ostream &operator<<(ostream &out, Set s); // Set 객체 출력을 연산자
    Set operator+(char newElement);                  // 원소 추가
    Set operator|(Set op2);                          // 합집합
    Set operator&(Set op2);                          // 교집합
    friend bool operator<=(Set op1, Set op2);        // op1이 op2의 부분집합인지 평가
    friend Set operator~(Set s);                     // 여집합(전체 집합 = 소문자 전체)
    friend Set operator-(Set op1, Set op2);          // 차집합
};


// 출력
ostream &operator<<(ostream &out, Set s) {
    if (!s.size) {
        cout << "{ }";
        return out;
    }

    out << "{";
    
    for (int i = 0; i < s.size; i++)
        out << s.p[i] << ", ";
    
    out << "\b\b}";

    return out;
}


// 생성자함수
Set::Set(const char *s) {
    this->size = strlen(s);
    int idx = 0;
    int cnt = 0;

    for ( int i=0 ; i < size ; i++ ) {
        bool flag = false;

        // 이미 존재하는 원소인지 확인
        for (int j=0 ; j<size ; j++ ) {
            if ( this->p[j] == s[i] ) {
                flag = true;
            }
        }

        // 이미 존재하는 원소가 아닐 때만 추가
        if ( ! flag ) {
            this->p[idx] = s[i];
            idx++;
        } else {
            cnt++;
        }
    }

    // 겹치는 만큼 size 줄임
    size -= cnt;
}


// 원소 추가
Set Set::operator+(char newElement) {
    bool flag = false;

    for (int i=0 ; i<size ; i++ ) {
        if ( this->p[i] == newElement ) {
            flag = true;
        }
    }

    if ( ! flag ) {
        this->p[size] = newElement;
        this->size++;
    }
    
    return *this;
}                


// 합집합
Set Set::operator|(Set op2) {
    char *temp = new char[size+op2.size];
    int i;

    // 일단 원본 복사
    for ( i=0 ; i < size ; i++ ) {
        temp[i] = this->p[i];
    }

    // 이후로는 op2 돌면서 안 겹치면 추가
    for ( int j=0 ; j < op2.size ; j++ ) {
        bool flag = false;

        for ( int k=0 ; k < strlen(temp) ; k++ ) {
            if ( op2.p[j] == temp[k] ) {
                flag = true;
            }
        }

        if ( ! flag ) {
            temp[i] = op2.p[j];
            i++;
        }
    } 

    Set result(temp);
    return result;
}              


// 교집합
Set Set::operator&(Set op2) {
    char *temp = new char[size];
    for ( int i=0 ; i < size ; i++ ) {
        for ( int j=0 ; j < size ; j++ ) {
            if ( op2.p[i] == this->p[j] ) {
                temp[i] = op2.p[i];
            } 
        }
    }
    Set result(temp);
    return result;
}             


// op1이 op2의 부분집합인지 평가
bool operator<=(Set op1, Set op2) {
    bool result = true;
    for (int i=0 ; i < op1.size ; i++ ) {
        if ( ! result ) {
            break;
        }
        for ( int j=0 ; j < op2.size ; j++ ) {
            if ( op1.p[i] != op2.p[j] ) {
                result = false;
            } else {
                result = true;
                break;
            }
        }
    }
    return result;
}      


// 여집합(전체 집합 = 소문자 전체)
Set operator~(Set s) {
    // 여집합 사이즈만큼으로 동적 할당
    char *alpha;
    int size = 26 - s.size;
    alpha = new char[size];
    int code = 'a';

    for (int i=0 ; i<size ; i++ ) {
        bool flag = false;
        for (int j=0 ; j<s.size ; j++ ) {
            if ( code == s.p[j] ) {
                flag = true;
            }
        }
        if ( !flag ) {
            alpha[i] = code;
        } else {
            i--;
        }
        code ++;
    }

    Set result(alpha);
    return result;
}               


// 차집합
Set operator-(Set op1, Set op2) {
    // 교집합을 구한 다음 op1에서 교집합에 포함되는 애 삭제 ... 
    Set inter = op1&op2;
    char *tmp;
    int size = op1.size - inter.size;
    tmp = new char[size];
    int idx = 0;

    for (int i=0 ; i<op1.size ; i++ ) {
        bool flag = false; 
        for (int j=0 ; j<inter.size ; j++ ) {
            if ( op1.p[i] == inter.p[j] ) {
                flag = true;
            }
        }
        if ( !flag ) {
            tmp[idx] = op1.p[i];
            cout << op1.p[i];
            idx++;
        }
    }   

    Set result(tmp);
    return result;
}   



int main() {
    Set s1, s2("mathematics"), s3, s4;
    
    s3 = s3 + 't' + 'e' + 's' + 't' + 'i' + 'n' + 'g'; //원소 삽입
    cout << "s1 = " << s1 << "\ns2 = " << s2 << "\ns3 = " << s3 << "\n\n";
    
    s1 = s2 & s3; //교집합
    cout << s2 << " ∩ " << s3 << " = " << s1 << "\n\n";
   
    s1 = s2 | s3; //합집합
    cout << s2 << " u " << s3 << " = " << s1 << "\n\n";
    
    s4 = s1 - s3; //차집합
    cout << s1 << " - " << s3 << " = " << s4 << "\n\n";
    
    s4 = ~s1; //여집합
    cout << "~" << s1 << " = " << s4 << "\n\n";
    
    if (s2 <= s1) //부분집합인지 검사
        cout << s2 << " ⊆ " << s1 << "\n\n";
    if (!(s2 <= s3))
        cout << s2 << " is not susbset of " << s3 << "\n\n";

    // 근데 함수 내에서 동적할당 받은 애들 반환 어케하지? ㅠㅠ 따로 안 해도 되나
    
    return 0;
}