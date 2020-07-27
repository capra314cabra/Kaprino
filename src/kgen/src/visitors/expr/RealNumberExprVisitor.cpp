#include "kgen/KgenAccelerator.h"
#include "kgen/visitors/ExprObject.h"
#include "kgen/visitors/StatementVisitor.h"

namespace kaprino::kgen {

class RealNumberExprObject : public ExprObject {
   public:
    double value;

    virtual llvm::Value* codegen(llvm::IRBuilder<>* builder, llvm::Module* module) override {
        logger->move_pos(line, pos);

        auto doubleVal = llvm::ConstantFP::get(KAPRINO_DOUBLE_TY(module), value);
        return doubleVal;
    }
};

antlrcpp::Any StatementVisitor::visitRealNumberExpr(KaprinoParser::RealNumberExprContext* ctx) {
    auto exprObj = new RealNumberExprObject();

    exprObj->setContextPosition(ctx);
    exprObj->value = atof(ctx->real_number()->getText().c_str());

    return (ExprObject*)exprObj;
}

};  // namespace kaprino::kgen
