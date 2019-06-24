//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03
// XFAIL: nvcc

// If we're just building the test and not executing it, it should pass.
// UNSUPPORTED: no_execute

// <cuda/std/initializer_list>

// template<class E> const E* begin(initializer_list<E> il);

#include <cuda/std/initializer_list>
#include <cuda/std/cassert>
#include <cuda/std/cstddef>

#include "test_macros.h"

struct A
{
    __host__ __device__
    A(cuda::std::initializer_list<int> il)
    {
        const int* b = begin(il);
        const int* e = end(il);
        assert(il.size() == 3);
        assert(static_cast<cuda::std::size_t>(e - b) == il.size());
        assert(*b++ == 3);
        assert(*b++ == 2);
        assert(*b++ == 1);
    }
};

#if TEST_STD_VER > 11
struct B
{
    __host__ __device__
    constexpr B(cuda::std::initializer_list<int> il)
    {
        const int* b = begin(il);
        const int* e = end(il);
        assert(il.size() == 3);
        assert(static_cast<cuda::std::size_t>(e - b) == il.size());
        assert(*b++ == 3);
        assert(*b++ == 2);
        assert(*b++ == 1);
    }
};

#endif  // TEST_STD_VER > 11

int main(int, char**)
{
    A test1 = {3, 2, 1};
#if TEST_STD_VER > 11
    constexpr B test2 = {3, 2, 1};
    (void)test2;
#endif  // TEST_STD_VER > 11

  return 0;
}