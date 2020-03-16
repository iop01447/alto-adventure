#pragma once

#ifndef __ENUM_H__
#define __ENUM_H__

namespace OBJID
{
	enum ID { PLAYER, MONSTER, BULLET, EFFECT, MOUSE, SHIELD, CLOUD, ROCK,
		TREE, BIGTREE, COIN, MAGNET, HEART, UI, END };
}

namespace GROUPID
{
	enum ID { BACKGROUND, BEFORE_GAMEOBJECT, GAMEOBJECT, FOREWORD_GAMEOBJECT, EFFECT, UI, END };
}

#endif // !__ENUM_H__
