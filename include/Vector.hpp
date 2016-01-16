#ifndef SM_VECTOR_HPP_
#define SM_VECTOR_HPP_

#include "Hints.hpp"

namespace sm_utils
{

template <typename T>
inline void elementMult(T *a, T *b, T *out, size_t n)
{
  for (size_t i = 0; i < n; ++i)
    out[i] = a[i] * b[i];
}

template <typename T>
inline void elementSub(T *a, T *b, T *out, size_t n)
{
  for (size_t i = 0; i < n; ++i)
    out[i] = a[i] - b[i];
}

}

#define SM_VECTOR_HPP_