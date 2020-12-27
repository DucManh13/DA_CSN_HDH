#include<stdio.h>
#include "common.h"

bool findopt(int pg){	//Tim xem co trang trong khung trang chua (co loi trang khong)
	for(int i=0;i<fnum;i++)
		if(frame[i]==pg) return true;
	return false;
}
bool availableopt(){	//Kiem tra xem co khung trang trong khong
	for(int i=0;i<fnum;i++)
		if(frame[i]==-1) return true;
	return false;	 
}
void addopt(int pg){	//Them trang khi khung trang trong
	for(int i=0;i<fnum;i++)
		if(frame[i]==-1) {
			frame[i]=pg;
			mark=i;
			break;
		}
}
int future(int pg, int index){	//tim chi so cua lan su dung trang gan nhat trong tuong lai
	for(int i=index+1;i<plength;i++){
		if(page[i]==pg) return i;
	}
	return 10000;
}
void replaceopt(int pg,int index){	//Thay the trang
	int t,k=0;
	int m=future(frame[0],index);
	for(int i=1;i<fnum;i++){
		t=future(frame[i],index);
		if (t>m){
			m=t;
			k=i;
		}
	}
	frame[k]=pg;
	mark=k; 		
}
void opt(){
	for(int i=0;i<fnum;i++) frame[i]=-1;
	int loi=0;
	mark=-1;
	printf("\tThay the trang theo thuat toan OPT: \n\n");
	for(int j=0;j<fnum;j++)
		printf("\tF%d",j);
	printf("\tPage\tLoi\n\t");
	for(int i=0;i<plength;i++){
		for(int j=0;j<fnum;j++) frame[j]==-1?printf(" -\t"):j==mark?printf("(%d) \t",frame[j]):printf("%2d \t",frame[j]);
		printf("%2d\t",page[i]);
		mark=-1;
		if(!findopt(page[i])) {
			if(availableopt()) addopt(page[i]);
			else replaceopt(page[i],i);
			printf("*");
			loi++;
		}	
		printf("\n\t");
	}
	for(int i=0;i<fnum;i++) frame[i]==-1?printf(" -\t"):i==mark?printf("(%d) \t",frame[i]):printf("%2d \t",frame[i]);
	printf("\n\n\tSo loi trang: %d",loi);
}

