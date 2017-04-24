#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <FIR/filt.h>

class FIRFilterFromCP {
private:
        std::vector<double> num;
        std::vector<double> denom;
        Filter *my_l_filter;
        Filter *my_h_filter;

public:
        FIRFilterFromCP (int num_taps, double Fs, double Fpass, double Fstop) {
            my_l_filter = new Filter(LPF, num_taps, Fs, Fpass);
            my_h_filter = new Filter(HPF, num_taps, Fs, Fstop);
            std::cout << num_taps << " " << Fs << " " << Fpass << " " << Fstop << std::endl;
        }

        sf::Int16* filter(sf::Int16* to_filter, size_t size, double coeff) {
            sf::Int16* result = new sf::Int16[size];
            double outval;
            for (size_t i = 0; i < size; i++) {
                outval = my_l_filter->do_sample( (double) to_filter[i] );
                outval = my_h_filter->do_sample(outval);
                result[i] = (sf::Int16) (outval * coeff);
            }
            return result;
        }

        virtual ~FIRFilterFromCP () {
            delete my_l_filter;
            delete my_h_filter;
        }
};
