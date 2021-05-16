//Cai ba lo 2 Nhanh Can
// C code by Nguyen Huu Nhan
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define MAX 100

typedef struct{
	char TenDV[MAX];
	float GT,TL,DG;
	int PA,SL;
}DoVat;
//Khai bao cau truc Do Vat gom cac thuoc tinh cua cai ba lo

//Ham doc file du lieu 
DoVat* readFile(int *pw, int *pn){
	FILE *f = fopen("CaiBalo2.inp","r");
	DoVat *pdsdv = (DoVat*)malloc(sizeof(DoVat));
	int i=0;
	if(f!=NULL){
		fscanf(f,"%d",&(*pw));
		while(!feof(f)){
			fscanf(f,"%f%f%d%[^\n]",&pdsdv[i].TL,&pdsdv[i].GT,&pdsdv[i].SL,&pdsdv[i].TenDV);
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
//Ham tao nut goc
void TaoNutGoc(int w, float *pTLCL, float *pCT, float *pGiaLNTT, float *pTGT, float DGMAX){
	*pTGT = 0;
	*pTLCL = w;
	*pCT = *pTLCL * DGMAX;
	*pGiaLNTT = 0.0;
}

//Ham cap nhat phuong an tot nhat tam thoi
void update_PA_TNTT(float TGT, float *pGiaLNTT, int x[], DoVat *dsdv, int n){
	int i;
	if(*pGiaLNTT < TGT){
		*pGiaLNTT = TGT;
		for(i=0;i<n;i++){
			dsdv[i].PA = x[i];
		}
	}
}
//Ham tim min
int min(int a, int b){
	return (a<b) ? a : b;
}
void NhanhCan(int i, float *pTGT, float *pCT, float *pTLCL, float *pGiaLNTT, int x[], DoVat *dsdv, int n){
	int j;//j la so luong do vat duoc chon
	int SDV_MAX_CAN_CHOOSE = min(dsdv[i].SL,*pTLCL/dsdv[i].TL);
	for(j=SDV_MAX_CAN_CHOOSE;j>=0;j--){
		
		*pTGT = *pTGT + j*dsdv[i].TL;
		*pTLCL = *pTLCL - j*dsdv[i].TL;
		*pCT = *pTGT + *pTLCL*dsdv[i+1].DG;
		
		if(*pCT > *pGiaLNTT){
			x[i]= j;
			if((i==n-1) || (*pTLCL==0.0))	update_PA_TNTT(*pTGT,&(*pGiaLNTT),x,dsdv,n);
			else NhanhCan(i+1,pTGT,pCT,pTLCL,pGiaLNTT,x,dsdv,n);
		}
		x[i] = 0;
		*pTGT  = *pTGT -j*dsdv[i].GT;
		*pTLCL  = *pTLCL + j*dsdv[i].TL;
	}		
		
}
//Ham do hoa cho mau me hoa la he 1 ti.
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
	TextColor(10);
	float TTL=0,TGT=0;
	printf("|---|---------------------|---CAI BA LO 2-----|---------|---------|-----------|\n");
	printf("|---|---------------------|---------|---------|---------|---------|-----------|\n");
	printf("|STT| Ten do vat          |  T.Luong|  Gia tri|  Don gia|  S.Luong|  Phuong an|\n");
	for(int i=0;i<n;i++){
		printf("|%2d |%-21s|%9.2f|%9.2f|%9.2f|%9d|%6d     |\n",(i+1),dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].DG,dsdv[i].SL,dsdv[i].PA);
		TTL += dsdv[i].PA * dsdv[i].TL;
		TGT += dsdv[i].PA * dsdv[i].GT;
	}
	printf("|---|---------------------|---------|---------|---------|---------|-----------|\n");
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
	float CT,TGT,TLCL,GiaLNTT;
	dsdv = readFile(&w,&n);
	printf("\nBai toan cai ba lo 2 KI THUAT NHANH CAN\n\n");
	int x[n];//Luu phuong an lon nhat tam thoi
	BubbleSort(dsdv,n);
	TaoNutGoc(w,&TLCL,&CT,&GiaLNTT,&TGT,dsdv[0].DG);
	NhanhCan(0,&TGT,&CT,&TLCL,&GiaLNTT,x,dsdv,n);
	print(dsdv,w,n);
	return 0;
}

