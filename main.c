#include "conf.h"

void main() {
	struct timespec time_stamp1,time_stamp2;
	double DueTime=0;
	uint64_t DueTime_s=0;
	uint64_t DueTime_ns=0;
	int counter1=2;
	int counter2;

	png_check("ExampleImg.png");
	png_read("ExampleImg.png");

	clock_gettime(CLOCK_MONOTONIC, &time_stamp1);

	// test code start ====================================

	rgba2bw_modified((uint32_t *) *row_pointers);
	// rgba2bw_origin((uint32_t *) *row_pointers);

	// test code end =====================================

	clock_gettime(CLOCK_MONOTONIC, &time_stamp2);
	DueTime_s = ((uint64_t)(time_stamp2.tv_sec) - (uint64_t)(time_stamp1.tv_sec)) * (1000000000LL);
	DueTime_ns = (uint64_t)(time_stamp2.tv_nsec) - (uint64_t)(time_stamp1.tv_nsec);
	DueTime = DueTime_s + DueTime_ns;
	printf("Due time = %7f seconds\n\r",DueTime*0.000000001);

	png_write("ResultImg.png");
}