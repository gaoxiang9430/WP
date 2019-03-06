//------------------------------------------------------------------------------
//// Program: Unit test for ControlFlowAnalysizer
//// Author: Xiang Gao (gaoxiang9430@gmail.com)
//// Time: 18, Feb, 2019
//------------------------------------------------------------------------------

#include "../src/ControlFlowAnalyzer.h"

char ControlFlowAnalyzer::ID = 0;
ControlFlowAnalyzer* init(char *fileName) {
    SMDiagnostic Err;
    LLVMContext Context;
    std::unique_ptr<Module> Mod(parseIRFile(fileName, Err, Context));

    // Create a pass manager and fill it with the passes we want to run.
    legacy::PassManager PM;
    ControlFlowAnalyzer* cfa = new ControlFlowAnalyzer("main", 12, "main", 10);
    PM.add(cfa);
    PM.run(*Mod);

    return cfa;
}

void checkFunctionList(ControlFlowAnalyzer* cfa){
//    cfa->getFunctionList();
}

void checkGetIRInstruction(ControlFlowAnalyzer* cfa){
//    cfa->getIRInstruction("fun", 123);
}

int main(int argc, char** argv){
    ControlFlowAnalyzer* cfa = init(argv[1]);
//    checkFunctionList(cfa);
//    checkGetIRInstruction(cfa);
}