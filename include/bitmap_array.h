#ifndef BITMAP_BITMAP_ARRAY_H_
#define BITMAP_BITMAP_ARRAY_H_

#include "bitmap.h"

#include <limits>

namespace bitmap {
template<typename T>
class BitmapArray : public Bitmap {
 public:
  class value_reference;
  class iterator;

  // Type definitions
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef value_reference reference;
  typedef std::random_access_iterator_tag iterator_category;

  // Reference to a value
  class value_reference {
   public:
    typedef typename BitmapArray<T>::pos_type pos_type;

    typedef typename BitmapArray<T>::difference_type difference_type;
    typedef typename BitmapArray<T>::value_type value_type;
    typedef typename BitmapArray<T>::pointer pointer;
    typedef typename BitmapArray<T>::value_reference reference;
    typedef typename BitmapArray<T>::iterator_category iterator_category;

    value_reference(BitmapArray<T>* array, pos_type pos) {
      array_ = array;
      pos_ = pos;
    }

    value_reference& operator=(T val) {
      array_->Set(pos_, val);
      return *this;
    }

    value_reference& operator=(const value_reference& ref) {
      return (*this) = T(ref);
    }

    operator T() const {
      return array_->Get(pos_);
    }

    value_reference& operator++() {
      T val = array_->Get(pos_);
      array_->Set(pos_, val + 1);
      return *this;
    }

    T operator++(int) {
      T val = (T) *this;
      ++(*this);
      return val;
    }

    value_reference& operator--() {
      T val = array_->Get(pos_);
      array_->Set(pos_, val - 1);
      return *this;
    }

    T operator--(int) {
      T val = (T) *this;
      --(*this);
      return val;
    }

    value_reference& operator+=(const T x) {
      T val = array_->Get(pos_);
      array_->Set(pos_, val + 1);
      return *this;
    }

    value_reference& operator-=(const T x) {
      T val = array_->Get(pos_);
      array_->Set(pos_, val - 1);
      return *this;
    }

    bool operator==(const value_reference& x) const {
      return T(*this) == T(x);
    }

    bool operator<(const value_reference& x) const {
      return T(*this) < T(x);
    }

    friend void swap(reference& lhs, reference& rhs) {
      T temp = T(lhs);
      lhs = rhs;
      rhs = temp;
    }

    friend void swap(reference lhs, reference& rhs) {
      T temp = T(lhs);
      lhs = rhs;
      rhs = temp;
    }

    friend void swap(reference& lhs, reference rhs) {
      T temp = T(lhs);
      lhs = rhs;
      rhs = temp;
    }

    friend void swap(reference lhs, reference rhs) {
      T temp = T(lhs);
      lhs = rhs;
      rhs = temp;
    }

    friend void swap(reference lhs, T rhs) {
      T temp = T(lhs);
      lhs = rhs;
      rhs = temp;
    }

    friend void swap(T lhs, reference rhs) {
      T temp = T(rhs);
      rhs = lhs;
      lhs = temp;
    }

   private:
    BitmapArray<T> *array_;
    pos_type pos_;
  };

  // Iterators
  class iterator {
   public:
    typedef typename BitmapArray<T>::pos_type pos_type;

    typedef typename BitmapArray<T>::difference_type difference_type;
    typedef typename BitmapArray<T>::value_type value_type;
    typedef typename BitmapArray<T>::pointer pointer;
    typedef typename BitmapArray<T>::value_reference reference;
    typedef typename BitmapArray<T>::iterator_category iterator_category;

    iterator() {
      array_ = NULL;
      pos_ = 0;
    }

    iterator(BitmapArray<T>* array, pos_type pos) {
      array_ = array;
      pos_ = pos;
    }

    reference operator*() const {
      return reference(array_, pos_);
    }

    iterator& operator++() {
      pos_++;
      return *this;
    }

    iterator operator++(int) {
      iterator it = *this;
      ++(*this);
      return it;
    }

    iterator& operator--() {
      pos_--;
      return *this;
    }

    iterator operator--(int) {
      iterator it = *this;
      --(*this);
      return it;
    }

    iterator& operator+=(difference_type i) {
      pos_ += i;
      return *this;
    }

    iterator& operator-=(difference_type i) {
      pos_ -= i;
      return *this;
    }

