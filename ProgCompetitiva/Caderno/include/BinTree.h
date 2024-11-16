#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <bits/stdc++.h>
using namespace std ;

template <typename T>
struct Node{
        
        T value ;
        *Node l = nullptr ;
        *Node r = nullptr ;

} ;

template <typename T>
class Tree{

    private:

        Node root ;
        void Tree::dfs() ;
        void Tree::bfs() ;
        
    public:

        Tree::Tree(Node);
        bool Tree::search(Node, T) ;
        void Tree::insert(T) ;
        void Tree::remove(T) ;


} ;

#endif