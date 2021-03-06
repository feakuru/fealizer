﻿#include <SFML/Audio.hpp>
#include <feafilter/filt.h>

class FIRFilterFromCP {
private:
        int num;
        Filter *my_filter;

public:
        FIRFilterFromCP (int num) {
            this->num = num;
            my_filter = new Filter(num);
        }

        sf::Int16* filter(sf::Int16* to_filter, size_t size, double coeff, sf::Int16* avg_ptr) {
            sf::Int16* result = new sf::Int16[size];
            double outval;
            for (size_t i = 0; i < size; i++) {
                outval = my_filter->do_sample( (double) (to_filter[i] * coeff));
                result[i] = (sf::Int16) (outval);
                *avg_ptr += to_filter[i] / size;
            }
            return result;
        }

        virtual ~FIRFilterFromCP () {
            delete my_filter;
        }
};
