#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define MAX_USERS 100
#define MAX_MOVIES 10
#define MAX_SHOWTIMES 3
#define MAX_SEATS 50

void clearScreen() {
    system("cls");
}

int movieIndex, showtimeIndex, numSeats;

typedef struct {
    char title[100];
    int year;
    int ticketPrice;  // New field for ticket price
} Movie;

typedef struct {
    char time[20];
} Showtime;

typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct {
    int movieIndex;
    int showtimeIndex;
    int seatNumber;
    int numSeats;
    int totalCost;
    int totalTicketPrice;  // Added field for total ticket price
} Booking;

User users[MAX_USERS];
Movie movies[MAX_MOVIES];
Showtime showtimes[MAX_SHOWTIMES];
int seatAvailability[MAX_SHOWTIMES][MAX_SEATS][MAX_MOVIES] = {0};

int numUsers = 0;
int numMovies = 10;
int numShowtimes = 3;

void saveUserDataToFile() {
    FILE *file = fopen("user_data.txt", "w");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
}

void loadUserDataFromFile() {
    FILE *file = fopen("user_data.txt", "r");

    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // Initialize numUsers to 0 before reading data
    numUsers = 0;

    while (fscanf(file, "%s %s", users[numUsers].username, users[numUsers].password) == 2) {
        numUsers++;
        if (numUsers >= MAX_USERS) {
            printf("Maximum number of users reached.\n");
            break;
        }
    }

    fclose(file);
}

void Data() {
    system("COLOR E");

    strcpy(movies[0].title, "\x1b[32m.2001: A Space Odyssey \x1b[0m ");
    movies[0].year = 1968;
    movies[0].ticketPrice = 1000;

    strcpy(movies[1].title, "\x1b[32m.The Godfather \x1b[0m ");
    movies[1].year = 1972;
    movies[1].ticketPrice = 1050;

    strcpy(movies[2].title, "\x1b[32m.Citizen Kane \x1b[0m ");
    movies[2].year = 1941;
    movies[2].ticketPrice = 1060;

    strcpy(movies[3].title, "\x1b[32m.Jeanne Dielman, 23, Quai du Commerce, 1080 Bruxelles\x1b[0m ");
    movies[3].year = 1975;
    movies[3].ticketPrice = 1100;

    strcpy(movies[4].title, "\x1b[32m.Raiders of the Lost Ark \x1b[0m ");
    movies[4].year = 1981;
    movies[4].ticketPrice = 1300;

    strcpy(movies[5].title, "\x1b[32m.La Dolce Vita (1960) \x1b[0m ");
    movies[5].year = 1960;
    movies[5].ticketPrice = 1100;
    strcpy(movies[6].title, "\x1b[32m.Seven Samurai \x1b[0m ");
    movies[6].year = 1954;
    movies[6].ticketPrice = 1030;

    strcpy(movies[7].title, "\x1b[32m.In the Mood for Love \x1b[0m ");
    movies[7].year = 2000;
    movies[7].ticketPrice = 1050;

    strcpy(movies[8].title, "\x1b[32m.There Will Be Blood \x1b[0m ");
    movies[8].year = 2007;
    movies[8].ticketPrice = 1000;;

    strcpy(movies[9].title, "\x1b[32m.Singin’ in the Rain \x1b[0m  ");
    movies[9].year = 1952;
    movies[9].ticketPrice = 8000;


    // Add other movies similarly

    strcpy(showtimes[0].time, "9.00am - 12.00 pm");
    strcpy(showtimes[1].time, "1.00pm - 4.00 pm");
    strcpy(showtimes[2].time, "6.00pm - 10.00 pm");
}

void registerUser() {
    if (numUsers < MAX_USERS) {
        printf("Enter username: ");
        scanf("%s", users[numUsers].username);
        printf("Enter password: ");
        scanf("%s", users[numUsers].password);
        numUsers++;
        clearScreen();

        saveUserDataToFile();

        printf("\x1b[32m=============================================\x1b[0m \n");
        printf("\x1b[32m=====     User registered successfully!     ===\x1b[0m\n");
        printf("\x1b[32m=============================================\x1b[0m \n");
    } else {
        printf("\x1b[31m=============================================\x1b[0m\n");
        printf("\x1b[31m===      Maximum number of users reached.  ==== \x1b[0m \n");
        printf("\x1b[31m=============================================\x1b[0m\n");
    }
}

int authenticateUser(char username[50], char password[50]) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i; // Return the index of the authenticated user
        }
    }
    return -1; // Return -1 if authentication fails
}
void displayMovies() {
    for (int i = 0; i < numMovies; i++) {
        printf("%d. %s (%d) - Ticket Price: %d taka\n", i + 1, movies[i].title, movies[i].year, movies[i].ticketPrice);
    }
}

