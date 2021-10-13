#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "id_query.h"

struct naive_data {
  struct record *rs;
  int n;
};

struct naive_data* mk_naive(struct record* rs, int n) {
	struct naive_data* data = malloc(sizeof(struct naive_data)); // allocating memory
	data->rs = rs; //sets our data to our record

	data->n = n; //sets n
	return data;
}

void free_naive(struct naive_data* data) {
	free(data->rs);
	free(data); 
	
}

const struct record* lookup_naive(struct naive_data *data, int64_t needle) {

	for (int n = 0; n < data->n; n++) //iterates through record
	{
		if (data->rs[n].osm_id == needle) //osm.id returns record with name, lon and lat
		{
			return &data->rs[n];
		} // returns pointer to object on position n
	}

	return NULL;
	
}

int main(int argc, char** argv) {
  return id_query_loop(argc, argv,
                    (mk_index_fn)mk_naive,
                    (free_index_fn)free_naive,
                    (lookup_fn)lookup_naive);
}
