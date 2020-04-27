#ifndef _SCENE_H_
#define _SCENE_H_

#include "menu.h"

#define scn_MENU 1
#define scn_LEVEL 2

typedef struct {
	int type;
	MenuManager* menu_manager;
	Level* level;
	void* data;

	//mouse
	int mx, my;
	float mf;
	Sprite *mouse_sprite;
	Vector4D mouse_color;

	int paused;
}Scene;

Scene* scene_get_active();

Scene *scene_new();

void scene_update(Scene *self);

void scene_draw(Scene *self);

#endif // !_SCENE_H_
