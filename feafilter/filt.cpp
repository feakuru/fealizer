#include "filt.h"

Filter::Filter(int number)
{
    b_len = sizeof(B_ARRAYS[number])/sizeof(B_ARRAYS[number][0]);
    b = new double[b_len];
    for (int i = 0; i < b_len; i++) {
        b[i] = B_ARRAYS[number][i];
    }
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
            retval += b[iter] * x[44100 - iter];
        else
            retval += b[iter] * x[cur_x - iter];
    }
    return retval;
}
