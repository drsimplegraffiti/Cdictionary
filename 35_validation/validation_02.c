#include <ctype.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SALT_LEN 16
#define HASH_LEN 32 // 32 bytes for SHA-256 output

// unsigned char is used instead of char because:
// - crypto functions expect raw bytes (0-255)
// - plain char can be signed (-128 to 127) on some platforms
// - unsigned char guarantees no sign extension when working with binary data
void hash_pin(const char *pin, const unsigned char *salt,
              unsigned char *out_hash) {
  // EVP_MD_CTX is an opaque struct that holds the hashing state
  EVP_MD_CTX *ctx = EVP_MD_CTX_new();

  // get SHA256 digest method by name
  const EVP_MD *md = EVP_get_digestbyname("SHA256");

  // initialize the digest context with SHA256
  EVP_DigestInit_ex(ctx, md, NULL);

  // feed salt first then pin into the hash
  // salting prevents rainbow table attacks:
  // same pin + different salt = different hash every time
  EVP_DigestUpdate(ctx, salt, SALT_LEN);
  EVP_DigestUpdate(ctx, pin, strlen(pin));

  // finalize and write result into out_hash
  // NULL = we dont need the length returned, HASH_LEN is always 32
  EVP_DigestFinal_ex(ctx, out_hash, NULL);

  // always free the context to avoid memory leak
  EVP_MD_CTX_free(ctx);
}

void input_required(const char *label, char *buf, int size) {
  do {
    printf("%s: ", label);
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = '\0'; // strip trailing newline fgets leaves
    if (buf[0] == '\0') {
      printf("%s cannot be empty, try again\n", label);
    }
  } while (buf[0] == '\0');
}

void input_email(char *buf, int size) {
  do {
    printf("Enter email: ");
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (buf[0] == '\0') {
      printf("email cannot be empty, try again\n");
    } else if (strchr(buf, '@') == NULL) {
      // strchr returns NULL if @ not found in string
      printf("email must contain @, try again\n");
      buf[0] = '\0'; // reset so loop continues
    }
  } while (buf[0] == '\0');
}

// needed for pin hash: sudo apt-get install libssl-dev
// compile with: gcc main.c -o main -lssl -lcrypto
void input_pin(char *buf, int size) {
  int valid;
  do {
    valid = 1; // assume valid until proven otherwise

    printf("Enter pin (4 digits only): ");
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = '\0';

    if (buf[0] == '\0') {
      printf("pin cannot be empty, try again\n");
      valid = 0;
    } else if (strlen(buf) != 4) {
      // strlen counts characters up to \0
      // buf is pin[6] (5 chars + \0) so fgets can read 5 chars
      // if user types 12345, strlen = 5, != 4 catches it
      // if buf were pin[5], fgets silently truncates to 4 and check never fires
      printf("pin must be exactly 4 digits, try again\n");
      buf[0] = '\0';
      valid = 0;
    } else {
      // loop through every character and check if digit
      // isdigit() from <ctype.h> returns non-zero if '0'-'9', zero otherwise
      for (int i = 0; buf[i] != '\0'; i++) {
        if (!isdigit(buf[i])) {
          printf("pin must contain digits only, try again\n");
          buf[0] = '\0';
          valid = 0;
          break;
        }
      }
    }
  } while (!valid);
}

int main() {
  char name[90];
  char email[90];
  char pin[6]; // 5 chars + \0 so we can detect if user typed too many digits

  input_required("Enter name", name, sizeof(name));
  input_email(email, sizeof(email));
  input_pin(pin, sizeof(pin));

  // unsigned char because salt and hash are raw binary data not text
  // unsigned char = 1 byte, values 0 to 255
  // char = 1 byte, values -128 to 127 (signed on most platforms)
  unsigned char salt[SALT_LEN];
  unsigned char hash[HASH_LEN];

  // 1. generate a random cryptographic salt
  // RAND_bytes fills buffer with cryptographically strong random bytes
  // returns 1 on success, 0 or -1 on failure
  if (RAND_bytes(salt, SALT_LEN) != 1) {
    printf("error generating salt\n");
    return 1;
  }

  // 2. hash the pin with the salt
  hash_pin(pin, salt, hash);

  // print hash as hex so it is readable
  // %02x = print as 2-digit hex, pad with 0 if needed e.g. 5 -> 05
  printf("\nname:  %s\nemail: %s\n", name, email);
  printf("pin hash: ");
  for (int i = 0; i < HASH_LEN; i++) {
    // %:02x broken down:
    // %    -- format specifier start
    // 0    -- pad with zeros (not spaces)
    // 2    -- minimum 2 characters wide
    // x    -- print as hexadecimal
    printf("%02x", hash[i]);
  }
  printf("\n");

  return 0;
}

// gcc main.c -o main -lssl -lcrypto && ./main
