#include <cstdint>
#include <iostream>
#include <cmath>
#include <cassert>

constexpr uint32_t segment_size = 100;
constexpr uint32_t prime_count = 100000;

void fill_array(uint64_t first, uint64_t* check_array) {
    for (uint32_t idx = 0; idx<segment_size; ++idx) {
        check_array[idx] = first++;
    }
}

void eratosphene_filter_array(uint64_t* check_array, uint64_t* prime_numbers, uint32_t& counter) {
    for (uint32_t i=0; i < segment_size && counter < prime_count; ++i) {
        auto val = check_array[i];
        if (val != 0) {
            prime_numbers[counter++] = val;
            for (uint32_t k=val*val-2; k<segment_size; k+=val) {
                check_array[k] = 0;
            }
        }
    }
}

void segment_filter_array(uint64_t* check_array, uint64_t* prime_numbers, uint32_t& counter) {
    uint32_t first_val = check_array[0];
    uint64_t max_prime = sqrt(first_val + segment_size)+1;
    for(unsigned i=0; prime_numbers[i]<max_prime; ++i) {
        uint32_t prime = prime_numbers[i];
        uint16_t idx = prime - first_val%prime;
        if(idx==prime)
            idx = 0;
        for(; idx < segment_size; idx += prime) {
            assert(check_array[idx]%prime == 0);
            check_array[idx] = 0;
        }
    }
}

int main()
{
    uint64_t check_array [segment_size] = {0};

    uint64_t result [prime_count] = {0};
    uint32_t prime_counter = 0;

    fill_array(2, check_array);
    eratosphene_filter_array(check_array, result, prime_counter);

    for (unsigned num_segment = 1; prime_counter < prime_count; ++num_segment) {
        fill_array(2*num_segment+2, check_array);
        segment_filter_array(check_array, result, prime_counter);

        for (unsigned i = 0; i<segment_size && prime_counter < prime_count; ++i) {
            if (check_array[i] != 0) {
                result[prime_counter++] = check_array[i];
                if (prime_counter == prime_count)
                    break;
            }
        }
    }

    for (uint16_t i=0; i<prime_counter; ++i)
        std::cout << result[i] << "\t";
    std::cout << std::endl << "Total numbers: " << prime_counter << std::endl;
    return 0;
}
