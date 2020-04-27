#include "menu_pause.h"

void menu_pause_init() {

    //save button
    menu_generic(
        box_save,
        vector2d(-100, -250),
        gf2d_sprite_load_image("images/ui/button.png"),
        button_save_think,
        Sans,
        "Save"
    );

    // //Level button
    menu_generic(
        box_lvl_b,
        vector2d(-100, -250),
        gf2d_sprite_load_image("images/ui/button.png"),
        button_level_think,
        Sans,
        "Next level"
    );

    // //Exit button
    menu_generic(
        box_exit,
        vector2d(-100, -250),
        gf2d_sprite_load_image("images/ui/button.png"),
        button_exit_think,
        Sans,
        "Exit"
    );


}