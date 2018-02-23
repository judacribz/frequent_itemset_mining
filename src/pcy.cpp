#include "../headers/pcy.h"

using namespace std;

int passThroughPcy(int dim, int numItemsets);

int pcy_hash(int item1, int item2, int num);

void pcy(string file)
{
    int size;
    long numItemsets;
    int freqPairCount, freqTripCount;
    filename = file;
    size = passThroughPcy(0, 1);
}

int passThroughPcy(int dim, int numItemsets)
{
    int freqCount = 0;
    // Read in file and get item frequency
    ifstream ifs(filename, ifstream::in);

    if (ifs.good())
    {
        string line;
        while (getline(ifs, line))
        {
            // Split items in string line and store in vector
            istringstream iss(line);
            basketItems.assign((istream_iterator<int>)iss,
                               istream_iterator<int>());
            switch (dim)
            {

            // Get frequent items
            case 0:

                for (vector<int>::iterator itemIt = basketItems.begin(); itemIt != basketItems.end(); itemIt++)
                {
                    (itemCount.count(*itemIt) > 0) ? itemCount[*itemIt]++ : itemCount[*itemIt] = 1;

                    if (itemCount[*itemIt] == SUPP_THRESH)
                    {
                        freqCount++;
                        freqItems.push_back(*itemIt);
                    }
                }

                break;

                // Check if pair or triple exists in each basket, add to pair count in array
            default:
                int count = 0;

                // Get and store pair count
                for (int i = 0; i < numItemsets; i++)
                {
                    count = 0;
                    for (vector<int>::iterator itemIt = basketItems.begin(); itemIt != basketItems.end(); itemIt++)
                    {
                        for (int j = 1; j < dim; j++)
                        {
                            if (*itemIt == freqArr[i][j])
                            {
                                count++;
                                break;
                            }
                        }

                        if (count == dim - 1)
                        {
                            freqArr[i][0]++;
                            break;
                        }
                    }
                }

                break;
            }
        }
        ifs.close();
    }
    else
        cout << "Unable to open file";

    if (dim != 0)
        printItemsets(freqArr, dim, SUPP_THRESH, numItemsets);

    return freqCount;
}

int pcy_hash(int item1, int item2, int num)
{
    return (item1 ^ item2) % num;
}