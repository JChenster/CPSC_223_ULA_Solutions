#include <stdlib.h>
#include <stdio.h>

#include "inventory.h"

int main(){
    unsigned long weight_limit;
    scanf("%lu", &weight_limit);

    Inventory inv = inventoryCreate(weight_limit);

    long price;
    long weight;
    char* item_name = NULL;
    while (scanf("%ld %ld %m[^\n]", &price, &weight, &item_name) == 3){
        //printf("%ld %ld %s\n", price, weight, item_name);
        inventoryAdd(inv, price, weight, item_name);
    }

    inventoryDestroy(inv);
}
