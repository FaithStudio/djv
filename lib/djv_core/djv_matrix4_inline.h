//------------------------------------------------------------------------------
// Copyright (c) 2004-2012 Darby Johnston
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions, and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions, and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the names of the copyright holders nor the names of any
//   contributors may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//------------------------------------------------------------------------------

//! \file djv_matrix4_inline.h

namespace djv
{

//------------------------------------------------------------------------------
// M<T, 4>
//------------------------------------------------------------------------------

template<typename T>
const int M<T, 4>::dimension = 4;
template<typename T>
const int M<T, 4>::dimension_x2 = 4 * 4;

template<typename T>
inline M<T, 4>::M()
{
    identity();
}

template<typename T>
inline M<T, 4>::M(const M<T, 4> & in)
{
    set(in);
}

template<typename T>
inline M<T, 4>::M(
    T _0,  T _1,  T _2,  T _3,
    T _4,  T _5,  T _6,  T _7,
    T _8,  T _9,  T _10, T _11,
    T _12, T _13, T _14, T _15)
{
    set(_0,  _1,  _2,  _3,
        _4,  _5,  _6,  _7,
        _8,  _9,  _10, _11,
        _12, _13, _14, _15);
}

template<typename T>
inline M<T, 4>::M(const T * in)
{
    set(in);
}

template<typename T>
inline M<T, 4> & M<T, 4>::operator = (const M<T, 4> & in)
{
    if (&in != this)
    {
        set(in);
    }

    return *this;
}

template<typename T>
inline void M<T, 4>::set(const M<T, 4> & in)
{
    for (int i = 0; i < dimension_x2; ++i)
    {
        e[i] = in.e[i];
    }
}

template<typename T>
inline void M<T, 4>::set(
    T _0,  T _1,  T _2,  T _3,
    T _4,  T _5,  T _6,  T _7,
    T _8,  T _9,  T _10, T _11,
    T _12, T _13, T _14, T _15)
{
    T * p = M<T, 4>::e;
    
    p[0 ] = _0;
    p[1 ] = _1;
    p[2 ] = _2;
    p[3 ] = _3;
    p[4 ] = _4;
    p[5 ] = _5;
    p[6 ] = _6;
    p[7 ] = _7;
    p[8 ] = _8;
    p[9 ] = _9;
    p[10] = _10;
    p[11] = _11;
    p[12] = _12;
    p[13] = _13;
    p[14] = _14;
    p[15] = _15;
}

template<typename T>
inline void M<T, 4>::set(const T * in)
{
    for (int i = 0; i < dimension_x2; ++i)
    {
        e[i] = in[i];
    }
}

template<typename T>
inline void M<T, 4>::identity()
{
    static const T zero = static_cast<T>(0.0);
    static const T one = static_cast<T>(1.0);

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            e[i * 4 + j] = (i == j) ? one : zero;
        }
}

template<typename T>
inline void M<T, 4>::zero()
{
    static const T zero = static_cast<T>(0.0);

    for (int i = 0; i < dimension_x2; ++i)
    {
        e[i] = zero;
    }
}

} // djv

