#pragma once

#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include <vector>
#include <list>
#include <map>
#include <functional>
#include <algorithm>

#include <time.h>
#include <iostream>

#include <assert.h>

using namespace std;

#include <windows.h>

// 부가적인 기능들이 들어있다. 벡터, 행렬등등. 
#include <d3dx9.h>
//D3DXVec3CatmullRom()을 사용하기 위한 헤더
#include <D3dx9math.h>
#pragma comment(lib, "d3dx9.lib")

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include "Define.h"
#include "Extern.h"
#include "Struct.h"
#include "Function.h"
#include "Enum.h"
#include "AbstractFactory.h"
#include "Functor.h"

#include "Device.h"

#endif // !__INCLUDE_H__
