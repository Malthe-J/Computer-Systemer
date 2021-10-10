#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>
#include <math.h>
#include <float.h>

#include "record.h"
#include "coord_query.h"


struct naive_data {
  struct record *rs;
  int n;
};


struct naive_data* mk_naive(struct record* rs, int n) {
  struct naive_data* data = malloc(sizeof(struct naive_data));
	data->rs = rs;

	data->n = n;
	return data;
}


void free_naive(struct naive_data* data) {
  free(data->rs);
  free(data);
}

double dist(double x, double y, double x1, double y1) {

  double dist = sqrt(pow(x-x1, 2.0) + pow(y-y1, 2.0)); // Querying by coordinates

  return dist;

}



const struct record* lookup_naive(struct naive_data *data, double lon, double lat) {
  
  struct record *point = NULL;
  double nearestDist = DBL_MAX;


  for (int n = 0; n < data->n; n++) //iterates through record
	{
    // Compare our coordinates with the rest of the array in a linear order
    double currentDist = dist(lon, lat, data->rs[n].lon, data->rs[n].lat);
    if (currentDist <= nearestDist)
    {
      point = &data->rs[n];

      nearestDist = currentDist;
    }

    
	}

	return point;
	
}


int main(int argc, char** argv) {
  return coord_query_loop(argc, argv,
                          (mk_index_fn)mk_naive,
                          (free_index_fn)free_naive,
                          (lookup_fn)lookup_naive);
}
