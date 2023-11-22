#include <bits/stdc++.h>


using namespace std;
using ll = long long;

ll bin_pow(ll a, ll b)
{   
    if(b == 0) return 1;
    ll ans = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
            ans *= a;
        a = a * a;
        b = b / 2;
    }
    return ans;
}

ll calc_pref(string s, int m){

    vector<vector<ll>> dp(s.length()+1,vector<ll>(m, 0) );
    

    len(n)*m

    for(int i=s.length()-1; i>=0; --i){   
        int l = s.length() - 1 - i;   // длина подстроки
        for(int j=0; j<m; ++j){ // остатки от 0 до m-1
            for(int k=0; k<int(s[i] - '0'); ++k){  // диапазон цифр от 0 до max - 1, относительно рассматриваемой цирфы
                if(i==0 && k==0) continue;
                int ost = (k*bin_pow(10,l)) % m;   // остаток от деления
                int dop = (m + j - ost) % m; 
                ll count = (bin_pow(10,l) - 1 - dop) / m;
                if (dop < bin_pow(10, l)){
                    count++;
                    
                }
                    
                dp[i][j] += count;
                
            }

            int ost = (int(s[i] - '0') * bin_pow(10,l)) % m;
            int dop = (m + j- ost)%m;
            dp[i][j] += dp[i+1][dop];
            
        }
    }
    
    return dp[0][0];
}


int main(){

    string n;
    int m;
    cin >> n;
    cin >> m;
    ll ans = 0;
    using namespace std::chrono;
    steady_clock::time_point start = steady_clock::now();
    for(int i = n.length(); i>0; --i){
        string s = n.substr(0,i);
        // for(auto x : s){
        //     cout << x;
        // }
        // cout <<'\n';
        ll q = atoll(s.c_str());
        if(q%m==0 && i!=n.length()){
            ans++;
        }
        ans += calc_pref(s,m);
    }

    steady_clock::time_point end = steady_clock::now();
    steady_clock::duration dur = end - start;
 
    cout << "timing in milliseconds: " << duration<double, milli>(dur).count() << " ms" << endl;


    cout <<  ans << '\n';
}