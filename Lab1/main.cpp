#include <iostream>
#include <random> // for std::mt19937 and std::uniform_int_distribution
#include <chrono> // for std::chrono
#include <vector>
#include <algorithm>  // for std::find
#include <numeric>   // for  std::iota
#include <string>
#include <functional> //for std::function


template<typename T>
void displayVector(const std::vector<T> &vector)
{
    std::cout << "["; 
    for (const T &element : vector)
    {
        std::cout << " "<< element << " ";
    }
    std::cout << "]\n";
}


void displayCycles(const std::vector<std::vector<int>> &cycles)  
{
    for (const std::vector<int> &cycle : cycles)
    {
        std::cout << "["; 
        for (const int element : cycle)
        {
            std::cout << " "<< element << " ";
        }
        std::cout << "]\n";
    }
}


std::vector<int> fisherYatesShuffle(std::vector<int> sequence)
{
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(
    std::chrono::steady_clock::now().time_since_epoch().count()
    ) };
    
    for (size_t i{0}; i < sequence.size() - 1; ++i)
    {
        // uniform distribution 
        std::uniform_int_distribution<size_t> uniformRandomInt{ i, sequence.size() - 1 };
        const size_t n = uniformRandomInt(mt);
        //swap
        int temp = sequence[i];
        sequence[i] = sequence[n];
        sequence[n] = temp;
    }

    return sequence;
} 


size_t countFixedPoints(const std::vector<int> &startingSeq, const std::vector<int> &shuffledSeq)
{
    size_t fixedPointsCounter {0};
    for (size_t i {0}; i < startingSeq.size(); ++i)
    {
        if (startingSeq.at(i) == shuffledSeq.at(i))
        {
            ++fixedPointsCounter;
        }
    }
    return fixedPointsCounter;
}


int countCycles(const std::vector<int> &startingSeq,  const std::vector<int> &shuffledSeq, std::vector<std::vector<int>> &cycles)
{
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(
    std::chrono::steady_clock::now().time_since_epoch().count()
    ) };

    std::uniform_int_distribution<size_t> uniformRandomInt{ 1, startingSeq.size() };

    size_t cyclesCount {0};
    std::vector<bool> isInCycle(startingSeq.size(), false);
    //std::vector<std::vector<int>> cycles {};


    while (std::find(isInCycle.begin(), isInCycle.end(), false) != isInCycle.end())
    {
        //1. get random (element) from seq,  isInCycle[element] = true,
        int selectedNumber = -1;
        while (selectedNumber == -1) 
        {
            size_t randomIndex = uniformRandomInt(mt);
            //if element is not in any cycle create new cycle staring from it
            if ( !isInCycle[randomIndex - 1] ) 
            {
                selectedNumber = randomIndex;
                isInCycle[selectedNumber - 1] = true;
            }
        }

        //2. find cycle starting from (element) and add every encountered elem to array (isInCycle[elem] = true)
        std::vector<int> newCycle { startingSeq[selectedNumber - 1] };

        int nextNumber = shuffledSeq[startingSeq[selectedNumber - 1] - 1];

        if (nextNumber != startingSeq[selectedNumber - 1])
        {
            newCycle.push_back(nextNumber);
            isInCycle[nextNumber - 1] = true;
        }
        
        while (nextNumber != startingSeq[selectedNumber - 1])
        {
            nextNumber = shuffledSeq[startingSeq[nextNumber - 1] - 1];
            if (isInCycle[nextNumber - 1])
            {
                //number already in cycle break
                break;
            }
            
            isInCycle[nextNumber - 1] = true;
            newCycle.push_back(nextNumber);
        }

        cycles.push_back(newCycle);
        ++cyclesCount;
    }

    return cyclesCount;
    return 0;
}


void test(int length, int numberOfPerm,  const std::vector<int> &sequence, float &avgPermWithZeroFixedPoints, float &avgPermWithOneFixedPoint, float &avgNoOfCycles)
{
    for (int i {0}; i < numberOfPerm; ++i)
    {
        std::cout << "---------------------------------\n";

        std::vector shuffledSeq = fisherYatesShuffle(sequence);

        displayVector(sequence);
        displayVector(shuffledSeq);

        std::cout << "\nFixed points: " << countFixedPoints(sequence, shuffledSeq) << "\n\n";

        if (countFixedPoints(sequence, shuffledSeq) == 0)
        { 
          ++avgPermWithZeroFixedPoints;
        }
        else if (countFixedPoints(sequence, shuffledSeq) == 1)
        {
            ++avgPermWithOneFixedPoint;
        }

        std::vector<std::vector<int>> cycles {};
        int numberOfCycles = countCycles(sequence, shuffledSeq, cycles);
        std::cout << "Cycles : " <<  numberOfCycles << "\n";
        avgNoOfCycles += numberOfCycles;
        displayCycles(cycles);

        std::cout << "---------------------------------\n\n";
    }

    avgPermWithZeroFixedPoints /= numberOfPerm;
    avgPermWithOneFixedPoint /= numberOfPerm;
    avgNoOfCycles /= numberOfPerm;
}


std::string genRandomSequence(const std::vector<char> &alphabeth, int length)
{
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(
    std::chrono::steady_clock::now().time_since_epoch().count()
    ) };

    std::uniform_int_distribution<int> uniformRandomInt{ 0, static_cast<int>(alphabeth.size() - 1)};

    std::vector<char> sequence(length);
    std::string seq {};

    for (int i {0}; i < length; ++i)
    {
        char randomCharFromAlphabeth = alphabeth[uniformRandomInt(mt)];
        sequence.push_back(randomCharFromAlphabeth);
        seq += randomCharFromAlphabeth;
    }
    
    return seq;
}


