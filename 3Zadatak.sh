#!/bin/bash
filedata='sm04010103101.wav'
filetext='sm04010103101.lab'
divider='10000000'
inc='1'
ukupno='ukupno'
sox --i sm04010103101.wav

while read -r start finish glas; do

	start1="$(echo "${start}/10000000" | bc -l)"
	finish1="$(echo "${finish}/10000000" | bc -l)"
	duration="$(echo "${finish}-${start}" | bc -l)"
	echo "$duration"
	
	sox $filedata $glas$inc.wav trim $start1 =$finish1
	#sox -m $glas*.wav $glas$ukupno.wav
	inc=$((inc+1))
done < $filetext


