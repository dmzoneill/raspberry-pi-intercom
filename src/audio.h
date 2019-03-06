#pragma once

#include <atomic>
#include <mutex>
#include <thread>
#include <queue>

#include <speex/speex_echo.h>
#include <speex/speex_preprocess.h>
#include <alsa/asoundlib.h>

using namespace std;

#define RATE 22050       // Hz
#define SAMPLE_SIZE 2    // 16 bits
#define SAMPLE_BY_FRAME 256  // Must be a power of 2, MAX 16384, around 10ms so ~ RATE/10 = 220 => 256
#define FRAME_SIZE (SAMPLE_BY_FRAME * SAMPLE_SIZE)
#define FILTER_LENGTH (10*SAMPLE_BY_FRAME)   // Echo filter, should be around 100ms

struct CAudioFrame {
    typedef shared_ptr<CAudioFrame> Ptr;
    char buf [FRAME_SIZE];
};

class CAudio {
public :
    
    void Init ();
    void AudioOnOff (bool abOn);
    void Play ();
    void Push (CAudioFrame::Ptr apFrame);
    void Record ();
    void Stop ();
    bool SetOwner (string aOwner, bool bWantToOwn);
    string GetOwner () {return mOwner;};
    
protected :
    int  StartPcm (const char* aName, bool bRecord);
    void StopPcm (bool bRecord);
    
    void PlayThread ();
    void RecordThread ();
    
    thread mPlayThread;
    thread mRecordThread;
    atomic<bool> mbPlay;
    atomic<bool> mbRecord;
    mutex mMutexQueue;
    queue<CAudioFrame::Ptr> mFramesQueue;
    long mOutputAudioOn;
    atomic<char> mNbAudioUser;
    string mOwner;
    SpeexEchoState* mEchoState;
    SpeexPreprocessState* mPreprocessState;
    snd_pcm_t* mPlayPcmHandle;
    snd_pcm_t* mRecordPcmHandle;
};

extern CAudio Audio;
