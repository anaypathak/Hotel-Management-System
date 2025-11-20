#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define DATAFILE "guests.dat"
#define MAX 100

struct Guest {
    int guestId;
    int roomNo;
    long idNumber;
    int numberofguest;
    char name[50];
    char address[100];
    char phone[15];
    char email[50];
    char typeOfRoom[20];
    char gender;
    int age;
    int days;
    float bill;
};

/* ---------- Helper Functions ---------- */
void choicemessage(int choice) {
    char *msgs[] = {
        "", "Book Room (Check In)", "View Customer Record", "Search Customer",
        "Edit Customer Record", "Delete Customer Record",
        "Room Availability", "Generate Bill (Check Out)", "Exit"
    };
    if (choice >= 1 && choice <= 8)
        printf("\n==== %s ====\n", msgs[choice]);
}


int countGuests() {
    FILE *fp = fopen(DATAFILE, "rb");
    if (!fp) return 0;
    fseek(fp, 0, SEEK_END);
    int count = ftell(fp) / sizeof(struct Guest);
    fclose(fp);
    return count;
}

int readAllGuests(struct Guest guests[], int max) {
    FILE *fp = fopen(DATAFILE, "rb");
    if (!fp) return 0;
    int count = fread(guests, sizeof(struct Guest), max, fp);
    fclose(fp);
    return count;
}

void saveAllGuests(struct Guest guests[], int count) {
    FILE *fp = fopen(DATAFILE, "wb");
    if (!fp) return;
    fwrite(guests, sizeof(struct Guest), count, fp);
    fclose(fp);
}

void addGuest(struct Guest g) {
    FILE *fp = fopen(DATAFILE, "ab");
    if (!fp) return;
    fwrite(&g, sizeof(struct Guest), 1, fp);
    fclose(fp);
}

/* ---------- Table Display Helpers ---------- */
void printTableHeader() {
    printf("+-------+--------------------+------------+------------------+------+-------+-----+------+-----------------+-----------------------------+\n");
    printf("| GID   | Name               | Room No    | Room Type        | Days | Guest | GDR | Age  | Phone           | Email                       |\n");
    printf("+-------+--------------------+------------+------------------+------+-------+-----+------+-----------------+-----------------------------+\n");
}

void printGuestRow(struct Guest g) {
    printf("| %-5d | %-18s | %-10d | %-16s | %-4d | %-5d | %-3c | %-4d | %-15s | %-27s |\n",
           g.guestId, g.name, g.roomNo, g.typeOfRoom,
           g.days, g.numberofguest, g.gender, g.age,
           g.phone, g.email);
}

void printTableFooter() {
    printf("+-------+--------------------+------------+------------------+------+-------+-----+------+-----------------+-----------------------------+\n");
}


