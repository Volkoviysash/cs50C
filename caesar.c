#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool only_digits(string s);
void caesar (int k);

int main(int argc, string argv[])
{
if (argc == 2 && only_digits(argv[1]))
    {
    int key = atoi(argv[1]) % 26;
    if (key <= 0)
    {
        printf("Stupid key!\n");
        return 0;
    }
    else
    {
        caesar(key);
        return 0;
    }
    }
else
    {
    printf ("Usage: ./caesar key\n");
    return 1;
    }
}

bool only_digits(string str)
{
bool boolean;
int i = 0;
    while (str[i] != '\0')
    {
        if (isdigit(str[i]))
        {
            boolean = true;
            i++;
        }
        else
        {
            boolean = false;
            break;
        }
    }
return boolean;
}

void caesar (int k)
{
string plaintext = get_string("Enter the plain text: ");

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {            
        bool caps = (plaintext[i] >= 65 && plaintext[i] <= 91);
        if (tolower(plaintext[i]) >= 97 && tolower(plaintext[i]) <= 122)
        {         
         plaintext[i] = 97 + ((tolower(plaintext[i]) - 97 + k) % 26);                  
         if (caps)
        {
            plaintext[i] = toupper(plaintext[i]);
        }
        }
        else
        {
            plaintext[i] += 0;
        }

    }
printf("Cryptotext: %s\n", plaintext);
}
