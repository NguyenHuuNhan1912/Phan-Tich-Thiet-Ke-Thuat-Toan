//Heap Sort Algorithm(Thuat toan sap xep vun dong)
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

//PushDown de tao cay heap theo qui tac(co 3 qui tac tham khao trong sgk PTTKTT Nguyen Van Linh)
void PushDown(Data arr[], int begin, int end){
    int r = begin;
    int last = (end-1)/2;
    while(r<=last){
        int L=2*r+1;
        int R;
        if(end==2*r+1){
            R=2*r+1;
        }
        else R=2*r+2;
        int Left=arr[L].key;
        int Right=arr[R].key;
        int key=arr[r].key;
        if(key<Left && Left>=Right){
            swap(&arr[r],&arr[L]);
            r=L;
        }
        else if(key<Right && Right>Left){
            swap(&arr[r],&arr[R]);
            r=R;
        }
        else r=end;
    }
}

//Heap Sort Algorithm
void heapSort(Data arr[], int n){
    int i;
    for(i=(n-2)/2;i>=0;i--){
        PushDown(arr,i,n-1);
    }
    for(i=n-1;i>=2;i--){
        swap(&arr[0],&arr[i]);
        PushDown(arr,0,i-1);
    }
    swap(&arr[0],&arr[1]);
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
	heapSort(arr,n);
	print_Tinh(arr,n);
	//print_Dong(arr,n);
	return 0;
}
//Link 2 file: https://drive.google.com/drive/folders/1HxoGSicfPOuN8tIriZ076Ml0ixcsPJdR?usp=sharing 

