#ifndef SQRT_H
#define SQRT_H

#include <bits/stdc++.h>
using namespace std ;

template <typename T>
class SQRT{

    private:

        const T initializer ;
        int n , q , b , b_ , k ; 
        vector<T> lista , blocos_resp , lista_lazy , blocos_resp_lazy ;
        vector<vector<T>> blocos ;
    
    public:

        SQRT(int);
        void update(T&, T);
        void view_data();
        void build();
        void insert(int, T);
        void lazy_update(int, int, T);
        T lazy_query(int);
        T query(int, int);

} ;

#endif