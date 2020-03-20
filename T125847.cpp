#include <stdio.h>
long long p;
struct seg_tree{
	seg_tree(){
		root=new_node(1,1000000000);
	}
	~seg_tree(){
		destroy(root);
	}
	struct node{
		node *l,*r;
		long long sum,add,ql,qr;
	};
	node *root;
	node *new_node(int l,int r){
		node *n=new node;
		n->ql=l;n->qr=r;
		n->sum=n->add=0;
		n->l=n->r=NULL;
		return n;
	}
	inline void push_up(node *n){
		n->sum=0;
		if(n->l)n->sum=(n->sum+n->l->sum)%p;
		if(n->r)n->sum=(n->sum+n->r->sum)%p;
	}
	inline void push_down(node *n){
		if(!(n->add))return;
		n->l->add=(n->l->add+n->add)%p;n->r->add=(n->r->add+n->add)%p;
		n->l->sum=(n->l->sum+n->add*(n->l->qr-n->l->ql+1))%p;n->r->sum=(n->r->sum+n->add*(n->r->qr-n->r->ql+1))%p;
		n->add=0;
	}
	long long query(int x,int y,node *k){
		if(x<=k->ql&&k->qr<=y)return k->sum;
		int mid=(k->ql+k->qr)>>1;
		if(!(k->l))k->l=new_node(k->ql,mid);
		if(!(k->r))k->r=new_node(mid+1,k->qr);
		long long res=0;
		push_down(k);
		if(x<=mid)res=(res+query(x,y,k->l))%p;
		if(mid<y)res=(res+query(x,y,k->r))%p;
		return res;
	}
	inline long long query(int x,int y){
		return query(x,y,root);
	}
	void update(int x,int y,long long v,node *k){
		if(x<=k->ql&&k->qr<=y){
			k->add=(k->add+v)%p;
			k->sum=(k->sum+v*(k->qr-k->ql+1))%p;
			return;
		}
		int mid=(k->ql+k->qr)>>1;
		if(!(k->l))k->l=new_node(k->ql,mid);
		if(!(k->r))k->r=new_node(mid+1,k->qr);
		push_down(k);
		if(x<=mid)update(x,y,v,k->l);
		if(mid<y)update(x,y,v,k->r);
		push_up(k);
	}
	inline void update(int x,int y,long long v){
		update(x,y,v,root);
	}
	void destroy(node *k){
		if(k->l)destroy(k->l);
		if(k->r)destroy(k->r);
		delete k;
	}
}st;
int t,t1,t2,t3,m;
inline int read(){
	static char ch;
	static int n;
	n=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')n=n*10+ch-'0',ch=getchar();
	return n;
}
int main(){
	m=read();p=read();
	while(m--){
		t=read();t1=read();t2=read();
		if(t==1){t3=read();st.update(t1,t2,t3);}
		else{printf("%lld\n",st.query(t1,t2));}
	}
	return 0;
}
