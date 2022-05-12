#include "app.h"
#include <stdio.h>

#include <SDL2/SDL_image.h>

void init_app(App *app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Generators",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL)
    {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0)
    {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL)
    {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO)
    {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else
    {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 10000);
}

void handle_app_events(App *app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int speed = 50;
    int x;
    int y;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_W:

                if (app->scene.canMove)
                {
                    set_camera_speed(&(app->camera), speed);
                }
                break;
            case SDL_SCANCODE_S:
                if (app->scene.canMove)
                {
                    set_camera_speed(&(app->camera), -speed);
                }
                break;
            case SDL_SCANCODE_A:
                if (app->scene.canMove)
                {
                    set_camera_side_speed(&(app->camera), speed);
                }
                break;
            case SDL_SCANCODE_D:
                if (app->scene.canMove)
                {
                    set_camera_side_speed(&(app->camera), -speed);
                }
                break;
            case SDL_SCANCODE_TAB:
                printf("\nx:%f, y:%f, z:%f, \ncamera_angle: x: %f, y:%f, z:%f",
                       app->camera.position.x, app->camera.position.y, app->camera.position.z, app->camera.rotation.x, app->camera.rotation.y, app->camera.rotation.z);
                break;
            case SDL_SCANCODE_KP_PLUS:
                if (app->scene.light_modifier < 1.0)
                {
                    app->scene.light_modifier += 0.02;
                }
                break;
            case SDL_SCANCODE_KP_MINUS:
                if (app->scene.light_modifier > 0.0)
                {
                    app->scene.light_modifier -= 0.02;
                }
                break;
            case SDL_SCANCODE_F1:
                show_help_panel(&(app->scene.helppanel_show));
                break;
            case SDL_SCANCODE_E:
                // Generator 1 collision
                if ((app->camera.position.x < 85 && app->camera.position.x > 75) && (app->camera.position.y < 5 && app->camera.position.y > -5))
                {
                    if ((app->scene.isGenerator_1_activated) == false)
                    {
                        app->scene.isGenerator_1_activated = true;
                    }
                }

                // Generator 2 collision
                if ((app->camera.position.x < 125 && app->camera.position.x > 115) && (app->camera.position.y < 45 && app->camera.position.y > 35))
                {
                    if ((app->scene.isGenerator_2_activated) == false)
                    {
                        app->scene.isGenerator_2_activated = true;
                    }
                }

                // Generator 3 collision
                if ((app->camera.position.x < 85 && app->camera.position.x > 75) && (app->camera.position.y < 45 && app->camera.position.y > 35))
                {
                    if ((app->scene.isGenerator_3_activated) == false)
                    {
                        app->scene.isGenerator_3_activated = true;
                    }
                }

                // Generator 4 collision
                if ((app->camera.position.x < 35 && app->camera.position.x > 25) && (app->camera.position.y < 106 && app->camera.position.y > 94))
                {
                    {
                        if ((app->scene.isGenerator_4_activated) == false)
                        {
                            app->scene.isGenerator_4_activated = true;
                        }
                    }
                }
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down)
            {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App *app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
}

void render_app(App *app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    if (app->camera.is_preview_visible)
    {
        show_texture_preview();
    }

    if (app->scene.helppanel_show == true)
    {
        render_help(app->scene.panel_help);
    }

    // Generator 1 collision
    if ((app->camera.position.x < 85 && app->camera.position.x > 75) && (app->camera.position.y < 5 && app->camera.position.y > -5))
    {
        if (app->scene.isGenerator_1_activated == false)
        {
            render_activation(app->scene.panel_activation);
        }
    }

    // Generator 2 collision
    if ((app->camera.position.x < 125 && app->camera.position.x > 115) && (app->camera.position.y < 45 && app->camera.position.y > 35))
    {
        if (app->scene.isGenerator_2_activated == false)
        {
            render_activation(app->scene.panel_activation);
        }
    }

    // Generator 3 collision
    if ((app->camera.position.x < 85 && app->camera.position.x > 75) && (app->camera.position.y < 45 && app->camera.position.y > 35))
    {
        if (app->scene.isGenerator_3_activated == false)
        {
            render_activation(app->scene.panel_activation);
        }
    }

    // Generator 4 collision
    if ((app->camera.position.x < 35 && app->camera.position.x > 25) && (app->camera.position.y < 106 && app->camera.position.y > 94))
    {
        {
            if (app->scene.isGenerator_4_activated == false)
            {
                render_activation(app->scene.panel_activation);
            }
        }
    }

    if ((app->scene.isGenerator_1_activated && app->scene.isGenerator_2_activated) && (app->scene.isGenerator_3_activated && app->scene.isGenerator_4_activated))
    {
        render_activation(app->scene.panel_winner);
        app->camera.position.x = -100;
        app->camera.position.y = 0;
        app->camera.position.z = 100;
        app->scene.canMove = false;
        app->scene.carRunning = true;
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App *app)
{
    if (app->gl_context != NULL)
    {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL)
    {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}

void show_help_panel(bool *helppanel_show)
{
    if (*helppanel_show == false)
    {
        *helppanel_show = true;
    }
    else
    {
        *helppanel_show = false;
    }
}

void render_help(GLuint texture)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, 1280, 800, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_CULL_FACE);
    glClear(GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(0.0, 800.0);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(1280.0, 800.0);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(1280.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glEnd();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void render_activation(GLuint texture)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, 1280, 800, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_CULL_FACE);
    glClear(GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(300.0, 180.0);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(980.0, 180.0);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(980.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(300.0, 0.0);
    glEnd();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}