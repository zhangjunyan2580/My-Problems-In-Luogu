#include <stdio.h>
#include <stack>
int a[500005],li[500005],ri[500005],lm[500005],rm[500005],n;
long long ma,mi;
std::stack<int> st,in;
int read(){
	static char ch;
	int n=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')n=n*10+ch-'0',ch=getchar();
	return n;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		while(in.size()&&st.top()<=a[i]){in.pop();st.pop();}
		lm[i]=in.size()?in.top():0;
		in.push(i);st.push(a[i]);
	}
	while(in.size()){in.pop();st.pop();}
	for(int i=1;i<=n;i++){
		while(in.size()&&st.top()>=a[i]){in.pop();st.pop();}
		li[i]=in.size()?in.top():0;
		in.push(i);st.push(a[i]);
	}
	while(in.size()){in.pop();st.pop();}
	for(int i=n;i;i--){
		while(in.size()&&st.top()>=a[i]){in.pop();st.pop();}
		ri[i]=in.size()?in.top():(n+1);
		in.push(i);st.push(a[i]);
	}
	while(in.size()){in.pop();st.pop();}
	for(int i=n;i;i--){
		while(in.size()&&st.top()<=a[i]){in.pop();st.pop();}
		rm[i]=in.size()?in.top():(n+1);
		in.push(i);st.push(a[i]);
	}
	for(int i=1;i<=n;i++){
		ma+=(long long)(i-lm[i])*(rm[i]-i)*a[i];
		mi+=(long long)(i-li[i])*(ri[i]-i)*a[i];
	}
	printf("%lld",ma-mi);
	return 0;
}
