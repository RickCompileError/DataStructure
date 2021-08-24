#include <bits/stdc++.h>

using namespace std;

void print(int arr[], int size){
	for (int i=0;i<size;i++) cout <<arr[i] <<' ';
	cout <<endl;
}

void quick(int a[],int left,int right){
	if (left<right){
		int pivot=a[left],i=left,j=right;
		do{
			while (a[i]<=pivot && i<=right) i++;
			while (a[j]>pivot) j--;
			if (i<j) swap(a[i],a[j]);
		}while (i<j);
		swap(a[left],a[j]);
		quick(a,left,j-1);
		quick(a,j+1,right);
	}
}

void test(){
	srand(time(NULL));
	int size=10;
	int arr[size];
	for (int i=0;i<size;i++) arr[i]=rand()%20;
	cout <<"Origin   : ", print(arr,size);
	quick(arr,0,size-1);
	cout <<"Sort down: ", print(arr,size);
}

int main()
{
	test();
}
