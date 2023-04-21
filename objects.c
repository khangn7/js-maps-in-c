#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10
#define KEY "\0\0\0\0\0\0\0\0\0\0"

// not really objects no methods
// more like JS Maps ('n')
// key-value pairs of strings and ints

// Int object keys are char[10]
// '\0' on index 0 when initObj()
typedef struct
{
    char keys[MAX][MAX];
    int values[MAX];
}
Int_Obj;


int setIntObj(Int_Obj *obj, const char *value, const int key);
void initObj(Int_Obj *obj);
int getIntObj(const Int_Obj *obj, const char *key);
int compareCharArr(const int maxlength, char *start_pa, char *start_pb);
int getKeyIndex(const Int_Obj *obj, const char *str);
void makeKey(char *key, char *keyname);

int main(void) 
{
    Int_Obj a;
    initObj(&a);
    printf("%s %d\n", a.keys[0], a.values[0]);

    char *key1str = "a";
    char *key1 = KEY;
    makeKey(key1, key1str);

    int set = setIntObj(&a, key1, 1);

    printf("set %d\n", set);
    printf("%s %d\n", a.keys[0], a.values[0]);

    // printf("%s %d\n", "a", getIntObj(&a, key1));

    int scmp = compareCharArr(MAX, key1, (char *) &(a.keys[0]));

    printf("scmp %d", scmp);

    return 0;
}

// if object is full returns 1, else success returns 0
int setIntObj(Int_Obj *obj, const char *key, const int value)
{
    unsigned int keylen = strlen(key);

    if (keylen > 10)
    {
        printf("MY ERROR: setIntObj() input str needs to be length of %d or less", MAX);
        return 1;
    }

    for (int i = 0; i < MAX; i++)
    {
        if ((*obj).keys[i][0] == '\0')
        {
            // set key
            for (int j = 0; j < keylen; j++)
            {
                (*obj).keys[i][j] = key[j];
            }
            for (int j = keylen; j < MAX; j++)
            {
                (*obj).keys[i][j] = '\0';
            }

            // set value
            (*obj).values[i] = value;
            return 0;
        }
    }
    
    return 1;
}

// if key doesn't exist return 0  ¯\_(ツ)_/¯

int getIntObj(const Int_Obj *obj, const char *str)
{
    if (strlen(str) > 10)
    {
        printf("MY ERROR: getIntObj() input str needs to be length of %d or less", MAX);
        return 0;
    }

    int index = getKeyIndex(obj, str);
    if (index != -1)
    {
        return (int) (*obj).values[index];
    }

    printf("getIntObj key doesn't exist\n");
    return 0;
}

// if key doesn't exist return -1, else return index
int getKeyIndex(const Int_Obj *obj, const char *str)
{
    for (int i = 0; i < MAX; i++)
    {
        if (compareCharArr(MAX, (char *) str, (char *) &((*obj).keys[i])) == 0)
        {
            return i;
        }
    }
    
    return -1;
}

void initObj(Int_Obj *obj)
{
    for (int i = 0; i < MAX; i++)
    {
        (*obj).keys[i][0] = '\0';
        (*obj).values[i] = 0;
    }

    return;
}

// gargabe values mess this up
// returns 0 if two char[] same, 1 if false
int compareCharArr(const int maxlength, char *start_pa, char *start_pb)
{
    for (int i = 0; i < maxlength; i++)
    {
        if (*start_pa != *start_pb)
        {
            return 1;
        }

        start_pa++;
        start_pb++;
    }

    return 0;
}

void makeKey(char *key, char *keyname)
{
    unsigned int keylen = strlen(keyname);

    if (keylen > 10)
    {
        printf("MY ERROR: makeKey() input str needs to be length of %d or less", MAX);
        return;
    }

    for (int i = 0; i < keylen; i++)
    {
        key[i] = keyname[i];
    }
}