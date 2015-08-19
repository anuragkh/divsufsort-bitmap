#include "bitmap_array.h"

#include <cstdio>
#include <sys/time.h>

typedef unsigned long long int TimeStamp;
static TimeStamp GetTimestamp() {
  struct timeval now;
  gettimeofday(&now, NULL);

  return now.tv_usec + (TimeStamp) now.tv_sec * 1000000;
}

#define ARRAY_SIZE (1024*1024*1024)

int main(int argc, char** argv) {
  if (argc > 1) {
    fprintf(stderr, "%s does not take any arguments.\n", argv[0]);
  }

  TimeStamp t0, t1;

  bitmap::SignedBitmapArray<int64_t> array(ARRAY_SIZE, 30);

  t0 = GetTimestamp();
  for (size_t i = 0; i < array.size(); i++) {
    array[i] = rand() % array.size();
  }
  t1 = GetTimestamp();

  fprintf(stderr, "Time to fill Bitmap Array = %llu\n", (t1 - t0));

  int64_t sum = 0;
  t0 = GetTimestamp();
  for (size_t i = 0; i < array.size(); i++) {
    sum += array[rand() % array.size()];
  }
  t1 = GetTimestamp();

  fprintf(stderr, "Time to read Bitmap Array = %llu; sum=%lld\n", (t1 - t0), sum);

  int64_t *array1 = new int64_t[ARRAY_SIZE];
  t0 = GetTimestamp();
  for (size_t i = 0; i < array.size(); i++) {
    array1[i] = rand() % array.size();
  }
  t1 = GetTimestamp();

  fprintf(stderr, "Time to fill Array = %llu\n", (t1 - t0));

  sum = 0;
  t0 = GetTimestamp();
  for (size_t i = 0; i < array.size(); i++) {
    sum += array1[rand() % array.size()];
  }
  t1 = GetTimestamp();

  fprintf(stderr, "Time to read Array = %llu; sum=%lld\n", (t1 - t0), sum);
}
