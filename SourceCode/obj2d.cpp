#include "all.h"

OBJ2D* Set(OBJ2D* arr, int dataNum, int diff, OBJ2D::FUNC_PTR moveAlg, int atcck, int defence, GameLib::Sprite* spr)
{
         
        if (arr->moveAlg != nullptr)  return arr;

        
        //arr[i] = {};
        arr->diff = diff;
        arr->moveAlg = moveAlg;
        arr->atacck = atcck;
        arr->defence = defence;
        arr->data = spr;
        arr->isflag = true;
        return arr;

    return NULL;                        // ê∂ê¨Ç≈Ç´Ç»Ç©Ç¡ÇΩ
}

OBJ2D* Setenemy(OBJ2D arr[], int dataNum, OBJ2D::FUNC_PTR moveAlg, VECTOR2 pos, VECTOR2 setspeed, int diff)
{
    for (int i = 0; i < dataNum; i++)
    {
        if (arr[i].moveAlg != nullptr)  continue;

        arr[i] = {};
        arr[i].moveAlg = moveAlg;
        arr[i].pos = pos;
        arr[i].speed = setspeed;
        arr[i].diff = diff;
        arr[i].isflag = true;



        return &arr[i];
    }

    return nullptr;
}


