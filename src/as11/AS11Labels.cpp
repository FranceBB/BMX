/*
 * Copyright (C) 2016, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
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

#include <bmx/as11/AS11Labels.h>

#include <bmx/Utils.h>
#include <bmx/BMXException.h>
#include <bmx/Logging.h>

using namespace std;
using namespace bmx;


static const MCALabelEntry AS11_MCA_LABELS[] =
{
    {AUDIO_CHANNEL_LABEL,               "chADSSdc",   "AD Studio Signal Data Channel",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x01, 0x0d, 0x01, 0x08, 0x01, 0x01, 0x01, 0x01, 0x00}},
    {SOUNDFIELD_GROUP_LABEL,            "sgADSS",     "AD Studio Signal",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x01, 0x0d, 0x01, 0x08, 0x01, 0x01, 0x02, 0x01, 0x00}},
    {GROUP_OF_SOUNDFIELD_GROUP_LABEL,   "ggAPg",      "Alternative Program",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x01, 0x0d, 0x01, 0x08, 0x01, 0x01, 0x03, 0x01, 0x00}},
    {GROUP_OF_SOUNDFIELD_GROUP_LABEL,   "ggADPgMx",   "Audio Description Programme Mix",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x01, 0x0d, 0x01, 0x08, 0x01, 0x01, 0x03, 0x02, 0x00}},
    {GROUP_OF_SOUNDFIELD_GROUP_LABEL,   "ggAD",       "Audio Description",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x01, 0x0d, 0x01, 0x08, 0x01, 0x01, 0x03, 0x03, 0x00}},
    {GROUP_OF_SOUNDFIELD_GROUP_LABEL,   "ggME",       "Music and Effects",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x01, 0x0d, 0x01, 0x08, 0x01, 0x01, 0x03, 0x04, 0x00}},
    {AUDIO_CHANNEL_LABEL,               "chL",        "Left",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d, 0x03, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00}},
    {AUDIO_CHANNEL_LABEL,               "chR",        "Right",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d, 0x03, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00}},
    {AUDIO_CHANNEL_LABEL,               "chC",        "Center",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d, 0x03, 0x02, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00}},
    {AUDIO_CHANNEL_LABEL,               "chLFE",      "LFE",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d, 0x03, 0x02, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00}},
    {AUDIO_CHANNEL_LABEL,               "chLs",       "Left Surround",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d, 0x03, 0x02, 0x01, 0x05, 0x00, 0x00, 0x00, 0x00}},
    {AUDIO_CHANNEL_LABEL,               "chRs",       "Right Surround",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d, 0x03, 0x02, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00}},
    {AUDIO_CHANNEL_LABEL,               "chVIN",      "Visually Impaired Narrative",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d, 0x03, 0x02, 0x01, 0x0f, 0x00, 0x00, 0x00, 0x00}},
    {SOUNDFIELD_GROUP_LABEL,            "sg51",       "5.1",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d, 0x03, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00}},
    {SOUNDFIELD_GROUP_LABEL,            "sgST",       "Standard Stereo",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d, 0x03, 0x02, 0x02, 0x20, 0x01, 0x00, 0x00, 0x00}},
    {GROUP_OF_SOUNDFIELD_GROUP_LABEL,   "ggMPg",      "Main Program",
        {0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0d, 0x03, 0x02, 0x03, 0x20, 0x01, 0x00, 0x00, 0x00}},
};


bool bmx::index_as11_mca_labels(MCALabelHelper *labels_helper)
{
    return labels_helper->IndexLabels(AS11_MCA_LABELS, BMX_ARRAY_SIZE(AS11_MCA_LABELS));
}
