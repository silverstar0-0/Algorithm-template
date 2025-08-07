#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
vector<int> v;
bool vis[maxn];
int cnt=0;
void search(int n){
	for(int i=2;i<=n;i++){
		if(vis[i]==false){
			v.push_back(i);
			cnt++;
		}
		for(int j=0;j<cnt;j++){
			if(i*v[j]>n) break;
			vis[i*v[j]]=true;
			if(i%v[j]==0) break;
		}
	}
	return;
}
//maxn是最大容量，可直接修改 
//search函数传进去的n就是要筛选到的上限
//质数按从小到大的顺序存在vector内，可直接按照数组方式调用 
