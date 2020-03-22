#pragma GCC optimize(3)
#include <stdio.h>
unsigned p;
struct seg_tree{
	unsigned add[10000000],sum[10000000],lc[10000000],rc[10000000],cnt;
	unsigned query(unsigned x,unsigned y,unsigned k,unsigned l,unsigned r,unsigned a){
		if(x==l&&r==y)return (sum[k]+(unsigned)((unsigned long long)(y-x+1)*a%p))%p;
		a=(a+add[k])%p;
		unsigned mid=(l+r)>>1;
		if(!lc[k])lc[k]=++cnt;
		if(!rc[k])rc[k]=++cnt;
		unsigned res=0;
		if(y<=mid)return query(x,y,lc[k],l,mid,a);
		if(mid<x)return query(x,y,rc[k],mid+1,r,a);
		return (query(x,mid,lc[k],l,mid,a)+query(mid+1,y,rc[k],mid+1,r,a))%p;
	}
	void update(unsigned x,unsigned y,unsigned v,unsigned k,unsigned l,unsigned r){
		sum[k]=(sum[k]+(unsigned)((unsigned long long)v*(y-x+1)%p))%p;
		if(x==l&&r==y){
			add[k]=(add[k]+v)%p;
			return;
		}
		unsigned mid=(l+r)>>1;
		if(!lc[k])lc[k]=++cnt;
		if(!rc[k])rc[k]=++cnt;
		if(y<=mid){update(x,y,v,lc[k],l,mid);return;}
		if(mid<x){update(x,y,v,rc[k],mid+1,r);return;}
		update(x,mid,v,lc[k],l,mid);update(mid+1,y,v,rc[k],mid+1,r);
	}
}st;
unsigned t,t1,t2,t3,m;
inline unsigned read(){
	static char ch;
	static unsigned n;
	n=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')n=n*10+ch-'0',ch=getchar();
	return n;
}
int main(){
	m=read();p=read();
	while(m--){
		t=read();t1=read();t2=read();
		if(t==1u){t3=read();st.update(t1,t2,t3,0u,1u,1000000000u);}
		else{printf("%u\n",st.query(t1,t2,0u,1u,1000000000u,0u));}
	}
	return 0;
}
