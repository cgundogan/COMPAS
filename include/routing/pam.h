#include <stdint.h>
#include <string.h>

typedef struct __attribute__((packed)) {
    uint16_t prefix_len;        /**< length of the prefix in bytes */
} routing_pam_t;

void routing_pam_set_prefix(routing_pam_t *pam, const char *prefix,
                            uint16_t prefix_len);
