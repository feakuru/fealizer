#ifndef FILT_H
#define FILT_H


class Filter
{
private:
    double b[30] = {5.2787e-04,
                    2.8936e-03,
                    -1.6373e-03,
                    5.2304e-03,
                    -8.6352e-03,
                    5.1387e-03,
                    -2.2644e-02,
                    -6.5751e-03,
                    -3.8073e-02,
                    -4.0634e-02,
                    -3.8663e-02,
                    -1.0893e-01,
                    1.2392e-02,
                    -2.7363e-01,
                    5.4030e-01,
                    5.4030e-01,
                    -2.7363e-01,
                    1.2392e-02,
                    -1.0893e-01,
                    -3.8663e-02,
                    -4.0634e-02,
                    -3.8073e-02,
                    -6.5751e-03,
                    -2.2644e-02,
                    5.1387e-03,
                    -8.6352e-03,
                    5.2304e-03,
                    -1.6373e-03,
                    2.8936e-03,
                    5.2787e-04};
    int b_len;
    double* x;
    int cur_x;
public:
    Filter(int number);
    ~Filter();
    double do_sample(double data_sample);
};

#endif // FILT_H