    iterator& operator=(const iterator& it) {
      if (this != &it) {
        array_ = it.array_;
        pos_ = it.pos_;
      }
      return *this;
    }

    iterator operator+(difference_type i) const {
      iterator it = *this;
      return it += i;
    }

    iterator operator-(difference_type i) const {
      iterator it = *this;
      return it -= i;
    }

    reference operator[](difference_type i) const {
      return *(*this + i);
    }

    bool operator==(const iterator& it) const {
      return it.pos_ == pos_;
    }

    bool operator!=(const iterator& it) const {
      return !(*this == it);
    }

    bool operator<(const iterator& it) const {
      return pos_ < it.pos_;
    }

    bool operator>(const iterator& it) const {
      return pos_ > it.pos_;
    }

    bool operator>=(const iterator& it) const {
      return !(*this < it);
    }

    bool operator<=(const iterator& it) const {
      return !(*this > it);
    }

    difference_type operator-(const iterator& it) {
      return pos_ - it.pos_;
    }

   private:
    BitmapArray<T> *array_;
    pos_type pos_;
  };

  class const_iterator {
   public:
    typedef typename BitmapArray<T>::pos_type pos_type;

    typedef typename BitmapArray<T>::difference_type difference_type;
    typedef typename BitmapArray<T>::value_type value_type;
    typedef typename BitmapArray<T>::pointer pointer;
    typedef typename BitmapArray<T>::value_reference reference;
    typedef typename BitmapArray<T>::iterator_category iterator_category;

    typedef typename BitmapArray<T>::value_type const_reference;

    const_iterator(const BitmapArray<T>* array, pos_type pos) {
      array_ = array;
      pos_ = pos;
    }

    const_reference operator*() const {
      return array_->Get(pos_);
    }

    const_iterator& operator++() {
      pos_++;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator it = *this;
      ++(*this);
      return it;
    }

    const_iterator& operator--() {
      pos_--;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator it = *this;
      --(*this);
      return it;
    }

    const_iterator& operator+=(difference_type i) {
      pos_ += i;
      return *this;
    }

    const_iterator& operator-=(difference_type i) {
      pos_ -= i;
      return *this;
    }

    const_iterator operator+(difference_type i) const {
      const_iterator it = *this;
      return it += i;
    }

    const_iterator operator-(difference_type i) const {
      const_iterator it = *this;
      return it -= i;
    }

    const_reference operator[](difference_type i) const {
      return *(*this + i);
    }

    bool operator==(const const_iterator& it) const {
      return it.pos_ == pos_;
    }

    bool operator!=(const const_iterator& it) const {
      return !(*this == it);
    }

    bool operator<(const const_iterator& it) const {
      return pos_ < it.pos_;
    }

    bool operator>(const const_iterator& it) const {
      return pos_ > it.pos_;
    }

    bool operator>=(const const_iterator& it) const {
      return !(*this < it);
    }

    bool operator<=(const const_iterator& it) const {
      return !(*this > it);
    }

    difference_type operator-(const const_iterator& it) {
      return pos_ - it.pos_;
    }

   private:
    const BitmapArray<T>* array_;
    pos_type pos_;
  };

  // Constructors and destructors
  BitmapArray()
      : Bitmap() {
    num_elements_ = 0;
    bit_width_ = 0;
  }

  BitmapArray(const BitmapArray& array) {
    data_ = array.data_;
    size_ = array.size_;
    num_elements_ = array.num_elements_;
    bit_width_ = array.bit_width_;
  }

  BitmapArray(size_type num_elements, width_type bit_width)
      : Bitmap(num_elements * bit_width) {
    num_elements_ = num_elements;
    bit_width_ = bit_width;
  }

  BitmapArray(T *elements, size_type num_elements, width_type bit_width)
      : Bitmap(num_elements * bit_width) {
    num_elements_ = num_elements;
    bit_width_ = bit_width;

    for (uint64_t i = 0; i < num_elements_; i++) {
      Set(i, elements[i]);
    }
  }

  virtual ~BitmapArray() {
  }

  // Getters
  inline size_type GetNumElements() {
    return num_elements_;
  }
  inline width_type GetBitWidth() {
    return bit_width_;
  }

