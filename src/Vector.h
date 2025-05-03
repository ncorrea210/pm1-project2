// Vector.h

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>

template<typename T>
class Vector {
  public:

    Vector(std::initializer_list<T> data, size_t size) {
      m_size = size;
      m_storage = data;
    }

    explicit Vector(const Vector<T>& other) {
      m_storage = other.m_storage;
      m_size = other.getSize();
    }

    Vector& operator=(const Vector<T>& other) {

      if (this == &other) return *this;
      m_storage = other.m_storage;
      m_size = other.m_size;

      return *this;
    }

    Vector& operator=(std::initializer_list<T> data) {
      
      m_storage = data;
      m_size = data.size();

      return *this;
    }

    Vector(size_t size) {
      m_size = size;
      m_storage = std::vector<T>(size);
    }

    Vector() {
      m_size = 0;
      m_storage = std::vector<T>(0);
    }

    virtual ~Vector() {}

    int getSize() const {
      return m_size;
    }    

    T& operator[](size_t i) {
      //size check
      if (i >= this->getSize()) {
        throw std::runtime_error("Size mismatch");
      }
      return m_storage[i];
    }

    const T& operator[](size_t i) const {
      //size check
      if (i >= this->getSize()) {
        throw std::runtime_error("Size mismatch");
      }
      return m_storage[i];
    }

    Vector operator+(const Vector<T>& other) const {
      if (other.getSize() != this->getSize()) {
        throw std::runtime_error("Size mismatch");
      } 
      std::vector<T> temp;
      for (auto& i : temp) {
        i = m_storage[i] + other[i];
      }
      return Vector(temp);
    }

    Vector operator-(const Vector<T>& other) const {
      if (getSize() != other.getSize()) {
        throw std::runtime_error("Size mismatch");
      }
      std::vector<T> temp;
      for (auto& i : temp) {
        i = m_storage[i] - other[i];
      }
      return Vector(temp);
    }

    Vector operator*(T scalar) const {
      std::vector<T> temp; 
      for (int i = 0; i < getSize(); i++) {
        temp[i] = m_storage[i] * scalar;
      }
      return Vector(temp);
    }

    friend Vector operator*(T scalar, const Vector<T>& vec);
    
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vector);

    friend std::istream& operator>>(std::istream& is, Vector<T>& vector);
  private: 
  
    std::vector<T> m_storage;
    size_t m_size;

};

template<typename T>
Vector<T>& operator*(T scalar, const Vector<T>& vec) {
  std::vector<T> temp;
  for (int i = 0; i < vec.getSize(); i++) {
    temp[i] = scalar * vec[i];
  }
  return Vector(temp);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
  os << "(";
  for (int i = 0; i < vec.getSize(); i++) {
    os << vec[i] << (i == vec.getSize() - 1 ? "" : ", ");
  }
  os << ")";
  return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Vector<T>& vec) {
  for (int i = 0; i < vec.getsize(); i++) {
    is >> vec[i];
  }
  return is;
}

#endif // VECTOR_H

