/*********************************************************************
* Filename:   sha256.c
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Implementation of the SHA-256 hashing algorithm.
              SHA-256 is one of the three algorithms in the SHA2
              specification. The others, SHA-384 and SHA-512, are not
              offered in this implementation.
              Algorithm specification can be found here:
               * http://csrc.nist.gov/publications/fips/fips180-2/fips180-2withchangenotice.pdf
              This implementation uses little endian byte order.
*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdlib.h>
#include <memory.h>
#include <openssl/sha.h> 
#include "sha256.h"
#include <stdint.h>

/*********************** FUNCTION DEFINITIONS ***********************/

void _sha256_init(SHA256_CTX *ctx)
{

 SHA256_Init(ctx);
//printf("%08x %08x\n", __func__, ctx->h[7]);
}

void _sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len)
{

 SHA256_Update(ctx, data, len);

}

void _sha256_final(SHA256_CTX *ctx, BYTE hash[])
{
WORD i,k;

 SHA256_Final(hash, ctx);
/*
printf("before \n");
for (i = 0; i < 32; i++) {
printf("%02x",  hash[i]);
}
printf(" \n");
*/
	// Since this implementation uses little endian byte ordering and SHA uses big endian,
	// reverse all the bytes when copying the final state to the output hash.
//BYTE h0, h1;
/*
WORD value;
	for (i = 0; i < 32; i+=4) {
    // reverse
	value = hash[i] & 0xFF;
    value |= (hash[i+1] << 8) & 0xFFFF;
    value |= (hash[i+2] << 16) & 0xFFFFFF;
    value |= (hash[i+3] << 24) & 0xFFFFFFFF;
    // push back

hash[i+3] = (value & 0x000000ff);
hash[i+2] = (value & 0x0000ff00) >> 8;
hash[i+1] = (value & 0x00ff0000) >> 16;
hash[i+0] = (value & 0xff000000) >> 24;
}
*/
/*
printf(" after \n");
for (i = 0; i < 32; i++) {
printf("%02x",  hash[i]);
}

printf(" \n");
*/
/*
		hash[i]      = (ctx->h[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4]  = (ctx->h[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8]  = (ctx->h[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx->h[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx->h[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (ctx->h[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (ctx->h[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (ctx->h[7] >> (24 - i * 8)) & 0x000000ff;
*/
	//}
//OPENSSL_cleanse(&ctx, sizeof(ctx));
}
