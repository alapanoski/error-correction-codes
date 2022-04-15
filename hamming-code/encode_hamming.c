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

/**
 * To find binary equivalent of a number.
 * I did not find a straightforward way to use library functions to find binary equivalent.
 */
int to_binary(int n)
{
    int binary = 0;

    for (int i = 0; n > 0; i++)
    {
        binary = binary + (n % 2) * pow(10, i);
        n = n / 2;
    }

    return binary;
}

int main()
{
    int message_size = 0;

    // Capacity of data types depends on the machine on which the code is run.
    const int MAX_MESSAGE_SIZE = (int)(pow(2, sizeof(message_size) * 8) / 2);
    // LOG_MAX_MESSAGE_SIZE contains the power to which 2 should be raised to get MAX_MESSAGE_SIZE.
    const int LOG_MAX_MESSAGE_SIZE = log(MAX_MESSAGE_SIZE) / log(2);

    // Returns error if a non integer value is entered.
    if (scanf("%d", &message_size) == 0)
    {
        printf("input type error\n");
    }

    // Starts from 3 as 0, 1, 2 are always parity bits.
    for (int s = 3; s < LOG_MAX_MESSAGE_SIZE; s++)
    {
        // Only proceeds if the message length matches possible Hamming code lengths.
        // Possible Hamming code message lengths are 4, 11, 26, 57, 120, 247, etc.
        if (message_size == (int)(pow(2, s) - (s + 1)))
        {
            // HAMMING_CODE_SIZE stores the length of output that will be generated.
            const int HAMMING_CODE_SIZE = (int)pow(2, s);

            // Input is accepted as char[] for easier handling.
            char input_str[message_size];
            scanf("%s", input_str);

            // message[] will store input message as an integer array. This is for easier handling.
            int message[message_size];
            for (int i = 0; i < message_size; i++)
            {
                // Checking whether any invalid characters have been entered.
                if (!(input_str[i] == '0' || input_str[i] == '1'))
                {
                    printf("input bit error\n");
                    return 1;
                }

                // ASCII value of 0 is 48 and 1 is 49.
                message[i] = input_str[i] - 48;
            }

            // hamming_code[] stores the final output code.
            int hamming_code[HAMMING_CODE_SIZE];

            // i controls hamming_code[] and j controls message[].
            for (int i = 0, j = 0; j < HAMMING_CODE_SIZE; i++)
            {
                // all parity bit positions are assigned 0 for now. The message is copied over otherwise.
                if (is_parity_bit_position(i))
                {
                    hamming_code[i] = 0;
                }
                else
                {
                    hamming_code[i] = message[j];
                    j++;
                }
            }

            // Assigning values to parity bits.
            // i controls the array and j controls the operations on temp.
            for (int i = 1, p = 1; i < HAMMING_CODE_SIZE; i++)
            {
                if (is_parity_bit_position(i))
                {
                    int count = 0;
                    for (int j = 1; j < HAMMING_CODE_SIZE; j++)
                    {
                        if (!(is_parity_bit_position(j)))
                        {
                            // Performing checks on designated positions by utilising the binary values and the cleverness of Hamming code.
                            // After these seemingly complicated operations, temp will have the value 1 if the bit is to evaluated.
                            int temp = to_binary(j);
                            temp = temp % (int)pow(10, p);
                            temp = temp / (int)pow(10, (p - 1));

                            // Counting the number of 1s.
                            if (temp == 1 && hamming_code[j] == 1)
                            {
                                count++;
                            }
                        }
                    }

                    // Changing parity bit to 1 if there are odd number of 1s. Leaving the parity bit as 0 if there are even number of 1s.
                    hamming_code[i] = (count % 2 == 0) ? 0 : 1;
                    p++;
                }
            }

            // Adding the final double error detection parity bit to the very first position.
            int count = 0;
            // Counting the number of 1s in the entire code.
            for (int i = 1; i < HAMMING_CODE_SIZE; i++)
            {
                count = count + (hamming_code[i] == 1) ? 1 : 0;
            }

            // Changing parity bit to 1 if there are odd number of 1s or to 0 if there are even number of 1s.
            hamming_code[0] = (count % 2 != 0) ? 0 : 1;

            // Printing the SEC Hamming code.
            for (int i = 1; i < HAMMING_CODE_SIZE; i++)
            {
                printf("%d", hamming_code[i]);
            }
            printf("\n");

            // Printing the SECDED Hamming code.
            for (int i = 0; i < HAMMING_CODE_SIZE; i++)
            {
                printf("%d", hamming_code[i]);
            }
            printf("\n");

            return 0;
        }
    }

    // The loop and if conditions are set up in a way that it fails to execute if the message size does not match possible Hamming code lengths.
    printf("invalid message size\n");
    return 1;
}