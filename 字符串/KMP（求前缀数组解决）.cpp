#include<bits/stdc++.h>
using namespace std;
string front;
void create(string &front){
	cin>>front;
	int l=front.size(),len=0;
	vector<int> next(l);
	next[0]=0;
	for(int i=1;i<l;i++){
		len=next[i-1];
		while(front[i]!=front[len]){
			if(len==0){
				next[i]=0;
				break;
			}
			len=next[len-1];
		}
		if(front[i]==front[len]) next[i]=len+1;
	}
	//next数组求解完成 
	return;
}
//next就是前缀函数数组
//实际操作时，将要寻找的字符串和给定字符串中间加上一个#拼接起来，如str（给定字符串）=front（前缀字符串）+'#'+str 
//不用单独先求front字符串的前缀数组，直接拼起来
//对整个字符串求前缀函数数组
//然后在数组中寻找跟寻找字符串长度相同的数组标号
//数组标号等于front长度的就是终点
//输入：字符串front
//输出：字符串的前缀数组
