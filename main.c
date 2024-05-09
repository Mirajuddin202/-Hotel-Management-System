#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 100
#define MAX_NAME_LENGTH 50

// Structure to hold guest information
struct Guest {
    char name[MAX_NAME_LENGTH];
    int roomNumber;
};

// Structure to hold room information
struct Room {
    int roomNumber;
    int isOccupied;
};

// Function prototypes
void initializeRooms(struct Room rooms[], int numRooms);
void addGuest(struct Guest guests[], int *numGuests);
void displayGuests(struct Guest guests[], int numGuests);
void displayAvailableRooms(struct Room rooms[], int numRooms);
void bookRoom(struct Room rooms[], struct Guest guests[], int *numGuests, int numRooms);
int findRoomIndex(struct Room rooms[], int numRooms, int roomNumber);

int main() {
    struct Room rooms[MAX_ROOMS];
    struct Guest guests[MAX_ROOMS];
    int numRooms, numGuests, choice;

    printf("Welcome to the Hotel Management System!\n");
    printf("Enter the number of rooms in the hotel: ");
    scanf("%d", &numRooms);

    initializeRooms(rooms, numRooms);
    numGuests = 0;

    do {
        printf("\nHotel Management Menu:\n");
        printf("1. Add Guest\n");
        printf("2. Display Guests\n");
        printf("3. Display Available Rooms\n");
        printf("4. Book Room\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addGuest(guests, &numGuests);
                break;
            case 2:
                displayGuests(guests, numGuests);
                break;
            case 3:
                displayAvailableRooms(rooms, numRooms);
                break;
            case 4:
                bookRoom(rooms, guests, &numGuests, numRooms);
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}

// Initialize room status
void initializeRooms(struct Room rooms[], int numRooms) {
    for (int i = 0; i < numRooms; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isOccupied = 0;
    }
}

// Add a guest
void addGuest(struct Guest guests[], int *numGuests) {
    if (*numGuests < MAX_ROOMS) {
        printf("Enter guest name: ");
        scanf("%s", guests[*numGuests].name);
        (*numGuests)++;
        printf("Guest added successfully!\n");
    } else {
        printf("Cannot add more guests. Maximum limit reached.\n");
    }
}

// Display list of guests
void displayGuests(struct Guest guests[], int numGuests) {
    printf("Guests in the hotel:\n");
    for (int i = 0; i < numGuests; i++) {
        printf("%d. %s\n", i + 1, guests[i].name);
    }
}

// Display available rooms
void displayAvailableRooms(struct Room rooms[], int numRooms) {
    printf("Available rooms:\n");
    for (int i = 0; i < numRooms; i++) {
        if (!rooms[i].isOccupied) {
            printf("%d\n", rooms[i].roomNumber);
        }
    }
}

// Book a room for a guest
void bookRoom(struct Room rooms[], struct Guest guests[], int *numGuests, int numRooms) {
    int roomNumber;
    printf("Enter room number to book: ");
    scanf("%d", &roomNumber);

    int roomIndex = findRoomIndex(rooms, numRooms, roomNumber);
    if (roomIndex != -1) {
        if (!rooms[roomIndex].isOccupied) {
            rooms[roomIndex].isOccupied = 1;
            guests[*numGuests - 1].roomNumber = roomNumber;
            printf("Room %d booked successfully for guest %s\n", roomNumber, guests[*numGuests - 1].name);
        } else {
            printf("Room %d is already occupied.\n", roomNumber);
        }
    } else {
        printf("Room %d does not exist.\n", roomNumber);
    }
}

// Find the index of a room in the rooms array
int findRoomIndex(struct Room rooms[], int numRooms, int roomNumber) {
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].roomNumber == roomNumber) {
            return i;
        }
    }
    return -1; // Room not found
}
