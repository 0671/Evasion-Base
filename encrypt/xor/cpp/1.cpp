#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void XOR(char* data, size_t data_len, char* key, size_t key_len){
	
	int j = 0;
	for(int i = 0; i < data_len; i++){
		if(j == key_len-1) j=0;
		data[i] = data[i] ^ key[j];
		j++;
	}
}

int main(void){

	char key[] = "ad780*^%21";

	FILE * input = NULL;
	input=fopen("p.bin","rb");

	int payloadlen = 0;
	unsigned char payload[1024];
	while(fread(payload+payloadlen,sizeof(unsigned char),1,input)){
		payloadlen++;
	}
	fclose(input);
	printf("-------------\npayload:\n{");
	for(int i=0; i< payloadlen ;i++){
		printf("0x%02x, ",payload[i]);
	}
	printf("}\nlen: %d\n-------------\n", payloadlen);

	XOR(payload,payloadlen,key,sizeof(key));

	printf("xor key:[%s]\n",key);
	printf("payload xor encrypt:\n{");
	for(int i=0; i< payloadlen ;i++){
		printf("0x%02x, ",payload[i]);
	}
	printf("}\nlen: %d\n-------------\n", payloadlen);
	return 0;
}