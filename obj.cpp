

#include <initializer_list>
#include <iostream>

void func(std::initializer_list<int> list)
{
    for(const auto& it : list)
    {
        std::cout << it << ",";
    }
    std::cout << "\n";
}

int main(int argc, char* argv[]){



    func({1, 2, 3});
    func({4, 5, 6, 7, 8, 0});    


    return 0;
}