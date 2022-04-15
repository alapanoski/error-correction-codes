#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/**
 * To check whether the position is a parity bit position.
 * Parity bit position occurs at positions that are a power of 2.
 */
bool is_parity_bit_position(int n)
{
    const int MAX_MESSAGE_SIZE = (int)(pow(2, sizeof(n) * 8) / 2);
    const int MAX_PARITY_POSITION = (int)(pow(2, sizeof(n) * 8) / 2);

    if (n == 0)
    {
        return true;
    }

    for (int i = 0; i <= n; i++)
    {
        if (n == (int)pow(2, i))
        {
            return true;
        }
    }
    return false;
}

int main()
{
    // message_size stores the size of message.
    int message_size = 0;

    // Returns error if a non integer value is entered.
    if (scanf("%d", &message_size) == 0)
    {
        printf("input type error\n");
        return 1;
    }

    // Only proceeds if the message length matches possible Hamming code lengths.

    // First checks whether the lenght is of a SECDED Hamming code.
    // Possible SECDED Hamming code message lengths are 8, 16, 32, 64, 128, 256, etc.
    if ((message_size & (message_size - 1)) == 0)
    {

        // Input is accepted as char[] for easier handling.
        char input_str[message_size];
        scanf("%s", input_str);

        // message[] will store input message as an integer array. This is for easier handling.
        int message[message_size];

        // Checking whether any invalid characters have been entered.
        for (int i = 0; i < message_size; i++)
        {
            if (!(input_str[i] == '0' || input_str[i] == '1'))
            {
                printf("input bit error\n");
                return 1;
            }

            // ASCII value of 0 is 48 and 1 is 49.
            message[i] = input_str[i] - 48;
        }

        // Checking for errors

        // Using XOR operators on all bits that are 1.
        // If only one bit has been changed, the result of XOR operations will be the position of the bit which has been corrupted.
        int parity = 0;
        for (int i = 0; i < message_size; i++)
        {
            if (message[i] == 1)
            {
                parity = parity ^ i;
            }
        }

        // If XOR operations returned a position, the bit at that position has been changed.
        if (parity != 0)
        {
            // additional_parity performs XOR operations and checks whether a second bit has been changed.
            int additional_parity = 0;
            for (int i = 0; i < message_size; i++)
            {
                additional_parity = additional_parity ^ message[i];
            }

            // If additional_parity detected a change in a second bit, the message cannot be corrected.
            if (additional_parity % 2 == 0)
            {
                printf("two errors have occured\n");
                return 0;
            }

            // If no additional errors have been detected, the affected bit is reversed to obtained the corrected message.
            message[parity] = (message[parity] == 1) ? 0 : 1;
        }

        // Prints out the message after any error corrections.
        for (int i = 0; i < message_size; i++)
        {
            if (!is_parity_bit_position(i))
            {
                printf("%d", message[i]);
            }
        }
        printf("\n");

        // If only one error occured, prints the position where the error occured.
        if (parity != 0)
        {
            printf("\none error has occured at %d\n", (parity + 1));
        }
    }

    // Checks whether the lenght is of a SEC Hamming code.
    // Possible SEC Hamming code message lengths are 7, 15, 31, 63, 127, 255, etc.
    else if (((message_size + 1) & message_size) == 0)
    {
        // Input is accepted as char[] for easier handling.
        char input_str[message_size];
        scanf("%s", input_str);

        // message[] will store input message as an integer array. This is for easier handling.
        int message[message_size + 1];

        // Checking whether any invalid characters have been entered.
        for (int i = 1; i < message_size + 1; i++)
        {
            if (!(input_str[i - 1] == '0' || input_str[i - 1] == '1'))
            {
                printf("input bit error\n");
                return 1;
            }

            // ASCII value of 0 is 48 and 1 is 49.
            message[i] = input_str[i - 1] - 48;
        }

        // Checking for errors

        // Using XOR operators on all bits that are 1.
        // If only one bit has been changed, the result of XOR operations will be the position of the bit which has been corrupted
        int parity = 0;
        for (int i = 1; i < message_size + 1; i++)
        {
            if (message[i] == 1)
            {
                parity = parity ^ i;
            }
        }

        // If XOR operations returned a position, the bit at that position has been changed.
        if (parity != 0)
        {
            // The affected bit is reversed to obtain the corrected message.
            message[parity] = (message[parity] == 1) ? 0 : 1;
        }

        // Prints out the message after any error corrections.
        for (int i = 1; i < message_size + 1; i++)
        {
            if (!is_parity_bit_position(i))
            {
                printf("%d", message[i]);
            }
        }
        printf("\n");

        // If only one error occured, prints the position where the error occured.
        if (parity != 0)
        {
            printf("\none error has occured at %d\n", parity);
        }
    }
    else
    {
        printf("invalid size\n");
        return 1;
    }

    return 0;
}