  // Accessors and mutators
  virtual inline void Set(pos_type i, T value) = 0;
  virtual inline T Get(pos_type i) const = 0;

  // Operators, iterators
  inline const T operator[](const pos_type& i) const {
    return Get(i);
  }

  inline value_reference operator[](const pos_type& i) {
    return value_reference(this, i);
  }

  inline iterator begin() {
    return iterator(this, 0);
  }

  inline const_iterator begin() const {
    return const_iterator(this, 0);
  }

  inline const_iterator cbegin() const {
    return const_iterator(this, 0);
  }

  inline iterator end() {
    return iterator(this, num_elements_);
  }

  inline const_iterator end() const {
    return iterator(this, num_elements_);
  }

  inline const_iterator cend() const {
    return iterator(this, num_elements_);
  }

  inline size_type size() {
    return num_elements_;
  }

  inline size_type max_size() {
    return num_elements_;
  }

  inline bool empty() {
    return num_elements_ == 0;
  }

  // Serialization and De-serialization
  virtual size_type Serialize(std::ostream& out) = 0;
  virtual size_type Deserialize(std::istream& in) = 0;

 protected:
  // Data members
  size_type num_elements_;
  width_type bit_width_;
};

template<typename T>
class UnsignedBitmapArray : public BitmapArray<T> {
 public:
  static_assert(!std::numeric_limits<T>::is_signed,
      "Signed types cannot be used with UnsignedBitmapArray.");

  typedef typename BitmapArray<T>::size_type size_type;
  typedef typename BitmapArray<T>::width_type width_type;
  typedef typename BitmapArray<T>::pos_type pos_type;

  typedef typename BitmapArray<T>::difference_type difference_type;
  typedef typename BitmapArray<T>::value_type value_type;
  typedef typename BitmapArray<T>::pointer pointer;
  typedef typename BitmapArray<T>::value_reference reference;
  typedef typename BitmapArray<T>::iterator_category iterator_category;

  using BitmapArray<T>::Set;
  using BitmapArray<T>::Get;
  using BitmapArray<T>::Serialize;
  using BitmapArray<T>::Deserialize;

  UnsignedBitmapArray()
      : BitmapArray<T>() {
  }

  UnsignedBitmapArray(size_type num_elements, width_type bit_width)
      : BitmapArray<T>(num_elements, bit_width) {
  }

  UnsignedBitmapArray(T *elements, size_type num_elements, width_type bit_width)
      : BitmapArray<T>(elements, num_elements, bit_width) {
  }

  virtual ~UnsignedBitmapArray() {
  }

  // Accessors and mutators
  virtual inline void Set(pos_type i, T value) override;
  virtual inline T Get(pos_type i) const override;

  inline void swap(const UnsignedBitmapArray<T>& other) {
    std::swap(this->data_, other.data_);
    std::swap(this->size_, other.size_);
    std::swap(this->num_elements_, other.num_elements_);
    std::swap(this->bit_width_, other.bit_width_);
  }

  // Serialization and De-serialization
  virtual size_type Serialize(std::ostream& out) override;
  virtual size_type Deserialize(std::istream& in) override;
};

template<typename T>
void UnsignedBitmapArray<T>::Set(pos_type i, T value) {
  this->SetValPos(i * this->bit_width_, value, this->bit_width_);
}

template<typename T>
T UnsignedBitmapArray<T>::Get(pos_type i) const {
  assert(i < this->num_elements_);
  Bitmap::data_type val = this->GetValPos(i * this->bit_width_,
                                          this->bit_width_);
  return (T) val;
}

template<typename T>
typename UnsignedBitmapArray<T>::size_type UnsignedBitmapArray<T>::Serialize(
    std::ostream& out) {
  size_t out_size = 0;

  out.write(reinterpret_cast<const char *>(&this->num_elements_),
            sizeof(size_type));
  out_size += sizeof(size_type);

  out.write(reinterpret_cast<const char *>(&this->bit_width_),
            sizeof(width_type));
  out_size += sizeof(width_type);

  out_size += Bitmap::Serialize(out);

  return out_size;
}

template<typename T>
typename UnsignedBitmapArray<T>::size_type UnsignedBitmapArray<T>::Deserialize(
    std::istream& in) {
  size_t in_size = 0;

  in.read(reinterpret_cast<char *>(&this->num_elements_), sizeof(size_type));
  in_size += sizeof(uint64_t);

  in.read(reinterpret_cast<char *>(&this->bit_width_), sizeof(width_type));
  in_size += sizeof(uint8_t);

  in_size += Bitmap::Deserialize(in);

  return in_size;
}

template<typename T>
class SignedBitmapArray : public BitmapArray<T> {
 public:
  static_assert(std::numeric_limits<T>::is_signed,
      "Unsigned types should not be used with SignedBitmapArray.");

