#include<bits/stdc++.h>
using namespace std;
int a[500005],lim,temp;
inline int lowbit(int x){
	return x&-x;
}
void add(int pos,int x){ // 单点添加
	while(pos<=lim){
		a[pos]+=x;
		pos+=lowbit(pos);
	}
}
int sum(int x){  //返回数组中1到x的和
	int ans=0;
	while(x!=0){
		ans+=a[x];
		x-=lowbit(x);
	}
	return ans;
}
int main(void){
	cin>>lim;
	for(int i=1;i<=lim;i++){
		cin>>temp; 
		add(i,temp);
	}
}
//树状数组大小自行修改
//初始化时调用add函数初始化
//适用于单点增加，单点和区间查询
//如果初始数组为差分数组，可以执行单点和区间增加，但是只能单点查询 
