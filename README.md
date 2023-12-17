# Linear Algebra
【 NYCU 2022 Fall Semester 】
## Final Project - Matrices Applied in Cryptography

### I. Abstract

Many people use the same passwords for numerous accounts, which is very dangerous. Thus, we created an encoding program to solve this problem, and used some quantitative methods to evaluate our results.

### II. Introduction

Nowadays, most people have multiple accounts, yet with all passwords the same, because creating a new password is quite annoying and will be easily forgotten. However, using the same password across multiple accounts can lead to credential stuffing, which is unsafe. As a result, we came up with an idea to write a code that can convert our commonly used passwords into different passwords with higher security corresponding to the account’s name.
### III. Methods

Our approach is structured around the following key steps:

1. **Input Phase**: Users input the website name and their generally used password.
2. **Encryption Process**: The core of our system lies in the application of matrix multiplication for encryption.
3. **Output**: The result is a new, more secure password, distinct for each account based on the input parameters.
