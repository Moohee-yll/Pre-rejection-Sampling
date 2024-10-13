#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "cpucycles.h"
#include "speed_print.h"

static int cmp_uint64(const void *a, const void *b) {
  if(*(uint64_t *)a < *(uint64_t *)b) return -1;
  if(*(uint64_t *)a > *(uint64_t *)b) return 1;
  return 0;
}

static uint64_t median(uint64_t *l, size_t llen) {
  qsort(l,llen,sizeof(uint64_t),cmp_uint64);

  if(llen%2) return l[llen/2];
  else return (l[llen/2-1]+l[llen/2])/2;
}

static uint64_t average(uint64_t *t, size_t tlen) {
  size_t i;
  uint64_t acc=0;

  for(i=0;i<tlen;i++)
    acc += t[i];

  return acc/tlen;
}

void print_results(const char *s, uint64_t *t, size_t tlen) {
  size_t i;
  static uint64_t overhead = -1;

  if(tlen < 2) {
    fprintf(stderr, "ERROR: Need a least two cycle counts!\n");
    return;
  }

  if(overhead  == (uint64_t)-1)
    overhead = cpucycles_overhead();

  tlen--;
  for(i=0;i<tlen;++i)
    t[i] = t[i+1] - t[i] - overhead;

  printf("%s\n", s);
  printf("median: %llu cycles/ticks\n", (unsigned long long)median(t, tlen));
  printf("average: %llu cycles/ticks\n", (unsigned long long)average(t, tlen));
  printf("\n");
}

void print_result_hybrid(const char *str_before, const char *str_later, uint64_t *t_before, uint64_t *t_later, size_t tlen){
  size_t i;
  static uint64_t overhead = -1;

  if(tlen < 2) {
    fprintf(stderr, "ERROR: Need a least two cycle counts!\n");
    return;
  }

  if(overhead  == (uint64_t)-1){
    // printf("overhead==(uint64)-1: %ld\n",overhead);
    overhead = cpucycles_overhead();
    // printf("overhead after cpucycles_overhead(): %ld\n",overhead);
  }

  tlen--;
  for(i=0;i<tlen;++i){
    t_before[i] = t_later[i] - t_before[i] - overhead;
    t_later[i] = t_before[i+1] - t_later[i] - overhead;
  }
    // t[i] = t[i+1] - t[i] - overhead;

  printf("%s\n", str_before);
  // printf("last overhead: %lu\n",overhead);
  printf("median: %llu cycles/ticks\n", (unsigned long long)median(t_before, tlen));
  printf("average: %llu cycles/ticks\n", (unsigned long long)average(t_before, tlen));
  printf("\n");

  printf("%s\n", str_later);
  // printf("last overhead: %lu\n",overhead);
  printf("median: %llu cycles/ticks\n", (unsigned long long)median(t_later, tlen));
  printf("average: %llu cycles/ticks\n", (unsigned long long)average(t_later, tlen));
  printf("\n");
}
