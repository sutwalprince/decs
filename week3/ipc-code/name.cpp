/*input
5
2
5 5
4
6 3 6 9
2
2 3
7
30 10 12 10 10 9 18
5
2 4 8 16 32
*/

#include<bits/stdc++.h> 
using namespace std ;
 
int main(){
    int t ;
    cin >> t ;
    while(t--){
        int n ;
        bool ans = false ;
        map<int , int> mp ;
        cin >> n ;
        int i = 0 ;
        for( ; i < n ; i++){
            
            int k ;
            cin>>k;
            if(mp[k]) ans = true ; ;
            mp[k]++;
        }
        if(!ans )cout << "NO" <<endl ;
        else cout<< "YES" <<endl;
    }
    return 0 ;
}