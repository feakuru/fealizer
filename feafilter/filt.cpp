#include "filt.h"

Filter::Filter(int number)
{
    double b_lens[] = {30, 30};
    b_len = b_lens[number];
    x = new double[44100];
    cur_x = 0;
}

Filter::~Filter() {
    delete b;
    delete x;
}

double Filter::do_sample(double data_sample) {
    double retval = b[0] * data_sample;
    if (cur_x > 44099) {
        cur_x = 0;
    }
    x[cur_x++] = data_sample;
    for (int iter = 1; iter < b_len; iter++) {
        if (iter > cur_x)
            retval += b[iter] * x[cur_x - iter];
        else
            retval += b[iter] * x[44100 - iter];
    }
    return retval;
}
