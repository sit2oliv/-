gcc *.c -std=c99 -o linked_list_driver
rm linked_list_input -rf
mkdir linked_list_input
cp ../ImagesTests/* ./linked_list_input
rm linked_list_output -rf
mkdir linked_list_output
for x in biang carte_france carte_monde celtique vigne
do
    echo ./linked_list_driver -specify -input ./linked_list_input/$x.pbm -output ./linked_list_output/linked_list_$x.ppm 
    ./linked_list_driver -specify -input ./linked_list_input/$x.pbm -output ./linked_list_output/linked_list_$x.ppm 
done
rm time.log
for size in  1000 2000 3000 4000 5000 6000 7000  8000 9000 10000
do
     echo ./linked_list_driver -generate -width $size -height $size
    echo $size >> time.log
     (time ./linked_list_driver -generate -width $size -height $size) >> time.log 2>&1
     echo >> time.log
     echo >> time.log
done
