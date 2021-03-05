/*
 ------------------------------------------------------------------
 
 ZMQInterface
 Copyright (C) 2016 FP Battaglia
 
 based on
 Open Ephys GUI
 Copyright (C) 2013, 2015 Open Ephys
 
 ------------------------------------------------------------------
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 */
/*
  ==============================================================================

    ZmqInterface.h
    Created: 19 Sep 2015 9:47:12pm
    Author:  Francesco Battaglia

  ==============================================================================
*/

#ifndef ZMQINTERFACE_H_INCLUDED
#define ZMQINTERFACE_H_INCLUDED


#include <ProcessorHeaders.h>

#include <queue>



//=============================================================================
/*
 */
class ZmqInterface: public GenericProcessor
{
public:
    ZmqInterface();
    ~ZmqInterface();
    
    virtual bool isSource(){ return false;};
    virtual bool isSink(){return false;}
    
    /** Defines the functionality of the processor.
     
     The process method is called every time a new data buffer is available.
     
     Processors can either use this method to add new data, manipulate existing
     data, or send data to an external target (such as a display or other hardware).
     
     Continuous signals arrive in the "buffer" variable, event data (such as TTLs
     and spikes) is contained in the "events" variable, and "nSamples" holds the
     number of continous samples in the current buffer (which may differ from the
     size of the buffer).
     */

    virtual void process(AudioSampleBuffer& continuousBuffer);
    
    AudioProcessorEditor* createEditor();
    bool hasEditor() const {return true;};
    bool isReady() const {return true;};

    void setPorts(uint32_t newDataPort){
        dataPort = newDataPort;
        closeDataSocket();
        createDataSocket();
    }
    uint32_t getDataPort () const { return dataPort; }

private:

    int createDataSocket();
    int closeDataSocket();

    int sendData(AudioSampleBuffer& continuousBuffer, int nRealSamples, 
                 int64 timestamp, int sampleRate);

    void *context;
    void *socket;
    
    int flag;
    int messageNumber;
    int dataPort; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ZmqInterface);
    
};






#endif  // ZMQINTERFACE_H_INCLUDED
