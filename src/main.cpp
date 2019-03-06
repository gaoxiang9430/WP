//------------------------------------------------------------------------------
//// Program: main
//// Author: Xiang Gao (gaoxiang9430@gmail.com)
//// Time: 1, Mar, 2019
//------------------------------------------------------------------------------
#include "ControlFlowAnalyzer.h"

char ControlFlowAnalyzer::ID = 0;
int main(int argc, char **argv) {
    if (argc < 2) {
        // Using very basic command-line argument parsing here...
        errs() << "Usage: " << argv[0] << "<IR file>\n";
        return 1;
    }
    // Parse the input LLVM IR file into a module.
    SMDiagnostic Err;
    LLVMContext Context;
    std::unique_ptr<Module> Mod(parseIRFile(argv[1], Err, Context));
    if (!Mod) {
        Err.print(argv[0], errs());
        return 1;
    }

    // Create a pass manager and fill it with the passes we want to run.
    legacy::PassManager PM;
    ControlFlowAnalyzer* cfa = new ControlFlowAnalyzer("main", 9, "main", 15);
    PM.add(cfa);
    PM.run(*Mod);

    return 0;
}
