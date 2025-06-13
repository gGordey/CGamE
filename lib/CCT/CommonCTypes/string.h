#ifndef _STRING_
#define _STRING_

// here when I say "string", I mean "string" struct. "cstr" is "const char*" (aka "null terminated string", aka "C-string") or just "char*"

#define PARSING_NOT_INT 245
// now isn't used, may be some where in the future

#include <stdint.h>

typedef struct string{
    uint64_t len;
    // len is how long "cstr" is. cstr[len] = 0
    char* cstr;
    // string content itself. (on heap, uses  "malloc")
} string;

string _str_from_cstr(const char* src);
// returns string with the same content as "src"

void _str_push(string* str, const char* src);
// pushes content from "src" to the end "str" 

void _str_push_char(string* dst, const char ch);

char* _str_reverse_cstr(const char* src);

string _str_merge(string* src1, string* src2);
// combines content from src1 and src2 to a new string

string _str_slice(string* src, uint64_t left, uint64_t right);
// returns slice of string, from "left" to "right" indexes as string

char* _str_slice_to_cstr(string* src, uint64_t left, uint64_t right);
// the same as one above but result is cstr

char* _str_cstr_slice_to_cstr(const char* src, uint64_t left, uint64_t right);
// this one takes slice of cstr and returns it as cstr

string _str_clone(string* src);
// returns clone of "src"

int8_t _str_is_alpha(string* str); // returns bool (int8_t (aka "char") because not all c standarts "bool" is a thing) - the same thing with other functions returning int8_t
// returns true (1) if all charecters in "str" are english letters (can be both uppercase and lower case), else => false

int8_t _str_is_numeric(string* str); // bool
// returns true if all charecters are numbers (0-9)

int32_t _str_parse_i32(string* src);
// returns number, from its ascii representation (type is signed 32 bit int)

int64_t _str_parse_i64(string* src);
// the same as the one above, but returns signed 64 bit int

void _str_free(string* str);
// frees "str->cstr"

uint64_t _str_size_cstr(const char* str);
// counts the length of "str"

int8_t _str_string_eql_string(string* s1, string* s2); // bool
// compares two strings

int8_t _str_string_eql_cstr(string* s1, const char* s2); // bool
// compares string and cstr

int8_t _str_cstr_eql_cstr(const char* s1, const char* s2); // bool
// compares two cstr

string _str_fstring(const char* format, ...);
// allowes you to make formated string (just like in C with printf - %s, %c, %d ...)

#endif//_STRING_