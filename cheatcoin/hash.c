/* хеш-функция, T13.654-T13.775 $DVS:time$ */

#include <string.h>
#include "sha256.h"
#include "hash.h"

void cheatcoin_hash(void *data, size_t size, cheatcoin_hash_t hash) {
	SHA256_CTX ctx;
	_sha256_init(&ctx);
	_sha256_update(&ctx, data, size);
	_sha256_final(&ctx, (uint8_t *)hash);
	_sha256_init(&ctx);
	_sha256_update(&ctx, (uint8_t *)hash, sizeof(cheatcoin_hash_t));
	_sha256_final(&ctx, (uint8_t *)hash);
}

unsigned cheatcoin_hash_ctx_size(void) {
	return sizeof(SHA256_CTX);
}

void cheatcoin_hash_init(void *ctxv) {
	SHA256_CTX *ctx = (SHA256_CTX *)ctxv;
	_sha256_init(ctx);
}

void cheatcoin_hash_update(void *ctxv, void *data, size_t size) {
	SHA256_CTX *ctx = (SHA256_CTX *)ctxv;
	_sha256_update(ctx, data, size);
}

void cheatcoin_hash_final(void *ctxv, void *data, size_t size, cheatcoin_hash_t hash) {
	SHA256_CTX ctx;
	memcpy(&ctx, ctxv, sizeof(ctx));
	_sha256_update(&ctx, (uint8_t *)data, size);
	_sha256_final(&ctx, (uint8_t *)hash);
	_sha256_init(&ctx);
	_sha256_update(&ctx, (uint8_t *)hash, sizeof(cheatcoin_hash_t));
	_sha256_final(&ctx, (uint8_t *)hash);
}

uint64_t cheatcoin_hash_final_multi(void *ctxv, uint64_t *nonce, int attempts, int step, cheatcoin_hash_t hash) {
	SHA256_CTX ctx;
	cheatcoin_hash_t hash0;
	uint64_t min_nonce = 0;
	int i;
	for (i = 0; i < attempts; ++i) {
		memcpy(&ctx, ctxv, sizeof(ctx));
		_sha256_update(&ctx, (uint8_t *)nonce, sizeof(uint64_t));
		_sha256_final(&ctx, (uint8_t *)hash0);
		_sha256_init(&ctx);
		_sha256_update(&ctx, (uint8_t *)hash0, sizeof(cheatcoin_hash_t));
		_sha256_final(&ctx, (uint8_t *)hash0);
		if (!i || cheatcoin_cmphash(hash0, hash) < 0) {
			memcpy(hash, hash0, sizeof(cheatcoin_hash_t));
			min_nonce = *nonce;
		}
		*nonce += step;
	}
	return min_nonce;
}

void cheatcoin_hash_get_state(void *ctxv, cheatcoin_hash_t state) {
	SHA256_CTX *ctx = (SHA256_CTX *)ctxv;
	memcpy(state, ctx->h, sizeof(cheatcoin_hash_t));
}

void cheatcoin_hash_set_state(void *ctxv, cheatcoin_hash_t state, size_t size) {
	SHA256_CTX *ctx = (SHA256_CTX *)ctxv;
	memcpy(ctx->h, state, sizeof(cheatcoin_hash_t));
//ctx->datalen = 0;
//ctx->bitlen = size << 3;
//ctx->Nl=size *8;	ctx->Nh=0; // Nl,Nh contains the length (in bits (64) lo/hi) of all the message fragments
ctx->num=0; // Length of the message fragment
ctx->md_len=SHA256_DIGEST_LENGTH;

SHA_LONG l, cNl,cNh;
cNl=0; cNh=0;
l=(cNl+(((SHA_LONG)size)<<3))&0xffffffffUL;
if (l < cNl) /* overflow */
{cNh ++;}
cNh += (size>>29);
ctx->Nl=l; ctx->Nh=cNh;
}
