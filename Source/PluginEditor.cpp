/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

#include <windows.h>
#include <commdlg.h>


#include <string>
#include <cstdlib> // for system function
#include <fstream>
#include <shlobj.h>
#include <regex>



std::string getFilenameFromPath(const std::string& path) {
    // Find the last occurrence of the path separator and get the substring after it
    size_t pos = path.find_last_of("/\\");
    if (pos != std::string::npos) {
        return path.substr(pos + 1);
    }
    return path;
}

std::string openFileDialog()
{
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
    ofn.lpstrFilter = "All Files\0*.*\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = "Select a File";
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn))
    {
        return fileName;
    }
    return "";
}


std::string openFolderDialog()
{
    BROWSEINFO bi = { 0 };
    bi.lpszTitle = "Select a Folder";
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != 0)
    {
        // Get the name of the folder and put it in path.
        char path[MAX_PATH];
        if (SHGetPathFromIDList(pidl, path))
        {
            CoTaskMemFree(pidl);
            return path;
        }
        // Free memory used.
        CoTaskMemFree(pidl);
    }
    return "";
}



//==============================================================================
Audio_ConverterAudioProcessorEditor::Audio_ConverterAudioProcessorEditor (Audio_ConverterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    if(getFolderPath() == 1){
        show_path.setText("Please select output folder.", juce::dontSendNotification);
    }
    else{
        show_path.setText("Please select file to convert.", juce::dontSendNotification);
    }
    upload.setClickingTogglesState(true);
    upload.onClick = [&]{
      std::string filePath = openFileDialog();
      if (!filePath.empty())
      {
          // The selected file path is available in filePath
          DBG("Selected file path: " + juce::String(filePath));
          filename = filePath;
          show_path.setText(juce::String(filePath), juce::dontSendNotification);
      }
    };

    opf.setClickingTogglesState(true);
    opf.onClick = [&]{
      std::string filePath = openFolderDialog();
      if (!filePath.empty())
      {
          // The selected file path is available in filePath
          DBG("Selected file path: " + juce::String(filePath));
          folder = filePath;
          std::ofstream outfile("root.txt");
          outfile << folder;
          outfile.close();
          folder_state = true;
          show_path.setText("Please select file to convert.", juce::dontSendNotification);
          //show_path.setText(juce::String(filePath), juce::dontSendNotification);
      }
    };

    convert.setClickingTogglesState(true);
    convert.onClick = [&]{
        if(!folder_state){
            show_path.setText("Select output folder first!.", juce::dontSendNotification);
        }
        else{
            std::string name =  getFilenameFromPath(filename);
            std::string output = folder + '\\' + name;
            output = std::regex_replace(output, std::regex("\\.m4a$"), ".mp3");
            std::string command = "C:\\Users\\jerryyyyy708\\VST_Plugins\\Audio_Converter\\Source\\ffmpeg.exe -i "+ filename + " " + output;
            //command = "dir >> C:\\Users\\jerryyyyy708\\output.txt";
            int result = system(command.c_str());
            //DBG(juce::String(name));
            DBG(juce::String(command));
            DBG(juce::String(result));
        }
    };
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(upload);
    addAndMakeVisible(opf);
    addAndMakeVisible(convert);
    addAndMakeVisible(show_path);
    setSize (400, 300);
}

Audio_ConverterAudioProcessorEditor::~Audio_ConverterAudioProcessorEditor()
{
}

//==============================================================================
void Audio_ConverterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Audio_ConverterAudioProcessorEditor::resized()
{

  upload.setBounds(getWidth()/2-120, getHeight()/2-25, 80, 30);
  opf.setBounds(getWidth()/2-50, getHeight()/2-140, 120, 30);
  convert.setBounds(getWidth()/2 + 40 , getHeight()/2-25, 80, 30);

  show_path.setBounds(10, upload.getBottom() -80, getWidth() - 20, 40);
  show_path.setColour(juce::Label::backgroundColourId, juce::Colours::grey);
  show_path.setColour(juce::Label::textColourId, juce::Colours::white);
  show_path.setJustificationType(juce::Justification::centred);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


int Audio_ConverterAudioProcessorEditor::getFolderPath()
{
    std::ifstream infile("root.txt"); // Open the file in read mode
    if (infile.is_open()) // Check if the file opened successfully
    {
        std::getline(infile, folder); // Read the first line into the 'folder' member variable
        infile.close(); // Close the file
        folder_state = true;
        return 0;
    }
    else
    {
        // Handle the error, such as setting a default value or showing an error message
       return 1;
    }
}