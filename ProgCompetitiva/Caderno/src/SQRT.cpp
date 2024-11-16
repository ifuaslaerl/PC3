template <typename T>
class SQRT{

    private:

        const T neutral=0 ; // definir caso a caso
        int n, b ;
        vector<T> lista, blocks ;

        T merge(T val1, T val2){ // definir caso a caso
            return max(val1, val2) ;
        }

    public:

        SQRT(vector<T>& lista_){
            n = lista_.size() ;
            lista = lista_ ;
            b = (int) sqrt(n) + 1 ;
            blocks.resize(b,neutral) ;

            for (int i=0; i<n; i++){
                blocks[i / b] = merge(blocks[i / b], lista[i]);
            }
        }

        T query(int l, int r){
            T asw=neutral ;
            int b_l = l / b, b_r = r / b;
            
            if (b_l == b_r){
                for (int i=l; i<=r; i++){
                    asw = merge(asw,lista[i]);
                }
            }

            else {
                for (int i=l, end=(b_l+1)*b-1; i<=end; i++){
                    asw = merge(asw,lista[i]);
                }
                for (int i=b_l+1; i<=b_r-1; i++){
                    asw = merge(asw,blocks[i]);
                }
                for (int i=b_r*b; i<=r; i++){
                    asw = merge(asw,lista[i]);
                }
            }

            return asw ;
        }

        void update(int index, T value){
            lista[index] += value ;
            int block_index = index/b ;
            
            blocks[block_index] = neutral ;
            for (int i=block_index*b ; i<(block_index+1)*b ; i++){
                blocks[i / b] = merge(blocks[i / b], lista[i]);
            }
        }

        int lower_bound(T value){
            int b_l = 0 / b, b_r = (n-1) / b;
            for (int i=0, end=(b_l+1)*b-1; i<=end; i++){
                if(value<=lista[i]){
                        return i ;
                    }
            }
            for (int i=b_l+1; i<=b_r-1; i++){
                if(value<=blocks[i]){
                    for(int j=i*b ; j<(i+1)*b ; j++){
                        if(value<=lista[j]){
                            return j ;
                        }
                    }
                }
            }
            for (int i=b_r*b; i<=n-1; i++){
                if(value<=lista[i]){
                    return i ;
                }
            }

            return -1 ;
        }

} ;