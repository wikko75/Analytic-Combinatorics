#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <array>


/// @brief Sums up number of 1's in binary representation of each number in [1, n] range
/// @param n max number in range
/// @return Sum of 1's in binary representation of numbers in [1, n] range 
int sigma(int n)
{
    if (n <= 0)
    {
        std::cerr << "[ERROR] sigma(n) : n <= 0 \n";
        return -1;
    }
    
    int sum {0};
    std::bitset<64> numInBinary {};
    for (int i {1}; i < n + 1; ++i)
    {
        numInBinary = i;
        sum += numInBinary.count();
    }

    return sum;
}

// first assumption
// IMO: sigma(n) = O(n)
// int sigmaAndAsymptotics(int n)
// {
//     return sigma(n) - n;
// }

//second assumption sigma(n) = O(nlogn)
// int sigmaAndAsymptotics(int n)
// {
//     int result = sigma(n) - n*log2(n);
//     std::cout << result << "\n";
//     return result;
// }


//third assumtion sigma(n) = O( nlog2[sqrt(n)] )
int sigmaAndAsymptotics(int n)
{
    int result = sigma(n) - n * log2( sqrt(n) -1 );
    //std::cout << result << "\n";
    return result;
}



void saveData(const std::string& path, const std::vector<int>& data)
{
    std::ofstream outSteam {};
    outSteam.open(path, std::ios::out);
    std::cout << path << "\n";

    if (!outSteam.is_open())
    {
        std::cerr << "Can't save data to file!\nAborting...\n";
        outSteam.close();
        return;
    }

    if (data.size() == 0)
    {
        std::cerr << "Nothing to save - no data provided!\nAborting...\n";
        outSteam.close();
        return;
    }
    
    int line {1};
    for(int result : data)
    {
        outSteam << line << " " << result << "\n";   
        ++line;
    }

    std::cout << "Sigma results saved!\n";
    outSteam.close();
}


int getSumOfAllDividers(int n, std::vector<int>& cache)
{
    if (cache[n] != 0)
    {
        return cache[n];
    }
    
    int sum {0};
    for(int i {1}; i < n + 1; ++i)
    {
        sum += n % i == 0 ? i : 0;
    }
    if(n == cache.size())
        std::cout << "Blond\n";
    cache[n] = sum;

    return sum;
}

size_t p_n(int n, std::vector<int>& cache)
{
    if (n == 0)
        return 1;

    size_t sum {0};
    for(int j {1}; j < n + 1; ++j)
    {
        sum += getSumOfAllDividers(j, cache) * p_n(n - j, cache);
    }
    //std::cout << sum/2 << "\n";
    return sum / n;
}




int main()
{
    // ex. 48
    //--------------------------------------------------
    constexpr int maxN {1024};

    std::vector<int> sigmaResults {};
    sigmaResults.reserve(maxN);

    std::vector<int> sigmaAndAsymptoticsResults {};
    sigmaAndAsymptoticsResults.reserve(maxN);

    for (int i {1}; i < maxN + 1; ++i)
    {
        sigmaResults.emplace_back(sigma(i));
        sigmaAndAsymptoticsResults.emplace_back(sigmaAndAsymptotics(i));
    }
    
    std::string path = "..\\sigmaResults.txt";
    saveData(path, sigmaResults);

    std::string path2 = "..\\sigmaAndAsymptoticsResults3.txt";
    saveData(path2, sigmaAndAsymptoticsResults);

    //no. of ones in binary rep increases O(logn)
    //when we grt sum of sigma(n) we get  O(log1 + log2 + ... logn) => O(log(n!)) => (stirling) -> O(log(n) * n)

    //--------------------------------------------------

    

    /**
     * !ex.49 freezes when MAX_P_N near 30. Why? No idea
    */
    //ex. 49
    //--------------------------------------------------
    // constexpr int MAX_P_N { 30 };
    // std::vector<size_t> p_n_data {};
    // p_n_data.reserve(MAX_P_N);

    // std::vector<int> cache(MAX_P_N + 1, 0);

    // for (int i{1}; i < MAX_P_N + 1; ++i)
    // {
    //     p_n_data.push_back(p_n(i, cache));
    // }

    // std::string path3 = "..\\p_n_data.txt";


    // for (int num : p_n_data)
    // {
    //     std::cout << num << "\n";
    // }
    
    // saveData(path3, p_n_data);

    // std::cout << p_n(1) << "\n";
    // std::cout << p_n(2) << "\n";
    // std::cout << p_n(3) << "\n";
    // std::cout << p_n(4) << "\n";
    // std::cout << p_n(5) << "\n";
    // std::cout << p_n(6) << "\n";
    // std::cout << p_n(7) << "\n";
    // std::cout << p_n(8) << "\n";
    // std::cout << p_n(9) << "\n";
    // std::cout << p_n(10) << "\n";

    //--------------------------------------------------


    return 0;
}