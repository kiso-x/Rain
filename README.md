_Rain{#mainpage}
=======================

# BRIEF

# What is __rain_

- Granular Synth with some extra features running on Rhaspberry PI
- loop-based Grainplayer
- Master section with filter and bitcrusher
- Control via OSC

## Features Grainplayer
- position: start sample of the section 
- Loop length: length of the section in samples 
- Loop mode 
 - infinite forward 
 - infinite backwards 
 - infinite forward / backward 
- Playback speed (pitch)
- Grain length: length of the window 

## _rain modes
- forward: Grainplayer is running forward
- backward: Grainplayer is running backwards
- forward/backward: Grainplayer is running forward/backwards
- funk (optional): randomizes propagation

## texture / choppy
- controls how far the grains jump during playback 

## color
- Lowpass (+ Bitcrusher): filters the overtones of the master signal with lowpass, distort the filtered signal with bitcrusher 

# Libraries
The following libraries are used within this project:

* JACK
* libsndfile
* liblo

# Usage

The binaray granular_example expects three
command line arguments:

- the wav file to read with the flag '-f'
- the grain size in samples '-l'

```console
~/rain $ ./rain -f ../../wav/dopesample.wav -l 1000
```
