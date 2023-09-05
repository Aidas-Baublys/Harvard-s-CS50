#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

bool valid(string password)
{
    bool reqs[] = {false, false, false, false};

    int length = strlen(password);

    for (int i = 0; i < length; i++)
    {
        if (password[i] > 64 && password[i] < 91)
        {
            reqs[0] = true;
        }

        if (password[i] > 96 && password[i] < 123)
        {
            reqs[1] = true;
        }

        if (password[i] > 47 && password[i] < 58)
        {
            reqs[2] = true;
        }

        if (password[i] > 32 && password[i] < 48)
        {
            reqs[3] = true;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (!reqs[i])
        {
            return false;
        }
    }

    return true;
}
