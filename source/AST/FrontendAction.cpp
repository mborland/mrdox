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

#include "ASTVisitor.hpp"
#include "FrontendAction.hpp"
#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/CompilerInstance.h>

namespace clang {
namespace mrdox {

namespace {

struct Action
    : public clang::ASTFrontendAction
{
    Action(
        tooling::ExecutionContext& exc,
        ConfigImpl const& config) noexcept
        : ex_(exc)
        , config_(config)
    {
    }

    bool
    PrepareToExecuteAction(
        CompilerInstance& Compiler) override
    {
        FrontendOptions& fe_opts =
            Compiler.getFrontendOpts();
        fe_opts.SkipFunctionBodies = true;
        return true;
    }

    std::unique_ptr<clang::ASTConsumer>
    CreateASTConsumer(
        clang::CompilerInstance& Compiler,
        llvm::StringRef InFile) override
    {
        return std::make_unique<ASTVisitor>(
            ex_, config_, Compiler);
    }

private:
    tooling::ExecutionContext& ex_;
    ConfigImpl const& config_;
};

//------------------------------------------------

struct Factory : tooling::FrontendActionFactory
{
    Factory(
        tooling::ExecutionContext& exc,
        ConfigImpl const& config) noexcept
        : ex_(exc)
        , config_(config)
    {
    }

    std::unique_ptr<FrontendAction>
    create() override
    {
        return std::make_unique<Action>(ex_, config_);
    }

private:
    tooling::ExecutionContext& ex_;
    ConfigImpl const& config_;
};

} // (anon)

//------------------------------------------------

std::unique_ptr<tooling::FrontendActionFactory>
makeFrontendActionFactory(
    tooling::ExecutionContext& exc,
    ConfigImpl const& config)
{
    return std::make_unique<Factory>(exc, config);
}

} // mrdox
} // clang
