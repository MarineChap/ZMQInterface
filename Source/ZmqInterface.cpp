/*
 ------------------------------------------------------------------
 
 ZMQInterface
 Copyright (C) 2016 FP Battaglia
 Copyright (C) 2017-2019 Andras Szell
 
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

    ZmqInterface.cpp
    Created: 19 Sep 2015 9:47:12pm
    Author:  Francesco Battaglia
    Updated by: Andras Szell

  ==============================================================================
*/

#include <zmq.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <chrono>
#include <errno.h>
#include "ZmqInterface.h"
#include "ZmqInterfaceEditor.h"

#define DEBUG_ZMQ
const int MAX_MESSAGE_LENGTH = 64000;

ZmqInterface::ZmqInterface()
    : GenericProcessor("Zmq Flatbuffer Interface")
{
    context = zmq_ctx_new();
    socket = 0;
    flag = 0;
    messageNumber = 0;
    dataPort = 3335;

    setProcessorType(PROCESSOR_TYPE_FILTER);
}

ZmqInterface::~ZmqInterface()
{
    closeDataSocket();
    if (context)
    {
        zmq_ctx_destroy(context);
        context = 0;
    }
}


int ZmqInterface::createDataSocket()
{
    if (!socket)
    {
        socket = zmq_socket(context, ZMQ_PUB);
        if (!socket)
            return -1;
        String urlstring;
        urlstring = String("tcp://*:") + String(dataPort);
        std::cout << urlstring << std::endl;
        int rc = zmq_bind(socket, urlstring.toRawUTF8());
        if (rc)
        {
            std::cout << "couldn't open data socket" << std::endl;
            std::cout << zmq_strerror(zmq_errno()) << std::endl;
            jassert(false);
        }
    }
    return 0;
}

int ZmqInterface::closeDataSocket()
{
    if (socket)
    {
        std::cout << "close data socket" << std::endl;
        int rc = zmq_close(socket);
        socket = 0;
    }
    return 0;
}

#include "channel_generated.h"

void ZmqInterface::sendData(AudioSampleBuffer& buffer, int nRealSamples,
                           int64 timestamp, int sampleRate)
{
    
    messageNumber++;
    int nChannels =  buffer.getNumChannels();
    int nSamples =  buffer.getNumSamples();


    // copy data onto buffers for each configured channel group
    std::vector<float> real_data;
    real_data.reserve(nRealSamples*nChannels);

    for (auto i=0; i<nChannels; i++) {

      auto start_index = buffer.getReadPointer(i);
      real_data.insert(real_data.end(), start_index,
                        start_index + nRealSamples);
    }
    // Create message

    flatbuffers::FlatBufferBuilder builder(1024);

    auto samples = builder.CreateVector(real_data);

    auto zmqbuffer = CreateContinuousData(builder, samples, nChannels, nRealSamples, timestamp, messageNumber, sampleRate);
    builder.Finish(zmqbuffer);
    uint8_t *buf = builder.GetBufferPointer();
    int size = builder.GetSize();
    // Send data
    zmq_msg_t request;
    zmq_msg_init_size(&request, size);
    memcpy(zmq_msg_data(&request), (void *)buf, size);
    int size_m = zmq_msg_send(&request, socket, 0);
    zmq_msg_close(&request);
}

AudioProcessorEditor* ZmqInterface::createEditor()
{
    editor = new ZmqInterfaceEditor(this, true);
    return editor;
}

void ZmqInterface::process(AudioSampleBuffer& buffer)
{
    if (!socket)
        createDataSocket();
    
    // current timestamp is at the end of the buffer; we want to send the timestamp of the first sample instead
    
    uint64_t firstTs = getTimestamp(0);
    float sampleRate;

    // Simplified sample rate detection (could check channel type or report
    // sampling rate of all channels separately in case they differ)
    if (dataChannelArray.size() > 0) 
    {
        sampleRate = dataChannelArray[0]->getSampleRate();
    }
    else 
    {   // this should never run - if no data channels, then no data...
        sampleRate = CoreServices::getGlobalSampleRate();
    }

    if(getNumSamples(0) > 0){
        sendData(buffer, getNumSamples(0), firstTs, (int)sampleRate);
    }

}

