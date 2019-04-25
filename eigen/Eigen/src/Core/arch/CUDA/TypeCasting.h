// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2016 Benoit Steiner <benoit.steiner.goog@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_TYPE_CASTING_CUDA_H
#define EIGEN_TYPE_CASTING_CUDA_H

namespace Eigen {

namespace internal {

template<>
struct scalar_cast_op<float, Eigen::half> {
  EIGEN_EMPTY_STRUCT_CTOR(scalar_cast_op)
  typedef Eigen::half result_type;
  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE Eigen::half operator() (const float& a) const {
    #if defined(EIGEN_HAS_CUDA_FP16) && defined(__CUDA_ARCH__) && __CUDA_ARCH__ >= 300
      return __float2half(a);
    #else
      return Eigen::half(a);
    #endif
  }
};

template<>
struct functor_traits<scalar_cast_op<float, Eigen::half> >
{ enum { Cost = NumTraits<float>::AddCost, PacketAccess = false }; };


template<>
struct scalar_cast_op<int, Eigen::half> {
  EIGEN_EMPTY_STRUCT_CTOR(scalar_cast_op)
  typedef Eigen::half result_type;
  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE Eigen::half operator() (const int& a) const {
    #if defined(EIGEN_HAS_CUDA_FP16) && defined(__CUDA_ARCH__) && __CUDA_ARCH__ >= 300
      return __float2half(static_cast<float>(a));
    #else
      return Eigen::half(static_cast<float>(a));
    #endif
  }
};

template<>
struct functor_traits<scalar_cast_op<int, Eigen::half> >
{ enum { Cost = NumTraits<float>::AddCost, PacketAccess = false }; };


template<>
struct scalar_cast_op<Eigen::half, float> {
  EIGEN_EMPTY_STRUCT_CTOR(scalar_cast_op)
  typedef float result_type;
  EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE float operator() (const Eigen::half& a) const {
    #if defined(EIGEN_HAS_CUDA_FP16) && defined(__CUDA_ARCH__) && __CUDA_ARCH__ >= 300
      return __half2float(a);
    #else
      return static_cast<float>(a);
    #endif
  }
};

template<>
struct functor_traits<scalar_cast_op<Eigen::half, float> >
{ enum { Cost = NumTraits<float>::AddCost, PacketAccess = false }; };



} // end namespace internal

} // end namespace Eigen

#endif // EIGEN_TYPE_CASTING_CUDA_H