void displayShowtimes() {
    for (int i = 0; i < numShowtimes; i++) {
        printf("%d. %s\n", i+1, showtimes[i].time);
    }
}


void bookTicket(int userIndex) {
    int movieIndex, showtimeIndex, numSeats;

    // Display available movies
    printf("Available Movies:\n");
    for (int i = 0; i < numMovies; i++) {
        printf("%d. %s (%d) - Ticket Price: %d taka\n", i + 1, movies[i].title, movies[i].year, movies[i].ticketPrice);
    }

    // Get user input for movie selection
    printf("Enter movie number: ");
    scanf("%d", &movieIndex);
    if (movieIndex < 1 || movieIndex > numMovies) {
        printf("Invalid movie selection.\n");
        return;
    }

    // Display available showtimes
    printf("\nAvailable Showtimes:\n");
    for (int i = 0; i < numShowtimes; i++) {
        printf("%d. %s\n", i + 1, showtimes[i].time);
    }

    // Get user input for showtime selection
    printf("Enter showtime number: ");
    scanf("%d", &showtimeIndex);
    if (showtimeIndex < 1 || showtimeIndex > numShowtimes) {
        printf("Invalid showtime selection.\n");
        return;
    }

    // Get user input for the number of seats
    printf("Enter the number of seats: ");
    scanf("%d", &numSeats);
    if (numSeats < 1 || numSeats > MAX_SEATS) {
        printf("Invalid number of seats.\n");
        return;
    }

    // Check if all selected seats are available
    int seats[numSeats];
    printf("Enter seat numbers (space-separated): ");
    for (int i = 0; i < numSeats; i++) {
        scanf("%d", &seats[i]);
        if (seats[i] < 1 || seats[i] > MAX_SEATS || seatAvailability[showtimeIndex - 1][seats[i] - 1][movieIndex - 1] == 1) {
            printf("Invalid or already booked seat number.\n");
            return;
        }
    }

    // Check if any selected seat is already booked for the given showtime
    for (int i = 0; i < numSeats; i++) {
        if (seatAvailability[showtimeIndex - 1][seats[i] - 1][movieIndex - 1] == 1) {
            printf("Seat %d is already booked for the selected showtime.\n", seats[i]);
            return;
        }
    }

    // Calculate total cost and total ticket price
    int ticketPrice = movies[movieIndex - 1].ticketPrice;
    int totalCost = ticketPrice * numSeats;
    int totalTicketPrice = ticketPrice * numSeats;

    // Book the selected seats
    for (int i = 0; i < numSeats; i++) {
        seatAvailability[showtimeIndex - 1][seats[i] - 1][movieIndex - 1] = 1;
    }

    // Display ticket summary
    printf("Movie: %s\n", movies[movieIndex - 1].title);
    printf("Showtime: %s\n", showtimes[showtimeIndex - 1].time);
    printf("Seat Numbers: ");
    for (int i = 0; i < numSeats; i++) {
        printf("%d ", seats[i]);
    }
    printf("\n");

    printf("Ticket Price per Seat: %d taka\n", ticketPrice);
    printf("Total Cost: %d taka\n", totalCost);
    printf("Total Ticket Price: %d taka\n", totalTicketPrice);

    // Update booking details
    Booking booking;
    booking.movieIndex = movieIndex;
    booking.showtimeIndex = showtimeIndex;
    booking.numSeats = numSeats;
    booking.totalCost = totalCost;
    booking.totalTicketPrice = totalTicketPrice;

    // If a user is logged in, you can store the booking in a user-specific array
    if (userIndex != -1) {
        // Store the booking details in a user-specific array or file
        // Example: userBookings[userIndex] = booking;
    }
}

void forgetPassword() {
    char username[50];
    int userIndex;

    printf("Enter your username: ");
    scanf("%s", username);

    // Find the user in the array
    for (userIndex = 0; userIndex < numUsers; userIndex++) {
        if (strcmp(users[userIndex].username, username) == 0) {
            break;
        }
    }

    if (userIndex < numUsers) {
        // User found, generate and display a temporary password
        char tempPassword[50];
        // You can use any method to generate a temporary password, for example, a random string
        strcpy(tempPassword, "TempPassword123");

        printf("Your temporary password : %s\n", tempPassword);

        // Prompt the user to log in with the temporary password and change it
        printf("Please log in with the temporary password and change it.\n");
    } else {
        printf("User not found.\n");
    }
}

