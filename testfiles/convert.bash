#!/bin/bash

for f in *.wav; do 
	echo "Processing $f to $f.raw..";
	ffmpeg -i $f -f s16be -ar 8000 -acodec pcm_s16be "`basename $f .wav`.raw"
done
