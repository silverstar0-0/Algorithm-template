#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5;
class node{
public:
	int c=0,fail=0,fa=0,isend=0;
	int son[26];
};
int cnt,n;
vector<string> pres;
node trie[maxn];
node reset0;
int indegree[maxn];
int endpos[maxn],endstring;
int vis[maxn];//用于统计每个子串出现次数 
void add(int x){				//大部分统计上的修改应当位于add函数内 
	string s=pres[x];
	int l=s.size(),posn=0;
	for(int i=0;i<l;i++){
		s[i]-='a';
		if(trie[posn].son[s[i]]==0){
			trie[posn].son[s[i]]=++cnt;
			trie[cnt].fa=posn;
			trie[cnt].c=s[i];
		}
		posn=trie[posn].son[s[i]];
		if(i==l-1){
			trie[posn].isend=1;
			endpos[endstring++]=posn;
		}
	}
	return;
}
void build_fail(void){ 			//build_fail函数构建fail指针 
	queue<int> q;
	int temp,failpos,c;
	for(int i=0;i<26;i++) if(trie[0].son[i]!=0) q.push(trie[0].son[i]);
	while(!q.empty()){
		temp=q.front();
		q.pop();
		for(int i=0;i<26;i++) if(trie[temp].son[i]!=0) q.push(trie[temp].son[i]);
		failpos=trie[trie[temp].fa].fail;
		c=trie[temp].c;
		while(failpos&&!trie[failpos].son[c]) failpos=trie[failpos].fail;
		if(trie[failpos].son[c]&&temp!=trie[failpos].son[c]) failpos=trie[failpos].son[c];
		trie[temp].fail=failpos;
		indegree[failpos]++;	//入度增加 
	}
	return;
}
void create(void){				//create函数初始化trie并构建fail指针 
	for(int i=0;i<=cnt;i++) trie[i]=reset0;
	cnt=endstring=0;
	for(int i=0;i<n;i++) add(i);
	build_fail();
	for(int i=0;i<=n;i++) vis[i]=0; //仅把需要用到的位置刷新为0 
	return;
}
void upload(void){				//拓扑排序上传出现次数 
	queue<int> q;
	int temp;
	for(int i=0;i<=cnt;i++) if(indegree[i]==0) q.push(i);
	while(!q.empty()){
		temp=q.front();
		q.pop();
		indegree[trie[temp].fail]--;
		vis[trie[temp].fail]+=vis[temp];
		if(indegree[trie[temp].fail]==0) q.push(trie[temp].fail);
	}
	return;
}
void search_from(string s){		//search_from函数应当在add函数修改后做出对应修改 
	int l=s.size(),pos=0,now=0;
	while(pos<l){
		while(now&&!trie[now].son[s[pos]-'a']) now=trie[now].fail;	//匹配操作，可忽略 
		if(trie[now].son[s[pos]-'a']) now=trie[now].son[s[pos]-'a'];	//匹配操作，可忽略 
		vis[now]++;
		pos++;
	}
	upload();	//拓扑排序优化 
	return;
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;//读入第一次的子串数量n 
	string s;
	vector<string> v; 
	while(n!=0){
		pres.clear();
		//所有的匹配子串读进pres内
		for(int i=0;i<n;i++){
			cin>>s;
			pres.push_back(s);
		}
		create();
		cin>>s;	//被匹配的大字符串 
		search_from(s);	//匹配操作 
		for(int i=0;i<n;i++) cout<<vis[endpos[i]]<<'\n';
		n=0;
	}
	return 0;
}
