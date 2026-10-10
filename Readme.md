# Password Manager (C++ Console App)

A simple console-based password manager with user authentication, credential storage, encryption, and admin features.

## Features
- User registration & login
- Secure password storage (Caesar cipher)
- Add, view, search, edit, delete credentials
- Random password generator
- Admin user with view-all-users access
- Credentials sorted by last updated

---

## Files

### `main.cpp`
Entry point. Runs main loop:  
- Shows login/register menu when no user  
- Shows user dashboard after login  
- Routes to menu functions based on choice

### `Credential.cpp`
Defines `Credential` class:  
- Auto-incrementing ID  
- Stores name, username, encrypted password, category  
- Timestamps: created & last updated  
- `display()`: shows masked or decrypted password  
- Setters update `lastUpdated`

### `Encryption.cpp`
Implements basic encryption:  
- Caesar cipher with fixed shift = 5  
- `encrypt()` and `decrypt()` static methods

### `MenuSystem.cpp`
All interactive menus:  
- `displayMainMenu()`, `displayUserMenu()`  
- `addCredentialMenu()` – supports manual or generated password  
- `viewCredentialsMenu()` – sorted list, reveal password by ID  
- `searchCredentialsMenu()` – partial name match  
- `editCredentialMenu()` – username/password/category  
- `deleteCredentialMenu()` – by ID

### `PasswordGenerator.cpp`
Static utility:  
- Generates random password (default 12 chars)  
- Uses letters, digits, special symbols  
- Seeded with `time(0)`

### `PasswordManager.cpp`
Central controller:  
- Manages `vector<User*>`, `currentUser`  
- Default admin: `admin` / `admin123`  
- `registerUser()`, `login()`, `logout()`  
- Admin-only: `viewAllUsers()`

### `User.cpp`
User entity:  
- Stores username, plaintext password, admin flag  
- Owns `vector<Credential*>`  
- Methods: add, search, delete, sort credentials  
- `verifyPassword()` for login

---

## Build & Run
```bash
g++ main.cpp -o password_manager
./password_manager

## References
- https://en.wikipedia.org/wiki/Caesar_cipher
- https://www.geeksforgeeks.org/cpp/c-plus-plus/ 
- https://www.cplusplus.com/reference/vector/vector/
- https://www.learncpp.com/
- chat.openai.com (Brainstorming)
```

    