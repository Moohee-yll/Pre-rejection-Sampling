#ifndef PRINT_SPEED_H
#define PRINT_SPEED_H

#include <stddef.h>
#include <stdint.h>

void print_results(const char *s, uint64_t *t, size_t tlen);
void print_result_hybrid(const char *str_before, const char *str_later, uint64_t *t_before, uint64_t *t_later, size_t tlen);

#endif
