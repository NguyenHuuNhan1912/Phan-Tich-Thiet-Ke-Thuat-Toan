//Cai ba lo 3
// C code by Nguyen Huu Nhan
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define MAX 100

typedef struct{
	char TenDV[MAX];
	float GT,TL,DG;
	int PA;
}DoVat;
//Khai bao cau truc Do Vat gom cac thuoc tinh cua cai ba lo

//Ham doc file du lieu 
DoVat* readFile(int *pw, int *pn){
	FILE *f = fopen("CaiBalo3.inp","r");
	DoVat *pdsdv = (DoVat*)malloc(sizeof(DoVat));
	int i=0;
	if(f!=NULL){
		fscanf(f,"%d",&(*pw));
		while(!feof(f)){
			fscanf(f,"%f%f%[^\n]",&pdsdv[i].TL,&pdsdv[i].GT,&pdsdv[i].TenDV);
			pdsdv[i].DG = pdsdv[i].GT / pdsdv[i].TL;
			pdsdv[i].PA = 0;
			i+=1;
			pdsdv = (DoVat*)realloc(pdsdv,sizeof(DoVat)*(i+1));
		}
		*pn = i;
	}
	else printf("\nLoi mo file !");
	fclose(f);
	return pdsdv;
}

//Ham doi cho
void swap(DoVat *a, DoVat *b){
	DoVat tmp = *a;
		   *a = *b;
		   *b = tmp;
}

//Bubble Sort Algorithm
void BubbleSort(DoVat *dsdv, int n){
	for(int i=0; i<n-1; i++){
		for(int j=n-1; j>=i+1; j--){
			if(dsdv[j].DG > dsdv[j-1].DG){
				swap(&dsdv[j], &dsdv[j-1]);	
			}
		}
	}
}

//Greedy Algorithm
void Greedy(DoVat *dsdv, int w, int n){
	for(int i=0; i<n; i++){
		if(w/dsdv[i].TL >= 1)
		dsdv[i].PA = 1;
		w = w - dsdv[i].PA * dsdv[i].TL;
	}
}

//Ham do hoa cho mau me hoa la he 1 ti
void TextColor(WORD color){ 
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0; wAttributes |= color;
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

//Ham in thong tin ket qua,xuat phuong an
void print(DoVat *dsdv, int w, int n){
	TextColor(3);
	float TTL=0,TGT=0;
	printf("|---|---------------------|---CAI BA LO 3-----|---------|-----------|\n");
	printf("|---|---------------------|---------|---------|---------|-----------|\n");
	printf("|STT| Ten do vat          |  T.Luong|  Gia tri|  Don gia| Phuong an |\n");
	for(int i=0;i<n;i++){
		printf("|%2d |%-21s|%9.2f|%9.2f|%9.2f|%6d     |\n",(i+1),dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].GT,dsdv[i].PA);
		TTL += dsdv[i].PA * dsdv[i].TL;
		TGT += dsdv[i].PA * dsdv[i].GT;
	}
	printf("|---|---------------------|---------|---------|---------|-----------|\n");
	printf("\n- Trong luong cua ba lo ban dau: %d\n",w);
	printf("- Tong trong luong: %.2f\n",TTL);
	printf("- Tong gia tri: %.2f\n",TGT);
	printf("- PA X( ");
	for(int i=0;i<n;i++){
		if(i==n-1) printf("%d",dsdv[i].PA);
		else printf("%d,",dsdv[i].PA);
	}
	printf(")\n");
}

int main(){
	DoVat *dsdv;
	int n,w;
	dsdv = readFile(&w,&n);
	BubbleSort(dsdv,n);
	Greedy(dsdv,w,n);
	print(dsdv,w,n);
	return 0;
}
