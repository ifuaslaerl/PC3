#include <bits/stdc++.h>
using namespace std ;

typedef long long ll ;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL) 

const ll BigINF = 2*(1e18) ;
const int INF = 2*(1e9) ;

void setIO(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

// Basicos
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

vector<long long> Prefix(vector<int> &lista){ // O(n)

    const int n = lista.size() ;
    vector<long long> prefixo(n+1) ;

    for(int i=1 ; i<=n ; i++) prefixo[i] = prefixo[i-1] + lista[i] ;

    return prefixo ;

    // para queries de range = prefix[r+1] - prefix[l]

}

vector<int> compress_indice(vector<long long> &lista){ // O(nlogn)
    
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

// Grafos
class Grafo{

    public : 

        Grafo(int num){
            n = num ;
            t=0 ;
            componentes_conexos=0 ;
            adj.resize(n+1) ;
            vis.resize(n+1) ;
            low.resize(n+1) ;
            pre.resize(n+1) ;
            prof.resize(n+1) ;
            pais.resize(n+1) ;
            grau_entrada.resize(n+1) ;
            grau_saida.resize(n+1) ;
        }
        
        // tipo == 0 : direcionado
        // tipo == 1 : bidirecionado
        void add_edge(int tipo, int a, int b){ // O(1)
            adj[a].insert(b) ;
            grau_entrada[b]++ ;
            grau_saida[a]++ ;
            if(tipo){
                adj[b].insert(a) ;
                grau_entrada[a]++ ;
                grau_saida[b]++ ;
            }
        }

        void unvis(){ // O(n)
            fill(vis.begin(),vis.end(),false) ;
        }

        void clear(){ // O(n)
            t = 0 ;
            unvis() ;
            fill(low.begin(),low.end(),0) ;
            fill(pre.begin(),pre.end(),0) ;
            fill(prof.begin(),prof.end(),0) ;
            fill(pais.begin(),pais.end(),0) ;
        } 

        void build_grafo(){ // O(n+m)
            for(int i=1 ; i<=n ; i++){
                if(!vis[i]){
                    componentes_conexos++ ;
                    dfs_tree(i,-1,0) ;
                }
            }
            clear() ;
        }

        // testar depois
        vector<int> Topo_sort(){ // O(n+m)

            vector<int> ord ;
            queue<int> fila ;

            for(int i=1 ; i<=n ; i++){
                if( !grau_entrada[i] ){
                    fila.push(i) ;
                    vis[i]=true ;
                }
            }

            while(!fila.empty()){
                
                int v = fila.front() ;
                fila.pop() ;

                if(!grau_entrada[v]) ord.push_back(v) ;
                grau_entrada[v]-- ;
                if(!grau_entrada[v]) ord.push_back(v) ;
                
                for(int prox : adj[v]){
                    if(!vis[prox]){
                        vis[v] = true ;
                        fila.push(prox) ;
                    }
                }

            }

            return ord ;

        }

        void dfs(int v){ // O(n+m)
            vis[v]=true ;
            for(int prox : adj[v]){
                if(!vis[prox]) dfs(prox) ;
            }
        }

        void bfs(int start){ // O(n+m)

            queue<int> fila ;
            fila.push(start) ;
            vis[start] = true ;

            while(!fila.empty()){
                
                int v = fila.front() ;
                fila.pop() ;

                for(int prox : adj[v]){
                    if(!vis[prox]){
                        vis[prox]=true ;
                        fila.push(prox) ;
                    }
                }

            }

        }

    protected : 

        void dfs_tree( int v , int pai , int deep ){ // O(n+m)
            
            t++ ;
            low[v] = pre[v] = t ;
            prof[v] = deep ;
            pais[v] = pai ;
            vis[v] = true ;

            bool artic_point=false ;
            int filhos=0 ;
            for(int prox : adj[v]){
                
                if(!vis[prox]){
                    
                    filhos++ ;
                    dfs_tree(prox,v,deep+1) ;
                    low[v] = min(low[v],low[prox]) ;

                    if(low[prox]>=pre[v]) artic_point=true ;

                }
                
                else{
                    if(prox==pai) continue ;
                    low[v] = min(low[v],pre[prox]) ;
                }
            
            }
            
            if( v!=1 && low[v]==pre[v] ) pontes.push_back({pai,v}) ;
            if( v!=1 && artic_point    ) artic.push_back(v) ;
            if( v==1 && filhos >= 2    ) artic.push_back(v) ;

        }

        void dfs_max_dist(int v, int prof, int &u , int &dist){
            vis[v]=true ;

            if(prof>dist){
                dist=prof ;
                u = v ;
            }

            for(int prox : adj[v]){
                if(!vis[prox]) dfs_max_dist(prox,prof+1,u,dist) ;
            }
        }

        int n , t , componentes_conexos ;
        vector<int> prof , low , pre , artic , pais , grau_entrada , grau_saida ;
        vector<bool> vis ;
        vector<pair<int,int>> pontes ;
        vector<set<int>> adj ;

} ;

class Arvore : public Grafo{

    public: 
    
        Arvore(int num, int raiz) : Grafo(num){
            n = num ; 
            raiz = raiz ;
            jumps.resize(33,vector<int>(n+1,-1)) ;
        }

        void build_arvore(int raiz){
            dfs_tree(raiz,-1,0) ; // preenche os vetores de lowlink e profundidade
            unvis() ;
            binery_lifting(pais,raiz) ;
        }

        void binery_lifting(vector<int> &lista_base, int raiz){ // O(n)
            
            for(int i=1 ; i<=n ; i++){
                if(i==raiz) continue ;
                jumps[0][i] = lista_base[i] ;
            }

            for( int k=1 ; k<33 ; k++ ){
                for( int i=2 ; i<=n ; i++ ){
                    if(jumps[k-1][i]==-1) continue ;
                    jumps[k][i] = jumps[k-1][jumps[k-1][i]] ;
                }
            }

        }

        pair<int,int> nivelar(int u , int v){ //O(logn)

            if( prof[u] > prof[v] ){

                for( int i = 32 ; i >= 0 ; i-- ){
                    if( (1LL<<i) & abs(prof[u]-prof[v]) ) u = jumps[i][u] ;
                }
                
            }

            else if( prof[u] < prof[v] ){

                for( int i = 32 ; i >= 0 ; i-- ){
                    if( (1LL<<i) & abs(prof[u]-prof[v]) ) v = jumps[i][v] ;
                }

            }

            return {u,v} ;

        }

        int lca(int u, int v){ // O(logn)
            
            pair<int,int> temp = nivelar(u,v) ;
            int a = temp.first ; // u nivelado
            int b = temp.second ; // v nivelado
            
            if( a == b ) return a ;
        
            for( int i = 32 ; i >= 0 ; i-- ){
                if( jumps[i][a] != jumps[i][b] ){
                    a = jumps[i][a] ;
                    b = jumps[i][b] ;
                }
            }
        
            if(pais[a]==pais[b] && pais[a] != -1) return pais[a] ;

            return -1 ;

        }

        // testar depois
        int diametro(){ // O(n+m)
            
            int vertice_distante=0 , vertice_distante2=0 , distancia=0 ;
            
            dfs_max_dist(1,0,vertice_distante,distancia) ;
            unvis() ;
            distancia = 0 ;
            dfs_max_dist(vertice_distante,0,vertice_distante2,distancia) ;

            return distancia ;

        }

    protected :

        // n eh o numero de vertices
        // grafo eh o grafo
        // jumps[k][i] e o resultado de 2^k passos a partir de i

        int n , raiz ;
        vector<vector<int>> jumps ;

} ;

// Estruturas de dados
struct SparceTable{

    // n eh o tamanho da lista
    // lista eh a lista original
    // sparcetable eh uma lista que trabalha com a resposta de subconjuntos para gerar a resposta de um conjunto maior

    const int n ;
    int k ;
    vector<long long> lista ;
    vector<vector<int>> sparcetable ;

    SparceTable(int n) : n(n) , lista(n) {}

    void insert(int indice, int val){ // O(1)
        if(indice<0 || indice>=n) return ;
        lista[indice] = val ;
    }

    void build(){ // O(nlogn*O(f))

        k = log2_floor(n)+1 ;
        sparcetable.resize(k+1,vector<int>(n)) ;

        for(int i=0 ; i<n ; i++){
            sparcetable[0][i] = lista[i] ; 
        }

        for(int i=1 ; i<=k ; i++){
            for(int j=0 ; j<n ; j++){
                sparcetable[i][j] = f(sparcetable[i-1][j],sparcetable[i-1][j+(1<<(i-1))]) ;
            }
        }

    }

    int f(int a, int b){ // O(1) // customisavel
        return min(a,b) ;
    }

    int log2_floor(unsigned long long i){ // O(1)
        return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1 ;
    }

    int SparceTableQuery(int l , int r){ // O(f)

        int i = log2_floor(r-l+1) ;
        return f(sparcetable[i][l], sparcetable[i][r - (1 << i) + 1]) ;

    }

} ;

class SQRT{

    const ll initializer=0 ;
    int n , q , b , b_ , k ; 

    // n = tamanho da lista
    // q = quantidade de queries 
    // b = tamanho de cada bloco
    // b_ = tamanho do ultimo bloco
    // k = quantidade de blocos

    vector<long long> lista , blocos_resp , lista_lazy , blocos_resp_lazy ;
    vector<vector<long long>> blocos ; // puramente pra debugar

    SQRT(int n) : n(n) , lista(n) {}

    void insert(int indice , ll valor){ lista[indice] = valor ;}

    void change(ll &resp , ll value){ resp = resp+value ; }
    void change(ll &resp , int value ){ resp = resp+value ; }

    void build(){
        
        k = (int) sqrt(n) ; // verificar precisao depois
        b = n/k ;
        b_ = n%k ;
        if(b_) k++ ;

        blocos.resize(k,vector<long long>(b,-1)) ;
        blocos_resp.resize(k,initializer) ;

        int linha=0 ; ll resp=initializer ;
        for(int i=0 ; i<n ; i++){
            
            blocos[linha][i%b] = lista[i] ;
            change(resp,lista[i]) ;
            
            if(!(i+1)%b){
                blocos_resp[linha] = resp ;
                linha++ ;
                resp=initializer ;
            }
        
        }

    }

    void lazy_update(int l, int r , int u){

        l-- ; r--;
        int bloco_esq=-1 , bloco_dir=-1 , extra_esq=-1 , extra_dir=-1 ;
        
        bloco_esq = l/b ;
        bloco_dir = r/b ;
        extra_esq=l ;
        extra_dir = r ;

        if(l%b) bloco_esq++ ; 
        if((r+1)%b) bloco_dir-- ;

        if(l==r){ change(lista[l],u) ; return ;}

        if(extra_dir-extra_esq<=b){
            for(int i=extra_esq ; i<=extra_dir ; i++) change(lista[i],u) ;
            return ;
        }

        if (extra_esq < bloco_esq*b) for(int i=extra_esq ; i<bloco_esq*b ; i++) change(lista[i],u) ;
        for(int i=bloco_esq ; i<=bloco_dir ; i++) change(blocos_resp[i], u ) ;
        if (extra_dir > bloco_dir*b) for(int i=(bloco_dir+1)*b ; i<=extra_dir ; i++) change(lista[i],u) ;

    }

    ll query(int k){
        k-- ;
        return lista[k] + blocos_resp[k/b]  ;
    }

    void update(int k , int u){
        
        int bloco ;
        
        k-- ;
        lista[k] = u ;
        bloco = k/b ;
        
        blocos_resp[bloco]=initializer ;
        for(int i=bloco*b ; i<(bloco+1)*b ; i++) change(blocos_resp[bloco],lista[i]) ;

    }

    ll query(int l, int r){
        
        l-- ; r--;
        int bloco_esq=-1 , bloco_dir=-1 , extra_esq=-1 , extra_dir=-1 ;
        
        bloco_esq = l/b ;
        bloco_dir = r/b ;
        extra_esq=l ;
        extra_dir = r ;

        if(l%b) bloco_esq++ ; 
        if((r+1)%b) bloco_dir-- ;
        
        //cout << extra_esq << "  " << bloco_esq << " " << bloco_dir << " " << extra_dir << " debug "<< endl ;

        ll asw=initializer ;

        if(l==r) return lista[l] ;

        if(extra_dir-extra_esq<=b){
            for(int i=extra_esq ; i<=extra_dir ; i++) change(asw,lista[i]) ;
            return asw ;
        }

        if (extra_esq < bloco_esq*b) for(int i=extra_esq ; i<bloco_esq*b ; i++) change(asw,lista[i]) ;
        for(int i=bloco_esq ; i<=bloco_dir ; i++) change(asw,blocos_resp[i]) ;
        if (extra_dir > bloco_dir*b) for(int i=(bloco_dir+1)*b ; i<=extra_dir ; i++) change(asw,lista[i]) ;

        return asw ;

    }

    void view_data(){
        
        cout << n << " "  << b << " " << b_ << " " << k << endl ;

        // for(int i=0 ; i<n ; i++) cout << lista[i] << " " ;
        // cout << "\n" << endl ;

        for(int i=0 ; i<k ; i++){
            for(int j=0 ; j<b ; j++){
                cout << blocos[i][j] << " " ;
            }
            cout << endl ;
        }

        for(int i=0 ; i<k ; i++) cout << blocos_resp[i] << " " ;
        cout << endl ;

    }

} ;

int main(){

    fastio ;

    return 0 ;

}