int main() {
    srand((unsigned)time(NULL));
    int choice;
    int singleRooms = 50, doubleRooms = 30, deluxeRooms = 20;

    while (1) {
        printf("\n========= HOTEL MANAGEMENT SYSTEM =========\n");
        printf("1. Book Room (Check In)\n");
        printf("2. View Customer Record\n");
        printf("3. Search Customer\n");
        printf("4. Edit Customer Record\n");
        printf("5. Delete Customer Record\n");
        printf("6. Room Availability\n");
        printf("7. Generate Bill (Check Out)\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); continue; }

        switch (choice) {
        case 1: {
            choicemessage(choice);
            struct Guest g;
            int roomChoice;
            printf("Select Room Type:\n1. Single Bed Room\n2. Double Bed Room\n3. Deluxe Room\nChoice: ");
            scanf("%d", &roomChoice);

            int totalGuests = countGuests();
            g.guestId = totalGuests + 1;

            if (roomChoice == 1 && singleRooms > 0) {
                strcpy(g.typeOfRoom, "Single Bed Room");
                g.roomNo = 100 + g.guestId;
                singleRooms--;
            } else if (roomChoice == 2 && doubleRooms > 0) {
                strcpy(g.typeOfRoom, "Double Bed Room");
                g.roomNo = 200 + g.guestId;
                doubleRooms--;
            } else if (roomChoice == 3 && deluxeRooms > 0) {
                strcpy(g.typeOfRoom, "Deluxe Room");
                g.roomNo = 300 + g.guestId;
                deluxeRooms--;
            } else {
                printf(" Selected room type not available!\n");
                break;
            }

            printf("Enter Name: "); scanf(" %[^\n]", g.name);
            printf("Enter Address: "); scanf(" %[^\n]", g.address);
            printf("Enter Phone: "); scanf(" %[^\n]", g.phone);
            printf("Enter Email: "); scanf(" %[^\n]", g.email);
            printf("Enter Days of Stay: "); scanf("%d", &g.days);
            printf("Enter Gov ID Number: "); scanf("%ld", &g.idNumber);
            printf("Enter No. of Guests: "); scanf("%d", &g.numberofguest);
            printf("Enter Gender (M/F): "); scanf(" %c", &g.gender);
            printf("Enter Age: "); scanf("%d", &g.age);

            addGuest(g);

            printf("\n Room booked successfully!\n");
            printf("\n--- Booking Details ---\n");
            printTableHeader();
            printGuestRow(g);
            printTableFooter();
            break;
        }

        case 2: {
            choicemessage(choice);
            struct Guest guests[MAX];
            int count = readAllGuests(guests, MAX);
            if (count == 0) {
                printf("No customers found.\n");
                break;
            }
            printTableHeader();
            for (int i = 0; i < count; i++)
                printGuestRow(guests[i]);
            printTableFooter();
            printf("Total Customers: %d\n", count);
            break;
        }

        case 3: {
            choicemessage(choice);
            int id;
            printf("Enter Guest ID to search: ");
            scanf("%d", &id);
            struct Guest guests[MAX];
            int count = readAllGuests(guests, MAX);
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (guests[i].guestId == id) {
                    printf("\nGuest found:\n");
                    printTableHeader();
                    printGuestRow(guests[i]);
                    printTableFooter();
                    found = 1;
                    break;
                }
            }
            if (!found) printf(" Guest ID not found!\n");
            break;
        }

        case 5: {
            choicemessage(choice);
            int delid;
            printf("Enter Guest ID to delete: ");
            scanf("%d", &delid);
            struct Guest guests[MAX];
            int count = readAllGuests(guests, MAX);
            int found = -1;
            for (int i = 0; i < count; i++)
                if (guests[i].guestId == delid) found = i;

            if (found != -1) {
                for (int i = found; i < count - 1; i++)
                    guests[i] = guests[i + 1];
                count--;
                saveAllGuests(guests, count);
                printf(" Record deleted successfully!\n");
            } else {
                printf(" Guest not found.\n");
            }
            break;
        }

        case 6: {
            choicemessage(choice);
            printf("Available Rooms:\n");
            printf("Single: %d | Double: %d | Deluxe: %d\n", singleRooms, doubleRooms, deluxeRooms);
            break;
        }

        case 7:
            choicemessage(choice);
            {
                int checkoutId;
                printf("Enter Guest ID for checkout: ");
                scanf("%d", &checkoutId);
                struct Guest guests[MAX];
                int count = readAllGuests(guests, MAX);
                int found = -1;
                for (int i = 0; i < count; i++)
                    if (guests[i].guestId == checkoutId) found = i;

                if (found != -1) {
                    struct Guest g = guests[found];
                    float ratePerDay;
                    if (strcmp(g.typeOfRoom, "Single Bed Room") == 0)
                        ratePerDay = 800.0;
                    else if (strcmp(g.typeOfRoom, "Double Bed Room") == 0)
                        ratePerDay = 1200.0;
                    else
                        ratePerDay = 2000.0;

                    g.bill = ratePerDay * g.days;
                    printf("\n--- Bill Details ---\n");
                    printTableHeader();
                    printGuestRow(g);
                    printTableFooter();
                    printf("Total Bill: Rs %.2f\n", g.bill);

                    // Remove guest after checkout
                    for (int i = found; i < count - 1; i++)
                        guests[i] = guests[i + 1];
                    count--;
                    saveAllGuests(guests, count);
                    printf(" Checkout successful!\n");
                } else {
                    printf(" Guest not found.\n");
                }
            }
            break;

        case 8:
            printf("\nExiting... Thank you for using the Hotel System!\n");
            exit(0);

        default:
            printf("Invalid option! Try again.\n");
        }
    }
    return 0;
}
