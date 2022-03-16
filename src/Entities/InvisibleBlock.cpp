#include "InvisibleBlock.h"

bool InvisibleBlock::onColide(Ent* ent,int colIndex){
    if(ent->tag == ETags::TController || ent->tag == ETags::TFireball || ent->tag == ETags::TShell){return false;}
    return true;
}