#include <iostream>
#include <string>

using namespace std;

long long int PowMod(int x, long long int power, long long int p) {
    long long int result = 1;

    for(int i = 1; i <= power; i++) {
        result = (result * x) % p;
    }
    return result % p;
}

long long int h(string& str, int x, int m, long long int p, long long int* Power) {

    int l = str.length();
    long long int hash = 0;

    for(int i = 0; i < l; i++) {
        hash = hash + ( ((int) str[i]) * Power[i] );
    }

    return (hash % p) % m;
}

void PushPower(int x, long long int p, long long int* P, int lP) {

    long long int result = 1;

    P[0] = 1;

    for(int i = 1; i < lP; i++) {
        result = (result * x) % p;

        P[i] = result % p;
    }

}


void PushHesh(long long int p, int x, long long int* Power, string& Text, long long int* Hesh, int m, int lT, int lP) {

     Hesh[lT - lP] = 0;
     for(int i = 0; i < lP; i++) {
         Hesh[lT - lP] = Hesh[lT - lP] + ((int)Text[lT-lP+i]) * Power[i];
     }
     Hesh[lT - lP] = Hesh[lT - lP] % p;


     for(int i = 1; i <= lT - lP; i++) {
         Hesh[lT - lP - i] = (((Hesh[lT - lP - i + 1] - ((int)Text[lT -i]) * Power[lP - 1] % p) % p + p) % p * x +
                 (int)Text[lT - lP - i]) % p;
     }

     for(int i = 0; i < lT - lP + 1; i++) {
         Hesh[i] = Hesh[i] % m;
     }
}

bool verify(string& Pattern, int lP, string& Text, int i) {
    for(int j = 0; j < lP; j++) {
        if(Pattern[j] != Text[i+j]) {
            return 0;
        }
    }
    return 1;
}

void FindPattern(string& Pattern, long long int p, int x, int m, string& Text,  long long int* Hesh,
                 long long int* Power, int lT, int lP) {

    long long int heshPattern = h(Pattern, x, m, p, Power);

    for(int i = 0; i < lT-lP+1; i++) {
        if( heshPattern == Hesh[i] ) {
            if(verify(Pattern, lP, Text, i)) {
                cout << i << " ";
            }
        }
    }
}

int main()
{
    string Pattern;
    string Text;

    long long int* Power;
    long long int* Hesh;

    int lP, lT;

    int x = 263;
    int m = 300;
    long long int p = 1000000007;

    cin >> Pattern;
    cin >> Text;

    lP = Pattern.length();
    lT = Text.length();


    Power = new long long int [lP];
    Hesh = new long long int [lT - lP + 1];

    PushPower(x, p, Power, lP);
    PushHesh(p, x, Power, Text, Hesh, m, lT, lP);

    FindPattern(Pattern, p, x, m, Text, Hesh, Power, lT, lP);


    delete [] Power;
    delete [] Hesh;

    return 0;
}
