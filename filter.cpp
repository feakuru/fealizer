#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <feafilter/filt.h>

class FIRFilterFromCP {
private:
        std::vector<double> num;
        int numa;
        std::vector<double> denom;
        Filter *my_filter;

public:
        FIRFilterFromCP (int num) {
            this->numa = num;
            my_filter = new Filter(1);
        }

        sf::Int16* filter(sf::Int16* to_filter, size_t size, double coeff) {
            sf::Int16* result = new sf::Int16[size];
            double outval;
            for (size_t i = 0; i < size; i++) {
                outval = my_filter->do_sample( (double) (to_filter[i] * coeff));
                result[i] = (sf::Int16) (outval);
            }
            return result;
        }

        virtual ~FIRFilterFromCP () {
            delete my_filter;
        }
};
