//------------------------------------------------------------------------------
//// Program: Intra-procedure control flow analysis based on LLVM Basic Block
//// Author: Xiang Gao (gaoxiang9430@gmail.com)
//// Time: 18, Feb, 2019
//------------------------------------------------------------------------------
#ifndef CFA_H
#define CFA_H

#include "llvm/ADT/DenseMap.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Pass.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "InterProceduralBasicBlock.h"
#include <string>
#include <vector>

using namespace llvm;

class ControlFlowAnalyzer : public FunctionPass {
  public:
    ControlFlowAnalyzer(std::string, int, std::string, int);
    virtual bool runOnFunction(Function&);
    InterProceduralBasicBlock* getIRInstruction(Function&, std::string, int);
    Function * getCallee(BasicBlock*);
    Instruction ** getNextInstruction(Instruction*);
    static char ID;
        
  private:
    Function * nextInstructionOFCall(BasicBlock*);
    void exploreControlFlow(InterProceduralBasicBlock*, InterProceduralBasicBlock*);
    const CallInst* getNextCall(InterProceduralBasicBlock*);
    std::string sourceFuncName;
    std::string targetFuncName;
    int sourceLineNo;
    int targetLineNo;
    std::vector<InterProceduralBasicBlock> interBBList;
};
#endif
