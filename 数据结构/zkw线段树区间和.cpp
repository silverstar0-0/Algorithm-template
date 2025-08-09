#include<cstdio>
#define MAXN 200005
#define fp(i,l,r) for(register int i=(l);i<=(r);++i)
#define fd(i,r,l) for(register int i=(r);i>=(l);--i)
#define il inline
int tree[MAXN<<2], add[MAXN<<2];
int n, N=1;

il void build() {
  scanf("%d", &n);
  for(; N <= n+1; N <<= 1);
  fp(i, N+1, N+n) scanf("%d", tree+i);
  fd(i, N-1, 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
}
il void update(int s, int t, int k) {
  int lNum=0, rNum=0, nNum=1;
  for(s = N+s-1, t = N+t+1; s^t^1; s >>= 1, t >>= 1, nNum <<= 1) {
    tree[s] += k*lNum;
    tree[t] += k*rNum;
    if(~s&1) {add[s^1] += k; tree[s^1] += k*nNum; lNum += nNum;}
    if(t&1) {add[t^1] += k; tree[t^1] += k*nNum; rNum += nNum;}
  }
  for(; s; s >>= 1, t >>= 1) {
      tree[s] += k*lNum;
      tree[t] += k*rNum;
  } 
}
il int query(int s, int t){
  int lNum=0, rNum=0, nNum=1;
  int ans=0;
  for(s = N+s-1, t = N+t+1; s^t^1; s >>= 1, t >>= 1, nNum <<= 1) {
    if(add[s]) ans += add[s]*lNum;
    if(add[t]) ans += add[t]*rNum;
    if(~s&1) {ans += tree[s^1]; lNum += nNum;}
    if(t&1) {ans += tree[t^1]; rNum += nNum;}
  }
  for(; s; s >>= 1, t >>= 1) {
    ans += add[s]*lNum;
    ans += add[t]*rNum;
  }
  return ans;
}
int main() {
}
