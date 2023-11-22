#include <bits/stdc++.h>


using namespace std;

using ll = long long;

struct wedeg_t {
    int u,v;
    ll w;
};

const ll INF = 1e18;

int n;
bool flag = true;
vector<ll> ford_belman(const vector<wedeg_t> &g, int start){
    
    vector<ll> d (n+1);
    int m = g.size();
	int x;
	for (int i=0; i<n+1; ++i) {
		x = -1;
		for (int j=0; j<m; ++j){

			if (d[g[j].v] > (d[g[j].u] + g[j].w)) {
				d[g[j].v] = max (-INF, d[g[j].u] + g[j].w);
				x = g[j].v;
			}
        }   
    }
 
	if (x == -1) flag=false;

    return d;
		
}

vector <ll> dijkstra(const vector<wedeg_t> &g, int start){

    vector<ll> d(n+1,INF);
    vector<bool> used (n+1, false);

    d[start] = 0;

    for(int t=0; t<n+1; ++t){
        int u=-1;
        
        for(int j=0; j<n+1; ++j){
            if (!used[j] && (d[j] < d[u] || u==-1)){
                u = j;
            }

        }
        // cout << u << '\n';
        if (d[u]==INF) break;
        used[u] = true;
    
        for(int i=0; i<g.size();++i){
            
            if(g[i].u == u){
                // cout << g[i].u << " " << g[i].v << " " << g[i].w << '\n';
                if(d[u]+g[i].w < d[g[i].v]){

                    d[g[i].v] = d[u]+g[i].w; 
                }
            }
        }

        
    }

    return d;
}

int main(){

    int m;
    cin >> n >> m;

    vector<wedeg_t>edge;

    for(int i = 0; i < m; ++i){
        int u,v;
        ll w;
        cin >> u >> v >> w;
        edge.push_back({u,v,w});

    }
    using namespace std::chrono;
    steady_clock::time_point start = steady_clock::now();
    vector<ll> s = ford_belman(edge,1);
    if(flag){
        cout << "Negative cycle\n"; 
        
    }
    else{
        
        for(int i=0; i<n;++i){
        edge.push_back({0,i+1,0});
        }

        vector<ll>h = ford_belman(edge, 0);

        for(int i=0; i<edge.size();++i){
            edge[i].w = edge[i].w + h[edge[i].u] - h[edge[i].v];
        }

        // for(auto x : edge){
        //     cout << x.u << " " << x.v << " " << x.w << '\n';
        // }

        for(int i=1; i<n+1;++i){
            vector<ll> res = dijkstra(edge,i);
            // for(int j=1; j<res.size();++j){
            //     if(res[j]==INF){
            //         cout << "inf" << " ";
            //     }
            //     else{
            //         cout << res[j] - h[i] + h[j]  << " ";
            //     }

            // }
            // cout << '\n';
        }

    }
    steady_clock::time_point end = steady_clock::now();
    steady_clock::duration dur = end - start;
 
    cout << "timing in milliseconds: " << duration<double, milli>(dur).count() << " ms" << endl;

}