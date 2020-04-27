#include <iostream>
#include <fstream>

#include "antlr4-runtime.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Pass.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Support/InitLLVM.h"

#include "KaprinoAccelerator.h"
#include "../parser/KaprinoLexer.h"
#include "../parser/KaprinoParser.h"
#include "StatementVisitor.h"
#include "abstructs/StatementObject.h"
#include "ExecutableGenerator.h"

using namespace antlr4;

std::vector<StatementObject*>* ParseFile(std::string text);
void GenerateCode(std::vector<StatementObject*>* programObj, std::string fileName);

int main(int argc, const char* argv[]) {
    llvm::InitLLVM X(argc, argv);

    KAPRINO_LOG_INIT();

    KAPRINO_LOG("Kaprino started");

    if (argc <= 1) {
        KAPRINO_ERR("No input");
        throw -1;
    }

    std::string input_file_path = argv[1];
    std::ifstream input_file(input_file_path);

    if (!input_file.good()) {
        KAPRINO_ERR("Not found input files: \"" << argv[1] << "\"");
        throw -1;
    }

    std::ostringstream ss;
    ss << input_file.rdbuf();
    std::string input_text;
    input_text = ss.str();

    KAPRINO_LOG("Read input files succeeded \"" << argv[1] << "\"");

    auto programObject = ParseFile(input_text);

    KAPRINO_LOG("Parsing succeeded");

    std::string output_file_path = KAPRINO_RM_FILE_EXT(input_file_path) + ".ll";

    GenerateCode(programObject, output_file_path);
}

std::vector<StatementObject*>* ParseFile(std::string text) {
    ANTLRInputStream input(text);
    KaprinoLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    KaprinoParser parser(&tokens);

    auto program = parser.program();

    StatementVisitor visitor;
    auto programObject = visitor.visitProgram(program).as<std::vector<StatementObject*>*>();

    return programObject;
}

void GenerateCode(std::vector<StatementObject*>* programObj, std::string fileName) {
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder(context);
    llvm::Module* module;

    module = new llvm::Module(fileName, context);

    std::vector<llvm::Type*> mainFuncArgs;

    auto mainFuncType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(context),
        mainFuncArgs,
        false
    );

    auto mainFunc = llvm::Function::Create(
        mainFuncType,
        llvm::GlobalValue::ExternalLinkage,
        "main",
        module
    );
    mainFunc->setCallingConv(llvm::CallingConv::C);

    auto mainBlock = llvm::BasicBlock::Create(context, "entry", module->getFunction("main"));
    builder.SetInsertPoint(mainBlock);

    for(auto statement : *programObj) {
        statement->codegen(&builder, module);
    }

    builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0));

    llvm::verifyModule(*module);

#ifdef KAPRINO_EMIT_LLVM_IR_ONLY

    EmitLLVMIR(module, false);

#else

    EmitExecutable(module, false);

#endif
}