void changePassword(int userIndex) {
    char newPassword[50];

    printf("Enter your new password: ");
    scanf("%s", newPassword);

    // Update the user's password
    strcpy(users[userIndex].password, newPassword);

    // Save the updated user data to the file
    saveUserDataToFile();

    printf("Password changed successfully.\n");
}





void displayBookedTickets() {
    // Display booked tickets
printf("=============================================\n");
printf("=====       Booked Seat Summary       =====\n");
printf("=============================================\n");

for (int i = 0; i < numShowtimes; i++) {
    printf("Showtime %d:\n", i + 1);
    for (int j = 0; j < MAX_SEATS; j++) {
        for (int k = 0; k < numMovies; k++) {
            if (seatAvailability[i][j][k] == 1) {
                printf("Seat %d is booked.\n", j + 1);
            }
        }
    }
}

printf("=============================================\n");

}
void displaySeatSummary() {
    printf("=============================================\n");
    printf("\x1b[32m====       Seat Availability !     ====\x1b[0m\n");
    printf("=============================================\n");

    for (int i = 0; i < numShowtimes; i++) {
        printf("Showtime %d:\n", i + 1);
        for (int j = 0; j < MAX_SEATS; j++) {
            for (int k = 0; k < numMovies; k++) {
                if (seatAvailability[i][j][k] == 1) {
                    printf("Seat %d: Booked for %s\n", j + 1, movies[k].title);
                }
            }
        }
        printf("=============================================\n");
    }
}




void displayMenu() {
    printf("\n");
    printf("=============================================\n");
    printf("=====       Welcome to the Movie App    =====\n");
    printf("=============================================\n");
    printf("=  \x1b[33m1. Register\x1b[0m                          =\n"); // Yellow color for option 1
    printf("=  \x1b[34m2. Login\x1b[0m                             =\n"); // Blue color for option 2
    printf("=  \x1b[35m3. Display Movies And Price List\x1b[0m     =\n"); // Magenta color for option 3
    printf("=  \x1b[36m4. Display Showtimes\x1b[0m                 =\n"); // Cyan color for option 4
    printf("=  \x1b[32m5. Book Ticket\x1b[0m                       =\n"); // Green color for option 5
    printf("=  \x1b[33m6. Booked Tickets\x1b[0m                    =\n"); // Red color for option 6
    printf("=  \x1b[34m7. Seat Summary\x1b[0m                      =\n");// Blue color for option 7
    printf("=  \x1b[34m8. ForgetPassword\x1b[0m                      =\n");// Blue color for option 7
    printf("=  \x1b[34m9. ChangePassword\x1b[0m                      =\n");// Blue color for option 7
    printf("=  \x1b[31m10. Quit\x1b[0m                              =\n");//Red color for option 8
    printf("=============================================\n");

}

int main() {
    Data();
    loadUserDataFromFile();

    int choice;
    char username[50];
    char password[50];
    int currentUserIndex = -1;

    do {
        displayMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearScreen();

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                clearScreen();
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                currentUserIndex = authenticateUser(username, password);
                clearScreen();
                if (currentUserIndex != -1) {
                    printf("=============================================\n");
                    printf("\x1b[32m=             Login Successfully            =\n");
                    printf("=============================================\n");
                } else {
                    printf("=============================================\n");
                    printf("x1b[33m===   Invalid username or password         ===\n");
                    printf("=============================================\n");
                }
                break;
            case 3:
                clearScreen();
                displayMovies();
                break;
            case 4:
                clearScreen();
                displayShowtimes();
                break;
            case 5:
                clearScreen();
                if (currentUserIndex != -1) {
                    bookTicket(currentUserIndex);
                } else {
                    printf("=============================================\n");
                    printf("\x1b[33m  =====   Login First to Book Ticket   =====  \n");
                    printf("=============================================\n");
                }
                break;
            case 6:
                clearScreen();
                displayBookedTickets();
                break;
            case 7:
                clearScreen();
                displaySeatSummary();
                break;


            case 8:
                clearScreen();
                forgetPassword();
                break;
            case 9:
                clearScreen();
                if (currentUserIndex != -1) {
                    changePassword(currentUserIndex);
                } else {
                    printf("=============================================\n");
                    printf("\x1b[33m  =====   Login First to Change Password   =====  \n");
                    printf("=============================================\n");
                }
                break;
            case 10:
                clearScreen();
                printf("Exiting...\n");
                break;
            default:
                printf("=============================================\n");
                printf("x1b[33m=    Invalid choice. Please try again.       =\n");
                printf("=============================================\n");
        }
    } while (choice != 11);

    return 0;
}

