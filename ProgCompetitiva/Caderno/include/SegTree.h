#ifndef SEG_TREE_H
#define SEG_TREE_H

#include <bits/stdc++.h>
using namespace std ;

template <class T> 
class SegTree{

    private:

        int n ;
        T neutral = 0 ;
        vector<T> lista , seg, lazy ;

        T merge(T val1, T val2);

        T merge_in_range(int l, int r, T seg_value , T lazy_value );

        void unlazy(int index, int l, int r);

        T search_query(int l, int r, int l0, int r0, int index);

        void seg_single_update(int l, int r, int pos, T value, int index);

        void lazy_propagation(int l, int r, int l0, int r0, T value, int index);

    public:

        SegTree(vector<T>& lista_);

        void build(int l, int r, int index);

        T query(int l, int r);

        void single_update(int pos, T value);

        void range_update(int l, int r, T value);

} ;

#endif