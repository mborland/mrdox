//
// This is a derivative work. originally part of the LLVM Project.
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Official repository: https://github.com/cppalliance/mrdox
//

#ifndef MRDOX_TOOL_AST_PARSEJAVADOC_HPP
#define MRDOX_TOOL_AST_PARSEJAVADOC_HPP

#include <mrdox/Platform.hpp>
#include <mrdox/Config.hpp>
#include <mrdox/Metadata/Javadoc.hpp>

namespace clang {

class Decl;
class ASTContext;
class RawComment;

namespace mrdox {

/** Initialize clang to recognize our custom comments.

    Safe to be called more than once, but
    not concurrently.
*/
void
initCustomCommentCommands(
    ASTContext& ctx);

/** Parse a javadoc.
*/
void
parseJavadoc(
    std::unique_ptr<Javadoc>& jd,
    RawComment* RC,
    Decl const* D,
    Config const& config);

} // mrdox
} // clang

#endif
