#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5; 
int n,m,point[maxn],nextx[maxn],to[maxn],cnt=1;
void create(void){
	int from,togo;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>from>>togo;
		nextx[cnt]=point[from];
		point[from]=cnt;
		to[cnt]=togo;
		cnt++;
	}
}
//n为节点数量，m为边数量
//本程序适用于带权有向图的建图 
