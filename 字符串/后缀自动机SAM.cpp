#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
string s;
int cnt,lastpos;
int ans;
class node{
public:
	int link=0,endpos=0,maxlen=0;//endpos沿着link推送可以得到子串的出现集合 
	int times=1;//记录在该endpos且长度为maxlen的子串出现了多少次 
	int to[26];
};
node sam[2*maxn];
pair<int,int> a[2*maxn];
void add(int pos){
	int now=lastpos,linked_to;
	sam[cnt].endpos=pos;
	sam[cnt].maxlen=sam[lastpos].maxlen+1;
	lastpos=cnt;
	pos=s[pos];
	while(now!=-1){
		if(sam[now].to[pos]==0){
			sam[now].to[pos]=cnt;
			now=sam[now].link;
		}
		else{
			linked_to=sam[now].to[pos];
			break;
		}
	}
	if(now==-1) linked_to=0;
	sam[cnt].link=linked_to;//进行连接 
	cnt++;
	if(now!=-1&&sam[linked_to].maxlen-sam[now].maxlen!=1){//如果产生跨越需要分裂节点 
		sam[cnt]=sam[linked_to];
		sam[cnt].times=0;//复制节点不需要出现次数，出现次数在原节点上 
		sam[linked_to].link=cnt;
		sam[cnt].maxlen=sam[now].maxlen+1;
		while(now!=-1&&sam[now].to[pos]==linked_to){
			sam[now].to[pos]=cnt;
			now=sam[now].link;
		}
		sam[lastpos].link=cnt;//重置连接 
		cnt++;
	}
	return;
}
void clear(void){//初始化 
	for(int i=0;i<cnt;i++){
		sam[i].endpos=sam[i].link=sam[i].maxlen=0;
		for(int j=0;j<26;j++) sam[i].to[j]=0;
	}
	sam[0].link=-1;
	lastpos=0;
	cnt=1;
	return;
}
void create(void){
	clear();//初始化 
	int l=s.size();
	for(int i=0;i<l;i++){
		add(i);//逐个添加 
	}
	return;
}
void dfs(void){				//更新所有子串出现次数，同时更新长度大于等于2的子串的长度乘次数的最大值 
	for(int i=0;i<cnt-1;i++) a[i]={sam[i+1].maxlen,i+1};
	sort(a,a+cnt-1,greater<pair<int,int>>());
	for(int i=0;i<cnt-1;i++){
		if(sam[a[i].second].link!=-1) sam[sam[a[i].second].link].times+=sam[a[i].second].times;
		if(sam[a[i].second].times>1) ans=max(ans,sam[a[i].second].times*sam[a[i].second].maxlen);
	}
	return;
}
signed main(void){
	cin>>s;
	for(int i=0;i<s.size();i++) s[i]-='a';
	create();
	dfs();
	cout<<ans<<'\n';
	return 0;
}
