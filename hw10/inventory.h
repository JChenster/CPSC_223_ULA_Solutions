typedef struct inventory* Inventory;

Inventory inventoryCreate(int weight_limit);

void inventoryDestroy(Inventory inv);

void inventoryAdd(Inventory inv, long price, long weight, char* item_name);

