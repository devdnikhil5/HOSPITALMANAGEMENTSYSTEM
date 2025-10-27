# 🏥 Hospital Management System (C++)

A simple **Hospital Management System** built using **C++**, featuring **role-based access control** for Admin, Doctor, and Receptionist.  
This program manages patients' records and supports secure login and registration.

---

# 🚀 Features

# 👤 User Management
- Register users with custom roles: **Admin**, **Doctor**, or **Receptionist**
- Login with stored credentials (saved in `users.txt`)
- Role-based access menus

# 🏥 Patient Management
- Add new patient records
- Auto-generate unique Patient IDs (based on disease type)
- View all patients
- Search patient by ID
- Delete patient record (Admin only)
- All records are stored persistently in `hospital.txt`

---

# 🧠 Roles and Permissions

| Role | Permissions |
|------|--------------|
| **Admin** | Add, View, Search, Delete patients |
| **Doctor** | View and Search patients |
| **Receptionist** | Add and View patients |
