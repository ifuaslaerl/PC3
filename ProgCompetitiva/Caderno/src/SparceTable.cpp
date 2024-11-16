#include "SparceTable.h"
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

        SparceTable::SparceTable(int n_){
            n = n_ ;
            lista.resize(n_) ;
        }

        void SparceTable::insert(int indice, T val){
            if(indice<0 || indice>=n) return ;
            lista[indice] = val ;
        }

        void SparceTable::build(){
            k = log2_floor(n)+1 ;
            sparcetable.resize(k+1,vector<int>(n)) ;

            for(int i=0 ; i<n ; i++){
                sparcetable[0][i] = lista[i] ; 
            }

            for(int i=1 ; i<=k ; i++){
                for(int j=0 ; j<n ; j++){
                    sparcetable[i][j] = f(sparcetable[i-1][j],sparcetable[i-1][j+(1<<(i-1))]) ;
                }
            }
        }

        T SparceTable::f(T a, T b){
            return min(a,b) ;
        }

        int SparceTable::log2_floor(unsigned long long i){ // depende da versao do c++
            return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1 ;
        }

        T SparceTable::SparceTableQuery(int l , int r){
            int i = log2_floor(r-l+1) ;
            return f(sparcetable[i][l], sparcetable[i][r - (1 << i) + 1]) ;
        }

} ;
