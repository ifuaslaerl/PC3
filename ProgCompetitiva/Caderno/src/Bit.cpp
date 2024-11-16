#include <bits/stdc++.h>
using namespace std ;

template <class T> 
class Bit{
    
    private:

        int n ;
        T neutral = 0 ;
        vector<T> lista, bit ;

        T function(T val1, T val2){
            return val1 + val2 ;            
        }

        void add(int index, T value){
            while( index <= n ){
                bit[index] = function( bit[index], value) ;
                index = get_next(index) ; // talvez eu tenha errado aq 
            }
        }

        int get_parent(int index){
            return index -(index & -index) ;
        }

        int get_next(int index){ // todos vertices que contem esse elemento no seu range
            return index +(index & -index) ;
        }

        void build(){
            for(int i=1 ; i<=n ; i++){
                add(i, lista[i-1]) ;
            }
        }

        T prefix(int r){
            T resp = neutral ;
            int index = r+1 ;
            while( index!=0 ){
                resp = function(resp, bit[index]) ;
                index = get_parent(index) ;
            }
            return resp ;
        }

    public:

        Bit(vector<T>& lista_){
            lista = lista_ ;
            n = lista.size() ;
            bit.resize(n+1,neutral) ;
            build() ;
            pr(bit) ;
        }

        void update(int pos, T value){
            add(pos, -lista[pos-1]) ;
            add(pos, value) ;
            lista[pos-1] = value ;
        }

        T query(int l, int r){
            return prefix(r-1) - prefix(l-2) ;
        }

};
