all: sequence pipeline

sequence: sequence.c
	gcc -o sequence sequence.c

pipeline: pipeline.c
	gcc -o pipeline pipeline.c

clean:
	rm -f sequence pipeline