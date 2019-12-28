#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
struct edge0{
	int f,t,w;
	bool operator<(edge0 a){
		return w>a.w;
	}
}a[50005];
struct edge{
	int t,w;
};
int n,m,q,a_,b_,f[10005][15],maxv[10005][15],vis[10005],ft[10005],dep[10005];
char ch;
std::vector<edge> g[10005];
inline int min(int a,int b){return a<b?a:b;}
template<typename T>inline void Tmin(T& a,T b){if(a>b)a=b;}
int find(int t){return ft[t]==t?t:ft[t]=find(ft[t]);}
inline void _union(int x,int y){ft[find(x)]=find(y);}
template<typename T1>
void read(T1& n){
	n=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')n=n*10+ch-'0',ch=getchar();
}
void dfs(int t){
	vis[t]=1;
	for(int i=0;i<g[t].size();i++){
		edge e=g[t][i];
		if(e.t==f[t][0])continue;
		f[e.t][0]=t;maxv[e.t][0]=e.w;dep[e.t]=dep[t]+1;
		for(int j=1;j<15;j++)f[e.t][j]=f[f[e.t][j-1]][j-1];
		for(int j=1;j<15;j++)maxv[e.t][j]=min(maxv[e.t][j-1],maxv[f[e.t][j-1]][j-1]);
		dfs(e.t);
	}
}
int lca(int a,int b){
	if(find(a)!=find(b))return -1;
	int mv=0x3f3f3f3f;
	if(dep[a]<dep[b])std::swap(a,b);
	for(int i=14;i>=0;i--)
		if(dep[f[a][i]]>=dep[b]){
			Tmin(mv,maxv[a][i]);
			a=f[a][i];
		}
	if(a==b)return mv;
	for(int i=14;i>=0;i--)
		if(f[a][i]!=f[b][i]){
			Tmin(mv,maxv[a][i]);Tmin(mv,maxv[b][i]);
			a=f[a][i];b=f[b][i];
		}
	return min(mv,min(maxv[a][0],maxv[b][0]));
}
int main(){
	memset(maxv,0x3f,sizeof(maxv));
	read(n);read(m);
	for(int i=1;i<=n;i++)ft[i]=i;
	for(int i=1;i<=m;i++){read(a[i].f);read(a[i].t);read(a[i].w);}
	std::sort(a+1,a+1+m);
	for(int i=1,j=1;i<n&&j<=m;i++){
		while(j<=m&&find(a[j].f)==find(a[j].t))j++;
		if(j>m)break;
		_union(a[j].f,a[j].t);
		g[a[j].f].push_back((edge){a[j].t,a[j].w});
		g[a[j].t].push_back((edge){a[j].f,a[j].w});
	}
	for(int i=1;i<=n;i++)if(!vis[i]){vis[i]=1;dep[i]=1;dfs(i);}
	read(q);
	for(int i=1;i<=q;i++){read(a_);read(b_);printf("%d\n",lca(a_,b_));}
	return 0;
}
