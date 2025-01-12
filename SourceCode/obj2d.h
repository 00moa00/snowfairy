#ifndef OBJ2D_H
#define OBJ2D_H

struct OBJ2D
{
    int             timer;      // �^�C�}�[

    //11/8�ǉ���
    int hp;
    int atacck;        //�U���l
    int defence;       //�h��l
    int diff;          //�u���b�N�̎�ޗp�ϐ�
    int state;         //��ԊǗ��p�ϐ�
    //�ǉ����I��

    bool landing;
    bool Aflag;
    //11/8�ǉ���
    bool isflag;       //�u���b�N���o�������ǂ����̔���
    //�ǉ��I��
    char pad[3];

    //break
    int breakC;

    //serihu��flag

    //11/8�ǉ���
    GameLib::Sprite* data;      //�摜�f�[�^
    //�ǉ��I��

    VECTOR2         pos;        // �ʒu
    VECTOR2         scale;      // �X�P�[��
    VECTOR2         texPos;     // �摜�ʒu
    VECTOR2         texSize;    // �摜�T�C�Y
    VECTOR2         pivot;      // ��_
    VECTOR4         color;      // �F

    VECTOR2         speed;      // ���x
    int             jumpCount;  // �c��W�����v��
    int             act;        // �v���C���[�̍s���J�ڗp
    int             anime;      // �A�j�������݉��R�}�ڂ�
    int             animeTimer; // �A�j���p�^�C�}�[

    //11/8�ǉ���
    typedef void(*FUNC_PTR)(OBJ2D*);
    FUNC_PTR moveAlg;

};

OBJ2D* Set(OBJ2D* arr, int dataNum, int diff, OBJ2D::FUNC_PTR moveAlg, int atcck, int defence, GameLib::Sprite* spr);
OBJ2D* Setenemy(OBJ2D arr[], int dataNum, OBJ2D::FUNC_PTR moveAlg, VECTOR2 pos, VECTOR2 setspeed, int diff);

#endif//OBJ2D_H#pragma once
