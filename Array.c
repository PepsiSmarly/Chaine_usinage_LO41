#include "Array.h"

Array* array_Create()
{
    Array* a = malloc(sizeof(Array));

    a->prev = NULL;
    a->next = NULL;

    return a;
}

Array* array_CreateWithValues(const char* _key, const char* _value)
{
    Array* a = malloc(sizeof(Array));

    a->prev = NULL;
    a->next = NULL;

    a->key = malloc(strlen(_key) + 1);
    strcpy(a->key, _key);

    a->value = malloc(strlen(_value) + 1);
    strcpy(a->value, _value);

    return a;
}

void array_Destroy(Array* _array)
{
    Array* current = _array;
    Array* tmp = NULL;

    while(current != NULL)
    {
        tmp = (Array*)current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = tmp;
    }
}

void array_Add(Array* _array, const char* _key, const char* _value)
{
    Array* last = array_GetLast(_array);
    Array* tmp = NULL;

    tmp = array_CreateWithValues(_key, _value);
    tmp->prev = (struct Array*)last;
    last->next = (struct Array*)tmp;
}

void array_AddArray(Array* _array, Array* _new)
{
    Array* last = array_GetLast(_array);

    _array->prev = (struct Array*)last;
    last->next = (struct Array*)_array;
}

Array* array_GetAt(Array* _array, int _index)
{
    int lenght = array_GetLenght(_array);

    Array* tmp = _array;
    int i = 0;
    while(i < _index)
    {
        if(i >= lenght) return NULL;

        i++;
        tmp = (Array*)tmp->next;
    }
    return tmp;
}

Array* array_GetKey(Array* _array, const char* _key)
{
    int lenght = array_GetLenght(_array);
    Array* tmp = _array;

    for (int i = 0; i < lenght; ++i)
    {
        if(strcmp(tmp->key, _key) == 0)
            return tmp;

        tmp = (Array*)tmp->next;
    }
    return NULL;
}

char* array_GetValueAt(Array* _array, int _index)
{
    Array* tmp = array_GetAt(_array, _index);
    if(tmp != NULL)
        return tmp->value;
    return NULL;
}

char* array_GetValueKey(Array* _array, const char* _key)
{
    Array* tmp = array_GetKey(_array, _key);
    if(tmp != NULL)
        return tmp->value;
    return NULL;
}

void array_DeleteAt(Array* _array, int _index)
{
    Array* tmp = array_GetAt(_array, _index);
    Array* prev = (Array*)tmp->prev;
    Array* next = (Array*)tmp->next;

    free(tmp->key);
    free(tmp->value);
    free(tmp);

    prev->next = (struct Array*)next;
    next->prev = (struct Array*)prev;
}

Array* array_GetLast(Array* _array)
{
    Array* tmp = _array;
    while(tmp->next != NULL)
    {
        tmp = (Array*)tmp->next;
    }
    return tmp;
}

int array_GetLenght(Array* _array)
{
    Array* tmp = _array;
    int i = 1;
    while(tmp->next != NULL)
    {
        tmp = (Array*)tmp->next;
        i++;
    }
    return i;
}
