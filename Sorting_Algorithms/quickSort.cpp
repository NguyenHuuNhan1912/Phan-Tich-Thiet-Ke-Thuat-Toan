//Quick Sort Algorithm(Thuat toan sap xep nhanh)
//C code by Nguyen Huu Nhan

#include <Stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct{
	int key;
	float otherkey;
}Data;
//Khai bao cau truc Data gom 2 truong (int and float)

//Doc file du lieu tinh
void readFile_Tinh(Data arr[], int *pn){
	FILE *f = fopen("dayso.inp","r");
	if(f!=NULL){
		fscanf(f,"%d",&(*pn));
		for(int i=0;i<*pn;i++){
			fscanf(f,"%d",&arr[i].key);
		}
	}
	else printf("Xay ra loi khong the mo file !");
	fclose(f);
}

//Doc file du lieu dong
void readFile_Dong(Data arr[], int *pn){
	FILE *f = fopen("data.inp","r");
	int i=0;
	if(f!=NULL){
		while(!feof(f)){
			fscanf(f,"%d%f",&arr[i].key,&arr[i].otherkey);
			i+=1;
		}
	}
	else printf("\nLoi khong the mo file du lieu");
	*pn=i;
	fclose(f);
}

//In danh sach la 1 mang da lay du lieu tu file tinh
void print_Tinh(Data arr[], int n){
	for(int i=0;i<n;i++){
		printf("%d ",arr[i].key);
	}
}

//In danh sach la 1 mang da lay du lieu tu file dong
void print_Dong(Data arr[], int n){
	for(int i=0;i<n;i++){
		printf("%d %.2f\n",arr[i].key,arr[i].otherkey);
	}
}

//Ham doi cho
void swap(Data *a, Data *b){
	Data tmp = *a;
		*a = *b;
		*b = tmp;
}
//Ham tim chot(Chon phan tu co khoa lon nhat trong hai phan tu co khoa khac nhau dau tien tu trai qua)
int findPivot(Data arr[], int i, int j){
	int firstkey = arr[i].key;
	int k = i+1;
	while((k<=j) && (arr[k].key == firstkey))	k++;
	if(k>j) return -1;
	if(arr[k].key > firstkey) return k;//bien the thi sua lai la return i;
	return i;//bien the thi sua lai return k;
}

//Ham phan hoach(Con tro L va con tro R, L<R swap, L>R stop)
int partition(Data arr[], int i, int j, int pivot){
	int L = i;
	int R = j;
	while(L<=R){
		while(arr[L].key < pivot ) L++;//bien the thi sua lai la >
		while(arr[R].key >= pivot) R--;//bien the thi sua lai la <=
		if (L <R) swap (& arr [L], & arr [R]);
	}
	return L;
}

//Quick Sort Algorithm
void quickSort(Data arr[], int i, int j){
	int pivot,pivotindex,k;
	pivotindex = findPivot(arr,i,j);
	if(pivotindex != -1){
		pivot = arr[pivotindex].key;
		k = partition(arr,i,j,pivot);
		quickSort(arr,i,k-1);
		quickSort(arr,k,j);
	} 
}
int main(){
	Data arr[MAX];
	int n;
	readFile_Dong(arr,&n);
	readFile_Tinh(arr,&n);
	printf("Thuat toan sap xep chon\n");
	printf("\nDay so truoc khi sap xep\n");
	print_Tinh(arr,n);
	//print_Dong(arr,n);
	printf("\n\nDay so sau khi sap xep\n");
	//Xu li tren truong so nguyen
	quickSort(arr,0,n-1);
	print_Tinh(arr,n);
	//print_Dong(arr,n);
	return 0;
}
//Link 2 file: https://drive.google.com/drive/folders/1HxoGSicfPOuN8tIriZ076Ml0ixcsPJdR?usp=sharing 

