#include <bits/stdc++.h>



using namespace std;

const int alphabet = 256;


vector<int> suf(string  &s){
    
    int n = s.size();
    vector<int> p(n), cnt(alphabet,0), c(n);
    
    // cout << s << '\n';
    // 0 step

    for(int i=0; i<n; ++i){
        ++cnt[s[i]];
    }
    for(int i=1; i<alphabet; ++i){
        cnt[i] += cnt[i-1];
    }
    for(int i=n-1; i>=0; --i){
        p[--cnt[s[i]]] = i;
    }
    c[p[0]] = 0;
    int classes = 0;
    for(int i=1; i<n; ++i){
        if (s[p[i]] != s[p[i-1]]){
            classes++;
        }
        
        c[p[i]]=classes;
        
    }
    
    vector<int> pn(n), cn(n);

    for(int j = 0; (1<<j)<n;j++){
        //cout << j << '\n';
        for(int i=0; i<n; ++i){
            int t = (p[i] - (1<<j))%n;
            pn[i] = t;
            
            if(pn[i] < 0){
                pn[i] += n;
            }
        }
       
        vector<int> cnt(n,0);
        for(int i=0; i<n; ++i){
            //cout << pn[i] << " " << c[pn[i]] << '\n';
            ++cnt[c[pn[i]]];
        }
        

        for(int i = 1; i<n; ++i){
            cnt[i] += cnt[i-1];
        }
        
        // cout << '\n';
        for(int i=n-1; i>=0; --i){
            //cout << pn[i] << " " << c[pn[i]] << " "  << cnt[c[pn[i]]] << '\n';
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cn[p[0]] = 0;
        classes = 1;
        for(int i=1; i<n; ++i){
            int m1 = (p[i] + (1<<j)) % n;
            int m2 = (p[i-1] + (1<<j)) % n;
            if(c[p[i]] != c[p[i-1]] || c[m1] != c[m2]){
                ++classes;
            }
            cn[p[i]] = classes-1;
        }


        for(int i=0; i<cn.size(); ++i){
            c[i] = cn[i];
        }
        
    }

    return p;

}

int main(){

    string s;
    cin >> s;
    string text;
    text = s;
    s += "$";
    using namespace std::chrono;
    steady_clock::time_point start = steady_clock::now();


    vector<int> suff = suf(s);

    steady_clock::time_point end = steady_clock::now();
    steady_clock::duration dur = end - start;
 
    cout << "timing in milliseconds: " << duration<double, milli>(dur).count() << " ms" << endl;

    string p;
    int ind = 0;
    vector<string> pattern;
    while(cin >> p){

        pattern.push_back(p);

    }

    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int m;
    for(int i = 0; i<pattern.size(); ++i){
        m = 1;
        p = pattern[i];

        

        vector<int> ans;
        while (s[suff[m]] <= p[0] && m<s.size()){
            // cout << m << "\n";
            if(p[ind] == s[suff[m]]){
                ind++;
                while(p[ind] == s[suff[m] + ind]  && (ind<p.size()) && (suff[m] + ind < s.size())){
                    
                    // cout << ind << " " << p[ind] << " " << s[suff[m] + ind] << " " << l << " " << r << " " << m << '\n';
                    ind++;
                }

                if(ind == p.size() && suff[m]+ind < s.size()){
                    ans.push_back(suff[m]+1);
                    ind=0;
                    m++;
                    
                }
                else{
                    
                    m++;
                    ind = 0;
                }

            }
            else{
                m++;
                ind=0;
            }

        }

    }
}