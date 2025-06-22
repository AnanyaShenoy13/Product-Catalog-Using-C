
 ###   PRODUCT CATALOG MANAGEMENT SYSTEM

This is a C program to manage a product catalog stored in a text file.

-------------------------------------------

### HOW TO RUN:

1. Compile the program:
   gcc product.c -o catalog

2. Run the executable:
   ./catalog        (on Linux/Mac)
   catalog.exe      (on Windows)

-------------------------------------------

### PRODUCT DATA FORMAT (Catalog.txt):

Each product is stored as a line in the format:
ProductName|ProductID|Price

Example:
Quantum Watch|QW001|149.99

-------------------------------------------

### AVAILABLE MENU OPTIONS:

1. Display All Products
   - Shows all products in a tabular view.

2. Add New Product
   - Input name, ID, and price to add a new item.

3. Delete Product by ID
   - Removes a product entry by ID.

4. Search Product by ID
   - Finds and shows product details for the entered ID.

5. Edit Product by ID
   - Lets you change the name and price of an existing product.

6. Sort Products by Price
   - Displays products sorted in ascending order of price.

7. Export Catalog to CSV
   - Converts the product list to CSV format (catalog.csv).

8. Exit
   - Closes the program.

-------------------------------------------

### AUTHOR:
Ananya Shenoy
