#include <openssl/evp.h>
#include<iostream>
#include<map>
using namespace std;
bool openssl_sm3_hash(const unsigned char *input,unsigned char* buffer,unsigned int* buf_len)
{
    memset(buffer, 0, *buf_len);
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!EVP_DigestInit_ex(ctx, EVP_sm3(), NULL)) {
        cout << "Failed to init" << endl;
        return false;
    }
    if (!EVP_DigestUpdate(ctx, input,64)) {
        cout << "Failed to update" << endl;
        return false;
    }

    if (!EVP_DigestFinal_ex(ctx, buffer, buf_len)) {
        cout << "Failed to final" << endl;
        return false;
    }

    EVP_MD_CTX_free(ctx);
    return true;
}
//map<unsigned int, map<unsigned int, map<unsigned int, map<unsigned int,bool>>>> f;//128bit
map<unsigned int, map<unsigned int, int>> f;//64bit
//map<unsigned int, int> f;//32bit

const bool CHECK=0;

bool check_32bit(unsigned int, unsigned int);
bool check_64bit(unsigned int, unsigned int);

int main() {
    if (CHECK) {
        unsigned int x, y;
        cin >> x >> y;
        if (check_64bit(x, y)) {
            printf("Right\n");
        }
        else {
            printf("Wrong\n");
        }
        return 0;
    }
    unsigned char s[64];
    unsigned char buf[100];
    unsigned int len=64 ;
    srand(19260817);
    for (int t = 0; 1;t++) {
        if (t % 1000000 == 0) {
            printf("%d\n", t / 1000000);
        }
        for (int i = 0; i < 16; i++) {
            *((int*)s + i) = rand();
        }
        openssl_sm3_hash(s, buf, &len);
        //64bit
        unsigned int a = *((int*)buf), b = *((int*)buf + 1);
        if (f.find(a) != f.end() && f[a].find(b) != f[a].end() ) {
            printf("found %d,%d\n", f[a][b], t);//0 134217728
            break;
        }
        else {
            f[a][b] = t;
        }/*
        //32bit
        unsigned int a = *((unsigned int*)buf);
        if (f.find(a)!=f.end()) {
            printf("found %d,%d\n",f[a],t);//37626 92666
            break;
        }
        else {
            f[a] = t;
        }*/
    }
    return 0;
}
bool check_32bit(unsigned int x, unsigned int y) {
    unsigned char s[64];
    unsigned char buf[100];
    unsigned int len = 64;
    srand(19260817);
    if (x > y) swap(x, y);
    unsigned int a=0, b=0;
    for (int i = 0; i < 100000000; i++) {
        if (i != x && i != y) {
            for (int i = 0; i < 16; i++) {
                rand();
            }
            continue;
        }          
        for (int i = 0; i < 16; i++) {
            *((int*)s + i) = rand();
        }
        openssl_sm3_hash(s, buf, &len);
        if (i == x)    a = *(unsigned int*)buf;
        else {
            b = *(unsigned int*)buf;
            break;
        }
    }
    return a == b;
}
bool check_64bit(unsigned int x, unsigned int y) {
    unsigned char s[64];
    unsigned char buf[100];
    unsigned int len = 64;
    srand(19260817);
    if (x > y) swap(x, y);
    unsigned long long a = 0, b = 0;
    for (int i = 0; 1; i++) {
        if (i != x && i != y) {
            for (int i = 0; i < 16; i++) {
                rand();
            }
            continue;
        }
        for (int i = 0; i < 16; i++) {
            *((int*)s + i) = rand();
        }
        openssl_sm3_hash(s, buf, &len);
        if (i == x)    a = *(unsigned long long*)buf;
        else {
            b = *(unsigned long long*)buf;
            break;
        }
    }
    return a == b;
}

