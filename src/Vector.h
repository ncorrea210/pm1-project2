// Vector.h

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <memory>

template<typename T>
class Vector {
  public:

    Vector(std::initializer_list<T> data) {
      m_count = data.size();
      m_data = new T[m_count];

      if (m_data == nullptr) {
        throw std::runtime_error("Failed to allocate for m_data");
      }

      for (int i = 0; i < m_count; i++) {
        m_data[i] = data[i];
      }
    }

    Vector(const Vector<T>& other) {

      m_count = other.m_count;
      m_data = new T[m_count];
      memcpy(m_data, other.m_data);

    }

    Vector& operator=(const Vector<T>& other) {
      return Vector(other);
    }

    ~Vector() {
      delete[] m_data;
    }

    int getsize() const {
      return m_count;
    }    

    virtual T& operator[](size_t i) const {
      if (i >= m_count) {
        throw std::runtime_error("Out of bounds error");
      }

      return m_data[i];
    }

    virtual Vector& operator+(const Vector<T>& other) const {
      if (m_count != other.m_count) {
        throw std::runtime_error("size mismatch in operator+ of vector");
      }

      std::array<T, m_count> temp;
      for (int i = 0; i < m_count; i++) {
        temp[i] = m_data[i] + other[i];
      }

      return Vector<T>(temp);
    }

    virtual Vector& operator-(const Vector<T>& other) const {
      if (m_count != other.m_count) {
        throw std::runtime_error("size mismatch in operator- of vector");
      }

      std::array<T, m_count> temp;
      for (int i = 0; i < m_count; i++) {
        temp[i] = m_data[i] + other[i];
      }

      return Vector<T>(temp);
    }



  private:
    
    T* m_data;
    size_t m_count;

};

#endif // VECTOR_H

