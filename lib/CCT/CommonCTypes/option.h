#ifndef _C_OPTION_
#define _C_OPTION_

#include <stdint.h>

typedef struct option {
    int8_t has_value; // bool
    // has_value telles is it "some" or "none"
    uint16_t byte_len;
    // byte_len is size of a value inside
    void* value;
    // value itself
} option;

option _opt_new(int8_t has_value, uint16_t byte_len);
// creates new "option" with arguments as proprties

void _opt_set_value(option* opt, void* value);
// sets "opt->value" to "value"

#endif//_C_OPTION