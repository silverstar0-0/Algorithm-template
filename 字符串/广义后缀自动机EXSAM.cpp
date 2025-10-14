#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;//字符串总长度上限 
const int chartype=26;//根据字符类型改变数量 
const char del='a';//初始化原始字符串，小写为a，大写为A，数字为0 
string s;
int samcnt,triecnt;
queue<int> q_bfs;
class node{
public:
	int link=0,endpos=0,maxlen=0;//endpos沿着link推送可以得到子串的出现集合 
	int times=1;//times记录在该endpos且长度为sam[sam[posnow].link].maxlen+1到maxlen的子串出现了多少次
	long long num0=0,num1=0;//num0记录沿着该转移往下共有多少子串(结束位置不同视为不同),num1记录所有不同子串(结束位置不同视为相同)
	int to[chartype];
};
class trienode{
public:
	int to[chartype],isend=0,dep,fa;
	char ch;
};
node sam[2*maxn];
trienode trie[maxn];
pair<int,int> a[2*maxn];
int trie_to_sam[maxn]; 
void insert(string s){
	int n=s.size(),pos=0;
	for(int i=0;i<n;i++){
		if(trie[pos].to[s[i]]) pos=trie[pos].to[s[i]];
		else{
			trie[pos].to[s[i]]=++triecnt;
			trie[triecnt].fa=pos;
			pos=triecnt;
			trie[pos].ch=s[i];
		}
		trie[pos].dep=i+1;
	}
	trie[pos].isend++;
	return;
}
void buildtrie(int n){
	for(int i=0;i<n;i++){
		cin>>s;
		for(int i=0;i<s.size();i++) s[i]-=del;
		insert(s);
	}
	return;
}
void add(int pos){
	int now=trie_to_sam[trie[pos].fa],linked_to;
	trie_to_sam[pos]=samcnt;
	sam[samcnt].endpos=trie[pos].dep;
	sam[samcnt].maxlen=sam[now].maxlen+1;
	int ch=trie[pos].ch;
	while(now!=-1){
		if(sam[now].to[ch]==0){
			sam[now].to[ch]=samcnt;
			now=sam[now].link;
		}
		else{
			linked_to=sam[now].to[ch];
			break;
		}
	}
	if(now==-1) linked_to=0;
	sam[samcnt].link=linked_to;//进行连接
	samcnt++;
	if(now!=-1&&sam[linked_to].maxlen-sam[now].maxlen!=1){//如果产生跨越需要分裂节点 
		sam[samcnt]=sam[linked_to];
		sam[samcnt].times=0;//复制节点不需要出现次数，出现次数在原节点上 
		sam[linked_to].link=samcnt;
		sam[samcnt].maxlen=sam[now].maxlen+1;
		while(now!=-1&&sam[now].to[ch]==linked_to){
			sam[now].to[ch]=samcnt;
			now=sam[now].link;
		}
		sam[samcnt-1].link=samcnt;//重置连接 
		samcnt++;
	}
	return;
}
void clear(void){//初始化 
	for(int i=0;i<=triecnt;i++){
		trie[i].isend=0;
		for(int j=0;j<chartype;j++) trie[i].to[j]=0;
	}
	for(int i=0;i<=samcnt;i++){
		trie_to_sam[i]=0;
		sam[i].endpos=sam[i].link=sam[i].maxlen=0;
		for(int j=0;j<chartype;j++) sam[i].to[j]=0;
	}
	sam[0].link=-1;
	triecnt=0;
	samcnt=1;
	return;
}
void topo(void){				//更新所有子串出现次数
	for(int i=0;i<samcnt-1;i++) a[i]={sam[i+1].maxlen,i+1};
	sort(a,a+samcnt-1,greater<pair<int,int>>());
	for(int i=0;i<samcnt-1;i++) if(sam[a[i].second].link!=-1) sam[sam[a[i].second].link].times+=sam[a[i].second].times;
	return;
}
void dfs_num(int pos){
	sam[pos].num0=sam[pos].times;
	sam[pos].num1=1;
	for(int i=0;i<chartype;i++){
		if(sam[pos].to[i]){
			if(!sam[sam[pos].to[i]].num0) dfs_num(sam[pos].to[i]);
			sam[pos].num0+=sam[sam[pos].to[i]].num0;
			sam[pos].num1+=sam[sam[pos].to[i]].num1;
		}
	}
	return;
}
void create(void){
	int pos;
	for(int i=0;i<chartype;i++) if(trie[0].to[i]) q_bfs.push(trie[0].to[i]);
	while(!q_bfs.empty()){
		pos=q_bfs.front();
		add(pos);
		q_bfs.pop();
		for(int i=0;i<chartype;i++) if(trie[pos].to[i]) q_bfs.push(trie[pos].to[i]);
	}
	topo();
	dfs_num(0);
	return;
}
void kth0(int k,int pos){	//第k大字符串(不去重) 
	int ans=sam[pos].times;
	if(pos==0) ans=0;
	if(k<=ans) return;
	for(int i=0;i<chartype;i++){
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
	for(int i=0;i<chartype;i++){
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
int main(void){
	int n;
	cin>>n;
	clear();
	buildtrie(n);
	create();
	//进行操作
	return 0;
}
