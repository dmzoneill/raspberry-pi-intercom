#pragma once

#include <atomic>
#include <mutex>
#include <thread>
#include <queue>

using namespace std;

#define RATE 22050  // Hz
#define FRAME_SIZE 2 // 16 bits
#define SAMPLE_SIZE 4096
#define FRAME_BY_SAMPLE (SAMPLE_SIZE / FRAME_SIZE)  // Must be a power of 2, MAX 16384

struct CAudioSample {
    typedef shared_ptr<CAudioSample> Ptr;
    char buf [SAMPLE_SIZE];
};

class CAudio {
public :
    
    void Init ();
    void AudioOnOff (bool abOn);
    void Play ();
    void Push (CAudioSample::Ptr apSample);
    void Record ();
    void Stop ();
    bool SetOwner (string aOwner, bool bWantToOwn);
    string GetOwner () {return mOwner;};
    
protected :
    void PlayThread ();
    thread mPlayThread;
    atomic<bool> mbPlay;
    void RecordThread ();
    thread mRecordThread;
    atomic<bool> mbRecord;
    mutex mMutexQueue;
    queue<CAudioSample::Ptr> mSamplesQueue;
    long mOutputAudioOn;
    atomic<char> mNbAudioUser;
    string mOwner;
};

extern CAudio Audio;
