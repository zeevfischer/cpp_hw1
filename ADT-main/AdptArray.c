#include "AdptArray.h"
#include "book.h"
#include "Person.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// implementing the struct
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
    //check input velidety
    if(copy == NULL || del == NULL || print == NULL)
    {
        return FAIL;
    }
    //init struct 
    PAdptArray arr = (PAdptArray)calloc(1,sizeof(struct AdptArray_));
    arr->Array = (PElement*)calloc(0,sizeof(PElement));
    arr->len = 0;
    arr->copy = copy;
    arr->del = del;
    arr->print = print;
    //if init failes
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
    //now we free the array
    free(arr->Array);
    //now we can free the struct
    free(arr);
}
Result SetAdptArrayAt(PAdptArray arr, int location, PElement element)
{
    //check input velidety
    if(location < 0 || element == NULL || arr == NULL)
    {
        return FAIL;
    }
    //lets check if the array is big enough
    if(arr->len-1 >= location)
    {
        //free the element in the array if exists
        if(arr->Array[location] != NULL)
        {
            arr->del(arr->Array[location]);
        }
        PElement obj = arr->copy(element);
        arr->Array[location] = obj;
        return SUCCESS;
    }
    //the arr is to small
    //if it is to small then obviesly arr->Array[location] == NULL
    else
    {
        // //creat a new array 
        PElement *new_array = (PElement*)calloc(location+1,sizeof(PElement));
        for(int i = 0;i <= arr->len-1;i++)
        {
            //now need to copy. all we need to do is set new pointers to the objects 
            new_array[i] = arr->Array[i];
            
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
        return SUCCESS;
    }
    return FAIL;
}
PElement GetAdptArrayAt(PAdptArray arr, int location)
{
    //check input velidety
    if(arr->Array[location] == NULL || location < 0)
    {
        return NULL;
    }
    return arr->copy(arr->Array[location]);
}
int GetAdptArraySize(PAdptArray arr)
{
    //check input velidety
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
    //check input velidety
    for (int i = 0; i < arr->len; i++)
    {
        if(arr->Array[i]!=NULL)
        {
            arr->print(arr->Array[i]);
        }
    }
}