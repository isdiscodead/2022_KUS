#include <iostream>
using namespace std;

bool is_reflexive(int** A, int n);
bool is_symmetric(int** A, int n);
bool is_antisymmetric(int** A, int n);
bool is_transitive(int** A, int n);

// transitive 판별을 위한 행렬 제곱 함수
int** square(int** A, int n);

int main(void) {
    int size;   
    string str;

    // input size 
    cout << "[ Relation R on X의 정보 입력 ]" << endl;
    cout << "X의 원소의 개수: ";
    cin >> size;

    // 행렬로 사용할 2차원 배열 동적 할당
    int** matrix = new int*[size];
    for ( int i=0 ; i<size ; i++ ) {
        matrix[i] = new int[size];
    }

    // input 
    cout << "relation R의 행렬 입력: " << endl;
    for ( int i=0 ; i<size ; i++ ) {
        cin >> str;
        for ( int j=0 ; j<size ; j++ ) {
            matrix[i][j] = int(str[j])-48;
        }
    }

    // output 
    cout << "--- Relation R의 matrix 표현 ---" << endl;
    for ( int i=0 ; i<size ; i++ ) {
        for ( int j=0 ; j<size ; j++ ) {
            cout << " " << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "---------------------------------" << endl;
    cout << endl << "R is" << endl;

    // computation part 
    bool flag_partial = true; // partial order check 
    bool flag_equivalence = true; // partial order check 

    if ( is_reflexive(matrix, size) ) {
        cout << "  - reflexive" << endl;
    } else {
        flag_partial = false;
        flag_equivalence = false;
    }

    if ( is_symmetric(matrix, size) ) {
        cout << "  - symmetric" << endl;
    } else {
        flag_equivalence = false;
    }

    if ( is_antisymmetric(matrix, size) ) {
        cout << "  - antisymmetric" << endl;
    } else {
        flag_partial = false;
    }

    if ( is_transitive(matrix, size) ) {
        cout << "  - transitive" << endl;
    } else {
        flag_partial = false;
        flag_equivalence = false;
    }

    if ( flag_partial ) {
        cout << "  - partial order" << endl;
    }

    if ( flag_equivalence ) {
        cout << "  - equivalence relation" << endl;
    }

    return 0;
} 

// reflexive -> 대각 원소가 모두 1
bool is_reflexive(int** A, int n) {
    for( int i=0 ; i<n ; i++ ) {
        if ( ! A[i][i] ) {
            return false;
        }
    }
    return true;
}

// symmetric -> 대칭 원소가 동일
bool is_symmetric(int** A, int n) {
    for( int i=0 ; i<n ; i++ ) {
        for ( int j=0 ; j<i ; j++ ) {
            if ( A[i][j] != A[j][i] ) {
                return false;
            }
        }
    }
    return true;
}

// antisymmetric -> 대칭 원소가 둘다 0이거나 하나만 1
bool is_antisymmetric(int** A, int n) {
    for( int i=0 ; i<n ; i++ ) {
        for ( int j=0 ; j<i ; j++ ) {
            if ( A[i][j] && A[j][i] ) {
                return false;
            }
        }
    }
    return true;
}

// 행렬 곱을 통해 판별 ... 
bool is_transitive(int** A, int n) {
    int** C = square(A, n);

    for( int i=0 ; i<n ; i++ ) {
        for ( int j=0 ; j<n ; j++ ) {
            if ( C[i][j] && (!A[i][j]) )  {
                cout << C[i][j] << A[i][j] << endl;
                return false;
            }
        }
    }
    return true;
}

// 행렬 제곱 
int** square(int** A, int n) {
    // 제곱 결과 매트릭스
    int** result = new int*[n];
    for ( int i=0 ; i<n ; i++ ) {
        result[i] = new int[n];
        for ( int j=0 ; j<n ; j++ ) {
            result[i][j] = 0;
        }
    }

    for( int i=0 ; i<n ; i++ ) {
        for ( int j=0 ; j<n ; j++ ) {
            for ( int k=0 ; k<n ; k++ ) {
                result[i][j] += A[i][k]*A[k][j];
            }
        }
    }

    return result;
}