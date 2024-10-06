// shell cmd: cc spark.c -o spark; ./spark

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <string.h> // memset()
#include <time.h>

#define CACHE_MIN (4 * 1024)        // 4 KB
#define CACHE_MAX (4 * 1024 * 1024) // 4 MB
#define N_REPETITIONS (100)

// returns elapsed time in seconds
double get_elapsed(struct timespec const *start) {
    struct timespec end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    double nanoseconds = ((end.tv_sec - start->tv_sec) * 1000000000) +
                         (end.tv_nsec - start->tv_nsec);
    return nanoseconds / 1000000000.0;
}

int main() {
    uint8_t *array = calloc(CACHE_MAX, sizeof(uint8_t));
    

    fputs("size\tstride\telapsed(s)\tcycles\n", stdout);
    struct timespec t1;
    double td_stride;
    size_t total_accesses = 0, a_stride, t_stride;
    for (size_t cache_size = CACHE_MIN; cache_size <= CACHE_MAX; cache_size = cache_size * 2) {
        fprintf(stderr, "[LOG]: running with array of size %zu KiB\n", cache_size >> 10);
        fflush(stderr);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
        size_t total_accesses = 0;
        for (size_t stride = 1; stride <= cache_size / 2; stride = 2 * stride) {
            size_t limit = cache_size - stride + 1;

            /* warm up the cache */
            for (size_t index = 0; index < limit; index += stride) {
                array[index] = array[index] + 1;
            }

            clock_t const start_cycles = clock();

            struct timespec start_time;
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);

            size_t n_iterations = 0;
            /* ************************************************************** */
            for (size_t repeat = 0; repeat < N_REPETITIONS * stride; repeat++) {
                for (size_t index = 0; index < limit; index += stride, n_iterations++) {
                    array[index] = array[index] + 1;
                }
            }
            /* ************************************************************** */

            clock_t const cycle_count = clock() - start_cycles;
            double const time_diff = get_elapsed(&start_time);
            if(stride == 2048) {
                a_stride = n_iterations;
                td_stride = time_diff;
                t_stride = stride;
            }
            total_accesses += n_iterations;

            /******************************************************************
             * Note: You can change the code bellow to calculate more measures
             * as needed.
             *****************************************************************/

            /* Output to stdout */
            fprintf(stdout, "%zu\t%zu\t%lf\t%zu\n", cache_size, stride,
                    time_diff, cycle_count);
        }
        double const total_time = get_elapsed(&t1);
        double const mean_time = (total_time / total_accesses) * 1000000000.0;
        double const mstr_time = (td_stride / a_stride) * 1000000000.0;
        fprintf(stdout, "t1 - t2: %lf\nMean Access Time (ns): %lf\n", total_time, mean_time);
        fprintf(stdout, "Stride: %zu -> t1 - t2: %lf \t Mean Access Time (ns): %lf\n", t_stride, td_stride, mstr_time);
    }
    return 0;
}
