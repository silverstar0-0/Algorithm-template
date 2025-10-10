#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e5+5;
string s;
int cnt,lastpos;
class node{
public:
	int link=0,endpos=0,maxlen=0;//endpos沿着link推送可以得到子串的出现集合 
	int times=1;//times记录在该endpos且长度为sam[sam[posnow].link].maxlen+1到maxlen的子串出现了多少次
	int num0=0,num1=0;//num0记录沿着该转移往下共有多少子串(结束位置不同视为不同),num1记录所有不同子串(结束位置不同视为相同)
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
void topo(void){				//更新所有子串出现次数
	for(int i=0;i<cnt-1;i++) a[i]={sam[i+1].maxlen,i+1};
	sort(a,a+cnt-1,greater<pair<int,int>>());
	for(int i=0;i<cnt-1;i++) if(sam[a[i].second].link!=-1) sam[sam[a[i].second].link].times+=sam[a[i].second].times;
	return;
}
void dfs_num(int pos){
	sam[pos].num0=sam[pos].times;
	sam[pos].num1=1;
	for(int i=0;i<26;i++){
		if(sam[pos].to[i]){
			if(!sam[sam[pos].to[i]].num0) dfs_num(sam[pos].to[i]);
			sam[pos].num0+=sam[sam[pos].to[i]].num0;
			sam[pos].num1+=sam[sam[pos].to[i]].num1;
		}
	}
	return;
}
void create(void){
	clear();//初始化 
	int l=s.size();
	for(int i=0;i<l;i++){
		add(i);//逐个添加 
	}
	topo();
	dfs_num(0);
	return;
}
void kth0(int k,int pos){	//第k大字符串(不去重) 
	int ans=sam[pos].times;
	if(pos==0) ans=0;
	if(k<=ans) return;
	for(int i=0;i<26;i++){
		if(!sam[pos].to[i]) continue;
		if(ans+sam[sam[pos].to[i]].num0<k) ans+=sam[sam[pos].to[i]].num0; 
		else{
			cout<<char(i+'a');
			kth0(k-ans,sam[pos].to[i]);
			return;
		}
	}
	if(pos==0) cout<<-1;
	return;
}
void kth1(int k,int pos){	//第k大字符串(去重) 
	int ans=1;
	if(pos==0) ans=0;
	if(k<=ans) return;
	for(int i=0;i<26;i++){
		if(!sam[pos].to[i]) continue;
		if(ans+sam[sam[pos].to[i]].num1<k) ans+=sam[sam[pos].to[i]].num1;
		else{
			cout<<char(i+'a');
			kth1(k-ans,sam[pos].to[i]);
			return;
		}
	}
	if(pos==0) cout<<-1;
	return;
}
signed main(void){
	cin>>s;
	for(int i=0;i<s.size();i++) s[i]-='a';
	create();
	//进行操作 
	return 0;
}
