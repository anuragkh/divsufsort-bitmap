#ifndef BITMAP_BITMAP_H_
#define BITMAP_BITMAP_H_

#include <cstdint>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace bitmap {

#define GETBIT(n, i)    ((n >> (63UL - i)) & 1UL)
#define SETBIT(n, i)    n = (n | (1UL << (63UL - i)))
#define CLRBIT(n, i)  n = (n & ~(1UL << (63UL - i)))

#define BITS2BLOCKS(bits) \
    (((bits) % 64 == 0) ? ((bits) / 64) : (((bits) / 64) + 1))

#define GETBITVAL(data, i) GETBIT((data)[(i) / 64], (i) % 64)
#define SETBITVAL(data, i) SETBIT((data)[(i) / 64], (i) % 64)
#define CLRBITVAL(data, i) CLRBIT((data)[(i) / 64], (i) % 64)

const uint64_t all_set = -1ULL;

static const uint64_t high_bits_set[65] = { 0x0000000000000000ULL,
    0x8000000000000000ULL, 0xC000000000000000ULL, 0xE000000000000000ULL,
    0xF000000000000000ULL, 0xF800000000000000ULL, 0xFC00000000000000ULL,
    0xFE00000000000000ULL, 0xFF00000000000000ULL, 0xFF80000000000000ULL,
    0xFFC0000000000000ULL, 0xFFE0000000000000ULL, 0xFFF0000000000000ULL,
    0xFFF8000000000000ULL, 0xFFFC000000000000ULL, 0xFFFE000000000000ULL,
    0xFFFF000000000000ULL, 0xFFFF800000000000ULL, 0xFFFFC00000000000ULL,
    0xFFFFE00000000000ULL, 0xFFFFF00000000000ULL, 0xFFFFF80000000000ULL,
    0xFFFFFC0000000000ULL, 0xFFFFFE0000000000ULL, 0xFFFFFF0000000000ULL,
    0xFFFFFF8000000000ULL, 0xFFFFFFC000000000ULL, 0xFFFFFFE000000000ULL,
    0xFFFFFFF000000000ULL, 0xFFFFFFF800000000ULL, 0xFFFFFFFC00000000ULL,
    0xFFFFFFFE00000000ULL, 0xFFFFFFFF00000000ULL, 0xFFFFFFFF80000000ULL,
    0xFFFFFFFFC0000000ULL, 0xFFFFFFFFE0000000ULL, 0xFFFFFFFFF0000000ULL,
    0xFFFFFFFFF8000000ULL, 0xFFFFFFFFFC000000ULL, 0xFFFFFFFFFE000000ULL,
    0xFFFFFFFFFF000000ULL, 0xFFFFFFFFFF800000ULL, 0xFFFFFFFFFFC00000ULL,
    0xFFFFFFFFFFE00000ULL, 0xFFFFFFFFFFF00000ULL, 0xFFFFFFFFFFF80000ULL,
    0xFFFFFFFFFFFC0000ULL, 0xFFFFFFFFFFFE0000ULL, 0xFFFFFFFFFFFF0000ULL,
    0xFFFFFFFFFFFF8000ULL, 0xFFFFFFFFFFFFC000ULL, 0xFFFFFFFFFFFFE000ULL,
    0xFFFFFFFFFFFFF000ULL, 0xFFFFFFFFFFFFF800ULL, 0xFFFFFFFFFFFFFC00ULL,
    0xFFFFFFFFFFFFFE00ULL, 0xFFFFFFFFFFFFFF00ULL, 0xFFFFFFFFFFFFFF80ULL,
    0xFFFFFFFFFFFFFFC0ULL, 0xFFFFFFFFFFFFFFE0ULL, 0xFFFFFFFFFFFFFFF0ULL,
    0xFFFFFFFFFFFFFFF8ULL, 0xFFFFFFFFFFFFFFFCULL, 0xFFFFFFFFFFFFFFFEULL,
    0xFFFFFFFFFFFFFFFFULL };

