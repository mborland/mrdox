//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Official repository: https://github.com/cppalliance/mrdox
//

#include <mrdox/Support/Dom.hpp>

namespace clang {
namespace mrdox {
namespace dom {

Array::
Impl::
~Impl() = default;

Object::
Impl::
~Impl() = default;

bool
Object::
Impl::
empty() const noexcept
{
    // default to false
    return false;
}

Value::
~Value()
{
    switch(kind_)
    {
    case Kind::Object:
        object_.~Object();
        break;
    case Kind::Array:
        array_.~Array();
        break;
    case Kind::String:
        string_.~basic_string();
        break;

    case Kind::Integer:
    case Kind::Boolean:
    case Kind::Null:
        break;
    default:
        MRDOX_UNREACHABLE();
    }
}

Value::
Value() noexcept
    : kind_(Kind::Null)
{
}

Value::
Value(bool b) noexcept
    : kind_(Kind::Boolean)
    , number_(b)
{
}

Value::
Value(
    Array arr) noexcept
    : kind_(Kind::Array)
    , array_(std::move(arr))
{
}

Value::
Value(
    Object obj) noexcept
    : kind_(Kind::Object)
    , object_(std::move(obj))
{
}

Value::
Value(std::nullptr_t) noexcept
    : kind_(Kind::Null)
{
}

Value::
Value(char const* s) noexcept
    : kind_(Kind::String)
    , string_(s)
{
}

Value::
Value(
    std::string_view s) noexcept
    : kind_(Kind::String)
    , string_(s)
{
}

Value::
Value(
    std::string string) noexcept
    : kind_(Kind::String)
    , string_(std::move(string))
{
}

bool
Value::
isTruthy() const noexcept
{
    switch(kind_)
    {
    case Kind::Object: return object_.empty();
    case Kind::Array: return array_.length() > 0;
    case Kind::String: return string_.size() > 0;
    case Kind::Integer:
    case Kind::Boolean: return number_ != 0;
    case Kind::Null: return false;
    default: MRDOX_UNREACHABLE();
    }
}

//------------------------------------------------

} // dom
} // mrdox
} // clang