#include <iostream>
#include <vector>

#include <interface/vector.h>

int main()
{
    std::cout << "Starting test for vector: " << std::endl;

    /* add 100 elements to default vector from STL */    
    std::vector<unsigned> defaultVector;
    for (unsigned element = 0; element < 100; ++element)
    {
        defaultVector.push_back(element);
    }

    /* add 100 elements to sudnya vector from STL */    
    sudnya::vector<unsigned> sudnyaVector;
    for (unsigned element = 0; element < 100; ++element)
    {
        sudnyaVector.push_back(element);
    }

    bool mismatch = false;
    for (unsigned element = 0; element < 100; ++element)
    {
        if (defaultVector[element] != sudnyaVector[element])
        {
            mismatch = true;
            std::cout << "Something went awry. Vector contents not the same. Default contains = " << defaultVector[element]
               << " while sudnyaVector contains = " << sudnyaVector[element] << " at location " << element << std::endl;
        }

    }
    if (!mismatch)
    {
        std::cout << "Both vectors were exactly the same " << std::endl;
    }


    return 0;
}

