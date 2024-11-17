#include <bits/stdc++.h>
using namespace std ;

// funcoes usadas
void solve(vector<pair<int,int>> &resp , int n , int inicio , int fim , int auxiliar) ;

int main(){

    int n ;
    vector<pair<int,int>> resposta ;

    cin >> n ;

    solve( resposta, n , 1 , 3 , 2 ) ;

    cout << resposta.size() << endl ;
    for(pair<int,int> par : resposta) cout << par.first << " " << par.second << endl ;

    return 0 ;
}

void solve(vector<pair<int,int>> &resp , int n , int inicio , int fim , int auxiliar){

    // caso de parada
    if(n==0) return ;

    solve( resp , n-1 , inicio , auxiliar , fim ) ; // move a parte de cima do inicio pro auxiliar
    resp.push_back( { inicio , fim } ) ; // move o maior disco do inicio para o fim
    solve( resp , n-1 , auxiliar , fim , inicio ) ; // move o resto que ficou no auxiliar para o fim

}