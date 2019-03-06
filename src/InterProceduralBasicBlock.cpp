//
// Program: Inter-procedural basic block structure
// Author: Gao Xiang(gaoxiang9430@gmail.com)
// Time: 05/03/19.
//

#include "InterProceduralBasicBlock.h"

InterProceduralBasicBlock::InterProceduralBasicBlock(const BasicBlock* BB, int index){
    this->BB = BB;
    this->index = index;
}

const BasicBlock * InterProceduralBasicBlock::getBasicBlock(){
    return this->BB;
}

int InterProceduralBasicBlock::getCurIndex(){
    return this->index;
}

void InterProceduralBasicBlock::setCurIndex(int index){
    this->index = index;
}
