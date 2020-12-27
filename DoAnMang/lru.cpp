#include <stdio.h>
#include "common.h"

struct pagenodelru{
	int pnum;
	pagenodelru *next;
};
typedef pagenodelru *List1;
List1 F1=NULL;

bool findlru(int pg){	//Tim xem co trang trong khung trang chua (co loi trang khong)
	for(int i=0;i<fnum;i++)
		if(frame[i]==pg) return true;
	return false;
}
bool availablelru(){	//Kiem tra xem co khung trang trong khong
	for(int i=0;i<fnum;i++)
		if(frame[i]==-1) return true;
	return false;	 
}
void addlru(int pg){	//Them trang khi khung trang trong
	//Them node vao ds
	if(F1==NULL){	//neu ds rong
		List1 np=new pagenodelru;
		(*np).pnum=pg;(*np).next=NULL;
		F1=np;
	}
	else {
		List1 p=F1;
		while((*p).next!=NULL) p=(*p).next;
		List1 np=new pagenodelru;
		(*p).next= np;(*np).pnum=pg;(*np).next=NULL;
	}
	//Cap nhat frame
	for(int i=0;i<fnum;i++)
		if(frame[i]==-1) {
			frame[i]=pg;
			mark=i; 
			break;
		}
}
void replacelru(int pg){	//Thay the trang
	//Xoa node dau tien
	List1 p=F1;
	int rp=(*p).pnum;
	F1=(*p).next;
	delete p;
	//Them node moi vao cuoi ds
	p=F1;
	while((*p).next!=NULL) p=(*p).next;
	List1 np=new pagenodelru;
	(*p).next= np;(*np).pnum=pg;(*np).next=NULL;
	//Cap nhat frame
	for(int i=0;i<fnum;i++)
		if(frame[i]==rp) {
			frame[i]=pg; 
			mark=i;
			break;
		}
}
void updatelru (int pg){	//Tim va dua node xuong cuoi danh sach
	//Tim node 
	List1 p=F1,before,last;
	while((*p).pnum!=pg) {
		before=p;
		p=(*p).next;
	}
	if ((*p).next==NULL) return;	//node da o cuoi ds
	if(p==F1) F1=(*p).next;			//node o dau ds, thay node thu 2 lam dau
	else (*before).next=(*p).next;	//noi node truoc p voi node sau p
	//Dua node xuong cuoi ds
	last=p;
	while((*p).next!=NULL) p=(*p).next;
	(*p).next=last;(*last).next=NULL;
}
void lru(){	
	for(int i=0;i<fnum;i++) frame[i]=-1;
	int loi=0;
	mark=-1;
	F1=NULL;
	printf("\tThay the trang theo thuat toan LRU: \n\n");
	for(int j=0;j<fnum;j++)
		printf("\tF%d",j);
	printf("\tPage\tLoi\n\t");
	for(int i=0;i<plength;i++){
		for(int j=0;j<fnum;j++) frame[j]==-1?printf(" -\t"):j==mark?printf("(%d) \t",frame[j]):printf("%2d \t",frame[j]);
		printf("%2d\t",page[i]);
		mark=-1;
		if(!findlru(page[i])) {
			if(availablelru()) addlru(page[i]);
			else replacelru(page[i]);
			printf("*");
			loi++;	
		}
		else updatelru(page[i]);	
		printf("\n\t");
	}
	for(int i=0;i<fnum;i++) frame[i]==-1?printf(" -\t"):i==mark?printf("(%d) \t",frame[i]):printf("%2d \t",frame[i]);
	printf("\n\n\tSo loi trang: %d",loi);
}

