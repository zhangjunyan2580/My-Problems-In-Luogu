#include <algorithm>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <set>
using namespace std;
int maxv[100005][17],pa[100005][17],dep[100005],n,m,bcj[100005];
long long ans;
vector<tuple<int,int> > graph[100005];
tuple<int,int,int> graph_g[200005];
set<tuple<int,int> > in_mst;
inline void add_edge(int f,int t,int w){
	graph[f].push_back(make_tuple(t,w));
	graph[t].push_back(make_tuple(f,w));
}
int find(int t){return t==bcj[t]?t:bcj[t]=find(bcj[t]);}
inline void _union(int a,int b){bcj[find(a)]=find(b);}
void dfs(int n){
	for(const auto& [t,w]:graph[n]){
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
	sort(graph_g+1,graph_g+m+1,[](const tuple<int,int,int>& a,const tuple<int,int,int>& b){
		const auto& [fa,ta,wa]=a;
		const auto& [fb,tb,wb]=b;
		return wa<wb;
	});
	for(int i=1;i<=n;i++)bcj[i]=i;
	int count=1,mst=0;
	for(const auto& [f,t,w]:graph_g){
		if(count==n)break;
		if(find(f)==find(t))continue;
		count++;
		_union(f,t);
		add_edge(f,t,w);
		in_mst.insert(make_tuple(f,t));
		mst+=w;
	}
	return mst;
}
void read(){}
template<typename T1,typename ... T2>
void read(T1& v,T2& ... rest){
	static char ch;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')v=v*10+ch-'0',ch=getchar();
	read(rest...);
}
int main(){
	read(n,m);
	for(int i=1;i<=m;i++){
		auto& [f,t,w]=graph_g[i];
		read(f,t,w);
	}
	int mst=kruskal();
	dfs(1);
	for(int i=1;i<=m;i++){
		const auto& [f,t,w]=graph_g[i];
		ans+=(long long)(f+t)*(in_mst.count(make_tuple(f,t))?mst:mst-lca(f,t)+w);
	}
	printf("%lld",ans);
	return 0;
}
