#ifndef ALL_H
#define ALL_H

//******************************************************************************
//
//
//      all.h
//
//
//******************************************************************************

// システムやライブラリのヘッダーファイルは上の方へ
#include "../GameLib/game_lib.h"
#include <time.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <windows.h>

// 共通で使われるようなヘッダー
#include "common.h"

// 個々のヘッダーファイルは下の方へ
//#include "audio.h"

#include "obj2d.h"
#include "fairy.h"

#include "scene_game.h"
#include "scene_title.h"
#include "game_over.h"
#include "B_OBJ.h"
#include "Vase.h"
#include "book.h"
#include "cloud.h"
#include "enemy.h"
#include "juge.h"
#include "book.h"
#include "score.h"
#include "audio.h"
#include "snowman.h"
#include "game_clear.h"

// namespace
using namespace GameLib;
using namespace input;

#endif//ALL_H