//------------------------------------------------------------------------------
//// Program: Create intra-procedure control flow graph based on LLVM Basic Block
//// Author: Xiang Gao (gaoxiang9430@gmail.com)
//// Time: 18, Feb, 2019
//------------------------------------------------------------------------------
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/ADT/SCCIterator.h"
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
#include <string>
#include <vector>

using namespace llvm;

class ControlFlowAnalyzer : public FunctionPass {
    public:
        ControlFlowAnalyzer(): FunctionPass(ID) {}

        virtual bool runOnFunction(Function &F) {
            outs() << "Function name: " << F.getName() << "\n";
            BasicBlock *BB = &F.getEntryBlock();
            outs() << "basic block: " << BB->getName() << "\n";

            getCallee(BB);

            const TerminatorInst *TInst = BB->getTerminator();
            for (unsigned I = 0, NSucc = TInst->getNumSuccessors(); I < NSucc; ++I) {
                BasicBlock *succ = TInst->getSuccessor(I);
                outs() << "edge from " << BB->getName() << " to " << succ->getName() << "\n";
                CallInst * callInst =  succ->getTerminatingMustTailCall ();
                outs() << "call site: " << callInst->getName();
            }
            return true;
        }

        static char ID;
        
    private:
        Function * getCallee(BasicBlock *bb){
            for (BasicBlock::iterator jt=bb->begin(), jend=bb->end();jt!=jend;++jt) {
                Instruction *inst = &*jt;
                if (CallInst *call_inst = dyn_cast<CallInst>(inst)) {
                    Function *callee = call_inst->getCalledFunction();
                    if (callee) {
                        // std::cout <<"=== has callee"  << "\n";
                        outs() << "=== callee: " << callee->getName() << "\n";
                        // DISubprogram *disubprogram = callee->getSubprogram();
                        // if (disubprogram) {
                        //     outs() << "=== has DI Subprogram" << "\n";
                        //     errs() << disubprogram->getName() << "\n";
                        // }
                    }
                }
            }
            return NULL;
        }
};

char ControlFlowAnalyzer::ID = 0;
int main(int argc, char **argv) {
    if (argc < 3) {
        // Using very basic command-line argument parsing here...
        errs() << "Usage: " << argv[0] << " -[topo|po|scc] <IR file>\n";
        return 1;
    }
    // Parse the input LLVM IR file into a module.
    SMDiagnostic Err;
    LLVMContext Context;
    std::unique_ptr<Module> Mod(parseIRFile(argv[2], Err, Context));
    if (!Mod) {
        Err.print(argv[0], errs());
        return 1;
    }

    // Create a pass manager and fill it with the passes we want to run.
    legacy::PassManager PM;
    PM.add(new ControlFlowAnalyzer());
    PM.run(*Mod);

    return 0;
}
