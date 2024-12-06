#include <stdio.h>
#include <string.h>

// Arrays to hold transaction data
int transaction_ids[100];
char transaction_types[100][10];
char transaction_categories[100][20];
float transaction_amounts[100];
int transaction_count = 0;

// Arrays for budget data
char budget_categories[100][20];
float budget_amounts[100];
int budget_count = 0;

// Function prototypes
void add_transaction();
void view_transactions();
void delete_transaction();
void generate_summary();
void set_budget();
void view_budget_status();

int main() {
    int choice;

    while (1) {
        // Main menu
        printf("\n=== Personal Finance Management System ===\n");
        printf("1. Add Transaction\n");
        printf("2. View Transactions\n");
        printf("3. Delete Transaction\n");
        printf("4. Generate Summary\n");
        printf("5. Set Budget\n");
        printf("6. View Budget Status\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_transaction();
                break;
            case 2:
                view_transactions();
                break;
            case 3:
                delete_transaction();
                break;
            case 4:
                generate_summary();
                break;
            case 5:
                set_budget();
                break;
            case 6:
                view_budget_status();
                break;
            case 7:
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to add a transaction
void add_transaction() {
    if (transaction_count >= 100) {
        printf("Error: Maximum transaction limit reached.\n");
        return;
    }

    int id = transaction_count + 1;
    char type[10];
    char category[20];
    float amount;

    printf("Enter transaction type (Income/Expense): ");
    scanf("%s", type);
    printf("Enter category (e.g., Food, Rent, Salary): ");
    scanf("%s", category);
    printf("Enter amount: ");
    scanf("%f", &amount);

    transaction_ids[transaction_count] = id;
    strcpy(transaction_types[transaction_count], type);
    strcpy(transaction_categories[transaction_count], category);
    transaction_amounts[transaction_count] = amount;
    transaction_count++;

    printf("Transaction added successfully!\n");
}

// Function to view all transactions
void view_transactions() {
    if (transaction_count == 0) {
        printf("No transactions found.\n");
        return;
    }

    printf("\nID\tType\t\tCategory\tAmount\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < transaction_count; i++) {
        printf("%d\t%-10s\t%-10s\t%.2f\n",
               transaction_ids[i],
               transaction_types[i],
               transaction_categories[i],
               transaction_amounts[i]);
    }
}

// Function to delete a transaction
void delete_transaction() {
    int id, found = 0;

    printf("Enter the transaction ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < transaction_count; i++) {
        if (transaction_ids[i] == id) {
            // Shift all subsequent transactions
            for (int j = i; j < transaction_count - 1; j++) {
                transaction_ids[j] = transaction_ids[j + 1];
                strcpy(transaction_types[j], transaction_types[j + 1]);
                strcpy(transaction_categories[j], transaction_categories[j + 1]);
                transaction_amounts[j] = transaction_amounts[j + 1];
            }
            transaction_count--;
            found = 1;
            printf("Transaction deleted successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Transaction with ID %d not found.\n", id);
    }
}

// Function to generate a summary of income and expenses
void generate_summary() {
    float total_income = 0.0, total_expense = 0.0;

    for (int i = 0; i < transaction_count; i++) {
        if (strcmp(transaction_types[i], "Income") == 0) {
            total_income += transaction_amounts[i];
        } else if (strcmp(transaction_types[i], "Expense") == 0) {
            total_expense += transaction_amounts[i];
        }
    }

    printf("\n=== Financial Summary ===\n");
    printf("Total Income: %.2f\n", total_income);
    printf("Total Expense: %.2f\n", total_expense);
    printf("Net Savings: %.2f\n", total_income - total_expense);
}

// Function to set a budget for a category
void set_budget() {
    if (budget_count >= 100) {
        printf("Error: Maximum budget categories limit reached.\n");
        return;
    }

    char category[20];
    float amount;

    printf("Enter category to set budget for: ");
    scanf("%s", category);
    printf("Enter budget amount: ");
    scanf("%f", &amount);

    // Check if the category already exists
    for (int i = 0; i < budget_count; i++) {
        if (strcmp(budget_categories[i], category) == 0) {
            budget_amounts[i] = amount;
            printf("Budget for category '%s' updated successfully!\n", category);
            return;
        }
    }

    // Add a new budget
    strcpy(budget_categories[budget_count], category);
    budget_amounts[budget_count] = amount;
    budget_count++;
    printf("Budget for category '%s' set successfully!\n", category);
}

// Function to view budget status
void view_budget_status() {
    if (budget_count == 0) {
        printf("No budgets have been set.\n");
        return;
    }

    printf("\n=== Budget Status ===\n");
    printf("Category\tBudget\t\tSpent\n");
    printf("--------------------------------------\n");

    for (int i = 0; i < budget_count; i++) {
        float spent = 0.0;

        // Calculate total spent for the category
        for (int j = 0; j < transaction_count; j++) {
            if (strcmp(transaction_categories[j], budget_categories[i]) == 0 &&
                strcmp(transaction_types[j], "Expense") == 0) {
                spent += transaction_amounts[j];
            }
        }

        printf("%-10s\t%.2f\t\t%.2f\n",
               budget_categories[i],
               budget_amounts[i],
               spent);
    }
}
