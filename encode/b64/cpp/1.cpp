#include <stdio.h>
#include <string.h>
#include "b64.h";
#include "b64.cpp";

// cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /Tc1.cpp /link /OUT:1.exe /SUBSYSTEM:CONSOLE /MACHINE:x64

int main(void){
	char s1[] = "123i1op<";
	printf("s1:[%s], len = %d\n", s1, strlen(s1));

	char s2[256] = {0};
	int  s2len = 0;
	b64encode(s1,strlen(s1),s2,&s2len);
	printf("s2:[%s], len = %d\n", s2, s2len);

	char s3[256] = {0};
	int  s3len = 0;
	b64decode(s2,strlen(s2),s3,&s3len);
	printf("s3:[%s], len = %d\n", s3, s3len);

	FILE * input = NULL;
	input=fopen("p.bin","rb");

	int payloadlen = 0;
	unsigned char payload[1024];
	while(fread(payload+payloadlen,sizeof(unsigned char),1,input)){
		payloadlen++;
	}
	fclose(input);

	printf("-------------\npayload:\n[");
	for(int i=0; i< payloadlen ;i++){
		printf("%02x",payload[i]);
	}
	printf("]\nlen: %d\n-------------\n", payloadlen);

	unsigned char s4[1024] = {0};
	int  s4len = 0;
	b64encode(payload,payloadlen,s4,&s4len);
	printf("payload encode:\n[%s]\nlen: %d\n-------------", s4, s4len);
	
	return 0;
}