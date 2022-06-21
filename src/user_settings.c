#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "utils.h"
#include "graphics.h"
#include "prototypes.h"
#include "user_settings.h"
#include "error_handler.h"

void load_default_settings()
{
    user_settings->show_time = 1;
    user_settings->show_date = 1;

    strcpy(user_settings->time_format, "%H:%M");
    strcpy(user_settings->date_format, "%a %d %b");

    user_settings->background_color = 0xAA000000;
    user_settings->foreground_color = 0xAAffffff;

    user_settings->vertical_margin = 10;
    user_settings->horizontal_margin = 10;

    user_settings->position = BOTTOM_RIGHT;
}

char * get_config_directory()
{
    char *home = getenv("HOME");

    if (!home)
        exit_with_error_message("Failed to get the users home directory");

    // On Linux the maximum path length is 4096 bytes
    char *directory = malloc(sizeof(char) * 4096);

    strcat(home, "/.config/lightclock/");
    strcpy(directory, home);

    mkdir(directory, S_IRWXU | S_IRWXG | S_IRWXO);

    return directory;
}

char * get_config_file_path()
{
    char *file_name = "lightclock.conf";
    char *config_directory = get_config_directory();

    // On Linux the maximum path length is 4096 bytes
    char *full_path = malloc(sizeof(char) * 4096);

    strcpy(full_path, config_directory);
    strcat(full_path, file_name);

    free(config_directory);

    return full_path;
}

uint8_t file_exists(char *file_path)
{
    return access(file_path, F_OK) == 0;
}

void save_settings(FILE *config_file)
{
    fprintf(config_file, 
            "position=%d\n", 
            user_settings->position);

    fprintf(config_file, 
            "show_time=%d\n", 
            user_settings->show_time);

    fprintf(config_file, 
            "show_date=%d\n", 
            user_settings->show_date);

    fprintf(config_file, 
            "time_format=%s\n", 
            user_settings->time_format);

    fprintf(config_file, 
            "date_format=%s\n", 
            user_settings->date_format);

    fprintf(config_file, 
            "background_color=%#010x\n",
            user_settings->background_color);

    fprintf(config_file, 
            "foreground_color=%#010x\n", 
            user_settings->foreground_color);

    fprintf(config_file, 
            "vertical_margin=%d\n", 
            user_settings->vertical_margin);

    fprintf(config_file, 
            "horizontal_margin=%d\n", 
            user_settings->horizontal_margin);
}

void update_user_setting(char *key, char *value)
{
    if (strcmp(key, "position") == 0)
        user_settings->position = atoi(value);

    else if (strcmp(key, "show_time") == 0)
        user_settings->show_time = atoi(value);

    else if (strcmp(key, "show_date") == 0)
        user_settings->show_date = atoi(value);

    else if (strcmp(key, "time_format") == 0)
        strcpy(user_settings->time_format, value);

    else if (strcmp(key, "date_format") == 0)
        strcpy(user_settings->date_format, value);

    else if (strcmp(key, "background_color") == 0)
        user_settings->background_color = strtol(value, NULL, 16);

    else if (strcmp(key, "foreground_color") == 0)
        user_settings->foreground_color = strtol(value, NULL, 16);

    else if (strcmp(key, "vertical_margin") == 0)
        user_settings->vertical_margin = atoi(value);

    else if (strcmp(key, "horizontal_margin") == 0)
        user_settings->horizontal_margin = atoi(value);
}

void read_settings(FILE *config_file)
{
    char buffer[256];

    char *delimiter = "=";

    while (fgets(buffer, 256, config_file) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = 0;

        char *key = strtok(buffer, delimiter);
        char *value = strtok(NULL, delimiter);

        update_user_setting(key, value);
    }
}

void initialize_user_settings()
{
    char *config_file_path = get_config_file_path();

    uint8_t config_file_exists = file_exists(config_file_path);

    FILE *config_file;

    if (config_file_exists)
    {
        config_file = fopen(config_file_path, "rt");

        if (!config_file)
            exit_with_error_message("Failed to read config file");

        read_settings(config_file);
    }

    else 
    {
        config_file = fopen(config_file_path, "wt");

        if (!config_file)
            exit_with_error_message("Failed to create config file");

        load_default_settings();
        save_settings(config_file);
    }

    fclose(config_file);
    free(config_file_path);
}

point_t get_position()
{
    point_t coordinates;

    coordinates.x = user_settings->horizontal_margin;
    coordinates.y = user_settings->vertical_margin;

    switch (user_settings->position)
    {
        case TOP_LEFT:
            break;

        case TOP_RIGHT:
            coordinates.x = 
                config->screen->width_in_pixels - 
                CLOCK_WINDOW_WIDTH - 
                user_settings->horizontal_margin;
            break;

        case BOTTOM_LEFT:
            coordinates.y = 
                config->screen->height_in_pixels - 
                CLOCK_WINDOW_HEIGHT -
                user_settings->vertical_margin;
            break;

        case BOTTOM_RIGHT:
            coordinates.x = 
                config->screen->width_in_pixels - 
                CLOCK_WINDOW_WIDTH - 
                user_settings->horizontal_margin;

            coordinates.y = 
                config->screen->height_in_pixels - 
                CLOCK_WINDOW_HEIGHT -
                user_settings->vertical_margin;
            break;
    }

    return coordinates;
}
