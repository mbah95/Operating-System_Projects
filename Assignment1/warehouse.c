#include "order.h"
#include "bench.h"
#include <stdio.h>
#include <assert.h>

int findLeastRecentlyUsedBin(int x, int y, int z, int a, int b);

int main(int argc, char **argv)
{
    // -1 means empty, to counter the bin that was used last
    int bins[5] = {-1, -1, -1, -1, -1};
    int Maximum;

    if (argc < 2)
    {
        printf("Please invoke as %s <order_file>\n", argv[0]);
        return 1;
    }
    if (!openOrder(argv[1]))
    {
        return 1;
    }

    do
    {
        int pn = nextPartNumber();
        int bin = pn / 10;

        /* Replace the following code with a better implementation */

        // Checking all 5 bin for parts
        if ((binInSlot(0) != bin) && (binInSlot(1) != bin) && (binInSlot(3) != bin) && (binInSlot(4) != bin))
        {
            // Make sure bins are emtpy and fills

            if (bins[0] == -1) // check if Bin 0 empty
            {
                fetchBin(bin, 0);
                bins[0] = 0;
            }
            /* Always use slot 0 */
            else if (bins[1] == -1) // check if Bin 1 empty
            {
                fetchBin(bin, 1);
                bins[0]++;
                bins[1] = 0;
            }
            else if (bins[2] == -1) // check if Bin 2 empty
            {
                fetchBin(bin, 2);
                bins[0]++;
                bins[1]++;
                bins[2] = 0;
            }
            else if (bins[3] == -1) // check if Bin 3 empty
            {
                fetchBin(bin, 3);
                bins[0]++;
                bins[1]++;
                bins[2]++;
                bins[3] = 0;
            }
            else if (bins[4] == -1) // check if Bin 4 empty
            {
                fetchBin(bin, 4);
                bins[0]++;
                bins[1]++;
                bins[2]++;
                bins[3]++;
                bins[4] = 0;
            }
            // check if no Bin is empty
            else
            {
                // Find the least used bin recently
                Maximum = findLeastRecentlyUsedBin(bins[0], bins[1], bins[2], bins[3], bins[4]);

                // Now replace recently used bin
                fetchBin(bin, 4);
                bins[0]++;
                bins[1]++;
                bins[2]++;
                bins[3]++;
                bins[4] = 0;
            }
        }
        // ckeck if there are remains bin for part
        else
        {
            for (int i = 0; i < 5; i++)
            {
                if ((binInSlot(i) == bin))
                {
                    bins[i] = 0;
                }
            }
        }
        /* End of simple implementation */
    } while (fetchNextPart());
    closeOrder();
    return 0;
}

// This function check the least Recently used Bin
int findLeastRecentlyUsedBin(int x, int y, int z, int a, int b)
{
    int max = -1;
    int maxIndex = -1;

    if (x > max)
    {
        max = x;
        maxIndex = 0;
    }

    if (y > max)
    {
        max = y;
        maxIndex = 1;
    }

    if (z > max)
    {
        max = z;
        maxIndex = 2;
    }

    if (a > max)
    {
        max = a;
        maxIndex = 3;
    }

    if (b > max)
    {
        max = b;
        maxIndex = 4;
    }

    return maxIndex;
}