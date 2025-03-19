# externals for pure-data

Some of my Max externals ported to [Pure Data](https://www.puredata.info)

- f0_auto_scale - Find minimum and maximum values of a stream of numbers and uses them as input scaling range.
- f0_construct - A constructive constructor.
- f0_distance - Calculate delta distance in 1, 2 or 3 dimensions.
- f0_fmod - Floating-point modulo operator.
- f0_fold - Fold float and integer numbers to a specified range.
- f0_gcd - Greatest common divisor.
- f0_inc_dec_split - Detect direction of incoming values and split to different outlets.
- f0_limit_counter - A different counter with floor and ceiling.
- f0_noergaard - Per Nørgård's infinity series.
- f0_range - Find minimum, middle and maximum values from a stream of values.
- f0_range2 - Similar to f0_range but with an added smooth factor.
- f0_round - Round values to nearest quantised value.
- f0_slub - Generate CPU spikes - disrupt timing version.
- f0_slub~ - Generate CPU spikes - audio click version.
- f0_smooth - Single exponential smoothing. Good for filtering data from sensors.
- f0_smooth2 - Double exponential smoothing.
- f0_snap - Smooth by snapping.
- f0_tune - Frequency quantiser.
- f0_wrap - Wrap float or integer numbers.

Latest macOS version (x86_64 and arm64) available for download from... [releases/latest](http://github.com/redFrik/f0extpd/releases/latest).

For older 32- and 64-bit macOS/OSX, Windows and Linux releases see... <https://fredrikolofsson.com/code/pd/>

The Max/MSP equivalents are here... <https://github.com/redFrik/f0ext>

Distributed under GNU GPL license. See included file.


## Build

```
git clone --recursive https://github.com/redFrik/f0extpd.git
cd f0extpd
make
```

For building macOS "fat" binaries (intel and arm) use...
```
make arch="x86_64 arm64"
```

## Install

```
make install
make clean
```

On macOS this will put the externals in ~/Library/Pd


## version history

-----250319
* f0_limit_counter bugfix minimum and maximum arguments

-----250318
* modernised everything using pd-lib-builder
* helpfiles cleanup
* f0_limit_counter set minimum bugfix
* new builds for macOS (both intel and arm)
* deleted f0_overview.pd
* moved f0.beats_to_frames, f0.frames_to_beats and f0.ratio to the [f0abspd](https://github.com/redFrik/f0abspd) package

-----130810
* uploaded to github
* recompiled all externals with the makefiletemplate
* lots of clean up in the source code
* some bugfixes

-----070116
* minor update to all externals - trimmed the initial post to the pd-window

-----060830
* new external f0_wrap

-----060515
* fixed rand() bug in f0_construct

-----060512
* first release. all externals ported from max/msp. very minor differences. f0_limit_counter differs the most.
