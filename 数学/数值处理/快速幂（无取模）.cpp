#include<bits/stdc++.h>
using namespace std;
long long ksm(long long a,long long b){
	long long out_put=1;//a为底，b为幂次，out_put为输出结果
	while(b>0){
		if(b&1==1) out_put=out_put*a;
		a*=a;
		b>>=1;
	}
	return out_put;
}
