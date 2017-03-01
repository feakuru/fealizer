#include "equalizer.h"

void EqualizerStream::streamFromFile(const std::string &filename)
{
    // load audio buffer from a sound file
    buffer.loadFromFile(filename);
    load(buffer);
}

std::string EqualizerStream::setTenEqualizerCoeffs(double coeff1, double coeff2, double coeff3, double coeff4, double coeff5, double coeff6, double coeff7, double coeff8, double coeff9, double coeff10) {
    coefficients.push_back(coeff1);
    coefficients.push_back(coeff2);
    coefficients.push_back(coeff3);
    coefficients.push_back(coeff4);
    coefficients.push_back(coeff5);
    coefficients.push_back(coeff6);
    coefficients.push_back(coeff7);
    coefficients.push_back(coeff8);
    coefficients.push_back(coeff9);
    coefficients.push_back(coeff10);
    prepareWeightCoeffs();
    return "All coeffs successfully set to " +
        to_string(coeff1) + ", " +
        to_string(coeff2) + ", " +
        to_string(coeff3) + ", " +
        to_string(coeff4) + ", " +
        to_string(coeff5) + ", " +
        to_string(coeff6) + ", " +
        to_string(coeff7) + ", " +
        to_string(coeff8) + ", " +
        to_string(coeff9) + ", " +
        to_string(coeff10) + "!";
}

void EqualizerStream::load(const sf::SoundBuffer& buffer)
{
    // extract the audio samples from the sound buffer to our own container
    m_samples.assign(buffer.getSamples(), buffer.getSamples() + buffer.getSampleCount());

    // reset the current playing position
    m_currentSample = 0;

    // initialize the base class
    initialize(buffer.getChannelCount(), buffer.getSampleRate());
}

virtual bool EqualizerStream::onGetData(Chunk& data)
{
    // number of samples to stream every time the function is called;
    // in a more robust implementation, it should be a fixed
    // amount of time rather than an arbitrary number of samples
    const int samplesToStream = buffer.getSampleRate();

    // set the pointer to the next audio samples to be played
    sf::Int16* new_samples = new sf::Int16[samplesToStream];
    sf::Int16 smpl = 0;
    double coeff = 0.0;
    sf::Int16 tmp_for_smpl = 0;
    for (size_t sample_num = 0; sample_num < samplesToStream; sample_num++) {
        try {
            smpl = m_samples.at(m_currentSample + sample_num);
            tmp_for_smpl = smpl;
            coeff = weightCoeffs[sample_num];
            new_samples[sample_num] = smpl * coeff;
            if (coeff != 0 && new_samples[sample_num] / coeff != 0) {
                new_samples[sample_num] = tmp_for_smpl;
            }
        }
        catch (std::out_of_range& e) {
            break;
        }
    }
    delete data.samples;
    data.samples = new_samples;

    // have we reached the end of the sound?
    if (m_currentSample + samplesToStream <= m_samples.size())
    {
        // end not reached: stream the samples and continue
        data.sampleCount = samplesToStream;
        m_currentSample += samplesToStream;
        return true;
    }
    else
    {
        // end of stream reached: stream the remaining samples and stop playback
        data.sampleCount = m_samples.size() - m_currentSample;
        m_currentSample = m_samples.size();
        return false;
    }
}

virtual void EqualizerStream::onSeek(sf::Time timeOffset)
{
    // compute the corresponding sample index according to the sample rate and channel count
    m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
}

void EqualizerStream::prepareWeightCoeffs() {
    if (coefficients.size() != 10) {
        throw std::range_error("Bad coefficients quantity!");
    }
    int f_discr = getSampleRate();
    weightCoeffs = new float[f_discr];
    int* delimiters = new int[f_discr];
    for (size_t filter_num = 0; filter_num < 10; filter_num++) {
        int fpass = 50 * pow(2, filter_num);
        int fstop = 50 * pow(2, filter_num + 1);
        if (fstop > f_discr) {
            fstop = f_discr;
        }
        int step;
        for (int freq = fpass; freq < fstop; freq++) {
            step = f_discr / freq;
            for (size_t sample_num = 0; sample_num < f_discr; sample_num += step) {
                delimiters[sample_num]++;
                weightCoeffs[sample_num] += float(coefficients[filter_num]);
            }
        }
    }
    for (size_t i = 0; i < f_discr; i++) {
        weightCoeffs[i] = weightCoeffs[i] / delimiters[i];
        if (weightCoeffs[i] != 1) {
            std::cout << weightCoeffs[i] << ", ";
        }
    }
}
