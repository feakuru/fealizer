#include "equalizer.h"

EqualizerStream::EqualizerStream(const char* filename) {
    filter = new IIRFilterFromMatlab(filename);
}

void EqualizerStream::streamFromFile(const std::string &filename)
{
    // load audio buffer from a sound file
    buffer.loadFromFile(filename);
    load(buffer);
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

bool EqualizerStream::onGetData(Chunk& data)
{
    // number of samples to stream every time the function is called;
    // in a more robust implementation, it should be a fixed
    // amount of time rather than an arbitrary number of samples
    const int samplesToStream = buffer.getSampleRate();
    sf::Int16* new_samples = new sf::Int16[samplesToStream];
    for (size_t sample_num = 0; sample_num < samplesToStream; sample_num++) {
        try {
            new_samples[sample_num] = m_samples.at(m_currentSample + sample_num);
        }
        catch (std::out_of_range& e) {
            break;
        }
    }
    filter->filter(new_samples, samplesToStream);
    // set the pointer to the next audio samples to be played
    // sf::Int16 smpl = 0;
    // double coeff = 0.0;
    // sf::Int16 tmp_for_smpl = 0;
    //     try {
    //         tmp_for_smpl = smpl;
    //         coeff = weightCoeffs[sample_num];
    //         new_samples[sample_num] = smpl * coeff;
    //         if (coeff != 0 && new_samples[sample_num] / coeff != 0) {
    //             new_samples[sample_num] = tmp_for_smpl;
    //         }
    //     }
    //     catch (std::out_of_range& e) {
    //         break;
    //     }
    // }
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

void EqualizerStream::onSeek(sf::Time timeOffset)
{
    // compute the corresponding sample index according to the sample rate and channel count
    m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
}
