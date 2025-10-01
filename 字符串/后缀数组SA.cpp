#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;	//随需要修改 
int sa[maxn],rk[maxn],satemp[maxn],cnt[maxn],n,k,rf,rktemp[maxn];
string s;
bool cmp(int posx,int posy){
    if(rk[sa[posx]]!=rk[sa[posy]]) return false;
    int rx=(sa[posx]+k<n?rk[sa[posx]+k]:0);
    int ry=(sa[posy]+k<n?rk[sa[posy]+k]:0);
    return rx==ry;
}
void resort(void){
	for(int i=0;i<=rf;i++) cnt[i]=0;	//清空 
	for(int i=0;i<n;i++) i+k<n?cnt[rk[i+k]]++:cnt[0]++;
	for(int i=1;i<=rf;i++) cnt[i]+=cnt[i-1];
	for(int i=n-1;i>=0;i--) i+k<n?satemp[--cnt[rk[i+k]]]=i:satemp[--cnt[0]]=i;	//第二关键字排序，放入的是第一关键字i 
	for(int i=0;i<=rf;i++) cnt[i]=0;	//清空 
	for(int i=0;i<n;i++) cnt[rk[i]]++;
	for(int i=1;i<=rf;i++) cnt[i]+=cnt[i-1];
	for(int i=n-1;i>=0;i--) sa[--cnt[rk[satemp[i]]]]=satemp[i];		//第一关键字排序 
	return;
}
void buildsa(void){
	k=1;
	for(int i=0;i<128;i++) cnt[i]=0;
	for(int i=0;i<n;i++) cnt[s[i]]=1;
	for(int i=1;i<128;i++) cnt[i]+=cnt[i-1];
	for(int i=0;i<n;i++) rk[i]=cnt[s[i]];
	rf=cnt[127];
	while(rf!=n){			//倍增法 
		resort();			//基数排序 
		rf=1;
		rktemp[sa[0]]=1;
		for(int i=1;i<n;i++) rktemp[sa[i]]=cmp(i-1,i)?rf:++rf;	//相同元素获得相同的rank，使用rktemp是为了防止直接更新rk会导致cmp失效 
		for(int i=0;i<n;i++) rk[i]=rktemp[i];		//赋值 
		k<<=1;
	}
}
int main(void){
	cin>>s;
	n=s.size();
	buildsa();				//构建后缀数组 
	//请输入文本 
	return 0;
}
