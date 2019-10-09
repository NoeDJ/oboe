//
// Created by MATABUMI 01 on 10/9/2019.
//

#include <oboe/oboe.h>
#include "AudioEngine.h"
#include "../../../../debug-utils/logging_macros.h"

void AudioEngine::start(){

    oboe::AudioStreamBuilder builder;
    builder.setDirection(oboe::Direction::Output);
    builder.setPerformanceMode(oboe::PerformanceMode::LowLatency);
    builder.setSharingMode(oboe::SharingMode::Exclusive);
    builder.setFormat(oboe::AudioFormat::Float);
    builder.setChannelCount(oboe::ChannelCount::Mono);

    oboe::AudioStream *stream;
    oboe::Result result = builder.openStream(&stream);
    if (result != oboe::Result::OK){
        LOGE("Error opening stream. Error: %s", oboe::convertToText(result));
    }

    result = stream -> requestStart();
    if (result != oboe::Result::OK){
        LOGE("Error starting stream. Error: %s", oboe::convertToText(result));
    }

    constexpr int kMilisecondstorecord = 2;
    const int32_t requestedFrames = (int32_t)(kMilisecondstorecord * (stream->getSampleRate()/oboe::kMillisPerSecond));
    int16_t mybuffer[requestedFrames];

    constexpr int64_t kTimeoutvalue = 3 * oboe::kNanosPerMillisecond;
    int framesRead = 0;
    do{
        auto result1 = stream->read(mybuffer,stream->getBufferSizeInFrames(),0);
        if (result1 != oboe::Result::OK) break;
        framesRead = result1.value();
    } while (framesRead != 0);

    while (isRecording){
        auto result2 = stream->read(mybuffer, requestedFrames, kTimeoutvalue);
        if (result2 == oboe::Result::OK){
            LOGD("Read %d frames", result2.value());
        } else{
            LOGE("Error reading stream. Error: %s", oboe::convertToText(result2.error()));
        }
    }
    stream->close();
}


