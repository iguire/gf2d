#include <stdlib.h>
#include "simple_logger.h"
#include "entity.h"
#include <SDL.h>
#include "player.h"
#include "level.h"
#include "projectile.h"

Vector2D spawn_top_left     = {100, 100};
Vector2D spawn_top_right    = {LEVEL_WIDTH - 100, 100};
Vector2D spawn_bottom_left  = {100, LEVEL_HEIGHT - 100};
Vector2D spawn_bottom_right = {LEVEL_WIDTH - 100, LEVEL_HEIGHT - 100};

void players_spawn(){

    player_new_ent(0,1, "images/white-circle.png", spawn_top_left);
    player_new_ent(1,1, "images/white-circle.png", spawn_top_right);
    player_new_ent(2,1, "images/white-circle.png", spawn_bottom_left);
    player_new_ent(3,1, "images/white-circle.png", spawn_bottom_right);
}

Player *player_new(float speed, int contNum){
    Player *p;
    p = (Player * )malloc(sizeof(Player));
    p->speed = speed;
    p->contNum = contNum;
    p->controller = SDL_GameControllerOpen(contNum);//Returns a gamecontroller identifier 
    p->canFire = 1;
    return p;
}

Entity *player_new_ent(int char_index, float default_speed, char sprite_path[], Vector2D init_pos){
    Entity *self;
    self = entity_new();
    if (!self)return NULL;
    self->sprite = gf2d_sprite_load_all(
        sprite_path,
        100,
        100,
        1
    );
    //
    self->radius = 50;
    self->size.x = 32;
    self->size.y = 32;
    vector2d_set(self-> drawOffset,-50,-50);
    vector2d_copy(self->position, init_pos);   
    //
    self->think = player_think;
    self->touch = player_touch;
    self->maxFrames = 1;
    self->typeOfEnt = player_new(default_speed,char_index);
    return self;
}

void player_think (Entity *self){
    Player *p = (Player *)self->typeOfEnt;
    SDL_GameController *c = p->controller;

    float x = SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTX);
    float y = SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTY);

    // if ( (x>(DEADZONE*2) || x< (DEADZONE * -2)) && (y>(DEADZONE*2) || y< (DEADZONE * -2)))
    vector2d_set(p->direction, x, y);

    if (x>DEADZONE || x< (DEADZONE * -1))
    self->position.x += x/ANALOG_SCALE*p->speed;
    if (y>DEADZONE || y< (DEADZONE * -1))
    self->position.y += y/ANALOG_SCALE*p->speed;

    // slog("Player %d, Movement vector: %f.%f, direction: %f",p->contNum, p->direction.x, p->direction.y, vector2d_angle(p->direction));

    if (SDL_GameControllerGetButton(c,SDL_CONTROLLER_BUTTON_A) && p->canFire){
        projectile_new_ent(p, p->speed, "images/white-circle.png", self->position);
        p->canFire = NULL;
        slog("got a");
    }
    // slog("Pos: %f.%f",self->position.x, self->position.y);
    // slog("Left stick of %s: %d,%d", SDL_GameControllerName(c),SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTX),SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTY));  
}

void player_touch(Entity *self,Entity *other)
{
    if ((!self) || (!other))return;
    slog("Player touched thing");
}