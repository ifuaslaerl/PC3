#ifndef SPARCE_TABLE_H
#define SPARCE_TABLE_H

#include <bits/stdc++.h>
using namespace std ;

template <typename T>
class SparceTable{

    private: 

        const int n ;
        int k ;
        vector<T> lista ;
        vector<vector<T>> sparcetable ;

    public:

        SparceTable(int n) ;
        void insert(int indice, T val) ;
        void build() ;
        T f(T a, T b) ;
        int log2_floor(unsigned long long i) ;
        T SparceTableQuery(int l , int r) ;

} ;

#endif