#include<bits/stdc++.h>
using namespace std;
const int maxn=2e4;
class node{
public:
	int c=0,end=0,fail=0,fa=0;
	int son[26];
};
int cnt,n,endcnt;
vector<string> pres;
node trie[maxn];
node reset0;
int vis[maxn];//用于统计每个子串出现次数 
void add(string s){				//大部分统计上的修改应当位于add函数内 
	int l=s.size(),posn=0;
	for(int i=0;i<l;i++){
		s[i]-='a';
		if(trie[posn].son[s[i]]==0){
			trie[posn].son[s[i]]=++cnt;
			trie[cnt].fa=posn;
			trie[cnt].c=s[i];
		}
		posn=trie[posn].son[s[i]];
		if(i==l-1) trie[posn].end=++endcnt;//①重复子串会覆盖先前的标号 
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
	}
	return;
}
void create(void){				//create函数初始化trie并构建fail指针 
	for(int i=0;i<=cnt;i++) trie[i]=reset0;
	cnt=0;
	endcnt=0;
	for(int i=0;i<n;i++) add(pres[i]);
	build_fail();
	return;
}
void search_from(string s){		//search_from函数应当在add函数修改后做出对应修改 
	int l=s.size(),pos=0,now=0;
	while(pos<l){
		while(now&&!trie[now].son[s[pos]-'a']) now=trie[now].fail;	//匹配操作，可忽略 
		if(trie[now].son[s[pos]-'a']) now=trie[now].son[s[pos]-'a'];	//匹配操作，可忽略 
		int temp=now;
		while(temp>0){
		    if(trie[temp].end) vis[trie[temp].end]++;
		    temp=trie[temp].fail;
		}
		pos++;
	}
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;//读入第一次的子串数量n 
	int maxx;//统计最大出现次数 
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
		for(int i=0;i<=endcnt;i++) vis[i]=0; //仅把需要用到的位置刷新为0 
		cin>>s;	//被匹配的大字符串 
		search_from(s);	//匹配操作 
		v.clear();
		maxx=0;
		for(int i=1;i<=endcnt;i++){	//寻找出现次数最多的子串 
			if(vis[i]>maxx){
				v.clear();
				v.push_back(pres[i-1]);
				maxx=vis[i];
			}
			else if(vis[i]==maxx) v.push_back(pres[i-1]);
		}
		cout<<maxx<<'\n';
		for(auto it=v.begin();it!=v.end();it++) cout<<*it<<'\n';
		cin>>n;	//下一次的子串数量n 
	}
	return 0;
}
//注：不支持重复匹配子串①
