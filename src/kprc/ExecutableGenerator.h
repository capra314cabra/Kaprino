#pragma once

#include "llvm/IR/Module.h"

std::string EmitLLVMIR(llvm::Module* module, bool optimize);

std::string EmitBitcode(llvm::Module* module, bool optimize);

std::string EmitExecutable(llvm::Module* module, bool optimize);
