#include "b64.h"
#include <stdio.h>
#include <stdlib.h>


static const char base64_alphabet[] = "IBC#JOc@e456f0123PQvwghAEFG+HKLMN)rs!ujklmno78(/pqUVWXYZ-bxyzTRS";
static const unsigned char base64_suffix_map[256] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 0, 3, 0, 0, 0, 0, 46, 33, 0, 27, 0, 56, 0, 47, 13, 14, 15, 16, 9, 10, 11, 44, 45, 0, 0, 0, 0, 0, 0, 0, 7, 23, 1, 2, 0, 24, 25, 26, 28, 0, 4, 29, 30, 31, 32, 5, 17, 18, 62, 63, 61, 50, 51, 52, 53, 54, 55, 0, 0, 0, 0, 0, 0, 0, 57, 6, 0, 8, 12, 21, 22, 0, 38, 39, 40, 41, 42, 43, 48, 49, 34, 35, 0, 37, 19, 20, 58, 59, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// a= "IBCDJOcde456f0123PQvwghAEFG+HKLMNirstujklmno789/pqUVWXYZabxyzTRS"
// b=[255 for i in range(256)]
// for i in range(0,len(a)):
// 	b[ord(a[i])]=i

int b64encode(const char *indata, int inlen, char *outdata, int *outlen) {
    
    int ret = 0; // return value
    if (indata == NULL || inlen == 0) {
        return ret = -1;
    }
    
    int in_len = 0; // 源字符串长度, 如果in_len不是3的倍数, 那么需要补成3的倍数
    int pad_num = 0; // 需要补齐的字符个数, 这样只有2, 1, 0(0的话不需要拼接, )
    if (inlen % 3 != 0) {
        pad_num = 3 - inlen % 3;
    }
    in_len = inlen + pad_num;
    int out_len = in_len * 8 / 6; 
    char *p = outdata;

    int _i1,_i2,_i3,_i4;
    char _c1,_c2,_c3,_c4;
    for (int i = 0; i < in_len; i+=3) {

        _i1 = (*(indata+0) & 0b11111100) >>2;
        _i2 = ((*(indata+0) & 0b00000011) <<4) + ((*(indata+1) >>4) & 0b00001111);
        _i3 = ((*(indata+1) & 0b00001111) <<2) + ((*(indata+2) >>6) & 0b00000011);
        _i4 = (*(indata+2) & 0b00111111) >>0;

        // printf("%d,%d,%d,%d\n",_i1,_i2,_i3,_i4);

        *(p + 0) = base64_alphabet[_i1];
        *(p + 1) = base64_alphabet[_i2];
        *(p + 2) = base64_alphabet[_i3];
        *(p + 3) = base64_alphabet[_i4];
        
        if ((i==(in_len-3)) && (_i3==0)) *(p + 2) = '=';
        if ((i==(in_len-3)) && (_i4==0)) *(p + 3) = '=';
        indata += 3;
        p += 4;
    }
    
    if(outlen != NULL) {
        *outlen = out_len;
    }
    
    return ret;
}


int b64decode(const char *indata, int inlen,  char *outdata, int *outlen){
	
	int ret = 0;
	if(indata == NULL || inlen <= 0 || outdata == NULL || outlen == NULL){
		return ret = -1;
	}
	if(inlen % 4 !=0){
		return ret = -2;
	}

	int pn=0;
	if(indata[inlen-1]=='='){
		pn++;
		if(indata[inlen-2]=='='){
			pn++;
		}
	}

	int _n1,_n2,_n3,_n4;
	int _i1,_i2,_i3;
	char _c1,_c2,_c3;
	int edn=0;
	for (int i = 0; i < inlen; i+=4){

		_n1 = base64_suffix_map[indata[i+0]];
		_n2 = base64_suffix_map[indata[i+1]];
		_n3 = base64_suffix_map[indata[i+2]];
		_n4 = base64_suffix_map[indata[i+3]];
		// char s4[10];
		// char s1[10];
		// char s2[10];
		// char s3[10];
		// printf("%06s %06s %06s %06s \n",itoa(_n1,s1,2),itoa(_n2,s2,2),itoa(_n3,s3,2),itoa(_n4,s4,2));
		// printf("-\n");

		_i1 = ((_n1 & 0b00111111 ) << 2) + ((_n2 >> 4 ) & 0b00001111);
		_i2 = ((_n2 & 0b00001111 ) << 4) + ((_n3 >> 2 ) & 0b00001111);
		_i3 = ((_n3 & 0b00111111 ) << 6) + ((_n4 >> 0 ) & 0b00111111);
		// printf("%08s %08s %08s \n",itoa(_i1,s1,2),itoa(_i2,s2,2),itoa(_i3,s3,2));

		_c1 = (char)(_i1);
		_c2 = (char)(_i2);
		_c3 = (char)(_i3);

		outdata[edn++] = _c1;
		outdata[edn++] = _c2;
		outdata[edn++] = _c3;

	}
	if(outdata!=NULL){
		*outlen = edn-pn;
	}
	return ret;
}