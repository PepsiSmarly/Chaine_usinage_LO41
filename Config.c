#include "Config.h"

Config* config_Create(const char* _file)
{
    Config* c = malloc(sizeof(Config));
    c->file = fopen(_file, "r");

    printf("Fichier config ouvert !\n");

    if(c->file == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier de config");
        exit(-1);
    }

    char field[CONFIG_MAX_LENGHT],
        equal[CONFIG_MAX_LENGHT],
        value[CONFIG_MAX_LENGHT];

    char* line;
    line = malloc(CONFIG_MAX_LENGHT * 2);
    fgets(line, CONFIG_MAX_LENGHT * 2, c->file);

    if(strlen(line) <= 0)
    {
        printf("fichier vide...\n");
        free(line);
        exit(-1);
    }

    sscanf(line, "%s %s %s", field, equal, value);
    c->content = array_CreateWithValues(field, value);
    free(line);

    line = malloc(CONFIG_MAX_LENGHT * 2);
    while(fgets(line, CONFIG_MAX_LENGHT * 2, c->file))
    {
        sscanf(line, "%s %s %s", field, equal, value);
        array_Add(c->content, field, value);

        free(line);
        line = malloc(CONFIG_MAX_LENGHT * 2);
    }

    free(line);
    fclose(c->file);

    return c;
}

void config_Destroy(Config* _config)
{
    if(_config == NULL)
        return;

    array_Destroy(_config->content);
    free(_config);
}

char* config_GetField(Config* _config, const char* _field)
{
    return array_GetValueKey(_config->content, _field);
}