static const uint64_t high_bits_unset[65] = { 0xFFFFFFFFFFFFFFFFULL,
    0x7FFFFFFFFFFFFFFFULL, 0x3FFFFFFFFFFFFFFFULL, 0x1FFFFFFFFFFFFFFFULL,
    0x0FFFFFFFFFFFFFFFULL, 0x07FFFFFFFFFFFFFFULL, 0x03FFFFFFFFFFFFFFULL,
    0x01FFFFFFFFFFFFFFULL, 0x00FFFFFFFFFFFFFFULL, 0x007FFFFFFFFFFFFFULL,
    0x003FFFFFFFFFFFFFULL, 0x001FFFFFFFFFFFFFULL, 0x000FFFFFFFFFFFFFULL,
    0x0007FFFFFFFFFFFFULL, 0x0003FFFFFFFFFFFFULL, 0x0001FFFFFFFFFFFFULL,
    0x0000FFFFFFFFFFFFULL, 0x00007FFFFFFFFFFFULL, 0x00003FFFFFFFFFFFULL,
    0x00001FFFFFFFFFFFULL, 0x00000FFFFFFFFFFFULL, 0x000007FFFFFFFFFFULL,
    0x000003FFFFFFFFFFULL, 0x000001FFFFFFFFFFULL, 0x000000FFFFFFFFFFULL,
    0x0000007FFFFFFFFFULL, 0x0000003FFFFFFFFFULL, 0x0000001FFFFFFFFFULL,
    0x0000000FFFFFFFFFULL, 0x00000007FFFFFFFFULL, 0x00000003FFFFFFFFULL,
    0x00000001FFFFFFFFULL, 0x00000000FFFFFFFFULL, 0x000000007FFFFFFFULL,
    0x000000003FFFFFFFULL, 0x000000001FFFFFFFULL, 0x000000000FFFFFFFULL,
    0x0000000007FFFFFFULL, 0x0000000003FFFFFFULL, 0x0000000001FFFFFFULL,
    0x0000000000FFFFFFULL, 0x00000000007FFFFFULL, 0x00000000003FFFFFULL,
    0x00000000001FFFFFULL, 0x00000000000FFFFFULL, 0x000000000007FFFFULL,
    0x000000000003FFFFULL, 0x000000000001FFFFULL, 0x000000000000FFFFULL,
    0x0000000000007FFFULL, 0x0000000000003FFFULL, 0x0000000000001FFFULL,
    0x0000000000000FFFULL, 0x00000000000007FFULL, 0x00000000000003FFULL,
    0x00000000000001FFULL, 0x00000000000000FFULL, 0x000000000000007FULL,
    0x000000000000003FULL, 0x000000000000001FULL, 0x000000000000000FULL,
    0x0000000000000007ULL, 0x0000000000000003ULL, 0x0000000000000001ULL,
    0x0000000000000000ULL };

static const uint64_t low_bits_set[65] = { 0x0000000000000000ULL,
    0x0000000000000001ULL, 0x0000000000000003ULL, 0x0000000000000007ULL,
    0x000000000000000FULL, 0x000000000000001FULL, 0x000000000000003FULL,
    0x000000000000007FULL, 0x00000000000000FFULL, 0x00000000000001FFULL,
    0x00000000000003FFULL, 0x00000000000007FFULL, 0x0000000000000FFFULL,
    0x0000000000001FFFULL, 0x0000000000003FFFULL, 0x0000000000007FFFULL,
    0x000000000000FFFFULL, 0x000000000001FFFFULL, 0x000000000003FFFFULL,
    0x000000000007FFFFULL, 0x00000000000FFFFFULL, 0x00000000001FFFFFULL,
    0x00000000003FFFFFULL, 0x00000000007FFFFFULL, 0x0000000000FFFFFFULL,
    0x0000000001FFFFFFULL, 0x0000000003FFFFFFULL, 0x0000000007FFFFFFULL,
    0x000000000FFFFFFFULL, 0x000000001FFFFFFFULL, 0x000000003FFFFFFFULL,
    0x000000007FFFFFFFULL, 0x00000000FFFFFFFFULL, 0x00000001FFFFFFFFULL,
    0x00000003FFFFFFFFULL, 0x00000007FFFFFFFFULL, 0x0000000FFFFFFFFFULL,
    0x0000001FFFFFFFFFULL, 0x0000003FFFFFFFFFULL, 0x0000007FFFFFFFFFULL,
    0x000000FFFFFFFFFFULL, 0x000001FFFFFFFFFFULL, 0x000003FFFFFFFFFFULL,
    0x000007FFFFFFFFFFULL, 0x00000FFFFFFFFFFFULL, 0x00001FFFFFFFFFFFULL,
    0x00003FFFFFFFFFFFULL, 0x00007FFFFFFFFFFFULL, 0x0000FFFFFFFFFFFFULL,
    0x0001FFFFFFFFFFFFULL, 0x0003FFFFFFFFFFFFULL, 0x0007FFFFFFFFFFFFULL,
    0x000FFFFFFFFFFFFFULL, 0x001FFFFFFFFFFFFFULL, 0x003FFFFFFFFFFFFFULL,
    0x007FFFFFFFFFFFFFULL, 0x00FFFFFFFFFFFFFFULL, 0x01FFFFFFFFFFFFFFULL,
    0x03FFFFFFFFFFFFFFULL, 0x07FFFFFFFFFFFFFFULL, 0x0FFFFFFFFFFFFFFFULL,
    0x1FFFFFFFFFFFFFFFULL, 0x3FFFFFFFFFFFFFFFULL, 0x7FFFFFFFFFFFFFFFULL,
    0xFFFFFFFFFFFFFFFFULL };

