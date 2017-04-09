#include "routing/nam.h"

void routing_nam_set_name(routing_nam_t *nam, const char *name,
                          uint16_t name_len)
{
    nam->name_len = name_len;
    memcpy(nam + 1, name, name_len);
}
