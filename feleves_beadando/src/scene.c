#include "skull.h"
#include "scene.h"
#include <stdio.h>

#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>

void init_scene(Scene *scene)
{
    init_models(scene);
    scene->isGenerator_1_activated = false;
    scene->isGenerator_2_activated = false;
    scene->isGenerator_3_activated = false;
    scene->isGenerator_4_activated = false;

    scene->carRunning = false;
    scene->canMove = true;

    scene->generator_index = 0;

    scene->car_position_x = 0;
    scene->car_position_y = -2;

    scene->material.ambient.red = 0.2;
    scene->material.ambient.green = 0.2;
    scene->material.ambient.blue = 0.2;

    scene->material.diffuse.red = 0.2;
    scene->material.diffuse.green = 0.2;
    scene->material.diffuse.blue = 0.2;

    scene->material.specular.red = 0.2;
    scene->material.specular.green = 0.2;
    scene->material.specular.blue = 0.2;

    scene->material.shininess = 0.0;

    scene->light_modifier = 1;
}

void init_models(Scene *scene)
{
    load_model(&(scene->ground), "assets/models/ground.obj");
    load_model(&(scene->generator), "assets/models/generator.obj");
    load_model(&(scene->sky), "assets/models/sky.obj");
    load_model(&(scene->skyRoof), "assets/models/skyRoof.obj");
    load_model(&(scene->car), "assets/models/car.obj");

    scene->texture_id_ground = load_texture("assets/textures/ground.jpg");
    scene->texture_id_generator = load_texture("assets/textures/generator.jpeg");
    scene->sky_texture_id = load_texture("assets/textures/skyRoof.jpg");
    scene->texture_id_car = load_texture("assets/textures/car.png");

    scene->panel_help = load_texture("assets/textures/panel_help.jpg");
    scene->panel_activation = load_texture("assets/textures/panel_activation.jpg");
    scene->panel_winner = load_texture("assets/textures/panel_winner.jpg");
}

void load_models(Scene *scene)
{
    // Ground
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id_ground);
    set_material(&(scene->material));
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->ground));
    glPopMatrix();

    // Generator 1
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id_generator);
    set_material(&(scene->material));
    glScalef(4, 4, 4);
    glTranslatef(20, 0, 0.7f);
    draw_model(&(scene->generator));
    glPopMatrix();

    // Generator 2
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id_generator);
    set_material(&(scene->material));
    glScalef(4, 4, 4);
    glTranslatef(30, 10, 0.7f);
    draw_model(&(scene->generator));
    glPopMatrix();

    // Generator 3
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id_generator);
    set_material(&(scene->material));
    glScalef(4, 4, 4);
    glTranslatef(20, 10, 0.7f);
    draw_model(&(scene->generator));
    glPopMatrix();

    // Generator 4
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id_generator);
    set_material(&(scene->material));
    glScalef(4, 4, 4);
    glTranslatef(8, 25, 0.7f);
    draw_model(&(scene->generator));
    glPopMatrix();

    if (scene->carRunning)
    {
        scene->car_position_x += 0.05f;
    }

    // Car
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id_car);
    set_material(&(scene->material));
    glScalef(6, 6, 6);
    glTranslatef(scene->car_position_x, scene->car_position_y, 0.2f);
    glRotated(90, 1, 0, 0);
    glRotated(90, 0, 1, 0);
    draw_model(&(scene->car));
    glPopMatrix();

    // Sky
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->sky_texture_id);
    glScalef(10, 10, 10);
    glRotatef(90, 0, 0, -1);
    glTranslatef(0, 24, 0);
    draw_model(&(scene->sky));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->sky_texture_id);
    glScalef(10, 10, 10);
    glTranslatef(0, -24, 0);
    draw_model(&(scene->sky));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->sky_texture_id);
    glScalef(10, 10, 10);
    glTranslatef(0, 24, 0);
    draw_model(&(scene->sky));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->sky_texture_id);
    glScalef(10, 10, 10);
    glRotatef(90, 0, 0, -1);
    glTranslatef(0, -24, 0);
    draw_model(&(scene->sky));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->sky_texture_id);
    glScalef(10, 10, 10);
    glTranslatef(0, 0, 24);
    draw_model(&(scene->skyRoof));
    glPopMatrix();
    // End sky
}

void set_lighting(Scene *scene)
{
    float ambient_light[] = {scene->light_modifier, scene->light_modifier, scene->light_modifier, 0.0f};
    float diffuse_light[] = {scene->light_modifier, scene->light_modifier, scene->light_modifier, 0.0f};
    float specular_light[] = {1.0f, 1.0f, 1.0f, 0.0f};
    float position[] = {0.0f, 0.0f, 10.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void render_scene(Scene *scene)
{
    set_material(&(scene->material));
    set_lighting(scene);
    load_models(scene);
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

double get_angle_between_player_skull(Skull *skull, Camera *camera)
{
    // double a, b;
    //  double angle = cos(b / +(sqrt(pow(a, 2) + pow(b, 2))));

    // double angle = atan2(skull->position.x * camera->position.y - skull->position.y * camera->position.x, skull->position.x * camera->position.x + skull->position.y * camera->position.y);
    double pi = 3.14159;
    double signed_angle = atan2(camera->position.y, camera->position.x) - atan2(skull->position.y, skull->position.x);
    double angle = signed_angle * (180 / pi);
    printf("\n%lf", angle);
    return angle;
}