//
// Created by MATABUMI 01 on 10/9/2019.
//

#include <oboe/AudioStreamBuilder.h>
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
        __android_log_print(ANDROID_LOG_ERROR,
                            "AudioEngine",
                            "Error opening stream %s",
                            convertToText(result));
    }

    result = stream -> requestStart();
    if (result != oboe::Result::OK){
        __android_log_print(ANDROID_LOG_ERROR,
                            "AudioEngine",
                            "Error starting stream %s",
                            convertToText(result));

    }



}


