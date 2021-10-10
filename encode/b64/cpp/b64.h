#ifndef b64_h
#define b64_h

#include <stdio.h>

#if __cplusplus
extern "C"{
#endif
	int b64encode(const char *in, int inlen, char *out, int *outlen);
	int b64decode(const char *in, int inlen, char *out, int *outlen);

#if __cplusplus
}
#endif

#endif
