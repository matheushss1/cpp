#include <iostream>
using namespace std;

// Since the numbers after the iteration 95 has more than 20 digits, need to create a class to store these numbers.
// In this case, we just need the R/W, equal and sum operators (and the fibonacci).
class BigNumber {
    string algarisms;
public:
    // Constructors
    BigNumber(unsigned long long n = 0);
    BigNumber(string &);
    BigNumber(const char *);
    BigNumber(BigNumber &);

    // Declaring the operators
    int operator[](const int)const;

    // Helper
    friend int Length(const BigNumber &);

    //Direct assignment
    BigNumber &operator=(const BigNumber &);

    // Operators & Incrementors
    BigNumber &operator++();
    BigNumber operator++(int temp);
    friend BigNumber &operator+=(BigNumber &, const BigNumber &);
    friend BigNumber operator+(const BigNumber &, const BigNumber &);
    friend bool operator==(const BigNumber &, const BigNumber &);

    // R/W
    friend ostream &operator<<(ostream &,const BigNumber &);
    friend istream &operator>>(istream &, BigNumber &);

    // fibonacci
    friend BigNumber fibonacci(int n);
};
BigNumber::BigNumber(string & s){
    algarisms = "";
    int n = s.size();
    for (int i = n - 1; i >= 0;i--){
        if(!isdigit(s[i]))
            throw("ERROR");
        algarisms.push_back(s[i] - '0');
    }
}
BigNumber::BigNumber(unsigned long long n){
    algarisms = "";
    while(n > 0){
        algarisms.push_back(n % 10);
        n /= 10;
    }
}
BigNumber::BigNumber(BigNumber & a){
    algarisms = a.algarisms;
}
int BigNumber::operator[](const int index)const{
    if(algarisms.size() <= index || index < 0)
        throw("ERROR");
    return algarisms[index];
}
int Length(const BigNumber & a){
    return a.algarisms.size();
}
bool operator==(const BigNumber &a, const BigNumber &b){
    return a.algarisms == b.algarisms;
}
BigNumber &BigNumber::operator=(const BigNumber &a){
    algarisms = a.algarisms;
    return *this;
}
BigNumber &BigNumber::operator++(){
    int i, n = algarisms.size();
    for (i = 0; i < n && algarisms[i] == 9;i++)
        algarisms[i] = 0;
    if(i == n)
        algarisms.push_back(1);
    else
        algarisms[i]++;
    return *this;
}
BigNumber BigNumber::operator++(int temp){
    BigNumber auxiliar;
    auxiliar = *this;
    ++(*this);
    return auxiliar;
}
BigNumber &operator+=(BigNumber &a,const BigNumber& b){
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if(m > n)
        a.algarisms.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n;i++){
        if(i < m)
            s = (a.algarisms[i] + b.algarisms[i]) + t;
        else
            s = a.algarisms[i] + t;
        t = s / 10;
        a.algarisms[i] = (s % 10);
    }
    if(t)
        a.algarisms.push_back(t);
    return a;
}
BigNumber operator+(const BigNumber &a, const BigNumber &b){
    BigNumber temp;
    temp = a;
    temp += b;
    return temp;
}

istream &operator>>(istream &in,BigNumber&a){
    string s;
    in >> s;
    int n = s.size();
    for (int i = n - 1; i >= 0;i--){
        if(!isdigit(s[i]))
            throw("INVALID NUMBER");
        a.algarisms[n - i - 1] = s[i];
    }
    return in;
}

ostream &operator<<(ostream &out,const BigNumber &a){
    for (int i = a.algarisms.size() - 1; i >= 0;i--)
        cout << (short)a.algarisms[i];
    return cout;
}

BigNumber fibonacci(int n){
    BigNumber a(1), b(1), c;
    if (!n)
        return c;
    n--;
    while(n--){
        c = a + b;
        b = a;
        a = c;
    }
    return b;
}


int main() {
    int numberOfIterations = 100;
    for (int i = 0; i <= numberOfIterations; i++) {
        if (i == 0){
            cout << "0" << endl;
            continue;
        }
        BigNumber Fibonacci;
        Fibonacci = fibonacci(i);
        cout << Fibonacci <<'\n';
    }
    return 0;
}