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

    ZmqInterfaceEditor.cpp
    Created: 22 Sep 2015 9:42:44am
    Author:  Francesco Battaglia

  ==============================================================================
*/




#include "ZmqInterfaceEditor.h"
#include "ZmqInterface.h"


ZmqInterfaceEditor::ZmqInterfaceEditor(GenericProcessor *parentNode, bool useDefaultParameters): GenericEditor(parentNode, useDefaultParameters)
{
    ZmqProcessor = (ZmqInterface *)parentNode;

    dataPortEditor = new TextEditor("dataport");
    addAndMakeVisible(dataPortEditor);
    dataPortEditor->setBounds(10, 110, 40, 16);
    dataPortEditor->setText(String(ZmqProcessor->getDataPort()));

    portButton = new TextButton("set_ports");
    addAndMakeVisible(portButton);
    portButton->setBounds(90, 110, 40, 16);
    portButton->setButtonText("set ports");
    portButton->addListener(this);

}

ZmqInterfaceEditor::~ZmqInterfaceEditor()
{
    deleteAllChildren();
}


void ZmqInterfaceEditor::buttonClicked(Button* button)
{
    if (button == portButton)
    {
        String dport = dataPortEditor->getText();
        int dportVal = dport.getIntValue();
        if ( (dportVal == 0) && !dport.containsOnly("0")) {
            // wrong integer input
            CoreServices::sendStatusMessage("Invalid data port value");
            dataPortEditor->setText(String(ZmqProcessor->getDataPort()));
        }else {
            ZmqProcessor->setPorts(dportVal);
            CoreServices::sendStatusMessage("ZMQ port updated");
        }
    }
}

void ZmqInterfaceEditor::startAcquisition()
{
    portButton->setEnabled (false);
    dataPortEditor->setEnabled (false);
}


void ZmqInterfaceEditor::stopAcquisition()
{
    portButton->setEnabled (true);
    dataPortEditor->setEnabled (true);
}


