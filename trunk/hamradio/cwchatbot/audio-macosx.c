/*
 * Copyright (C) 2005 Serge Vakulenko, <vak@cronyx.ru>
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You can redistribute this file and/or modify it under the terms of the GNU
 * General Public License (GPL) as published by the Free Software Foundation;
 * either version 2 of the License, or (at your discretion) any later version.
 * See the accompanying file "COPYING" for more details.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <CoreAudio/AudioHardware.h>
#include "audio.h"

static int audio_channels;
static int buffer_size;
static AudioDeviceID outdev;
static AudioDeviceIOProcID audio_callback_id;

/*
 * Ring buffer
 */
#define MAXSAMPLES 50000

static short buffer [MAXSAMPLES];
static unsigned int buf_read_pos;
static unsigned int buf_count;

static pthread_mutex_t buffer_mutex; /* mutex covering buffer variables */
static pthread_cond_t buffer_mailbox;

/*
 * The function that the CoreAudio thread calls when it wants more data
 */
static OSStatus audio_callback (
        AudioDeviceID         device,
        AudioTimeStamp const  *now,
	AudioBufferList const *input_data,
        AudioTimeStamp const  *input_time,
	AudioBufferList       *output_data,     /* put data here */
        AudioTimeStamp const  *output_time,
	void                  *client_data)
{
	float *output_ptr, *limit;
	float sample;

	/* Fill buffer with audio data. */
	output_ptr = (float*) output_data->mBuffers[0].mData;
	limit = output_ptr + buffer_size / sizeof (float);

	/* Accessing common variables, locking mutex */
	pthread_mutex_lock (&buffer_mutex);
	while (output_ptr < limit) {
                if (buf_read_pos >= buf_count) {
                    buf_read_pos = 0;
                    buf_count = audio_output (buffer, MAXSAMPLES);
//printf ("[%d] ", buf_count); fflush (stdout);
                    if (buf_count == 0)
                        break;
                }
                sample = buffer [buf_read_pos++] / 32767.0;

		*output_ptr++ = sample;
		if (audio_channels > 1)
			*output_ptr++ = sample;
	}
	pthread_mutex_unlock (&buffer_mutex);
	pthread_cond_signal (&buffer_mailbox);

	/* Return the number of prepared bytes. */
	int nbytes = (char*) output_ptr -
                     (char*) output_data->mBuffers[0].mData;
	output_data->mBuffers[0].mDataByteSize = nbytes;
//printf ("%d ", nbytes); fflush (stdout);
	return 0;
}

/*
 * Initialize the audio output, but do not start it yet.
 * Return sample rate.
 */
int audio_init ()
{
	AudioStreamBasicDescription outinfo;
	OSStatus status;
	unsigned size;
	unsigned int buflen;
        AudioObjectPropertyAddress property_address = {
                0,                                  // mSelector
                kAudioObjectPropertyScopeGlobal,    // mScope
                kAudioObjectPropertyElementMaster   // mElement
        };

	pthread_mutex_init (&buffer_mutex, 0);
	pthread_cond_init (&buffer_mailbox, 0);

	/* Get default output device */
        property_address.mSelector = kAudioHardwarePropertyDefaultOutputDevice;
        outdev = kAudioObjectUnknown;
        size = sizeof(outdev);
        status = AudioObjectGetPropertyData (kAudioObjectSystemObject,
                &property_address, 0, 0, &size, &outdev);
	if (status || outdev == kAudioObjectUnknown) {
		fprintf (stderr, "audio: cannot get audio device\n");
		exit (-1);
	}

	/* Get default output format */
        property_address.mSelector = kAudioDevicePropertyStreamFormat;
	size = sizeof (outinfo);
        status = AudioObjectGetPropertyData (outdev, &property_address,
            0, 0, &size, &outinfo);
	if (status) {
		fprintf (stderr, "audio: cannot get audio stream format\n");
		exit (-1);
	}
	if (outinfo.mFormatID != kAudioFormatLinearPCM) {
		fprintf (stderr, "audio: unsupported audio format = %u\n",
                        outinfo.mFormatID);
		exit (-1);
	}
	if (! (outinfo.mFormatFlags & kAudioFormatFlagIsFloat)) {
		fprintf (stderr, "audio: no support for float audio format, flags = %#x\n",
                        outinfo.mFormatFlags);
		exit (-1);
	}
	if (outinfo.mFramesPerPacket != 1) {
		fprintf (stderr, "audio: too many frames per packet = %u\n",
                        outinfo.mFramesPerPacket);
		exit (-1);
	}
	if (outinfo.mBytesPerFrame / outinfo.mChannelsPerFrame != sizeof (float)) {
		fprintf (stderr, "audio: bad sample size = %u, expected %lu\n",
                        outinfo.mBytesPerFrame / outinfo.mChannelsPerFrame, sizeof (float));
		exit (-1);
	}

	/* get requested buffer length */
        property_address.mSelector = kAudioDevicePropertyBufferSize;
	size = sizeof (buflen);
        status = AudioObjectGetPropertyData (outdev, &property_address,
            0, 0, &size, &buflen);
	if (status) {
		fprintf (stderr, "audio: cannot get audio buffer length\n");
		exit (-1);
	}

	audio_channels = outinfo.mChannelsPerFrame;
	buffer_size = buflen;
//printf ("%lu samples per buffer\n", buffer_size / sizeof (float) / audio_channels);
//printf ("%lu buffers per second\n", (unsigned) outinfo.mSampleRate * sizeof (float) * audio_channels / buffer_size);

	/* Set the IO proc that CoreAudio will call when it needs data */
        audio_callback_id = 0;
        status = AudioDeviceCreateIOProcID (outdev, audio_callback,
            0, &audio_callback_id);
	if (status) {
		fprintf (stderr, "audio: cannot add audio i/o procedure\n");
		exit (-1);
	}

	return (unsigned) outinfo.mSampleRate;
}

/*
 * Start audio output.
 */
void audio_start ()
{
	OSStatus status;

	/* Start callback */
	status = AudioDeviceStart (outdev, audio_callback);
	if (status) {
		fprintf (stderr, "audio: cannot start audio device\n");
		exit (-1);
	}
}

/*
 * Stop audio output.
 */
void audio_stop ()
{
	OSStatus status;

	/* Start callback */
	status = AudioDeviceStop (outdev, audio_callback);
	if (status) {
		fprintf (stderr, "audio: cannot stop audio device\n");
		exit (-1);
	}
}

#if 0
/*
 * Wait until all the audio output data are played.
 */
void audio_flush ()
{
	if (! device_started)
		audio_start ();

	pthread_mutex_lock (&buffer_mutex);
	while (buf_count != buf_read_pos) {
		pthread_mutex_unlock (&buffer_mutex);
		pthread_cond_wait (&buffer_mailbox, &buffer_mutex);
	}
	pthread_mutex_unlock (&buffer_mutex);
}

/*
 * Add a sample to output data.
 */
void audio_output (float sample)
{
	int next_write_pos;

	pthread_mutex_lock (&buffer_mutex);
again:
	next_write_pos = buf_count + 1;
	if (next_write_pos >= MAXSAMPLES)
		next_write_pos = 0;

	if (next_write_pos == buf_read_pos) {
		/* buffer is full */
		pthread_mutex_unlock (&buffer_mutex);
		if (! device_started)
			audio_start ();
		pthread_cond_wait (&buffer_mailbox, &buffer_mutex);
		goto again;
	}

	buffer [buf_count] = sample;
	buf_count = next_write_pos;

	pthread_mutex_unlock (&buffer_mutex);
}
#endif
