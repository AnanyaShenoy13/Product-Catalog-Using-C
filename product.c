#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100

typedef struct {
    char name[100];
    char id[20];
    float price;
} Product;

void add_product();
void display_products();
void delete_product();
void search_product();
void edit_product();
void sort_products();
void export_to_csv();
int load_products(Product products[]);

void add_product() {
    FILE *fp = fopen("Catalog.txt", "a");
    if (fp == NULL) {
        printf("[ERROR] Unable to open file to add product.\n");
        return;
    }

    Product p;
    getchar();

    printf("Enter Product Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Enter Product ID: ");
    scanf("%s", p.id);

    printf("Enter Product Price: ");
    scanf("%f", &p.price);

    fprintf(fp, "%s|%s|%.2f\n", p.name, p.id, p.price);
    fclose(fp);

    printf("[OK] Product Added Successfully!\n");
}

void display_products() {
    FILE *fp = fopen("Catalog.txt", "r");
    if (fp == NULL) {
        printf("[ERROR] Catalog file not found.\n");
        return;
    }

    Product p;
    char line[200];

    printf("\n%-30s %-15s %10s\n", "Product Name", "Product ID", "Price ($)");
    printf("---------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^|]|%[^|]|%f", p.name, p.id, &p.price);
        printf("%-30s %-15s %10.2f\n", p.name, p.id, p.price);
    }

    fclose(fp);
}

void delete_product() {
    char target_id[20];
    printf("Enter Product ID to Delete: ");
    scanf("%s", target_id);

    FILE *fp = fopen("Catalog.txt", "r");
    FILE *temp = fopen("Temp.txt", "w");

    if (!fp || !temp) {
        printf("[ERROR] File operation failed.\n");
        return;
    }

    Product p;
    char line[200];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^|]|%[^|]|%f", p.name, p.id, &p.price);
        if (strcmp(p.id, target_id) != 0) {
            fprintf(temp, "%s|%s|%.2f\n", p.name, p.id, p.price);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("Catalog.txt");
    rename("Temp.txt", "Catalog.txt");

    if (found)
        printf("[OK] Product deleted.\n");
    else
        printf("[ERROR] Product ID not found.\n");
}

void search_product() {
    char target_id[20];
    printf("Enter Product ID to Search: ");
    scanf("%s", target_id);

    FILE *fp = fopen("Catalog.txt", "r");
    if (fp == NULL) {
        printf("[ERROR] File not found.\n");
        return;
    }

    Product p;
    char line[200];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^|]|%[^|]|%f", p.name, p.id, &p.price);
        if (strcmp(p.id, target_id) == 0) {
            printf("\n[OK] Product Found:\n");
            printf("Name: %s\nID: %s\nPrice: $%.2f\n", p.name, p.id, p.price);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("[ERROR] Product ID not found.\n");
    }

    fclose(fp);
}

void edit_product() {
    char target_id[20];
    printf("Enter Product ID to Edit: ");
    scanf("%s", target_id);

    FILE *fp = fopen("Catalog.txt", "r");
    FILE *temp = fopen("Temp.txt", "w");
    if (!fp || !temp) {
        printf("[ERROR] File operation failed.\n");
        return;
    }

    Product p;
    char line[200];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^|]|%[^|]|%f", p.name, p.id, &p.price);
        if (strcmp(p.id, target_id) == 0) {
            found = 1;
            printf("Editing %s (%s):\n", p.name, p.id);
            getchar();

            printf("Enter New Name: ");
            fgets(p.name, sizeof(p.name), stdin);
            p.name[strcspn(p.name, "\n")] = 0;

            printf("Enter New Price: ");
            scanf("%f", &p.price);
        }
        fprintf(temp, "%s|%s|%.2f\n", p.name, p.id, p.price);
    }

    fclose(fp);
    fclose(temp);

    remove("Catalog.txt");
    rename("Temp.txt", "Catalog.txt");

    if (found)
        printf("[OK] Product updated.\n");
    else
        printf("[ERROR] Product ID not found.\n");
}

int load_products(Product products[]) {
    FILE *fp = fopen("Catalog.txt", "r");
    if (fp == NULL) return 0;

    int count = 0;
    char line[200];
    while (fgets(line, sizeof(line), fp) && count < MAX_PRODUCTS) {
        sscanf(line, "%[^|]|%[^|]|%f", products[count].name, products[count].id, &products[count].price);
        count++;
    }
    fclose(fp);
    return count;
}

void sort_products() {
    Product products[MAX_PRODUCTS];
    int n = load_products(products);

    if (n == 0) {
        printf("[INFO] No products to sort.\n");
        return;
    }

    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (products[j].price > products[j + 1].price) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }

    printf("\nProducts Sorted by Price:\n");
    printf("%-30s %-15s %10s\n", "Product Name", "Product ID", "Price ($)");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; ++i)
        printf("%-30s %-15s %10.2f\n", products[i].name, products[i].id, products[i].price);
}

void export_to_csv() {
    FILE *src = fopen("Catalog.txt", "r");
    FILE *dest = fopen("catalog.csv", "w");

    if (!src || !dest) {
        printf("[ERROR] File operation failed.\n");
        return;
    }

    Product p;
    char line[200];
    fprintf(dest, "Product Name,Product ID,Price\n");

    while (fgets(line, sizeof(line), src)) {
        sscanf(line, "%[^|]|%[^|]|%f", p.name, p.id, &p.price);
        fprintf(dest, "\"%s\",%s,%.2f\n", p.name, p.id, p.price);
    }

    fclose(src);
    fclose(dest);
    printf("[OK] Exported to catalog.csv\n");
}

int main() {
    int choice;

    do {
        printf("\n========= PRODUCT CATALOG MENU =========\n");
        printf("1. Display All Products\n");
        printf("2. Add New Product\n");
        printf("3. Delete Product by ID\n");
        printf("4. Search Product by ID\n");
        printf("5. Edit Product by ID\n");
        printf("6. Sort Products by Price\n");
        printf("7. Export Catalog to CSV\n");
        printf("8. Exit\n");
        printf("Enter your choice (1-8): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: display_products(); break;
            case 2: add_product(); break;
            case 3: delete_product(); break;
            case 4: search_product(); break;
            case 5: edit_product(); break;
            case 6: sort_products(); break;
            case 7: export_to_csv(); break;
            case 8: printf("[INFO] Exiting program. Goodbye!\n"); break;
            default: printf("[ERROR] Invalid choice. Try again.\n");
        }
    } while (choice != 8);

    return 0;
}
