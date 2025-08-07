#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5; 
int n,m,point[maxn],nextx[maxn],to[maxn],value[maxn],cnt=1;
void create(void){
	int from,togo;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>from>>togo>>value[cnt];
		nextx[cnt]=point[from];
		point[from]=cnt;
		to[cnt]=togo;
		cnt++;
	}
}
//n为节点数量，m为边数量，value[x]为编号x的边的边权
//本程序适用于带权有向图的建图 
