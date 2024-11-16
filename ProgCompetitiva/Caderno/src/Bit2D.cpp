template <class T> 
class Bit2D{
    
    private:

        int n, m ;
        T neutral = 0 ;
        vector<vector<T>> grid, bit ;

        T function(T val1, T val2){
            return val1 + val2 ;            
        }

        void add(int x, int y, T value){
            for(int index=x ;index<=n ; index = get_next(index)){
                for(int jndex=y ; jndex<=m; jndex = get_next(jndex)){
                    bit[index][jndex] = function( bit[index][jndex], value) ;
                }
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
                for(int j=1 ; j<=m ; j++){
                    add(i, j, grid[i-1][j-1]) ;
                }
            }
        }

        T prefix(int x, int y){
            T resp = neutral ;
            // x++ ; y++ ;
            for(int index = x ;index>0 ; index = get_parent(index)){
                for(int jndex = y ; jndex>0; jndex = get_parent(jndex)){
                    resp = function(resp, bit[index][jndex]) ;
                }
            }
            return resp ;
        }

    public:

        Bit2D(vector<vector<T>>& grid_){
            grid = grid_ ;
            n = grid.size() ;
            m = grid[0].size() ;
            bit.resize(n+1,vector<T>(m+1,neutral)) ;
            build() ;
        }

        void update(int x, int y){
            int old_ = grid[x-1][y-1] ;
            add(x, y, -old_) ;
            int new_ = (old_==1? 0 : 1) ;
            grid[x-1][y-1] = new_ ;
            add(x, y, new_) ;
        }

        T query(int x1, int y1, int x2, int y2){
            x1-- ; y1-- ;
            return prefix(x2,y2) - prefix(x2,y1) - prefix(x1,y2) + prefix(x1,y1) ; 
        }

};