#include <iostream>
#include <array>

struct Quad {
    std::array<long double, 4> matrix;

    long double& operator[](int index) {return matrix[index];}
    long double at(const int row, const int column) const {return matrix[(row-1)*2 + column-1];}

    Quad operator*(const Quad& right) {
        Quad result;
        result[0] = this->at(1,1)*right.at(1,1) + this->at(1,2)*right.at(2,1);
        result[1] = this->at(1,1)*right.at(1,2) + this->at(1,2)*right.at(2,2);
        result[2] = this->at(2,1)*right.at(1,1) + this->at(2,2)*right.at(2,1);
        result[3] = this->at(2,1)*right.at(1,2) + this->at(2,2)*right.at(2,2);
        return result;
    }
};

int main()
{
    Quad matrix;
    matrix[0] = 1; matrix[1] = 1;
    matrix[2] = 1; matrix[3] = 0;

    unsigned num;
    std::cout << "Please input number more 0: ";
    std::cin >> num;
    std::cout << "Fibo number " << num << ":\t";
    if (0 == num) {
        std::cout << 0 << std::endl;
        return 0;
    } else if (1 == num) {
        std::cout << 1 << std::endl;
        return 0;
    }

    Quad result = matrix;
    num-=2;
    while (num>=1) {
        if (num&0x1 == 1) {
            result = result * matrix;
        }
        matrix = matrix * matrix;
        num = num >> 1;
    }

    std::cout << result.at(1, 1) << std::endl;

    return 0;
}
