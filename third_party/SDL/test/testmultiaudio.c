/*
  Copyright (C) 1997-2023 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_test.h>

#include "testutils.h"

#include <stdio.h> /* for fflush() and stdout */

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "testutils.h"

static SDL_AudioSpec spec;
static Uint8 *sound = NULL; /* Pointer to wave data */
static Uint32 soundlen = 0; /* Length of wave data */

typedef struct
{
    SDL_AudioDeviceID dev;
    int soundpos;
    SDL_AtomicInt done;
} callback_data;

static callback_data cbd[64];

static void SDLCALL
play_through_once(void *arg, Uint8 *stream, int len)
{
    callback_data *cbdata = (callback_data *)arg;
    Uint8 *waveptr = sound + cbdata->soundpos;
    int waveleft = soundlen - cbdata->soundpos;
    int cpy = len;
    if (cpy > waveleft) {
        cpy = waveleft;
    }

    SDL_memcpy(stream, waveptr, cpy);
    len -= cpy;
    cbdata->soundpos += cpy;
    if (len > 0) {
        stream += cpy;
        SDL_memset(stream, spec.silence, len);
        SDL_AtomicSet(&cbdata->done, 1);
    }
}

#ifdef __EMSCRIPTEN__
static void loop(void)
{
    if (SDL_AtomicGet(&cbd[0].done)) {
        emscripten_cancel_main_loop();
        SDL_PauseAudioDevice(cbd[0].dev);
        SDL_CloseAudioDevice(cbd[0].dev);
        SDL_free(sound);
        SDL_Quit();
    }
}
#endif

static void
test_multi_audio(int devcount)
{
    int keep_going = 1;
    int i;

#ifdef __ANDROID__
    SDL_Event event;

    /* Create a Window to get fully initialized event processing for testing pause on Android. */
    SDL_CreateWindow("testmultiaudio", 320, 240, 0);
#endif

    if (devcount > 64) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Too many devices (%d), clamping to 64...\n",
                     devcount);
        devcount = 64;
    }

    spec.callback = play_through_once;

    for (i = 0; i < devcount; i++) {
        const char *devname = SDL_GetAudioDeviceName(i, 0);
        SDL_Log("playing on device #%d: ('%s')...", i, devname);

        SDL_memset(&cbd[0], '\0', sizeof(callback_data));
        spec.userdata = &cbd[0];
        cbd[0].dev = SDL_OpenAudioDevice(devname, 0, &spec, NULL, 0);
        if (cbd[0].dev == 0) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Open device failed: %s\n", SDL_GetError());
        } else {
            SDL_PlayAudioDevice(cbd[0].dev);
#ifdef __EMSCRIPTEN__
            emscripten_set_main_loop(loop, 0, 1);
#else
            while (!SDL_AtomicGet(&cbd[0].done)) {
#ifdef __ANDROID__
                /* Empty queue, some application events would prevent pause. */
                while (SDL_PollEvent(&event)) {
                }
#endif
                SDL_Delay(100);
            }
            SDL_PauseAudioDevice(cbd[0].dev);
#endif
            SDL_Log("done.\n");
            SDL_CloseAudioDevice(cbd[0].dev);
        }
    }

    SDL_memset(cbd, '\0', sizeof(cbd));

    SDL_Log("playing on all devices...\n");
    for (i = 0; i < devcount; i++) {
        const char *devname = SDL_GetAudioDeviceName(i, 0);
        spec.userdata = &cbd[i];
        cbd[i].dev = SDL_OpenAudioDevice(devname, 0, &spec, NULL, 0);
        if (cbd[i].dev == 0) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Open device %d failed: %s\n", i, SDL_GetError());
        }
    }

    for (i = 0; i < devcount; i++) {
        if (cbd[i].dev) {
            SDL_PlayAudioDevice(cbd[i].dev);
        }
    }

    while (keep_going) {
        keep_going = 0;
        for (i = 0; i < devcount; i++) {
            if ((cbd[i].dev) && (!SDL_AtomicGet(&cbd[i].done))) {
                keep_going = 1;
            }
        }
#ifdef __ANDROID__
        /* Empty queue, some application events would prevent pause. */
        while (SDL_PollEvent(&event)) {
        }
#endif

        SDL_Delay(100);
    }

#ifndef __EMSCRIPTEN__
    for (i = 0; i < devcount; i++) {
        if (cbd[i].dev) {
            SDL_PauseAudioDevice(cbd[i].dev);
            SDL_CloseAudioDevice(cbd[i].dev);
        }
    }

    SDL_Log("All done!\n");
#endif
}

int main(int argc, char **argv)
{
    int devcount = 0;
    int i;
    char *filename = NULL;
    SDLTest_CommonState *state;

    /* Initialize test framework */
    state = SDLTest_CommonCreateState(argv, 0);
    if (state == NULL) {
        return 1;
    }

    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    /* Parse commandline */
    for (i = 1; i < argc;) {
        int consumed;

        consumed = SDLTest_CommonArg(state, i);
        if (!consumed) {
            if (!filename) {
                filename = argv[i];
                consumed = 1;
            }
        }
        if (consumed <= 0) {
            static const char *options[] = { "[sample.wav]", NULL };
            SDLTest_CommonLogUsage(state, argv[0], options);
            return 1;
        }

        i += consumed;
    }

    /* Load the SDL library */
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Log("Using audio driver: %s\n", SDL_GetCurrentAudioDriver());

    filename = GetResourceFilename(filename, "sample.wav");

    devcount = SDL_GetNumAudioDevices(0);
    if (devcount < 1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Don't see any specific audio devices!\n");
    } else {
        /* Load the wave file into memory */
        if (SDL_LoadWAV(filename, &spec, &sound, &soundlen) == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load %s: %s\n", filename,
                         SDL_GetError());
        } else {
            test_multi_audio(devcount);
            SDL_free(sound);
        }
    }

    SDL_free(filename);

    SDL_Quit();
    SDLTest_CommonDestroyState(state);

    return 0;
}
