
# 🏨 Hotel Management System (C Project)

A complete **Hotel Management System** built using **C**, showcasing practical usage of structures, file handling, menu-driven programming, and formatted console output.  
Customer records are saved in a binary file (`guests.dat`) to maintain persistent data across sessions.

---

## 📚 Table of Contents
- [Project Overview](#project-overview)  
- [Features](#features)  
- [Data Structure](#data-structure)  
- [How the System Works](#how-the-system-works)  
- [Room Types & Pricing](#room-types--pricing)  
- [Compilation & Execution](#compilation--execution)  
- [Project File Structure](#project-file-structure)  
- [Sample Output](#sample-output)  
- [Future Enhancements](#future-enhancements)  
- [Technologies Used](#technologies-used)  
- [Author](#author)

---

## 📌 Project Overview

This project is a hotel management system designed to handle:

- Customer check-in  
- Room assignment  
- Record search  
- Deletion of records  
- Billing at checkout  
- Real-time room availability  

All data is stored in **`guests.dat`** using binary file operations, making the system fast and persistent.

---

## ⭐ Features

### ✔ 1. Book Room (Check-In)
- Select from 3 room types:
  - Single Bed Room  
  - Double Bed Room  
  - Deluxe Room  
- Auto-generated:
  - Guest ID  
  - Room Number  
- Customer inputs include:
  - Name, Address, Phone, Email  
  - ID Number, Gender, Age  
  - Number of Guests, Days of Stay  

### ✔ 2. View Customer Records
Displays all customers in a formatted table with columns:



### ✔ 3. Search Customer
Searches for a customer by **Guest ID**  
Displays complete profile in table format.

### ✔ 4. Delete Customer Record
- Delete by Guest ID  
- Records shift automatically  
- Updated list saved to `guests.dat`

### ✔ 5. Room Availability
Shows how many rooms are left:
- 50 Single Rooms  
- 30 Double Rooms  
- 20 Deluxe Rooms  

### ✔ 6. Checkout & Bill Generation
Automatically calculates billing:
- Single Room → ₹800/day  
- Double Room → ₹1200/day  
- Deluxe Room → ₹2000/day  

After bill generation:
- Customer is removed from file  
- Room becomes available again  

---

## 🗂 Data Structure

Customer records are stored using this struct:

```c
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

