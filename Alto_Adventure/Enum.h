#pragma once

#ifndef __ENUM_H__
#define __ENUM_H__

namespace OBJID
{
	enum ID { PLAYER, MONSTER, BULLET, EFFECT, MOUSE, SHIELD, CLOUD, ROCK,
		TREE, BIGTREE, COIN, MAGNET, POWERUP, HEART, UI, END };
}

namespace GROUPID
{
	enum ID { BACKGROUND, BEFORE_GAMEOBJECT, GAMEOBJECT, FOREWORD_GAMEOBJECT, EFFECT, UI, END };
}

namespace SCENE
{
	enum ID { SCENE_MENU, SCENE_STAGE, SCENE_END };
}
#endif // !__ENUM_H__
