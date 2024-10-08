/*
 * Copyright (C) 2010, British Broadcasting Corporation
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

#ifndef BMX_ESSENCE_PARSER_H_
#define BMX_ESSENCE_PARSER_H_


#include <bmx/BMXTypes.h>
#include <utility>


#define ESSENCE_PARSER_NULL_OFFSET          0xffffffff
#define ESSENCE_PARSER_NULL_FRAME_SIZE      0x00000000



namespace bmx
{


class ParsedFrameSize
{
public:
    ParsedFrameSize();
    ParsedFrameSize(const ParsedFrameSize &other);
    ParsedFrameSize(uint32_t frame_size);
    ParsedFrameSize(std::pair<uint32_t, uint32_t> field_sizes);
    ~ParsedFrameSize();

    ParsedFrameSize& operator=(const ParsedFrameSize &other);

    std::pair<uint32_t, uint32_t> GetFieldSizes() const;
    uint32_t GetFirstFieldSize() const;
    uint32_t GetSecondFieldSize() const;
    uint32_t GetSize() const;
    uint32_t GetFirstFieldOrFrameSize() const;

    bool IsUnknown() const;
    bool IsNull() const;

    bool IsFrame() const;
    bool IsFields() const;

    bool HaveFirstField() const;
    bool HaveSecondField() const;
    bool HaveFirstFieldOrFrame() const;

    bool IsComplete() const;

    void SetSize(uint32_t size);
    void SetFirstFieldSize(uint32_t size);
    void SetSecondFieldSize(uint32_t size);

    bool CompleteSize(uint32_t data_size);

    void Reset();

private:
    bool mIsFields;
    std::pair<uint32_t, uint32_t> mFieldSizes;
};


class EssenceParser
{
public:
    virtual ~EssenceParser() {}

    virtual uint32_t ParseFrameStart(const unsigned char *data, uint32_t data_size) = 0;

    virtual void ResetParseFrameSize() = 0;
    virtual uint32_t ParseFrameSize(const unsigned char *data, uint32_t data_size);
    virtual ParsedFrameSize ParseFrameSize2(const unsigned char *data, uint32_t data_size);

    virtual void ParseFrameInfo(const unsigned char *data, uint32_t data_size);
    virtual ParsedFrameSize ParseFrameInfo2(const unsigned char *data, ParsedFrameSize frame_size);
};


};



#endif

