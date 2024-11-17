#include <bits/stdc++.h>
#define int long long
#define fastio cin.tie(0), ios_base::sync_with_stdio(0)
using namespace std;

int n, m , k;
vector<vector<int>> sensores ;
vector<int> vertice_componente ;
vector<bool> vis ;
vector<pair<bool,bool>> componente_parede ; 

void dfs(int v , int comp){
    vis[v] = true ;
    vertice_componente[v] = comp ;

    //cout << v << " " ;

    int x0 = sensores[v][0] , y0 = sensores[v][1] , s0 = sensores[v][2] ;
    
    if(x0+s0>=m || y0-s0<=0) componente_parede[comp].first  = true ;
    if(x0-s0<=0 || y0+s0>=n) componente_parede[comp].second = true ;

    for(int i=0 ; i<k ; i++){
        int x = sensores[i][0] , y = sensores[i][1] , s = sensores[i][2] ;
        if( !vis[i] && (x-x0)*(x-x0) + (y-y0)*(y-y0) <= (s+s0)*(s+s0) ){
            dfs(i,comp) ;
        }
    }
}

signed main(){
    fastio;
    
    cin >> m >> n >> k;

    vis.resize(n,false) ;
    vertice_componente.resize(n,-1) ;
    sensores.resize(n,vector<int>(3)) ;
    
    for(int i=0 ; i<k ; i++){
        int x , y , s ;
        cin >> x >> y >> s ;
        sensores[i][0] = x ;
        sensores[i][1] = y ;
        sensores[i][2] = s ;
    }

    int id=0 ;
    for(int i=0 ; i<k ; i++){
        if(!vis[i]){
            //cout <<  "\ncomponente " << id << " = " ;
            componente_parede.push_back({false,false}) ;
            dfs(i,id++) ;
        }
    }

    for(auto par : componente_parede){
        //cout << "\n" << par.first << " " << par.second << "\n" ;
        if( par.first == true && par.second == true ){
            cout << "N\n" ; return 0 ;
        }
    }

    cout << "S\n" ; return 0 ;

}