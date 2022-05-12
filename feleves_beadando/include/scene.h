#ifndef SCENE_H
#define SCENE_H

#include "skull.h"
#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model ground;
    Model generator;
    Model sky;
    Model skyRoof;
    Model car;
    float car_position_x;
    float car_position_y;
    Material material;
    GLuint texture_id_ground;
    GLuint texture_id_generator;
    GLuint texture_id_car;
    GLuint sky_texture_id;
    GLuint skyRoof_texture_id;
    GLuint panel_help;
    GLuint panel_activation;
    GLuint panel_winner;
    float light_modifier;
    int generator_index;
    bool helppanel_show;
    bool activationpanel_show;
    bool isGenerator_1_activated;
    bool isGenerator_2_activated;
    bool isGenerator_3_activated;
    bool isGenerator_4_activated;
    bool carRunning;
    bool canMove;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene *scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material *material);

/**
 * Render the scene objects.
 */
void render_scene(Scene *scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Initialize models
 */
void init_models(Scene *scene);

#endif /* SCENE_H */
