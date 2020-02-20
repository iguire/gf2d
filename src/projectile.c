#include <stdlib.h>
#include "simple_logger.h"
#include "entity.h"
#include <SDL.h>
#include "projectile.h"
#include "player.h"

Projectile *projectile_new(Entity *owner_entity){
    //Initializations of owner player
    Player  *owner_player;
    owner_player = owner_entity->typeOfEnt;
    //Declaration of projectile
    Projectile *projectile;
    projectile = (Projectile * )malloc(sizeof(Projectile));
    //Initialization of projectile
    projectile->owner_entity = owner_entity;
    projectile->direction = owner_player->direction;
    projectile->time_to_live = 120;//TODO: pass from function
    projectile->time_alive = 0;

    return projectile;
}

Entity *projectile_new_ent(Entity *owner_entity, float default_speed, char sprite_path[], Vector2D init_pos){
    Entity *self;
    self = entity_new();
    if (!self)return NULL;
    //Init ent
    strcpy(self->name, "Projectile");
    self->sprite = gf2d_sprite_load_all(
        sprite_path,
        100,
        100,
        1
    );
    self->radius = 20;
    vector2d_set(self-> drawOffset,-50,-50);
    vector2d_copy(self->position, init_pos);  

    self->typeOfEnt = projectile_new(owner_entity);
    self->think = projectile_think;
    return self;
}

void projectile_think(Entity *self){
    Projectile *p = (Projectile *)self->typeOfEnt;
    p->time_alive += 1;
    if (p->time_alive > p->time_to_live){
        if (self->name)
            slog("Freed: %s", self->name);
        entity_free(self);
        return;
    }
    self->position.x += p->direction.x/ANALOG_SCALE;
    self->position.y += p->direction.y/ANALOG_SCALE;
    slog("Pos: %f.%f", self->position.x, self->position.y);
}