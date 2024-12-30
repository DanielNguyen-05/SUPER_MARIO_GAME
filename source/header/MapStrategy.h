#pragma once
#include "DEFINITION.h"

// Base strategy
class MapStrategy {
public:
    virtual void buildMap(position* coinPosition, position* stonePosition,
        position* stoneCoinPosition, position* questCoinPosition,
        position* questMashPosition, position* questFlowerPosition,
        position* rockPosition,
        int& coinCnt, int& stoneCnt, int& stoneCoinCnt,
        int& quesCoinCnt, int& quesMashCnt, int& quesFlowerCnt,
        int& rockCnt) = 0;
    virtual ~MapStrategy() = default;
};