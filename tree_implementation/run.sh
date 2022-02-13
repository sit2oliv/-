gcc *.c -std=c99 -o tree_driver
rm tree_input -rf
mkdir tree_input
cp ../ImagesTests/* ./tree_input
rm tree_output -rf
mkdir tree_output
for x in biang carte_france carte_monde celtique vigne
do
    echo ./tree_driver -specify -input ./tree_input/$x.pbm -output ./tree_output/tree_$x.ppm 
    ./tree_driver -specify -input ./tree_input/$x.pbm -output ./tree_output/tree_$x.ppm 
done
rm time.log
for size in  1000 2000 3000 4000 5000 6000 7000  8000 9000 10000
do
     echo ./tree_driver -generate -width $size -height $size
     echo $size >> time.log
     (time ./tree_driver -generate -width $size -height $size) >> time.log 2>&1
     echo >> time.log
     echo >> time.log
done
