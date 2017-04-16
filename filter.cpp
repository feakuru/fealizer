#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

class IIRFilterFromMatlab {
private:
        std::vector<double> num;
        std::vector<double> denom;

public:
        IIRFilterFromMatlab (const char* filename) {
                std::ifstream file;
                file.open(filename);
                std::string delimiter;
                std::cout << "I'm open!" << std::endl;

                double coeff = 0.0, first_coeff = 0.0;

                file >> first_coeff;
                num.push_back(first_coeff);
                std::cout << first_coeff << std::endl;

                while(first_coeff != coeff && first_coeff != -coeff && coeff != 1488.15) {
                        file >> coeff;
                        if (coeff == 1488.15) break;
                        std::cout << coeff << std::endl;
                        num.push_back(coeff);
                }

                file >> delimiter;
                std::cout << delimiter << std::endl;

                coeff = 0.0;
                first_coeff = 0.0;

                file >> first_coeff;
                denom.push_back(first_coeff);

                while(!file.eof()) {
                        file >> coeff;
                        denom.push_back(coeff);
                }
        }

        sf::Int16* filter(sf::Int16* to_filter, size_t size) {
                sf::Int16* result = new sf::Int16[size];
                for (size_t i = 0; i < size; i++) {
                        result[i] = iteration(to_filter, result, i);
                }
                return result;
        }

        sf::Int16 iteration(sf::Int16* to_filter, sf::Int16* filtered, size_t pos) {
                sf::Int16 tmp, to_add;

                sf::Int16 sum_by_x = 0;
                for (size_t backw_iter_num = 0; backw_iter_num <= pos && (backw_iter_num) < this->num.size(); backw_iter_num++) {
                        tmp = sum_by_x;
                        to_add = this->num.at(backw_iter_num) * to_filter[pos - backw_iter_num];
                        sum_by_x += to_add;
                        // overflow?
                        if ((to_add < 0) ? (sum_by_x > tmp) : (sum_by_x < tmp)) {
                            sum_by_x = tmp;
                        }
                }

                sf::Int16 sum_by_y = 0;
                for (size_t backw_iter_num = 1; backw_iter_num <= pos && backw_iter_num < this->denom.size(); backw_iter_num++) {
                        tmp = sum_by_y;
                        to_add = this->denom.at(backw_iter_num) * filtered[pos - backw_iter_num];
                        sum_by_y += to_add;
                        // overflow?
                        if ((to_add < 0) ? (sum_by_y > tmp) : (sum_by_y < tmp)) {
                            sum_by_y = tmp;
                        }
                }

                return sum_by_x - sum_by_y;
        }

        double popNum() {
                if (num.size() > 0) {
                        double retval = num.back();
                        num.pop_back();
                        return retval;
                }
                else {
                        throw std::length_error("No more values");
                }
        }

        double popDenom() {
                if (denom.size() > 0) {
                        double retval = denom.back();
                        denom.pop_back();
                        return retval;
                }
                else {
                        throw std::length_error("No more values");
                }
        }

        virtual ~IIRFilterFromMatlab () {}
};
