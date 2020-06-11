#ifndef MD5_H_
#define MD5_H_

#include <stdio.h>
#include <stdint.h>

/* Define the state of the MD5 Algorithm. */
typedef struct md5_state_s {
	uint32_t count[2];	/* message length in bits, lsw first */
	uint32_t abcd[4];		/* digest buffer */
	uint8_t buf[64];		/* accumulate block */
} md5_state_t;

void md5_init(md5_state_t *pms);
void md5_append(md5_state_t *pms, const uint8_t *data, int nbytes);
void md5_finish(md5_state_t *pms, uint8_t digest[16]);

void get_md5_hash(uint8_t * input, int input_length, uint8_t * md5hash);

#endif  // MD5_H_
