//------------------------------------------------------------------------------
//// Program: Create intra-procedure control flow graph based on LLVM Basic Block
//// Author: Xiang Gao (gaoxiang9430@gmail.com)
//// Time: 18, Feb, 2019
//------------------------------------------------------------------------------

#include "ControlFlowAnalyzer.h"
#include "llvm/IR/CallSite.h"

using namespace llvm;

ControlFlowAnalyzer::ControlFlowAnalyzer(std::string sourceFuncName, int sourceLineNo,
                                            std::string targetFuncName, int targetLineNo): FunctionPass(ID){
        this->sourceFuncName = sourceFuncName;
        this->targetFuncName = targetFuncName;
        this->sourceLineNo = sourceLineNo;
        this->targetLineNo = targetLineNo;
}

bool ControlFlowAnalyzer::runOnFunction(Function &function) {

    outs()<< "Function name: " << function.getName() << "\n";
    InterProceduralBasicBlock* sourceBB = getIRInstruction(function, sourceFuncName, sourceLineNo);
    if (sourceBB){
        const BasicBlock* curBB = sourceBB->getBasicBlock();
        outs() << "Source BasicBlock: " << curBB->getName() << " Block index: " << sourceBB->getCurIndex() << "\n";

        InterProceduralBasicBlock* targetBB = getIRInstruction(function, targetFuncName, targetLineNo);
        if (targetBB){
            const BasicBlock* curBB = targetBB->getBasicBlock();
            outs() << "Target BasicBlock: " << curBB->getName() << " Block index: " << targetBB->getCurIndex() << "\n";
        }
        if (sourceBB->getBasicBlock() == targetBB->getBasicBlock()){
            outs() << "The source and target belongs to same basic block.\n";
        }
        else
            exploreControlFlow(sourceBB, targetBB);
    }
  /*
  auto *callInst = dyn_cast<CallInst>(sourceInst);
  if (callInst)
    outs() << "instruction type is call\n";
  outs() << "Function name: " << F.getName() << "\n";
  BasicBlock *BB = &F.getEntryBlock();
  outs() << "basic block: " << BB->getName() << "\n";

  ControlFlowAnalyzer::getCallee(BB);

  const TerminatorInst *TInst = BB->getTerminator();
  for (unsigned I = 0, NSucc = TInst->getNumSuccessors(); I < NSucc; ++I) {
    BasicBlock *succ = TInst->getSuccessor(I);
    outs() << "edge from " << BB->getName() << " to " << succ->getName() << "\n";
    CallInst * callInst =  succ->getTerminatingMustTailCall ();
    outs() << "call site: " << callInst->getName();
  }*/
    return true;
}

void ControlFlowAnalyzer::exploreControlFlow(InterProceduralBasicBlock* sourceBB, InterProceduralBasicBlock* targetBB){

    while (const CallInst* callInst = getNextCall(sourceBB)){
        auto* calledFunc = dyn_cast<const Function>(callInst->getCalledValue()->stripPointerCasts());
        if(!calledFunc) {
            errs() << "Non-defined Function Call \n";
        }
        else{
            outs() << "=== callee: " << calledFunc->getName() << "\n";
            if (calledFunc->getBasicBlockList().size()!=0){
                const BasicBlock &newEntryBB = calledFunc->getEntryBlock();
                outs() << "new entry basic block is " << newEntryBB.getName() << "\n";
            }
        }
    }

//    const BasicBlock* curBB = sourceBB->getBasicBlock();
//    const TerminatorInst *tInst = curBB->getTerminator();
//    if (!tInst)
//        errs() << "there is no terminator instruction\n";
//    for (unsigned i = 0, nSucc = tInst->getNumSuccessors(); i < nSucc; ++i) {
//        BasicBlock * succ = tInst->getSuccessor(i);
//        outs() << "edge from " << curBB->getName() << " to " << succ->getName() << "\n";
//    }

}

const CallInst* ControlFlowAnalyzer::getNextCall(InterProceduralBasicBlock* sourceBB){
    int index = -1;
    const BasicBlock* curBB = sourceBB->getBasicBlock();
    for (const Instruction &inst : curBB->getInstList()) {
        index++;
        if (index <= sourceBB->getCurIndex())
            continue;
        const Instruction *tempInst = &inst;
        auto callInst = dyn_cast<CallInst>(tempInst);
        if (callInst){
            outs() << "instruction type is call\n";
            sourceBB->setCurIndex(index);
            return callInst;
        }
    }
    sourceBB->setCurIndex(index);
    return nullptr;
}

Function * ControlFlowAnalyzer::getCallee(BasicBlock *bb){
//    for (BasicBlock::iterator jt=bb->begin(), jend=bb->end();jt!=jend;++jt) {
//        Instruction *inst = &*jt;
//
//        CallSite CS(cast<Value>(inst));
//
//        // //If callSite
//        if (CS) {
//            auto &callInst = static_cast<CallInst&>(*inst);
//            auto* fnxCalled = dyn_cast<const Function>(callInst.getCalledValue()->stripPointerCasts());
//            if(!fnxCalled) {
//                errs() << "Non-defined Function Call \n";
//            } else
//                outs() << "=== callee: " << fnxCalled->getName() << "\n";
//        }
        /*
        if (CallInst *call_inst = dyn_cast<CallInst>(inst)) {
          Function *callee = call_inst->getCalledFunction();
          if (callee) {
            outs() << "=== callee: " << callee->getName() << "\n";
          }
        }*/
//    }
    return nullptr;
}

Instruction ** ControlFlowAnalyzer::getNextInstruction(Instruction* currentInst){

}

InterProceduralBasicBlock* ControlFlowAnalyzer::getIRInstruction(Function &function, std::string funcName, int lineNo){
    InterProceduralBasicBlock* sourceBB = nullptr;
    // first check function name
    if (function.getName() != funcName)
        return sourceBB;

    for (const BasicBlock &BB : function.getBasicBlockList()) {
        int index = -1;
        for (const Instruction &inst : BB.getInstList()) {
            index++;
            // get the debug information and compare with source line number
            const DebugLoc debugLoc = inst.getDebugLoc();
            // the argument operation does not contain debug location
            if (!debugLoc){
                continue;
            }
            int currentLineNo = debugLoc.getLine();
            if (lineNo == currentLineNo){
                sourceBB = new InterProceduralBasicBlock(&BB, index);
                return sourceBB;
            }
        }
    }
    return nullptr;
}

Function * ControlFlowAnalyzer::nextInstructionOFCall(BasicBlock *bb){

}
