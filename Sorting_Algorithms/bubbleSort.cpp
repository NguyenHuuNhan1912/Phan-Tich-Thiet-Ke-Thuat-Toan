//Bubble Sort Algorithm(Thuat toan sap xep noi bot)
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

//Bubble Sort Algorithm
void bubbleSort(Data arr[], int n){
	int i,j;
	for(i=0;i<n-1;i++){
		for(j=n-1;j>=i+1;j--){
			if(arr[j].key < arr[j-1].key){
				swap(&arr[j],&arr[j-1]);
			}
		}
	}
}
int main(){
	Data arr[MAX];
	int n;
	readFile_Dong(arr,&n);
	readFile_Tinh(arr,&n);
	printf("Thuat toan sap xep chon\n");
	printf("\nDay so truoc khi sap xep\n");
	//print_Tinh(arr,n);
	print_Dong(arr,n);
	printf("\n\nDay so sau khi sap xep\n");
	//Xu li tren truong so nguyen
	bubbleSort(arr,n);
	//print_Tinh(arr,n);
	print_Dong(arr,n);
	return 0;
}
//Link 2 file: https://drive.google.com/drive/folders/1HxoGSicfPOuN8tIriZ076Ml0ixcsPJdR?usp=sharing 

