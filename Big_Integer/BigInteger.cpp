#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

// constructor and destructor
BigInteger::BigInteger(){
    signum = 0;
    List digits;
}

BigInteger::BigInteger(std::string s){
    if(s.size() == 0){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    int dig = 0;
    bool num = false;
    std::string enter = "";
    signum = s[0] == '-'?-1:1;
    for(int i = s.size()-1; i >= 0; i--){
        if(s[i] >= 48 && s[i] <= 57){
            num = true;
            dig++;
            enter += s[i];
            if(dig == POWER){
                enter = std::string(enter.rbegin(),enter.rend());
                digits.insertAfter(std::stol(enter));
                dig = 0;
                enter = "";
            }
        }else if(i == 0 && num == true && (s[0] == '+' || s[0] == '-')){
            continue;
        }else{
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }
    if(enter.size() != 0){
        enter = std::string(enter.rbegin(),enter.rend());
        digits.insertAfter(std::stol(enter));
    }
    digits.moveFront();
    while(digits.front() == 0){
        digits.eraseAfter();
    }
}

BigInteger::BigInteger(const BigInteger& N){
    this->signum = N.signum;
    digits = N.digits;
}

// Access functions --------------------------------------------------------
int BigInteger::sign() const{
       return signum;
   }

int BigInteger::compare(const BigInteger& N) const{
    List A = this->digits;
    List B = N.digits;
    if(A.length() != B.length()){
        return A.length() > B.length()?1:-1;
    }
    A.moveFront();
    B.moveFront();
    while(A.position() < A.length() && B.position() < B.length()){
        if(sign()*A.moveNext() > N.sign()*B.moveNext()){
            return 1;
        }else if(this->sign()*A.peekPrev() < N.sign()*B.peekPrev()){
            return -1;
        }
    }
    return 0;
   }

// Manipulation procedures -------------------------------------------------
void BigInteger::makeZero(){
    digits.List::clear();
    signum = 0;
}

void BigInteger::negate(){
    if(signum != 0){
        signum = signum==-1?1:-1;
    }
}

// private function
// param: List
// return: None
// func: add two big integer together
void vectorCal(List&S,List A, List B, int sig, int sigA, int sigB){
    A.moveBack();
    B.moveBack();
    while(A.position() > 0 || B.position() > 0){
        if(B.position() == 0){
            S.insertAfter(sigA*A.movePrev());
        }else if(A.position() == 0){
            S.insertAfter(sigB*sig*B.movePrev());
        }else{
            S.insertAfter(sigA*A.movePrev()+sig*sigB*B.movePrev());
        }
    }
    S.moveFront();
    while(S.position() != S.length()){
        if(S.moveNext() == 0){
            S.eraseBefore();
        }else{
            break;
        }
    }
    
}

//private function
// param: List
// return: Int-sign
// func: clean up the list to keep the elements in list have the same amount
//       of digits
int normalize(List&L){
    
    if(L.length() == 0){
        return 0;
    }
    //check sign
    int sign = L.front()<0?-1:1;
    L.moveBack();
    int carry = 0;

    while(L.position() != 0){
        ListElement data = L.movePrev();
        data += carry;
        if(sign == 1){
            if((data/BASE)> 0){
                L.setAfter((data%BASE));
                carry = (data/BASE);
            }else if(data < 0){
                L.setAfter((data+BASE));
                int mul = data/BASE>=1?data/BASE:1;
                carry = -1 * mul;
            }else{
                L.setAfter(data);
                carry = data/BASE;
            }
        }else{
            if(data < 0){
                L.setAfter((data%BASE)*-1);
                carry = (data/BASE);
            }else if(data > 0){
                L.setAfter((data-BASE)*-1);
                int mul = data/BASE>=1?data/BASE:1;
                carry = 1 * mul;
            }else{
                L.setAfter(data);
                carry = data/BASE;
            }
        }
    }
    if(carry != 0){
        carry = carry<0?carry*-1:carry;
        L.insertBefore(carry);
    }
    return sign;
}

// private function
// param: List,Int
// return: None
// func: shift the list to the left by p power
void shiftList(List &L, int p){
    L.moveBack();
    while(p != 0){
        L.insertAfter(0);
        p--;
    }
}

// private function
// param:
// return: 
// func: 
void scalarMultList(List &L, ListElement m){
    L.moveFront();
    while(L.position() != L.length()){
        ListElement data = L.moveNext() * m;
        L.setBefore(data);
    }

}

//private function
// param: List,List,List,Int,Int
// return: Int-
// func: multiplying two big integer
int multOp(List &S, List A, List B,int sigA,int sigB){
    B.moveBack();
    int shift = 0;
    int sign;
    if(A.length() == 0 || B.length() == 0){
        sign = 0;
    }else{
        sign = sigA==sigB?1:-1;
    }

    while(B.position() != 0){
        List C = A;
        ListElement mul = B.movePrev();
        if(mul != 1){
            scalarMultList(C,mul);
        }
        shiftList(C,shift);
        normalize(C);
        if(S.length() != 0){
            S.moveBack();
            C.moveBack();
            while(C.position() != 0){
                if(S.position() > 0){
                    S.setAfter(S.movePrev()+C.movePrev());
                }else if(S.position() == 0){
                    S.insertBefore(C.movePrev());
                    S.moveFront();
                }
            }
        }else{
            S = C;
        }
        //std::cout << std::endl;
        //std::cout << "S: " << S << std::endl;
        normalize(S);
        //std::cout << "norm S: " << S << std::endl;
        shift++;
    }
    //std::cout << "S: " << S << std::endl;
    sign = normalize(S)==0?0:sign;
    return sign;
}

// private function
// param: List
// return: None
// func: remove all leading zeros
void cleanup(List&S){
    if(S.length() > 0){
        S.moveFront();
        while(S.front() == 0){
            S.eraseAfter();
        }
    }

}
// BigInteger Arithmetic operations ----------------------------------------
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger out;
    vectorCal(out.digits,this->digits,N.digits,1,this->signum,N.signum);
    out.signum = normalize(out.digits);
    cleanup(out.digits);
    return out;
}

BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger out;
    vectorCal(out.digits,this->digits,N.digits,-1,this->signum,N.signum);
    out.signum = normalize(out.digits);
    cleanup(out.digits);
    return out;
}

BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger out;
    out.signum = multOp(out.digits,this->digits,N.digits,this->signum,N.signum);
    cleanup(out.digits);
    //std::cout << out.digits << std::endl;
    return out;
}

 // Other Operation
std::string BigInteger::to_string(){
    if(signum == 0){
        return "0";
    }
    digits.moveFront();
    std::string s = signum==-1?"-":"";
    //std::cout << digits << std::endl;
    while(digits.position() != digits.length()){
        ListElement num = digits.moveNext();
        if(digits.position() == 1){
            s += std::to_string(num);
        }else{
            int precision = POWER-1;
            ListElement t = num/10;
            while(t != 0){
                t /= 10;
                precision--;
            }
            s += std::string(precision,'0').append(std::to_string(num));
        }
    }   
    return s;
}

 // OverLoad Operation
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

bool operator==(const BigInteger &A, const BigInteger &B){
    return A.compare(B) == 0?true:false;
}

bool operator<(const BigInteger &A, const BigInteger &B){
    return A.compare(B) == -1?true:false;
}

bool operator<=(const BigInteger &A, const BigInteger &B){
    return A.compare(B) <= 0?true:false;
}

bool operator>(const BigInteger &A, const BigInteger &B){
    return A.compare(B) == 1?true:false;
}

bool operator>=(const BigInteger &A, const BigInteger &B){
    return A.compare(B) >= 0?true:false;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

BigInteger operator+=(BigInteger &A, const BigInteger &B){
    BigInteger newInt = A.add(B);
    std::swap(A,newInt);
    return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

BigInteger operator-=(BigInteger &A, const BigInteger &B){
    BigInteger newInt = A.sub(B);
    std::swap(A,newInt);
    return A;
}

BigInteger operator*(const BigInteger &A, const BigInteger &B){
    return A.mult(B);
}

BigInteger operator*=(BigInteger &A, const BigInteger &B){
    BigInteger newInt = A.mult(B);
    std::swap(A,newInt);
    return A;
}

