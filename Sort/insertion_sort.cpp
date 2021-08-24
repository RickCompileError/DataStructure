#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a[10]{1,5,2,4,7,8,3,4,8,10};
	for (int i=1;i<10;i++){
		int j,tem=a[i];
		for (j=i-1;j>=0 && tem<a[j];j--) swap(a[j+1],a[j]);
		a[j+1]=tem;
	}
	for (int i : a) cout <<i <<' ';
	cout <<endl;
}
