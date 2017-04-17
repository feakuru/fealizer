﻿#ifndef EQUALIZER_H
#define EQUALIZER_H

#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include "filter.cpp"

//template < typename T > std::string std::to_string( const T& n )
//{
//    std::ostringstream stm ;
//    stm << n ;
//    return stm.str() ;
//}



// custom audio stream that plays a loaded buffer
class FilteredStream : public sf::SoundStream
{
public:

    FilteredStream(const char* filename = "../fealizer/f_test.fcf");

    void streamFromFile(const std::string &filename);

private:

    void load(const sf::SoundBuffer& buffer);

    virtual bool onGetData(Chunk& data);

    virtual void onSeek(sf::Time timeOffset);

    std::vector<sf::Int16> m_samples;

    // float* weightCoeffs;

    std::size_t m_currentSample;

    sf::SoundBuffer buffer;

    std::vector<double> coefficients;

    IIRFilterFromMatlab* filter;
};

#endif // EQUALIZER_H