class Bitmap {
 public:
  // Type definitions
  typedef size_t pos_type;
  typedef size_t size_type;
  typedef uint64_t data_type;
  typedef uint8_t width_type;

  // Constructors and Destructors
  Bitmap();
  Bitmap(size_type num_bits);
  virtual ~Bitmap();

  // Getters
  inline data_type* GetData();
  inline size_type GetSizeInBits();

  // Bit operations
  inline void Clear();
  inline void SetBit(pos_type i);
  inline void UnsetBit(pos_type i);
  inline bool GetBit(pos_type i) const;

  // Integer operations
  inline void SetValPos(pos_type pos, data_type val, width_type bits);
  inline data_type GetValPos(pos_type pos, width_type bits) const;

  // Serialization/De-serialization
  virtual size_type Serialize(std::ostream& out);
  virtual size_type Deserialize(std::istream& in);

 protected:
  // Data members
  data_type *data_;
  size_type size_;
};

Bitmap::Bitmap() {
  data_ = NULL;
  size_ = 0;
}

Bitmap::Bitmap(size_type num_bits) {
  assert(num_bits > 0);
  data_ = new data_type[BITS2BLOCKS(num_bits)]();
  size_ = num_bits;
}

Bitmap::~Bitmap() {
  if (data_ != NULL) {
    delete[] data_;
    data_ = NULL;
  }
}

Bitmap::data_type* Bitmap::GetData() {
  return data_;
}

Bitmap::size_type Bitmap::GetSizeInBits() {
  return size_;
}

void Bitmap::Clear() {
  memset((void *) data_, 0, BITS2BLOCKS(size_) * sizeof(uint64_t));
}

void Bitmap::SetBit(pos_type i) {
  SETBITVAL(data_, i);
}

void Bitmap::UnsetBit(pos_type i) {
  CLRBITVAL(data_, i);
}

bool Bitmap::GetBit(pos_type i) const {
  return GETBITVAL(data_, i);
}

void PrintBits(uint64_t n) {
  for (uint8_t i = 0; i < 64; i++) {
    fprintf(stderr, "%llu", GETBIT(n, i));
  }
  fprintf(stderr, "\n");
}

void Bitmap::SetValPos(pos_type pos, data_type val, width_type bits) {
  pos_type s = pos, e = pos + (bits - 1);
  if (s % 64 + bits <= 64) {
    data_[s / 64] = (data_[s / 64]
        & (high_bits_set[s % 64] | high_bits_unset[s % 64 + bits]))
        | (val << (63 - e % 64));
  } else {
    data_[s / 64] = (data_[s / 64] & high_bits_set[s % 64])
        | (val >> (e % 64 + 1));
    data_[e / 64] = (data_[e / 64] & high_bits_unset[e % 64 + 1])
        | (val << (63 - e % 64));
  }
}

Bitmap::data_type Bitmap::GetValPos(pos_type pos, width_type bits) const {
  if (bits == 0)
    return 0;

  assert(pos < size_);

  uint64_t val;
  uint64_t s = pos, e = pos + (bits - 1);
  uint64_t s_off = s & 0x3F, e_off = e & 0x3F;
  uint64_t s_idx = s >> 6, e_idx = e >> 6;
  if (s_off + bits <= 64) {
    val = (data_[s_idx] >> (63 - e_off)) & low_bits_set[bits];
  } else {
    uint64_t val1 = (data_[s_idx] << (e_off + 1)) & low_bits_set[bits];
    uint64_t val2 = data_[e_idx] >> (63 - e_off);
    val = val1 | val2;
  }

  return val;
}

Bitmap::size_type Bitmap::Serialize(std::ostream& out) {
  size_t out_size = 0;

  out.write(reinterpret_cast<const char *>(&size_), sizeof(uint64_t));
  out_size += sizeof(uint64_t);

  for (uint64_t i = 0; i < BITS2BLOCKS(size_); i++) {
    out.write(reinterpret_cast<const char *>(&data_[i]), sizeof(uint64_t));
    out_size += sizeof(uint64_t);
  }

  return out_size;
}

Bitmap::size_type Bitmap::Deserialize(std::istream& in) {
  size_t in_size = 0;

  in.read(reinterpret_cast<char *>(&size_), sizeof(uint64_t));
  in_size += sizeof(uint64_t);

  data_ = new uint64_t[BITS2BLOCKS(size_)];
  for (uint64_t i = 0; i < BITS2BLOCKS(size_); i++) {
    in.read(reinterpret_cast<char *>(&data_[i]), sizeof(uint64_t));
    in_size += sizeof(uint64_t);
  }

  return in_size;
}

}

#endif
