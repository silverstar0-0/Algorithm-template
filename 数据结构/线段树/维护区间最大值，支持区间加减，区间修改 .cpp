#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int tree[4*maxn],lazy[4*maxn],change[4*maxn];
bool ischanged[4*maxn];
int a[maxn];
void create(int l,int r,int pos){
	if(l==r){
		tree[pos]=a[l];
		return;
	}
	else{
		int mid=(l+r)>>1;
		create(l,mid,pos*2);
		create(mid+1,r,pos*2+1);
		tree[pos]=max(tree[pos*2],tree[pos*2+1]);
		return;
	}
}
void push(int l,int r,int pos,int x){
	if(x!=0){
		tree[pos]+=x;
		if(l!=r) lazy[pos]+=x;
	}
	return;
}
void rechange(int l,int r,int pos,int x){
	tree[pos]=x;
	lazy[pos]=0; 
	if(l!=r){
		change[pos]=x;
		ischanged[pos]=true;
	}
	return;
}
void pushdown(int l, int r, int pos) {
    int mid=(l+r)>>1;
    if(ischanged[pos]){
        rechange(l,mid,pos*2,change[pos]);
        rechange(mid+1,r,pos*2+1,change[pos]);
        ischanged[pos]=false;
    }
    if(lazy[pos]!=0){
        push(l,mid,pos*2,lazy[pos]);
        push(mid+1,r,pos*2+1,lazy[pos]);
        lazy[pos]=0;
    }
}
void add(int l,int r,int pos,int tarl,int tarr,int x){
	if(l>=tarl&&r<=tarr){
		tree[pos]+=x;
		if(l!=r) lazy[pos]+=x;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(l,r,pos);
	if(tarl<=mid) add(l,mid,pos*2,tarl,tarr,x);
	if(tarr>mid) add(mid+1,r,pos*2+1,tarl,tarr,x);
	tree[pos]=max(tree[pos*2],tree[pos*2+1]);
	return;
}
void reset(int l,int r,int pos,int tarl,int tarr,int x){
	if(l>=tarl&&r<=tarr){
		tree[pos]=x;
		lazyp[pos]=0;
		if(l!=r){
			change[pos]=x;
			ischanged[pos]=true;
		}
		return;
	}
	int mid=(l+r)>>1;
	pushdown(l,r,pos);
	if(tarl<=mid) reset(l,mid,pos*2,tarl,tarr,x);
	if(tarr>mid) reset(mid+1,r,pos*2+1,tarl,tarr,x);
	tree[pos]=max(tree[pos*2],tree[pos*2+1]);
	return;
}
int query(int l,int r,int pos,int tarl,int tarr){
	if(l>=tarl&&r<=tarr) return tree[pos];
	int mid=(l+r)>>1,ans=INT_MIN;
	pushdown(l,r,pos);
	if(tarl<=mid) ans=max(ans,query(l,mid,pos*2,tarl,tarr));
	if(tarr>mid) ans=max(ans,query(mid+1,r,pos*2+1,tarl,tarr)); 
	return ans;
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    int n,m,temp,l,r,x;
    cin>>n>>m; 
    for(int i=1;i<=n;i++) cin>>a[i];
	create(1,n,1);
	return 0;
}
