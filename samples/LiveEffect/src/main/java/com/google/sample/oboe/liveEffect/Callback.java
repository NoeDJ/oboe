package com.google.sample.oboe.liveEffect;

public interface Callback {
    void onBufferAvailable(byte[] buffer);
}