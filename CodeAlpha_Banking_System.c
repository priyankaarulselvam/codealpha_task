#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int accNum;
    char holderName[50];
    float balance;
} Account;

const char* BANK_FILE = "accounts.txt";

void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

int main() {
    int choice;
    while(1) {
        printf("\n--- Bank Account Management System ---\n");
        printf("1. Create New Account\n2. Deposit Money\n3. Withdraw Money\n4. Balance Enquiry\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceEnquiry(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

void createAccount() {
    FILE *fp = fopen(BANK_FILE, "ab");
    if (!fp) { printf("File error!\n"); return; }
    
    Account acc;
    printf("Enter New Account Number: "); scanf("%d", &acc.accNum);
    printf("Enter Account Holder Name: "); scanf(" %[^\n]s", acc.holderName);
    printf("Enter Initial Deposit Amount: "); scanf("%f", &acc.balance);
    
    fwrite(&acc, sizeof(Account), 1, fp);
    fclose(fp);
    printf("Account created successfully!\n");
}

void deposit() {
    FILE *fp = fopen(BANK_FILE, "rb+");
    if (!fp) { printf("No accounts found!\n"); return; }
    
    int accNum, found = 0;
    float amount;
    printf("Enter Account Number: "); scanf("%d", &accNum);
    
    Account acc;
    while(fread(&acc, sizeof(Account), 1, fp)) {
        if(acc.accNum == accNum) {
            printf("Current Balance: %.2f\nEnter Deposit Amount: ", acc.balance);
            scanf("%f", &amount);
            
            if(amount > 0) {
                acc.balance += amount;
                fseek(fp, -sizeof(Account), SEEK_CUR);
                fwrite(&acc, sizeof(Account), 1, fp);
                printf("Deposit successful! New Balance: %.2f\n", acc.balance);
            } else {
                printf("Invalid deposit amount!\n");
            }
            found = 1;
            break;
        }
    }
    if(!found) printf("Account number not found.\n");
    fclose(fp);
}

void withdraw() {
    FILE *fp = fopen(BANK_FILE, "rb+");
    if (!fp) { printf("No accounts found!\n"); return; }
    
    int accNum, found = 0;
    float amount;
    printf("Enter Account Number: "); scanf("%d", &accNum);
    
    Account acc;
    while(fread(&acc, sizeof(Account), 1, fp)) {
        if(acc.accNum == accNum) {
            printf("Current Balance: %.2f\nEnter Withdrawal Amount: ", acc.balance);
            scanf("%f", &amount);
            
            if(amount > 0 && amount <= acc.balance) {
                acc.balance -= amount;
                fseek(fp, -sizeof(Account), SEEK_CUR);
                fwrite(&acc, sizeof(Account), 1, fp);
                printf("Withdrawal successful! Remaining Balance: %.2f\n", acc.balance);
            } else {
                printf("Insufficient funds or invalid amount!\n");
            }
            found = 1;
            break;
        }
    }
    if(!found) printf("Account number not found.\n");
    fclose(fp);
}

void balanceEnquiry() {
    FILE *fp = fopen(BANK_FILE, "rb");
    if (!fp) { printf("No accounts found!\n"); return; }
    
    int accNum, found = 0;
    printf("Enter Account Number: "); scanf("%d", &accNum);
    
    Account acc;
    while(fread(&acc, sizeof(Account), 1, fp)) {
        if(acc.accNum == accNum) {
            printf("\n--- Account Details ---\n");
            printf("Account Number: %d\n", acc.accNum);
            printf("Holder Name: %s\n", acc.holderName);
            printf("Current Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }
    if(!found) printf("Account number not found.\n");
    fclose(fp);
}