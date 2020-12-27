#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "common.h"
#include "fifo.h"
#include "lru.h"
#include "opt.h"
#include "hr.h"
#include "sc.h"
#include "nru.h"
#define max 1000

int frame[max];
int fnum;	
int page[max];
int plength;
int mark;

void setup();
void khungtrang();
void nhaptrang();
void menu();

int main(){
	system("color F0");
	setup();
	menu();
	return 0;
}

void setup(){
	fnum=3;
	for(int i=0;i<fnum;i++) frame[i]=-1;
	int A[]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
	plength=(int) sizeof(A) / sizeof(A[0]);
	for(int i=0;i<plength;i++) page[i]=A[i];
}
void khungtrang(){
	do{
		printf("\tNhap so khung trang cap phat: ");
		scanf("%d",&fnum);
	} while(fnum<=0);
}
void nhaptrang(){
	for(int u=0;u<max;u++) page[u]=NULL;	
	char A[max];
	int i,k,t;
	bool gotnum;
	do{
		printf("\tNhap chuoi tham chieu trang nho: ");
		fflush(stdin);gets(A);	
		i=k=t=0;
		gotnum=false;
		while(true){
			if(A[i]!=NULL) {				//chuoi nhap vao chua ket thuc
				if('0'<=A[i]&&A[i]<='9'){	//neu gap chu so thi cap nhat t
					gotnum=true;
					t=t*10+(A[i]-'0');
				}
				else if(A[i]==' ') {		//gap dau cach
					if(gotnum){			//neu co so trang t thi them t vao chuoi trang
						page[k]=t;
						k++;
						t=0;
						gotnum=false;
					}	
				}
				else {			//gap ki tu khac
					k=0;
					break;
				}
				i++;
			}
			else {		//ket thuc chuoi nhap vao
				if(gotnum){			//neu co so trang t thi them t vao chuoi trang
					page[k]=t;
					k++;
				}
				break;	
			}
		}
	} while(k==0);
	plength=k;
}
void menu(){
	char chon[2];
	bool check=true;
	while(check){
		printf("\n\n\t--------------------------Page Replacement------------------------\n\n");
		printf("\tSo khung trang: %d\n",fnum);
		printf("\tChuoi tham chieu trang: "); for(int i=0;i<plength;i++) printf("%d ",page[i]);
		printf("\n\n");
		printf("\t1. Thuat toan FIFO\n");
		printf("\t2. Thuat toan OPT\n");
		printf("\t3. Thuat toan LRU\n");
		printf("\t4. Thuat toan History\n");
		printf("\t5. Thuat toan Second chance\n");
		printf("\t6. Thuat toan NRU\n");
		printf("\t7. Thay doi so khung trang\n");
		printf("\t8. Thay doi chuoi tham chieu trang\n");
		printf("\t0. Thoat\n\n");
		printf("\tMoi chon chuc nang: ");
		
		fflush(stdin);gets(chon);
		if(chon[1]!=NULL) chon[0]='9';
		
		printf("\n");
		switch(chon[0]-48){
			case 1:
				fifo();
				break;
			case 2:
				opt();
				break;
			case 3:
				lru();
				break;
			case 4:
				hr();
				break;
			case 5:
				sc();
				break;
			case 6:
				nru();
				break;	
			case 7:
				khungtrang();
				break;
			case 8:
				nhaptrang();
				break;	
			case 0: 
				check=false;
				break;
			default:
				printf("\tSai cu phap, vui long nhap lai!\n");
				break;
		}
	}
}

