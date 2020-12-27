#include<stdio.h>
#include <stdlib.h> 
#include<time.h>
#include "common.h"

struct pagenodenru{
	int pnum;
	int ref;
	int dir;
	pagenodenru *next;
};
typedef pagenodenru *List4;
List4 F4=NULL;

bool findnru(int pg){	//Tim xem co trang trong khung trang chua (co loi trang khong)
	for(int i=0;i<fnum;i++)
		if(frame[i]==pg) return true;
	return false;
}
bool availablenru(){	//Kiem tra xem co khung trang trong khong
	for(int i=0;i<fnum;i++)
		if(frame[i]==-1) return true;
	return false;	 
}
void addnru(int pg){	//Them trang khi khung trang trong
	//Them node vao ds
	if(F4==NULL){	//neu ds rong
		List4 np=new pagenodenru;
		F4=np;
		(*np).pnum=pg;(*np).next=NULL;
		(*np).ref=1;(*np).dir=rand()%2;
	}
	else {
		List4 p=F4;
		while((*p).next!=NULL) p=(*p).next;
		List4 np=new pagenodenru;
		(*p).next= np;(*np).pnum=pg;(*np).next=NULL;
		(*np).ref=1;(*np).dir=rand()%2;
	}
	//Cap nhat frame
	for(int i=0;i<fnum;i++)
		if(frame[i]==-1) {
			frame[i]=pg;
			mark=i; 
			break;
		}
}
void replacenru(int pg){	//Thay the trang
	List4 p=F4;
	while(p!=NULL){
		if((*p).ref==0&&(*p).dir==0) break;
		p=(*p).next;
	}
	if(p==NULL){
		p=F4;
		while(p!=NULL){
			if((*p).ref==0&&(*p).dir==1) break;
			p=(*p).next;
		}
	}
	if(p==NULL){
		p=F4;
		while(p!=NULL){
			if((*p).ref==1&&(*p).dir==0) break;
			p=(*p).next;
		}
	}
	if(p==NULL){
		p=F4;
		while(p!=NULL){
			if((*p).ref==1&&(*p).dir==1) break;
			p=(*p).next;
		}
	}
	//Cap nhat node theo trang moi
	int rp=(*p).pnum;
	(*p).pnum=pg;
	(*p).ref=1;(*p).dir=rand()%2;
	//Cap nhat frame
	for(int i=0;i<fnum;i++)
		if(frame[i]==rp) {
			frame[i]=pg; 
			mark=i;
			break;
		}
}
void updatenru(int pg){	//Tim va cap nhat reference cua node
	List4 p=F4;
	while((*p).pnum!=pg) {
		p=(*p).next;
	}
	(*p).ref=1;
	if((*p).dir==0) (*p).dir=rand()%2;
}
void clearref(){
	List4 p=F4;
	while(p!=NULL){
		(*p).ref=0;
		p=(*p).next;
	}
}
void nru(){
	for(int i=0;i<fnum;i++) frame[i]=-1;
	int loi=0;
	mark=-1;
	srand(time(0));
	F4=NULL;
	printf("\tThay the trang theo thuat toan NRU: \n\n"); 
	printf("\t(REF,DIRTY)\n");
	for(int j=0;j<fnum;j++) printf("\t  F%d",j);
	printf("\t|");	
	for(int j=0;j<fnum;j++) printf("\tF%d",j);
	printf("\tPage\tLoi\n\t");
	for(int i=0;i<plength;i++){
		List4 p=F4;
		for(int j=0;j<fnum;j++) {
			if(frame[j]!=-1){
				printf("(%d,%2d)\t",(*p).ref,(*p).dir);
				p=(*p).next;
			}
			else printf("(    )\t");
		}
		printf("|\t");
		for(int j=0;j<fnum;j++) frame[j]==-1?printf(" -\t"):j==mark?printf("(%d) \t",frame[j]):printf("%2d \t",frame[j]);
		printf("%2d\t",page[i]);
		mark=-1;
		if(!findnru(page[i])) {
			if(availablenru()) addnru(page[i]);
			else replacenru(page[i]);
			printf("*");
			loi++;
		}
		else updatenru(page[i]);
		printf("\n\t");
		if(i%4==3) clearref();
	}
	for(int j=0;j<=fnum;j++) printf("\t");
	for(int i=0;i<fnum;i++) frame[i]==-1?printf(" -\t"):i==mark?printf("(%d) \t",frame[i]):printf("%2d \t",frame[i]);
	printf("\n\n\tSo loi trang: %d",loi);
}


