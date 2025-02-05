exec: main.o pictures.o filename.o read_write.o manage_images.o handle_pixels_directly.o lut.o image_arithmetic.o image_resample.o # target by default
	gcc -o exec $^

pictures.o: pictures.c pictures.h lut.h manage_images.h
	gcc -Wall -c pictures.c

filename.o: filename.c filename.h
	gcc -Wall -c filename.c

read_write.o: read_write.c read_write.h pictures.h filename.h manage_images.h
	gcc -Wall -c read_write.c

manage_images.o: manage_images.c manage_images.h pictures.h
	gcc -Wall -c manage_images.c

handle_pixels_directly.o: handle_pixels_directly.c handle_pixels_directly.h manage_images.h pictures.h
	gcc -Wall -c handle_pixels_directly.c

lut.o: lut.c lut.h pictures.h manage_images.h
	gcc -Wall -c lut.c

image_arithmetic.o: image_arithmetic.c image_arithmetic.h pictures.h manage_images.h
	gcc -Wall -c image_arithmetic.c

image_resample.o: image_resample.c image_resample.h pictures.h manage_images.h
	gcc -Wall -c image_resample.c

main.o: main.c pictures.h filename.h read_write.h manage_images.h handle_pixels_directly.h image_arithmetic.h image_resample.h
	gcc -Wall -c main.c