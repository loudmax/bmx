/*
 * Copyright (C) 2023, Fraunhofer IIS
 * All Rights Reserved.
 *
 * Author: Nisha Bhaskar
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the British Broadcasting Corporation nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <bmx/writer_helper/JPEGXSWriterHelper.h>
#include <bmx/BMXException.h>
#include <bmx/Logging.h>

using namespace std;
using namespace bmx;
using namespace mxfpp;

JPEGXSWriterHelper::JPEGXSWriterHelper()
{
    mPosition = 0;
    mDescriptorHelper = 0;
    mEssenceParser = NULL; 
}

JPEGXSWriterHelper::~JPEGXSWriterHelper()
{
    if (mEssenceParser)
        delete mEssenceParser;
}

void JPEGXSWriterHelper::SetDescriptorHelper(JPEGXSMXFDescriptorHelper *descriptor_helper)
{
    mDescriptorHelper = descriptor_helper;
}

void JPEGXSWriterHelper::ProcessFrame(const unsigned char *data, uint32_t size)
{
    
    if (mDescriptorHelper->GetParseStatus())
    {
        if (!mEssenceParser)
            mEssenceParser = new JXSEssenceParser();
        mEssenceParser->ParseFrameInfo(data, size);
    }

    mPosition++;

    if (mPosition == 1)  // the first frame. mPosition has already been incremented
    {
        if(mDescriptorHelper->GetParseStatus())
            mDescriptorHelper->UpdateFileDescriptor(mEssenceParser);
        else
            mDescriptorHelper->UpdateFileDescriptor();
    }
}
