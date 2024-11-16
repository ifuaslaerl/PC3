#include "BinTree.h"
#include <bits/stdc++.h>
using namespace std ;

template <typename T>
class Tree{

    private:

        Node root ;

        void Tree::dfs() ;
        void Tree::bfs() ;
        
    public:

        Tree::Tree(Node root_){
            root = root_ ;
        }

        *Node Tree::search(Node node, T value){

            if (value > node.value && node.r != nullptr){
                return search(node.r, value) ;
            }    

            if (value < node.value && node.l != nullptr){
                return search(node.l, value) ;
            }

            if ( value == node.value ){
                return &node ;
            }

            return nullptr ;

        }

        void Tree::insert(Node node, T value){
            if (value >= node.value){
                if (node.r != nullptr){
                    insert(node.r, value) ;
                }
                else{
                    node.r = &value ;
                }
            }    

            else if (value < node.value){
                if(node.l != nullptr){
                    insert(node.l, value) ;
                }
                else{
                    node.l = &value ;
                }
            }
        
            return ;
        }

        void Tree::remove(Node node, T value){
            if (value > node.value && node.r != nullptr){
                
                if (node.r.value == value){
                    node.r = nullptr ;
                    return 
                }

                remove(node.r , value) ;

            }    

            if (value < node.value && node.l != nullptr){
                return search(node.l, value) ;
            }
        }


} ;
