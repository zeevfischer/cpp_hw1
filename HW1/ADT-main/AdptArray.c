#include "AdptArray.h"
#include "book.h"
#include "Person.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct AdptArray_
{
    PElement *Array;
    int len;

    COPY_FUNC copy;
    DEL_FUNC del;
    PRINT_FUNC print;

};

PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC del, PRINT_FUNC print)
{
    PAdptArray arr = (PAdptArray)calloc(1,sizeof(struct AdptArray_));
    arr->Array = (PElement*)calloc(0,sizeof(PElement));
    // printf("%ld\n",sizeof((arr->Array)));
    arr->len = 0;
    arr->copy = copy;
    arr->del = del;
    arr->print = print;

    if(arr == NULL)
    {
        return NULL;
    }
    return arr;
}
void DeleteAdptArray(PAdptArray arr)
{
    //first we need to delate all the objects in the array
    for(int i =0;i<arr->len;i++)
    {
        if(arr->Array[i] != NULL)
        {
            arr->del(arr->Array[i]);
        }
    }
    free(arr->Array);
    //now we can free the struct
    free(arr);
}
Result SetAdptArrayAt(PAdptArray arr, int location, PElement element)
{
    //lets check if arr is big enough
    if(arr->len-1 >= location)
    {
        PElement obj = arr->copy(element);
        arr->Array[location] = obj;
        return 1;
    }
    //the arr is to small
    else
    {
        // //creat a new array 
        PElement *new_array = (PElement*)calloc(location+1,sizeof(PElement));
        for(int i = 0;i <= arr->len-1;i++)
        {
            //now need for copy alll you need to do is set pointers to the old array
            new_array[i] = arr->Array[i];
            
            // //copy all elements from old to new
            // if(arr->Array[i] != NULL)
            // {
            //     PElement obj = arr->copy(arr->Array[i]);
            //     new_array[i] = obj;
            // }
            // //new deleat it from the old array
            // arr->del(arr->Array[i]);
        }
        //free old array
        if(arr->Array != NULL)
        {
            free(arr->Array);
        }
        //set new array
        arr->Array = new_array; 

        //set length
        arr->len = location+1;
        //set new object
        PElement obj = arr->copy(element);
        arr->Array[location] = obj;
        return 1;
    }
    return 0;
}
PElement GetAdptArrayAt(PAdptArray arr, int location)
{
    if(arr->Array[location] == NULL)
    {
        return NULL;
    }
    return arr->copy(arr->Array[location]);
}
int GetAdptArraySize(PAdptArray arr)
{
    if(arr->Array == NULL || arr->len == 0)
    {
        return 1;
    }
    else
    {
        int a = arr->len;
        return a;
    }
}
void PrintDB(PAdptArray arr)
{
    for (int i = 0; i < arr->len; i++)
    {
        if(arr->Array[i]!=NULL)
        {
            arr->print(arr->Array[i]);
        }
    }
}