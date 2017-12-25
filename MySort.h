#include<ctime>
#include<cstdlib>
using namespace std;

void QuickSort3(double arr[],int L,int R){	

	if(R<=L)
		return;

	srand(time(NULL));
	swap(arr[L],arr[rand()%(R-L+1)+L]);	
	int lt=L+1;
	int gt=R;
	int eq=L+1;	

	while(eq <= gt){
		if( arr[eq] < arr[L]){
			swap(arr[eq],arr[lt]);
			lt++;
			eq++;
		}
		else if( arr[eq] > arr[L]){
			swap( arr[eq] , arr[gt] );
			gt--;
		}
		else
			eq++;
	}	
	
	//这个地方是个大坑 选择交换的元素是有讲究的一定是靠左边的那一部分,这样才能保证左半部分长度一定会减少，避免陷入死循环
	//边界问题一定要自己画图分析一下
	swap(arr[L],arr[lt-1]);
	QuickSort3(arr,L,lt-2);
	QuickSort3(arr,gt+1,R);

}


void QuickSort2(double arr[],int L,int R){

	if(R<=L)
		return;
	srand(time(NULL));
	swap(arr[L],arr[rand()%(R-L+1)+L]);
	int lt=L+1;
	int gt=R;
	
	while(1){
		
		while(lt<=R&&arr[lt]<arr[L])
			lt++;
		while(gt>=L+1&&arr[gt]>arr[L])
			gt--;
		//注意lt gt连个指针的含义 它们扫过的值一定要么大于要么小于 最后两个指针相遇退出		
		if(gt<=lt)
			break;
		
		swap(arr[lt],arr[gt]);	
		lt++;gt--;	
	}

	swap(arr[L],arr[lt-1]);
	QuickSort2(arr,L,lt-2);
	QuickSort2(arr,lt,R);
}


void QuickSort1(double arr[],int L,int R){

	if(R<=L)
		return;
	
	srand(time(NULL));
	swap(arr[L],arr[rand()%(R-L+1)+L]);
	int i=L+1;
	int lt=L+1;
	while(i<=R){
		if(arr[i]<arr[L]){
			swap(arr[i],arr[lt]);
			lt++;
		}
		i++;
	}
	//同样注意边界问题  lt指向左半部分后一个元素
	swap(arr[L],arr[lt-1]);
	QuickSort1(arr,L,lt-2);
	QuickSort1(arr,lt,R);

}