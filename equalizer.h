#ifndef EQUALIZER_H
#define EQUALIZER_H

#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

//template < typename T > std::string std::to_string( const T& n )
//{
//    std::ostringstream stm ;
//    stm << n ;
//    return stm.str() ;
//}



// custom audio stream that plays a loaded buffer
class EqualizerStream : public sf::SoundStream
{
public:

    void streamFromFile(const std::string &filename);

    std::string setTenEqualizerCoeffs(double coeff1, double coeff2, double coeff3, double coeff4, double coeff5, double coeff6, double coeff7, double coeff8, double coeff9, double coeff10);

private:

    void load(const sf::SoundBuffer& buffer);

    virtual bool onGetData(Chunk& data);

    virtual void onSeek(sf::Time timeOffset);

    void prepareWeightCoeffs();

    std::vector<sf::Int16> m_samples;

    float* weightCoeffs;

    std::size_t m_currentSample;

    sf::SoundBuffer buffer;

    std::vector<double> coefficients;
};

#endif // EQUALIZER_H
