#include<stdio.h>
#include "common.h"

struct pagenodehr{
	int pnum;
	int ref;
	unsigned char his;
	pagenodehr *next;
};
typedef pagenodehr *List2;
List2 F2=NULL;

bool findhr(int pg){	//Tim xem co trang trong khung trang chua (co loi trang khong)
	for(int i=0;i<fnum;i++)
		if(frame[i]==pg) return true;
	return false;
}
bool availablehr(){	//Kiem tra xem co khung trang trong khong
	for(int i=0;i<fnum;i++)
		if(frame[i]==-1) return true;
	return false;	 
}
void addhr(int pg){	//Them trang khi khung trang trong
	//Them node vao ds
	if(F2==NULL){	//neu ds rong
		List2 np=new pagenodehr;
		F2=np;
		(*np).pnum=pg;(*np).next=NULL;
		(*np).ref=1;(*np).his=0;
	}
	else {
		List2 p=F2;
		while((*p).next!=NULL) p=(*p).next;
		List2 np=new pagenodehr;
		(*p).next= np;(*np).pnum=pg;(*np).next=NULL;
		(*np).ref=1;(*np).his=0;
	}
	//Cap nhat frame
	for(int i=0;i<fnum;i++)
		if(frame[i]==-1) {
			frame[i]=pg;
			mark=i; 
			break;
		}
}
void replacehr(int pg){	//Thay the trang
	//Tim his min
	unsigned char min=~0;
	List2 p=F2;
	while(p!=NULL){
		if((*p).his<min) min=(*p).his;
		p=(*p).next;
	}
	//Tim node co his=min
	p=F2;
	while(p!=NULL){
		if((*p).his==min) break;
		p=(*p).next;
	}	
	//Cap nhat node theo trang moi
	int rp=(*p).pnum;
	(*p).pnum=pg;
	(*p).ref=1;(*p).his=0;
	//Cap nhat frame
	for(int i=0;i<fnum;i++)
		if(frame[i]==rp) {
			frame[i]=pg; 
			mark=i;
			break;
		}
}
void updatehr(int pg){	//Tim va cap nhat reference cua node
	List2 p=F2;
	while((*p).pnum!=pg) {
		p=(*p).next;
	}
	(*p).ref=1;
}
void history(){
	List2 p=F2;
	while(p!=NULL){
		(*p).his=((*p).ref<<7)+((*p).his>>1);
		(*p).ref=0;
		p=(*p).next;
		
	}
}
void printhis(char his){
	char c=his;
	for (int i= 0;i<8;i++) {
	  printf("%d", ((c<<i) & 0x80)>>7);
	}
	printf("\t");
}
void hr(){
	for(int i=0;i<fnum;i++) frame[i]=-1;
	int loi=0;
	mark=-1;
	F2=NULL;
	printf("\tThay the trang theo thuat toan History: \n\n");
	printf("\tHISTORY\n");
	for(int j=0;j<fnum;j++) printf("\t   F%d\t",j);
	printf("\t|");
	for( int j=0;j<fnum;j++)printf("\tF%d",j);
	printf("\tPage\tLoi\n\t");
	for(int i=0;i<plength;i++){
		List2 p=F2;
		for(int j=0;j<fnum;j++) {
			if(frame[j]!=-1){
				printhis((*p).his);
				p=(*p).next;
			}
			else printf("   -    \t");
		}
		printf("|\t");
		for(int j=0;j<fnum;j++) frame[j]==-1?printf(" -\t"):j==mark?printf("(%d) \t",frame[j]):printf("%2d \t",frame[j]);
		printf("%2d\t",page[i]);
		mark=-1;
		if(!findhr(page[i])) {
			if(availablehr()) addhr(page[i]);
			else replacehr(page[i]);
			printf("*");
			loi++;
		}
		else updatehr(page[i]);
		history();	
		printf("\n\t");
	}
	for(int j=0;j<=fnum*2;j++) printf("\t");
	for(int i=0;i<fnum;i++) frame[i]==-1?printf(" -\t"):i==mark?printf("(%d) \t",frame[i]):printf("%2d \t",frame[i]);
	printf("\n\n\tSo loi trang: %d",loi);
}

