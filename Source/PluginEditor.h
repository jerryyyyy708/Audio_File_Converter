/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Audio_ConverterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Audio_ConverterAudioProcessorEditor (Audio_ConverterAudioProcessor&);
    ~Audio_ConverterAudioProcessorEditor() override;
    std::string filename = "";
    std::string folder=".";
    std::string root = "";
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    bool folder_state = false;
    int getFolderPath();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Audio_ConverterAudioProcessor& audioProcessor;
    juce::TextButton upload {"Upload"};
    juce::TextButton opf {"Set output path"}; //output folder
    juce::TextButton convert {"Convert"};
    juce::Label show_path;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Audio_ConverterAudioProcessorEditor)
};
