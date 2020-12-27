#include <stdio.h>
#include "common.h"

int first;

bool findfifo(int pg){
	for(int i=0;i<fnum;i++)
		if(frame[i]==pg) return true;
	return false;
}
void replacefifo(int pg){
	frame[first]=pg;
	mark=first;
	if(first<fnum-1)first++;
	else first=0;
}
void fifo(){
	for(int i=0;i<fnum;i++) frame[i]=-1;	
	first=0;		
	mark=-1;
	int loi=0;
	printf("\tThay the trang theo thuat toan FIFO: \n\n");
	for(int j=0;j<fnum;j++)
		printf("\tF%d",j);
	printf("\tPage\tLoi\n\t");
	for(int i=0;i<plength;i++){
		for(int j=0;j<fnum;j++) frame[j]==-1?printf(" -\t"):j==mark?printf("(%d) \t",frame[j]):printf("%2d \t",frame[j]);
		printf("%2d\t",page[i]);
		mark=-1;
		if(!findfifo(page[i])) {
			replacefifo(page[i]);
			printf("*");
			loi++;
		}
		printf("\n\t");
	}
	for(int i=0;i<fnum;i++) frame[i]==-1?printf(" -\t"):i==mark?printf("(%d) \t",frame[i]):printf("%2d \t",frame[i]);
	printf("\n\n\tSo loi trang: %d",loi);
}


