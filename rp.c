/*
Copyright (c) 2016-2020 Jeremy Iverson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/* assert */
#include <assert.h>

/* fabs */
#include <math.h>

/* printf, fopen, fclose, fscanf, scanf */
#include <stdio.h>

/* EXIT_SUCCESS, malloc, calloc, free, qsort */
#include <stdlib.h>

struct distance_metric {
  size_t viewer_id;
  double distance;
};

int
main(int argc, char * argv[])
{
  size_t n, m;

  /* Validate command line arguments. */
  assert(2 == argc);

  /* ... */
  char const * const fn = argv[1];

  /* Validate input. */
  assert(fn);

  /* Open file. */
  FILE * const fp = fopen(fn, "r");
  assert(fp);

  /* Read file. */
  fscanf(fp, "%zu %zu", &n, &m);

  /* Allocate memory. */
  double * const rating = malloc(n * m * sizeof(*rating));

  /* Check for success. */
  assert(rating);

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      fscanf(fp, "%lf", &rating[i * m + j]);
    }
  }

  /* Close file. */
  int const ret = fclose(fp);
  assert(!ret);

  /* Allocate more memory. */
  double * const urating = malloc(m * sizeof(*urating));

  /* Check for success. */
  assert(urating);

  /* Get user input. */
  for (size_t j = 0; j < m - 1; j++) {
    printf("Enter your rating for movie %zu: ", j + 1);
    scanf("%lf", &urating[j]);
  }

  /* Allocate more memory. */
  double sumR[10] = {0.0};
  double prob[10] = {0.0};
  

  /* Compute probabilities */
  for (int k = 0; k < 10; k++) {
    for (size_t i = 0; i < n; i++) {
      prob[k] += (rating[i * m + 4] == (k + 1) / 2.0);
      sumR[k] += (rating[i * m + 4] == (k + 1) / 2.0);
    }
  }

  /* Finalize computation of probabilities. */
  for (int k = 0; k < 10; k++) {
    prob[k] /= n;
  }

  for (int k = 0; k < 10; k++) {
    printf("prob[%d] = %lf\n", k, prob[k]);
  }

  /* Allocate memory for the conditional probabilities */

  double *cprob = malloc(( m - 1 ) * 10 * sizeof(double));

  /* Create nested for loop to compute conditional probabilities */
  for(int i = 0; i < n;i++){
    for(int j = 0; j < m - 1; j++){
      for(int k = 0; k < 10; k++){
	if(urating[j] == rating[ i * m + j] && rating [ i * m + 4] = = (k + 1 ) / 2.0){
	  cprob[(j * 10) + k] += 1;
	    }
      }
    }
  }

  /* Final step: Making a prediction using conditional probabilities */
  double prediction[10];
  for(int k = 0; k <10; k++){
    if(prob[k]!=0){
      prediction[k]=prob[k]*(cprob[k]/sumR[k])*(cprob[k+10]/sumR[k])*(cprob[k+20]/sumR[k])*(cprob[k+ 30]/sumR[k]);
    }
    else{
      prediction[k] = 0.0;
    }
  }
  
  /* compare which one is the most likely one */
  double mostL = 0.0;
  int maxI = 0;
  for(int k = 0; k<10; k++){
    if(prediction[k] > mostL){
      maxI = k;
      mostL = prediction[k];
    }
  }

  /* Output prediction. */

  
  printf("The predicted rating for movie five is %.1lf.\n", (maxI+1)/2.0);

  /* Deallocate memory. */
  free(rating);
  free(urating);

  return EXIT_SUCCESS;
}
