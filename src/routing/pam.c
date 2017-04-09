#include "routing/pam.h"

void routing_pam_set_prefix(routing_pam_t *pam, const char *prefix,
                            uint16_t prefix_len)
{
    pam->prefix_len = prefix_len;
    memcpy(pam + 1, prefix, prefix_len);
}
