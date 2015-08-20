#include "divsufsortxx.h"

#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "bitmap_array.h"

#define ISPOWOF2(n)     ((n != 0) && ((n & (n - 1)) == 0))

uint32_t IntegerLog2(uint64_t n) {
  // TODO: Add support for hardware instruction
  uint32_t l = ISPOWOF2(n) ? 0 : 1;
  while (n >>= 1)
    ++l;
  return l;
}

typedef unsigned long long int TimeStamp;
static TimeStamp GetTimestamp() {
  struct timeval now;
  gettimeofday(&now, NULL);

  return now.tv_usec + (TimeStamp) now.tv_sec * 1000000;
}

// Write array to file
template<typename data_type, typename size_type>
void WriteToFile(data_type *data, size_type size, std::string& outfile) {
  std::ofstream out(outfile);
  out.write(reinterpret_cast<const char *>(data), size * sizeof(data_type));
  out.close();
}

// Read array from file
template<typename data_type, typename size_type>
void ReadFromFile(data_type *data, size_type size, std::string& infile) {
  std::ifstream in(infile);
  in.read(reinterpret_cast<char*>(data), size * sizeof(data_type));
  in.close();
}

size_t GetFileSize(std::string& filename) {
  std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
  return in.tellg();
}

int main(int argc, char** argv) {

//  if (argc < 2) {
//    fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
//    return -1;
//  }
//
//  // Get filename, filesize
//  std::string filename = std::string(argv[1]);
//  size_t filesize = GetFileSize(filename);
//
//  TimeStamp t0, t1;
//  t0 = GetTimestamp();
//
//  uint64_t input_size = filesize + 1;
//  char *data = new char[input_size]();
//  ReadFromFile(data, filesize, filename);
//
//  uint8_t bits = IntegerLog2(input_size + 1);
//
//  bitmap::SignedBitmapArray<int64_t> SA(input_size, bits);
//  divsufsortxx::constructSA(data, data + input_size, SA.begin(), SA.end(), 256);
//
//  t1 = GetTimestamp();
//  fprintf(stderr, "Time taken to construct SA = %llu\n",
//          (t1 - t0) / (1000 * 1000));

  for (uint8_t i = 0; i < 64; i++) {
    fprintf(stderr, "0x%016llXULL,\n", 0x8000000000000000ULL >> i);
  }

#ifdef TEST
  int64_t *SA_test = new int64_t[input_size];
  divsufsortxx::constructSA(data, data + input_size, SA_test,
                            SA_test + input_size, 256);

  for (uint64_t i = 0; i < input_size; i++) {
    assert(SA_test[i] == int64_t(SA[i]));
  }
#endif

  return 0;
}
