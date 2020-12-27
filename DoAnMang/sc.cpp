#include<stdio.h>
#include "common.h"

struct pagenodesc{
	int pnum;
	int ref;
	pagenodesc *next;
};
typedef pagenodesc *List3;
List3 F3=NULL;
List3 victim=NULL;

bool findsc(int pg){	//Tim xem co trang trong khung trang chua (co loi trang khong)
	for(int i=0;i<fnum;i++)
		if(frame[i]==pg) return true;
	return false;
}
bool availablesc(){	//Kiem tra xem co khung trang trong khong
	for(int i=0;i<fnum;i++)
		if(frame[i]==-1) return true;
	return false;	 
}
void addsc(int pg){	//Them trang khi khung trang trong
	//Them node vao ds
	if(F3==NULL){	//neu ds rong
		List3 np=new pagenodesc;
		F3=np;
		(*np).pnum=pg;(*np).next=F3;(*np).ref=1;
	}
	else {
		List3 p=F3;
		while((*p).next!=F3) p=(*p).next;
		List3 np=new pagenodesc;
		(*p).next= np;(*np).pnum=pg;(*np).next=F3;(*np).ref=1;
	}
	//Cap nhat frame
	for(int i=0;i<fnum;i++)
		if(frame[i]==-1) {
			frame[i]=pg;
			mark=i; 
			break;
		}
}
void replacesc(int pg){	//Thay the trang
	if(victim==NULL) victim=F3;
	//Tim node trang nan nhan co ref=0
	while((*victim).ref==1) {
		(*victim).ref=0;
		victim=(*victim).next;
	}
	//Cap nhat node theo trang moi
	int rp=(*victim).pnum;
	(*victim).pnum=pg;
	(*victim).ref=1;
	victim=(*victim).next;
	//Cap nhat frame
	for(int i=0;i<fnum;i++)
		if(frame[i]==rp) {
			frame[i]=pg; 
			mark=i;
			break;
		}
}
void updatesc(int pg){	//Tim va cap nhat reference cua node
	List3 p=F3;
	while((*p).pnum!=pg) {
		p=(*p).next;
	}
	(*p).ref=1;
}
void sc(){
	for(int i=0;i<fnum;i++) frame[i]=-1;
	int loi=0;
	mark=-1;
	F3=NULL;
	victim=NULL;
	printf("\tThay the trang theo thuat toan Second Chance: \n\n");
	printf("\tREF\n");
	for(int j=0;j<fnum;j++) printf("\tF%d",j);
	printf("\t|");
	for(int j=0;j<fnum;j++) printf("\tF%d",j);
	printf("\tPage\tLoi\n\t");
	for(int i=0;i<plength;i++){
		List3 p=F3;
		for(int j=0;j<fnum;j++) {
			if(frame[j]!=-1){
				printf("%d\t",(*p).ref);
				p=(*p).next;
			}
			else printf("-\t");
		}
		printf("|\t");
		for(int j=0;j<fnum;j++) frame[j]==-1?printf(" -\t"):j==mark?printf("(%d) \t",frame[j]):printf("%2d \t",frame[j]);
		printf("%2d\t",page[i]);
		mark=-1;
		if(!findsc(page[i])) {
			if(availablesc()) addsc(page[i]);
			else replacesc(page[i]);
			printf("*");
			loi++;
		}
		else updatesc(page[i]);	
		printf("\n\t");
	}
	for(int j=0;j<=fnum;j++) printf("\t");
	for(int i=0;i<fnum;i++) frame[i]==-1?printf(" -\t"):i==mark?printf("(%d) \t",frame[i]):printf("%2d \t",frame[i]);
	printf("\n\n\tSo loi trang: %d",loi);
}

