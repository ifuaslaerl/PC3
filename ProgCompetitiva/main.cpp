#include <bits/stdc++.h>
using namespace std;

// g++ -Dlocal main.cpp -o main 

#ifdef local
    #include "debug.h"
    #define pr(...) debug(#__VA_ARGS__, __VA_ARGS__)
    #define prs(...) debug_nameless(__VA_ARGS__)
#else
    #define pr(...) 69
    #define prs(...) 69
#endif

#define fastio ios_base::sync_with_stdio(NULL); cin.tie(nullptr)

typedef long long ll ;
const ll INF = 2e18 ;

template <typename T>
class SegTree{

    private:

    int n ;    
    vector<T> lista ;
    T neutral = 0 ; // change

    struct Node{
        T value, lazy = 0 ; // same as neutral, may change
        int left, right ;
        Node *left_node = nullptr, *right_node = nullptr ;
        
        Node(int left_, int right_ , SegTree* tree) : left(left_), right(right_){
            if(left == right){
                value = tree->lista[left] ;
                return ;
            }
            int mid = (left+right)/2 ;
            left_node = new Node(left, mid, tree) ;
            right_node = new Node(mid+1, right, tree) ;
            value = tree->merge(left_node->value, right_node->value) ;
        }
    } ;

    Node *root ;

    T merge(T no1, T no2){ // change
        return no1 + no2 ;
    } 

    void remove(Node *no){
        if(no->left_node != nullptr) remove(no->left_node) ;
        if(no->right_node != nullptr) remove(no->right_node) ;
        delete no ;
    }

    void unlazy(Node *no){ // maybe change for range update queries
        if (no->lazy == neutral) return ;

        no->value += (no->right - no->left + 1) * no->lazy ;
        if(no->left_node != nullptr) no->left_node->lazy += no->lazy ;
        if(no->right_node != nullptr) no->right_node->lazy += no->lazy ;
        no->lazy = neutral ;
        }

    void update(Node *no, int pos, T new_value){
        int l = no->left , r = no->right ;

        pr(l, r, pos) ;
        if(l==r){
            no->value = new_value ;
            lista[l] = new_value ;
            return ;
        }

        int md = (l+r)/2 ;
        if(pos<=md)
            update(no->left_node, pos, new_value) ;
        else
            update(no->right_node, pos, new_value) ;

        no->value = merge(no->left_node->value, no->right_node->value) ;
    }

    void lazy_propagation(Node *no, int l, int r, T value){ // maybe change for range updates
            unlazy(no) ;
            if( no->left > r || no->right < l){
                return ;
            }

            if(no->left >= l && no->right <= r){
                no->lazy = value ;
                unlazy(no) ;
                return ;
            }

            lazy_propagation(no->left_node, l, r, value) ;
            lazy_propagation(no->right_node, l, r, value) ;

            no->value = merge(no->left_node->value, no->right_node->value) ;
    }

    T query(Node *no, int l, int r){
        unlazy(no) ;
        if(no->left > r || no->right < l){ // se ele ta fora do intervalo dado, nao entra.
            return neutral ;
        }

        if(no->left >= l && no->right <= r){ // se ele ta completamente dentro do intervalo dado, entra. Nao existe sobreposicao de intervalos
            return no->value ;
        }

        return merge( query(no->left_node, l, r) , query(no->right_node, l, r) ) ;
    }

    T lower_bound(Node *no, T value){
        if(no->left == no->right){
            return no->left ;
        }

        if(value <= no->left_node->value){
            return lower_bound(no->left_node, value) ;
        }
        
        return lower_bound(no->right_node, value - no->left_node->value) ;
    }

    public:

    SegTree(vector<T> &lista_){
        lista = lista_ ;
        n = lista_.size() ;
        root = new Node(0, n-1, this) ;
    }

    void clear(){
        remove(root) ;
    }

    void update(int pos, T value){
        update(root, pos, value) ;
    }

    void increment(int l, int r, T increment_value){
        lazy_propagation(root, l, r, increment_value) ;
    }

    T query(int l, int r){
        return query(root,l,r) ;
    }

    T lower_bound(T value){
        return lower_bound(root, value) ;
    }

} ;

int main(){
    fastio ;

    int n ;
    vector<long long> lista, queries, indexes ;

    cin >> n ;

    lista.assign(n,0) ;
    for(int i=0 ; i<n ; i++) cin >> lista[i] ;

    queries.assign(n,0) ;
    for(int i=0; i<n ; i++) cin >> queries[i] ;

    indexes.assign(n,1) ;
    SegTree seg(indexes) ;

    for(int i=0 ; i<n ; i++){
        int index = seg.lower_bound(queries[i]) ;
        seg.update(index, 0) ;
        cout << lista[index] << " " ;
    }

    cout << endl ;

    return 0;
}

