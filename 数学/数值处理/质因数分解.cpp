#include<bits/stdc++.h>
using namespace std;
const int maxn=2;
vector<int> v;
map<int,int> brok[maxn]; //使用时直接auto迭代器遍历即可
bool vis[100005];
int cnt=0,cnt_brk=0;
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
void broken(int x){
	for(int i=0;i<cnt;i++){
		int temp=0;
		if(v[i]*v[i]>x) break;
		if(x%v[i]!=0) continue;
		while(x%v[i]==0){
			temp++;
			x/=v[i];
		}
		brok[cnt_brk][v[i]]=temp;
	}
	if(x!=1) brok[cnt_brk][x]=1;
	cnt_brk++;
	return;
}
//broken函数会把输入的x拆解为质因子和每个质因子的个数
//maxn是需要拆多少个数的质因子
//search函数是欧拉筛板子 
