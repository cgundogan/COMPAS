#include <stdint.h>
#include <string.h>

typedef struct __attribute__((packed)) {
    uint16_t name_len;        /**< length of the name in bytes */
} routing_nam_t;

void routing_nam_set_name(routing_nam_t *nam, const char *name,
                          uint16_t name_len);
