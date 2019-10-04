#!/bin/bash

dir_1=output/
dir_2=output_png/


for k in `seq 0 89`
do
    count=$k
    if [ $k -le 9 ]
    then
	count=00${k}
    else 
	if [ $k -le 99 ]
	then
	    count=0${k}
	fi
    fi

    echo "export png $k "

    pic_1=${dir_1}ray_${count}.ppm
    pic_2=${dir_1}mip_${count}.ppm

    convert -resize 800x800 $pic_1 ${dir_2}ray_${count}.png
    convert -resize 800x800 $pic_2 ${dir_2}mip_${count}.png

done

echo "export gif"
convert ${dir_1}ray_*.ppm -loop 0 ${dir_2}ray.gif
convert ${dir_1}mip_*.ppm -loop 0 ${dir_2}mip.gif