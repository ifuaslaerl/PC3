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

#define fastio ios_base::sync_with_stdio(false);cin.tie(nullptr)

typedef long long ll ;

const int inf = 2e9 ;

int n , m ;
pair<int,int> start ;
vector<pair<int,int>> monsters , options , possible_ways_out ;
vector<vector<bool>> vis ;
vector<vector<int>> monster_steps , steps , mapa ;
vector<vector<char>> grid ;
vector<char> translate ;

void BFS_mapa(vector<pair<int,int>> sources , vector<vector<int>> &step_count ) ;
void BFS_out(pair<int,int> coord) ;
bool inside(int a, int b) ;
string way_out() ;

template <typename T>
void printGrid(const vector<vector<T>>& grid) {
    for (const auto& row : grid) {
        for (const auto& elem : row) {
            cout << elem << " " ;
        }
        cout << "\n" ;
    }
    cout << "\n" ;
}

int main(){
    fastio;

    options = {
        {0,1} ,
        {1,0} ,
        {0,-1} ,
        {-1,0} 
    } ;

    translate = {
        'R' ,
        'D' ,
        'L' ,
        'U' 
    } ;

    cin >> n >> m ;

    steps.resize(n,vector<int>(m,inf)) ;
    monster_steps.resize(n,vector<int>(m,inf)) ;
    mapa.resize(n,vector<int>(m,-1)) ;
    vis.resize(n,vector<bool>(m)) ;
    grid.resize(n,vector<char>(m)) ;
    
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<m ; j++){ 
            cin >> grid[i][j] ;
        }
    }

    // guardar as coordenadas importantes
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<m ; j++){
            if(grid[i][j] == 'M'){
                monsters.push_back({i,j}) ;
            }
            else if(grid[i][j]=='A'){
                mapa[i][j] = -2 ;
                start = {i,j} ;
            }
        }
    }

    // montar mapas
    BFS_mapa({start},steps) ;
    BFS_mapa(monsters,monster_steps) ;
    BFS_out(start) ;

    /*
    // debug
    printGrid(vis) ;
    printGrid(mapa) ;
    printGrid(steps) ;
    printGrid(monster_steps) ;
    */

    // procurar um caminho valido a partir de cada saida encontrada
    string asw = way_out() ;

    if(possible_ways_out.size()!=0){
        cout << "YES\n" ;
        cout << asw.size() << "\n" ;
        cout << asw << "\n" ;
    }
    else cout << "NO\n" ;

    return 0;
}

void BFS_mapa(vector<pair<int,int>> sources , vector<vector<int>> &step_count ){

    queue<pair<pair<int,int>,int>> fila ;
    for(auto pos : sources) fila.push({pos,0}) ;

    while(!fila.empty()){

        int x = fila.front().first.first ;
        int y = fila.front().first.second ;
        int count = fila.front().second ;
    
        fila.pop() ;

        if(step_count[x][y]!=inf) continue ;
        step_count[x][y] = count ;  

        for(auto [i,j] : options){
            if(!inside(x+i,y+j)) continue ;
            if(step_count[x+i][y+j]==inf && grid[x+i][y+j]!='#'){
                fila.push({{x+i,y+j},count+1}) ;
            }
        }

    }

}

void BFS_out(pair<int,int> coord){

    queue<pair<int,int>> fila ;
    fila.push(coord) ;

    while(!fila.empty()){

        int x = fila.front().first ;
        int y = fila.front().second ;
        fila.pop() ;

        if(vis[x][y]) continue ;
        vis[x][y] = true ;

        if(x==n-1||x==0) possible_ways_out.push_back({x,y}) ;
        if(y==m-1||y==0) possible_ways_out.push_back({x,y}) ;

        for(int k=0 ; k<4 ; k++){
            auto [i,j] = options[k] ;
            
            if(!inside(x+i,y+j)) continue ;
            if(vis[x+i][y+j]) continue ;
            if(grid[x+i][y+j]=='#') continue ;

            if(monster_steps[x+i][y+j]>steps[x+i][y+j]){
                mapa[x+i][y+j] = k ;
                fila.push({x+i,y+j}) ;
            }
        }

    }

}

bool inside(int a, int b){
    if(a<0  || b<0 ) return false ;
    if(a>=n || b>=m) return false ;
    return true ;
}

string way_out(){
    string resp ;
    for(auto [x,y] : possible_ways_out){
        // verificar se eh possivel chegar nessa saida

        int passo = mapa[x][y] ;
        while(passo!=-2){
            resp+=translate[passo] ;
            auto [i,j] = options[passo] ;
            passo = mapa[x-=i][y-=j] ; 
        }

        reverse(resp.begin(),resp.end()) ;
        return resp ;

    }

    return "" ;

}