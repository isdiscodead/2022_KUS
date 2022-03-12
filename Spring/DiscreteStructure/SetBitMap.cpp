#include <iostream>

using namespace std;


class BitSet {
    int BitMap;

public:
    BitSet() { BitMap = 0; }
    BitSet(const char s[]);
    friend ostream &operator<<(ostream &out, BitSet s);
    BitSet operator+(char newElement);               //원소 추가
    BitSet operator|(BitSet op2);                    //합집합
    BitSet operator&(BitSet op2);                    //교집합
    friend bool operator<=(BitSet op1, BitSet op2);  // op1이 op2의 부분집합인지 평가
    friend BitSet operator~(BitSet s);               // 여집합(전체 집합 = 소문자 전체)
    friend BitSet operator-(BitSet op1, BitSet op2); //차집합
};


// 출력
ostream &operator<<(ostream &out, BitSet s) {
    if (!s.BitMap) {
        out << "{ }";
        return out;
    }
    int temp = s.BitMap;
    out << "{";
    for (int i = 0; i < 26; i++) {
        // temp & 1의 값이 있으면 맨 끝자리 (1)이 존재함 
        if (temp & 1)
            out << (char)('a' + i) << ", ";
        // 맨 끝자리 한 칸 밀어서 다음 인덱스 확인 
        temp >>= 1;
    }
    out << "\b\b}";
    return out;
}


// 생성자
BitSet::BitSet(const char s[]) {
    this->BitMap = 0;
    for ( int i=0 ; i < strlen(s) ; i++ ) {
        int tmpIdx = s[i]-'a';
        int tmpBit = 1;
        for ( int j=0 ; j < tmpIdx ; j++ ) {
            tmpBit *= 2;
        }
        this->BitMap = this->BitMap | tmpBit;
    }
}

// 원소 추가
BitSet BitSet::operator+(char newElement) {
    // Element에 포함되는 문자열 ( 알파벳 )을 구해 그 인덱스의 값을 1로 만들어야 함
    // 인덱스늕 뒤에서부터 0으로 시작
    int tmpIdx = newElement - 'a';
    int tmpBit = 1;
    // 인덱스 위치에 1이 들어간 정수로 만들어줌
    for (int i=0 ; i<tmpIdx ; i++ ) {
        tmpBit *= 2;
    }
    // or 연산으로 추가
    this->BitMap = this->BitMap | tmpBit;
    return *this;
}            


//합집합
BitSet BitSet::operator|(BitSet op2) {
    BitSet tmp;
    tmp.BitMap = this->BitMap | op2.BitMap;
    return tmp;
}                 

//교집합
BitSet BitSet::operator&(BitSet op2) {
    BitSet tmp;
    tmp.BitMap = this->BitMap & op2.BitMap;
    return tmp;
}

// op1이 op2의 부분집합인지 평가
bool operator<=(BitSet op1, BitSet op2) {
    bool flag = true;
    int tmp1 = op1.BitMap;
    int tmp2 = op2.BitMap;
    if ( (tmp1 & tmp2) != tmp1 ) {
        flag = false;
    }
    return flag;
}

// 여집합(전체 집합 = 소문자 전체)
BitSet operator~(BitSet s) {
    BitSet tmp;
    tmp.BitMap = ~ s.BitMap;
    return tmp;
}           


//차집합
BitSet operator-(BitSet op1, BitSet op2) {
    // 차집합 = A 교집합 B^c
    BitSet tmp;
    tmp = op1 | (~op2);
    return tmp;
}


// 생성자함수와 나머지 연산자 함수 정의
int main() {
    BitSet s1, s2("mathematics"), s3, s4;
    
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
    
    return 0;
}