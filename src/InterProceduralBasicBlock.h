//
// Created by gx on 05/03/19.
//

#ifndef CRASH_FREE_INTREPROCEDURALBASICBLOCK_H
#define CRASH_FREE_INTREPROCEDURALBASICBLOCK_H

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

using namespace llvm;
class InterProceduralBasicBlock{
public:
    InterProceduralBasicBlock(const BasicBlock*, int);
    const BasicBlock* getBasicBlock();
    void setCurIndex(int index);
    int getCurIndex();

private:
    const BasicBlock* BB;
    int index;
};

#endif //CRASH_FREE_INTRAPROCEDUREBASICBLOCK_H
