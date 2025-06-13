#include "option.h"

#include <memory.h>
#include <malloc.h>

option _opt_new(int8_t has_halue, uint16_t byte_len) {
    option opt;
    opt.has_value = has_halue;
    opt.byte_len = byte_len;
    opt.value = malloc(byte_len);
    return opt;
}

void _opt_set_value(option* opt, void* value) {
    memcpy(opt->value, value, opt->byte_len);
}
