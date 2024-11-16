#include <bits/stdc++.h>
using namespace std;

template <class T> 
class Prefix2D{

    private:

        int n, m ;
        T neutral = 0 ;
        vector<vector<T>> grid, prefix ;

        void build(){
            for(int i=1 ; i<=n ; i++){
                for(int j=1 ; j<=m ; j++){
                    prefix[i][j] = grid[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] ;
                    //pr(i,j,prefix[i][j]) ;
                }
            }
        }

    public:

        Prefix2D(vector<vector<T>>& grid_){
            grid = grid_ ;
            n = grid_.size() ;
            m = grid[0].size() ;
            prefix.resize(n+1,vector<T>(m+1,neutral)) ;
            build() ;
            pr(prefix) ;
        }

        T query(int x1, int y1, int x2, int y2){
            x1-- ; y1-- ;
            pr(x1,y1) ;
            pr(x2,y2) ;
            return prefix[x2][y2] - prefix[x2][y1] - prefix[x1][y2] + prefix[x1][y1] ; 
        }

};