std::vector<int> computeLPSArray(const std::string& subsequence) {
    int M = subsequence.length();
    std::vector<int> lps(M);
    int len {0};
    lps[0] = 0;
    int i {1};

    while (i < M) {
        if (subsequence[i] == subsequence[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}


int KMPSearch(const std::string& subsequence, const std::string& sequence) {
    int M = subsequence.length();
    int N = sequence.length();

    std::vector<int> lps {computeLPSArray(subsequence)};
    int subsequenceFoundCounter {0};

    
    int i {0}; // index for sequence[]
    int j {0}; // index for subsequence[]
    while (i < N) {
        if (subsequence[j] == sequence[i]) {
            ++j;
            ++i;
        }

        if (j == M) {
            std::cout << "Found pattern at index " << i - j << "\n";
            ++subsequenceFoundCounter;
            j = lps[j - 1];
        } else if (i < N && subsequence[j] != sequence[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }

    return subsequenceFoundCounter;
}


void test2(const std::vector<char> &alphabeth, const std::string &subsequence, int sequenceLength,  int numberOfRandomSequences)
{
    std::cout << "\nGenerating [ " << numberOfRandomSequences << " ] random sequences and searching for [ " << subsequence << " ]\n";
    
    float avgNoOfSubseqInSeq {0};
    int subsequencePresenceCounter {0};
    
    for (int i {0}; i < numberOfRandomSequences; ++i)
    {
        std::string randomSeq = genRandomSequence(alphabeth, sequenceLength);
        std::cout << "\nSequence : " << randomSeq << "\n";

        //current iteration counter
        int currentNoOfSubseqInSeq = KMPSearch(subsequence, randomSeq);
        if (currentNoOfSubseqInSeq > 0)
        {
            ++subsequencePresenceCounter;
        }
        
        avgNoOfSubseqInSeq += currentNoOfSubseqInSeq;
    }

    std::cout << "\nSubsequence: " << subsequence << " appears in [ " << subsequencePresenceCounter << " ] out of [ " << numberOfRandomSequences << " ] random sequences\n";
    std::cout << "Subsequence: " << subsequence << " appears (on average): " << avgNoOfSubseqInSeq / numberOfRandomSequences << "\n";
}



double factorial(int n)
{
    double factorial {1.0};

    for (int i {1}; i <= n; ++i)
    {
        factorial *= i;
    }

    return factorial;
    
}


std::vector<double> formalSeriesReverse(const std::function<double(unsigned int)> &f, int n)
{
    std::vector<double> inverse(n, 0.0);
    std::vector<double> functionValues(n, 0.0);

    for (int i {0}; i < n; ++i)
    {
        functionValues[i] = f(i);
    }

    
    inverse[0] = 1.0 / functionValues[0];

    for (int i{1}; i < n; ++i)
    {
        inverse[i] = 0;

        for (int j {1}; j <= i; ++j)
        {
            inverse[i] += functionValues[j] * inverse[i - j];
        }

        inverse[i] *= (-1 / functionValues[0]);
        
        
    }

    return inverse;
}


int main()
{

    //ex 9
    //---------------------------------------------------------------------------

    const int numberOfPerm = 10;
    const int length = 10;

    std::vector<int> seq(length);
    
    //fill seq vector with increasing numbers [1,length]
    std::iota(std::begin(seq), std::end(seq), 1);
    
    float avgPermWithZeroFixedPoints {0.f};
    float avgPermWithOneFixedPoint {0.f}; 
    float avgNoOfCycles {0.f};

    test(length, numberOfPerm, seq, avgPermWithZeroFixedPoints, avgPermWithOneFixedPoint, avgNoOfCycles);

    std::cout << "Average number of Permutations with 0 fixed points: " << avgPermWithZeroFixedPoints << "\n";
    std::cout << "Average number of Permutations with one fixed point: " << avgPermWithOneFixedPoint << "\n";
    std::cout << "Average number of cycles " << avgNoOfCycles << "\n";

    //---------------------------------------------------------------------------




    //ex 10
    //---------------------------------------------------------------------------

    const std::string subsequence1 {"aaa"};

    // test2({'a', 'b'}, subsequence1, 50, 100);
    
    const std::string subsequence2 {"abb"};

    test2({'a', 'b'}, subsequence2, 50, 10);

    //---------------------------------------------------------------------------




        //ex 32
    //---------------------------------------------------------------------------

        auto f = [](int n) { return static_cast<double>( 1 ); };
        auto g = [](int n) { return static_cast<double>( std::pow(2, n) ); };
        auto h = [](int n) { return static_cast<double>( factorial(n) ); };
        auto i = [](int n) { return static_cast<double>( 1 / factorial(n) ); };

        std::cout << "Series Reverse for f(n) = 1 (10 first elements): \n";
        std::vector<double> results = formalSeriesReverse(f, 10);
        displayVector(results);
        std::cout << "Series Reverse for f(n) = 2^n (10 first elements): \n";
        results = formalSeriesReverse(g, 10);
        displayVector(results);
        std::cout << "Series Reverse for f(n) = n! (10 first elements): \n";
        results = formalSeriesReverse(h, 10);
        displayVector(results);
        std::cout << "Series Reverse for f(n) = 1/n! (10 first elements): \n";
        results = formalSeriesReverse(i, 10);
        displayVector(results);

    //---------------------------------------------------------------------------


	return 0;
}