#include <bits/stdc++.h>
using namespace std ;

vector<bool> crivo(int n){ // O(nlogn)
    vector<bool> eh_primo(n+1) ;
    vector<int> sieve ;

    for(int i=2 ; i*i<=n ; i++ ){
        for(int j=i+i ; j<=n ; j+=i ){
            eh_primo[j]=false ;
        }
    }

    for(int i=1 ; i<=n ; i++) if(eh_primo[i]) sieve.push_back(i) ;
    return eh_primo ;
}

vector<long long> prefix(vector<int> &lista){ // O(n)
    const int n = lista.size() ;
    vector<long long> prefixo(n+1) ;

    for(int i=1 ; i<=n ; i++) prefixo[i] = prefixo[i-1] + lista[i] ;
    return prefixo ;
    // para queries de range = prefix[r+1] - prefix[l]
}

vector<int> index_compression(vector<long long> &lista){ // O(nlogn)
    const int n = lista.size() ;
    int id=0 ;
    vector<int> asw ;
    vector<long long> ord ;
    map<long long,int> indice ;

    // crio uma copia ordenada da lista
    ord = lista ;
    sort(ord.begin(),ord.end()) ;

    // defino um indice menor para cada elemento diferente da lista 
    for(int i=0 ; i<n ; i++) if(indice.count(ord[i])==0) indice[ord[i]] = id++ ;

    // monto a resposta com os indices ja definidos 
    asw.resize(n) ;
    for(int i=0 ; i<n ; i++) asw[i] = indice[lista[i]] ;

    return asw ;
} 

// a lista precisa estar ordenada
int bb(vector<long long> &lista , long long x ){ // o(logn) 
    const int n = lista.size() ;
    int l=0 , r=n-1 , asw=0 ;

    while(l<=r){
        int md = (l+r)/2 ;

        if(lista[md]>=x){
            asw = md ;
            r = md-1 ;
        }
        else l = md+1 ;
    }

    if(lista[asw]==x) return asw ;
    return -1 ;
}