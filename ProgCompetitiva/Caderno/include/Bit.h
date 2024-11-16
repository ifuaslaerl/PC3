#ifndef BIT_H
#define BIT_H

#include <bits/stdc++.h>
using namespace std ;

template <class T> 
class Bit{

    private:

        int n ;
        T neutral = 0 ;
        vector<T> lista , bit ;

        T merge(T val1, T val2);

        T merge_in_range(int l, int r, T seg_value , T lazy_value );

        //void unlazy(int index, int l, int r);

        T search_query(int l, int r, int l0, int r0, int index);

        void seg_single_update(int l, int r, int pos, T value, int index);

        //void lazy_propagation(int l, int r, int l0, int r0, T value, int index);

        void build(int l, int r, int index);

    public:

        Bit(vector<T>& lista_);

        T query(int l, int r);

        void single_update(int pos, T value);

        void range_update(int l, int r, T value);

} ;

#endif