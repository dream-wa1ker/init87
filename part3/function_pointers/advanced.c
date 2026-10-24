// name : number-ops.c
// date : 2026-10-21
// std  : C 23 standard

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

enum status {
    OK  = 0,
    ERR = -1,
};

// ---------------------------- declarations ----------------------------
bool is_armstrong(int num);
int  fact(int num);
int  fib(int num);
void gen_fib(int num);
int  sum_digits(int num);
int  reverse_num(int num);
bool is_palindrome(int num);
bool is_prime(int num);
bool is_perfect(int num);
int  gcd(int a, int b);
void panic(int code, char *msg);


/*
Yes, it’s called a tagged union (or discriminated union). It’s how you fake a sum type in C: the tag says which member is live, and the union stores them in the same space.
*/
// ----------------------------- dispatcher -----------------------------
enum kind { K_BOOL, K_INT, K_INT2, K_VOID, K_EXIT };

struct command {
    const char *label;  // menu text
    const char *noun;   // used in the output sentence
    enum kind   kind;   // which signature the function has
    union {
        bool (*pred)(int);         // K_BOOL : is_*(int)
        int  (*unary)(int);        // K_INT  : fact, sum_digits, reverse_num
        int  (*binary)(int, int);  // K_INT2 : gcd
        void (*action)(int);       // K_VOID : gen_fib
    };
};

static int read_int(const char *prompt) {
    int n;
    printf("%s", prompt);
    if (scanf("%d", &n) != 1) {
        panic(ERR, "Invalid input");
    }
    return n;
}

// menu number = index + 1
static const struct command commands[] = {
    { "Check Armstrong number",    "an Armstrong number", K_BOOL, .pred   = is_armstrong  },
    { "Check prime number",        "prime",               K_BOOL, .pred   = is_prime      },
    { "Find GCD of two numbers",   "GCD",                 K_INT2, .binary = gcd           },
    { "Find factorial",            "factorial",           K_INT,  .unary  = fact          },
    { "Check palindrome number",   "a palindrome",        K_BOOL, .pred   = is_palindrome },
    { "Sum of digits",             "sum of digits",       K_INT,  .unary  = sum_digits    },
    { "Check perfect number",      "a perfect number",    K_BOOL, .pred   = is_perfect    },
    { "Reverse a number",          "reverse",             K_INT,  .unary  = reverse_num   },
    { "Generate Fibonacci series", NULL,                  K_VOID, .action = gen_fib       },
    { "Exit",                      NULL,                  K_EXIT                          },
};

// number of commands
constexpr size_t NCMDS = sizeof(commands) / sizeof(commands[0]);

static void run(const struct command *c) {
    int a, b;

    switch (c->kind) {
        case K_BOOL:
            a = read_int("Enter a number: ");
            printf("%d is %s%s.\n", a, c->pred(a) ? "" : "not ", c->noun);
            break;

        case K_INT:
            a = read_int("Enter a number: ");
            printf("The %s of %d is %d.\n", c->noun, a, c->unary(a));
            break;

        case K_INT2:
            printf("Enter two numbers: ");
            if (scanf("%d %d", &a, &b) != 2) panic(ERR, "Invalid input");
            printf("The %s of %d and %d is %d.\n", c->noun, a, b, c->binary(a, b));
            break;

        case K_VOID:
            c->action(read_int("Enter the number of terms: "));
            break;

        case K_EXIT:
            puts("Exiting...");
            exit(EXIT_SUCCESS);
    }
}

// ------------------------------- main ---------------------------------
int main(void) {
    while (1) {
        puts("\n-------------------- Number Operations --------------------\n");
        for (size_t i = 0; i < NCMDS; i++) {
            printf("%zu. %s\n", i + 1, commands[i].label);
        }
        puts("");

        int choice = read_int("Enter your choice: ");
        puts("");

        if (choice < 1 || (size_t)choice > NCMDS) {
            puts("Invalid choice. Try again.");
        } else {
            run(&commands[choice - 1]);
        }
    }
    return EXIT_SUCCESS;
}

// --------------------------- definitions ------------------------------
bool is_armstrong(int num) {
    if (num <= 0) {
        fprintf(stderr, "[error] : num = %d, provide a positive integer\n", num);
        return false;
    }

    int temp = num;
    int digits = 0;
    while (temp > 0) {
        digits++;
        temp /= 10;
    }

    temp = num;
    int sum = 0;
    while (temp > 0) {
        int digit = temp % 10;
        sum += (int)pow(digit, digits);
        temp /= 10;
    }

    return num == sum;
}

int fact(int num) {
    if (num < 0) {
        fprintf(stderr, "[error] : num = %d, provide a non negative integer\n", num);
        return ERR;
    }
    return (num == 0 || num == 1) ? 1 : num * fact(num - 1);
}

// 1 1 2 3 5 ..  fib(n) = fib(n - 1) + fib(n - 2)
int fib(int num) {
    if (num <= 0) {
        fprintf(stderr, "[error] : num = %d, provide a positive integer\n", num);
        return ERR;
    }
    return (num == 1 || num == 2) ? 1 : fib(num - 1) + fib(num - 2);
}

void gen_fib(int num) {
    printf("The first %d numbers of the fib series are : ", num);
    for (int i = 1; i <= num; i++) {
        printf("%d ", fib(i));
    }
    puts("");
}

int sum_digits(int num) {
    if (num <= 0) {
        fprintf(stderr, "[error] : num = %d, provide a positive integer\n", num);
        return ERR;
    }
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int reverse_num(int num) {
    if (num <= 0) {
        fprintf(stderr, "[error] : num = %d, provide a positive integer\n", num);
        return ERR;
    }
    int rev = 0;
    while (num > 0) {
        rev = (rev * 10) + (num % 10);
        num /= 10;
    }
    return rev;
}

bool is_palindrome(int num) {
    if (num <= 0) {
        fprintf(stderr, "[error] : num = %d, provide a positive integer\n", num);
        return false;
    }
    return num == reverse_num(num);
}

int gcd(int a, int b) {
    int base = (a > b) ? b : a;
    int gcd = 0;
    for (int i = 1; i <= base; i++) {
        if (a % i == 0 && b % i == 0) {
            gcd = i;
        }
    }
    return gcd;
}

bool is_perfect(int num) {
    int sum = 0;
    for (int i = 1; i < num; i++) {
        if (num % i == 0) sum += i;
    }
    return sum == num;
}

// testing up to the square root is enough
bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void panic(int code, char *msg) {
    fprintf(stderr, "[error] : %s\n", msg);
    exit(code);
}
