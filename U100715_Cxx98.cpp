#include <algorithm>
#include <stdio.h>
#include <vector>
#include <set>
using namespace std;
struct edge{
	int t,w;
};
struct edge_k{
	int f,t,w;
	bool operator<(const edge_k& p)const{
		return w<p.w;
	}
}graph_g[200005];
struct edge_mst{
	int f,t;
	bool operator<(const edge_mst& p)const{
		return f==p.f?t<p.t:f<p.f;
	}
	bool operator==(const edge_mst& p)const{
		return f==p.f&&t==p.t;
	}
};
int maxv[100005][17],pa[100005][17],dep[100005],n,m,bcj[100005];
long long ans;
vector<edge> graph[100005];
set<edge_mst> in_mst;
inline void add_edge(int f,int t,int w){
	graph[f].push_back((edge){t,w});
	graph[t].push_back((edge){f,w});
}
int find(int t){return t==bcj[t]?t:bcj[t]=find(bcj[t]);}
inline void _union(int a,int b){bcj[find(a)]=find(b);}
void dfs(int n){
	for(int i=0;i<graph[n].size();i++){
		int t=graph[n][i].t,w=graph[n][i].w;
		if(t==pa[n][0])continue;
		pa[t][0]=n;
		maxv[t][0]=w;
		for(int i=1;i<17;i++)pa[t][i]=pa[pa[t][i-1]][i-1];
		for(int i=1;i<17;i++)maxv[t][i]=max(maxv[t][i-1],maxv[pa[t][i-1]][i-1]);
		dep[t]=dep[n]+1;
		dfs(t);
	}
}
int lca(int a,int b){
	if(a==b)return 0;
	int res=0;
	if(dep[a]<dep[b])swap(a,b);
	for(int i=16;i>=0;i--)
		if(dep[pa[a][i]]>=dep[b]){
			res=max(res,maxv[a][i]);
			a=pa[a][i];
		}
	if(a==b)return res;
	for(int i=16;i>=0;i--)
		if(pa[a][i]!=pa[b][i]){
			res=max(max(res,maxv[a][i]),maxv[b][i]);
			a=pa[a][i];b=pa[b][i];
		}
	return max(max(res,maxv[a][0]),maxv[b][0]);
}
int kruskal(){
	sort(graph_g+1,graph_g+m+1);
	for(int i=1;i<=n;i++)bcj[i]=i;
	int count=1,mst=0;
	for(int i=1;i<=m;i++){
		int f=graph_g[i].f,t=graph_g[i].t,w=graph_g[i].w;
		if(count==n)break;
		if(find(f)==find(t))continue;
		count++;
		_union(f,t);
		add_edge(f,t,w);
		in_mst.insert((edge_mst){f,t});
		mst+=w;
	}
	return mst;
}
template<typename T1>
void read(T1& v){
	static char ch;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')v=v*10+ch-'0',ch=getchar();
}
int main(){
	read(n);
	read(m);
	for(int i=1;i<=m;i++){
		read(graph_g[i].f);
		read(graph_g[i].t);
		read(graph_g[i].w);
	}
	int mst=kruskal();
	dfs(1);
	for(int i=1;i<=m;i++){
		int f=graph_g[i].f,t=graph_g[i].t,w=graph_g[i].w;
		ans+=(long long)(f+t)*(in_mst.count((edge_mst){f,t})?mst:mst-lca(f,t)+w);
	}
	printf("%lld",ans);
	return 0;
}
