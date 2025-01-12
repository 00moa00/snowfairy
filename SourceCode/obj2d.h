#ifndef OBJ2D_H
#define OBJ2D_H

struct OBJ2D
{
    int             timer;      // タイマー

    //11/8追加分
    int hp;
    int atacck;        //攻撃値
    int defence;       //防御値
    int diff;          //ブロックの種類用変数
    int state;         //状態管理用変数
    //追加分終了

    bool landing;
    bool Aflag;
    //11/8追加分
    bool isflag;       //ブロックが出現中かどうかの判定
    //追加終了
    char pad[3];

    //break
    int breakC;

    //serihuのflag

    //11/8追加分
    GameLib::Sprite* data;      //画像データ
    //追加終了

    VECTOR2         pos;        // 位置
    VECTOR2         scale;      // スケール
    VECTOR2         texPos;     // 画像位置
    VECTOR2         texSize;    // 画像サイズ
    VECTOR2         pivot;      // 基準点
    VECTOR4         color;      // 色

    VECTOR2         speed;      // 速度
    int             jumpCount;  // 残りジャンプ回数
    int             act;        // プレイヤーの行動遷移用
    int             anime;      // アニメが現在何コマ目か
    int             animeTimer; // アニメ用タイマー

    //11/8追加分
    typedef void(*FUNC_PTR)(OBJ2D*);
    FUNC_PTR moveAlg;

};

OBJ2D* Set(OBJ2D* arr, int dataNum, int diff, OBJ2D::FUNC_PTR moveAlg, int atcck, int defence, GameLib::Sprite* spr);
OBJ2D* Setenemy(OBJ2D arr[], int dataNum, OBJ2D::FUNC_PTR moveAlg, VECTOR2 pos, VECTOR2 setspeed, int diff);

#endif//OBJ2D_H#pragma once
