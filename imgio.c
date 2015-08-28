#include "conf.h"

FILE *fp;

if((fp=fopen(name,"rb")) == NULL) {
	printf("image open failed !!\n");
}

