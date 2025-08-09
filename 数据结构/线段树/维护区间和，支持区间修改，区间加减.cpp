#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int tree[4*maxn],lazy[4*maxn],change[4*maxn];
bool ischanged[4*maxn];
vector<int> v;
void create(int l,int r,int pos){
	if(l==r){
		tree[pos]=v[l];
		return;
	}
	else{
		int mid=(l+r)>>1;
		create(l,mid,pos*2);
		create(mid+1,r,pos*2+1);
		tree[pos]=tree[pos*2]+tree[pos*2+1];
		return;
	}
}
void push(int l,int r,int pos,int x){
	if(x!=0){
		tree[pos]+=(r-l+1)*x;
		if(l!=r) lazy[pos]+=x;
	}
	return;
}
void rechange(int l,int r,int pos,int x){
	tree[pos]=(r-l+1)*x;
	if(l!=r){
		change[pos]=x;
		ischanged[pos]=true;
	}
	return;
}
void add(int l,int r,int pos,int tarl,int tarr,int x){
	if(l>=tarl&&r<=tarr){
		tree[pos]+=(r-l+1)*x;
		if(l!=r) lazy[pos]+=x;
		return;
	}
	int mid=(l+r)>>1;
	if(ischanged[pos]==true){
		rechange(l,mid,pos*2,change[pos]);
		rechange(mid+1,r,pos*2+1,change[pos]);
		ischanged[pos]=false;
	}
	if(lazy[pos]!=0){
		push(l,mid,pos*2,lazy[pos]);
		push(mid+1,r,pos*2+1,lazy[pos]);
		lazy[pos]=0;
	}
	if(tarl<=mid) add(l,mid,pos*2,tarl,tarr,x);
	if(tarr>mid) add(mid+1,r,pos*2+1,tarl,tarr,x);
	tree[pos]=tree[pos*2]+tree[pos*2+1];
	return;
}
void reset(int l,int r,int pos,int tarl,int tarr,int x){
	if(l>=tarl&&r<=tarr){
		tree[pos]=(r-l+1)*x;
		lazy[pos]=0;
		if(l!=r){
			change[pos]=x;
			ischanged[pos]=true;
		}
		return;
	}
	int mid=(l+r)>>1;
	if(tarl<=mid) reset(l,mid,pos*2,tarl,tarr,x);
	if(tarr>mid) reset(mid+1,r,pos*2+1,tarl,tarr,x);
	tree[pos]=tree[pos*2]+tree[pos*2+1];
	return;
}
int query(int l,int r,int pos,int tarl,int tarr){
	if(l>=tarl&&r<=tarr) return tree[pos];
	int mid=(l+r)>>1,ans=0;
	if(ischanged[pos]==true){
		rechange(l,mid,pos*2,change[pos]);
		rechange(mid+1,r,pos*2+1,change[pos]);
	}
	push(l,mid,pos*2,lazy[pos]);
	push(mid+1,r,pos*2,lazy[pos]);
	if(tarl<=mid) ans+=query(l,mid,pos*2,tarl,tarr);
	if(tarr>mid) ans+=query(mid+1,r,pos*2+1,tarl,tarr);
	tree[pos]=tree[pos*2]+tree[pos*2+1];
	return ans;
}
int main(void){
    int n,m,temp,l,r,x;
    cin>>n>>m; 
    v.push_back(0);
    for(int i=0;i<n;i++){
		cin>>temp;
		v.push_back(temp);
	}
	create(1,n,1);
	return 0;
}
//create函数建线段树 
//支持区间修改-reset函数
//支持区间加减-add函数
//维护区间和，支持查询区间和-query函数
//若需扩展值域到long long级别，请#define int long long
