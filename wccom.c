#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <getopt.h>

#define CASENUM 4

static void count_line(int *case_num, char *filename);

static struct option longopts[] = {
	{"lines", no_argument, NULL, 'l'},
	{"words", no_argument, NULL, 'w'},
	{"bytes", no_argument, NULL, 'c'},

	{"tab", no_argument, NULL, 't'},
	{0, 0, 0, 0}
};

int main(int argc, char *argv[]){
	int option;
	int case_num[CASENUM] = {1, 1, 1, 0};
	while ((option = getopt_long(argc, argv, "lwct", longopts, NULL)) != -1) {
		if(case_num[0] == 1 && case_num[1] == 1 && case_num[2] == 1){
			for(int i = 0; i < CASENUM; i++){
				case_num[i] = 0;
			}
		}
		switch (option) {
			case 'l':
				case_num[0] = 1;
				break;
			case 'w':
				case_num[1] = 1;
				break;
			case 'c':
				case_num[2] = 1;
				break;
			case 't':
				case_num[3] = 1;
				break;
			case '?':
				fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
				exit(1);
		}
	}
	if (optind == argc) {
		fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
		exit(1);
	} else {
		count_line(case_num, argv[optind]);
	}
	fprintf(stdout, "%s\n", argv[optind]);
	exit(0);
}

static void count_line(int *case_num, char *filename){
	int c;
	int buf = ' ';
	int bytes = 0;
	int words = 0;
	int lines = 0;
	int tab = 0;
	FILE *f;

	f = fopen(filename, "r");
	if (!f) {
		perror(filename);
		exit(1);
	}
	while ((c = getc(f)) != EOF) {
		if (c == ' '){
			if(buf != ' '){
				words++;
			}
		}
		if (c == '\n') {
			if (buf != ' ') {
				words++;
			}
			lines++;
			buf = ' ';
		} else if (c == '\t') {
			tab++;
			buf = ' ';
		} else {
			buf = c;
		}
		bytes++;
	}
	fclose(f);
	if(case_num[0] == 1){
		fprintf(stdout, "%d ", lines);
	}
	if(case_num[1] == 1){
		fprintf(stdout, "%d ", words);
	}
	if(case_num[2] == 1){
		fprintf(stdout, "%d ", bytes);
	}
	if(case_num[3] == 1){
		fprintf(stdout, "%d ", tab);
	}
}