  typedef typename BitmapArray<T>::size_type size_type;
  typedef typename BitmapArray<T>::width_type width_type;
  typedef typename BitmapArray<T>::pos_type pos_type;

  typedef typename BitmapArray<T>::difference_type difference_type;
  typedef typename BitmapArray<T>::value_type value_type;
  typedef typename BitmapArray<T>::pointer pointer;
  typedef typename BitmapArray<T>::value_reference reference;
  typedef typename BitmapArray<T>::iterator_category iterator_category;

  using BitmapArray<T>::Set;
  using BitmapArray<T>::Get;
  using BitmapArray<T>::Serialize;
  using BitmapArray<T>::Deserialize;

  SignedBitmapArray()
      : BitmapArray<T>() {
    signs_ = NULL;
  }

  SignedBitmapArray(size_type num_elements, width_type bit_width)
      : BitmapArray<T>(num_elements, bit_width) {
    signs_ = new Bitmap(this->num_elements_);
  }

  SignedBitmapArray(T *elements, size_type num_elements, width_type bit_width)
      : BitmapArray<T>(num_elements, bit_width) {
    signs_ = new Bitmap(this->num_elements_);
    for (uint64_t i = 0; i < this->num_elements_; i++) {
      Set(i, elements[i]);
    }
  }

  virtual ~SignedBitmapArray() {
    delete signs_;
  }

  // Accessors and mutators
  virtual inline void Set(pos_type i, T value) override;
  virtual inline T Get(pos_type i) const override;

  // Serialization and De-serialization
  virtual size_type Serialize(std::ostream& out) override;
  virtual size_type Deserialize(std::istream& in) override;

  inline void swap(const SignedBitmapArray<T>& other) {
    std::swap(this->data_, other.data_);
    std::swap(this->size_, other.size_);
    std::swap(this->num_elements_, other.num_elements_);
    std::swap(this->bit_width_, other.bit_width_);
    std::swap(this->signs_, other.signs_);
  }

 private:
  Bitmap *signs_;
};

template<typename T>
void SignedBitmapArray<T>::Set(pos_type i, T value) {
  if (value < 0) {
    signs_->SetBit(i);
    value = -value;
  } else {
    signs_->UnsetBit(i);
  }
  this->SetValPos(i * this->bit_width_, value, this->bit_width_);
}

template<typename T>
T SignedBitmapArray<T>::Get(pos_type i) const {
  T value = (T) this->GetValPos(i * this->bit_width_, this->bit_width_);
  bool negate = signs_->GetBit(i);
  return (value ^ -negate) + negate;
}

template<typename T>
typename SignedBitmapArray<T>::size_type SignedBitmapArray<T>::Serialize(
    std::ostream& out) {
  size_t out_size = 0;

  out.write(reinterpret_cast<const char *>(&this->num_elements_),
            sizeof(size_type));
  out_size += sizeof(size_type);

  out.write(reinterpret_cast<const char *>(&this->bit_width_),
            sizeof(width_type));
  out_size += sizeof(width_type);

  out_size += signs_->Serialize(out);

  out_size += Bitmap::Serialize(out);

  return out_size;
}

template<typename T>
typename SignedBitmapArray<T>::size_type SignedBitmapArray<T>::Deserialize(
    std::istream& in) {
  size_t in_size = 0;

  in.read(reinterpret_cast<char *>(&this->num_elements_), sizeof(size_type));
  in_size += sizeof(uint64_t);

  in.read(reinterpret_cast<char *>(&this->bit_width_), sizeof(width_type));
  in_size += sizeof(uint8_t);

  in_size += signs_->Deserialize(in);

  in_size += Bitmap::Deserialize(in);

  return in_size;
}

}

#endif
