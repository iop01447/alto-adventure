#pragma once

#ifndef __DEFINE_H__
#define __DEFINE_H__

#define WINCX 1280
#define WINCY 720

#define OBJ_NOEVENT 0
#define OBJ_DEAD 1

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define PI 3.141592f


//#define TILECX 64
//#define TILECY 64
//#define TILEX 30
//#define TILEY 20

#endif // !__DEFINE_H__
