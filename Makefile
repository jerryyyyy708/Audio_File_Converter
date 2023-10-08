all:
	python exe2str.py
	g++ converter.cpp -o converter
	rm -f ffmpeg_bytes.h

clean:
	rm -f converter ffmpeg_bytes.h
