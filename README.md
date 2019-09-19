# Rain
 Granular Synthesizer for Rhaspberry Pi


# What is __rain_

- Granular Synth with some extra features running on Rhaspberry PI
- 4 loopbasierte Grainplayer
- Mastersektion mit Filter (opt. Bitcrusher)
- Steuerung via OSC (PD oder App)


## schmematischer Aufbau
- 4 unabhänige Grainplayer
- gemeinsamter LFO gesteuerter Lowpassfilter
- parrallel Bitcrusher
- VCA

## Eigenschaften Grainplayer
- Position: Startsample des Ausschnitts
- Looplänge: Länge des Ausschnitts in Samples
- Loop Modus
 - unendlich vorwärts
 - unendlich rückwärts
 - unendlich vor/rückwärts
- Wiedergabegeschwindigkeit (Pitch)
- Grainlänge: Länge des Fensters

## _rain Modes
- straight: alle Grainplayer laufen vorwärts
- funky: zufällige Auswahl von Loopmodes der Grainplayer
- chaotic: funky + Grains in unterschiedlicher Reihenfolge
- backwards: alle Grainplayer laufen rückwärts

## texture / choppy
- regelt wie viel Grains bei der Wiedergabe übersprungen werden

## harmonic Modes
- normal: unveränderter Pitch
- harmonic: Pitch (+/- 12 Semintones) pro Grainplayer
- chord: Grainplayer 1 stellt den Grundton dar (+/- 12 Semintones), Grainplayer 2-4 relativ Dur/Moll gestimmt.

## colour

Lowpass (+ Bitcrusher): filtern der Obertöne des Mastersignals mittels Lowpass, verzerren des gefilterten Signals mittels Bitcrushers

-> Überblenden zwischen alten und neuen Obertönen

-> Mittenfrequenz invers proportional zu Bitcrusher Anteil
