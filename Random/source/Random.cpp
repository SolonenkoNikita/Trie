#include "Random/Random.hpp"

std::string generate_random_word(size_t length)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, 25);

    std::string word;
    for (int i = 0; i < length; ++i)
    {
        word += static_cast<char>(distribution(generator) + 'a');
    }
    return word;
}