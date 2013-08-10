externals for puredata
======================

* **f0_auto_scale** - finds min and max values of a stream of numbers and uses them as input scaling range
* **f0_beats_to_frames** - calculates how many [video]frames will fit in x beats
* **f0_construct** - a constructive constructor
* **f0_distance** - calculate the distance between successive (delta) points in 1, 2 or 3 dimensions
* **f0_fmod** - floating-point modulo operator
* **f0_fold** - fold float and integer numbers to a specified range
* **f0_frames_to_beats** - calculates how many beats will fit in x [video]frames
* **f0_gcd** - find the greatest common divisor
* **f0_inc_dec_split** - detect direction of incoming values and split to different outlets
* **f0_limit_counter** - a different counter with floor and ceiling
* **f0_noergaard** - per nørgård's infinity series
* **f0_range** - finds minimum, middle and maximum values from a stream of values
* **f0_range2** - similar to **f0_range** but with an added smooth factor
* **f0_ratio** - keep width/height proportion
* **f0_round** - round values to nearest quantised value
* **f0_slub** - generate cpu spikes - disrupt timing version
* **f0_slub~** - generate cpu spikes - audio click version
* **f0_smooth** - single exponential smoothing. good for filtering data from sensors
* **f0_smooth2** - double exponential smoothing
* **f0_snap** - smooth by snapping
* **f0_tune** - an external that "quantise" frequencies
* **f0_wrap** - wrap float or integer numbers

see also <http://www.fredrikolofsson.com/pages/code-pd.html>

the max/msp equivalents are here... <http://www.fredrikolofsson.com/pages/code-max.html>

download&install
----------------
osx: download this zipped archive and extract the folder `f0extpd_osx`.  (the other stuff you can trash).  put the f0extpd_osx folder somewhere on your harddrive, open pd and go to preferences/path and add the folder there.

(optional) build
----------------
open terminal, cd to source folder and type `make` and then `make install`.

on mac osx that should build and automatically copy all the externals+helpfiles to your `~/Library/Pd` folder.

todo
----
* f0.auto_scale~
* f0.distance~
* f0.range~
* f0.range2~
* f0.smooth~
* f0.smooth2~
* f0.tune~
* f0.ultimate_counter
