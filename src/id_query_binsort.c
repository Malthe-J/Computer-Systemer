#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>
#include <math.h>


#include "record.h"
#include "id_query.h"

struct index_record {
    int64_t osm_id;
    const struct record *record;
};


struct indexed_data
{
    struct index_record *irs;
    int n;
};


struct indexed_data* mk_indexed(struct record* rs, int n) {
    struct indexed_data* data = malloc(sizeof(struct indexed_data));
    data->irs = malloc(sizeof(struct index_record) * n);
    for (int i = 0; i < n; i++)
    {

        data->irs[i].osm_id = rs[i].osm_id;
        data->irs[i].record = &rs[i];

    
    }


    data->n = n;
    return data;
}


void free_indexed(struct indexed_data* data) {
    free(data->irs);
    free(data);
}



const struct record* lookup_indexed(struct indexed_data *data, int64_t needle) {
    int c, first, last, middle, n, search, array[1000000000000000000];
   printf("Enter number of elements:\n");
   scanf("%d",&n); 
   printf("Enter %d integers:\n", n);
   for (c = 0; c < n; c++)
      scanf("%d",&array[c]); 
   printf("Enter the value to find:\n");
   scanf("%d", &search);
   first = 0;
   last = n - 1;
   middle = (first+last)/2;
   while (first <= last) {
      if (array[middle] < search)
         first = middle + 1;    
      else if (array[middle] == search) {
         printf("%d is present at index %d.\n", search, middle+1);
         break;
      }
      else
         last = middle - 1;
      middle = (first + last)/2;
   }
   if (first > last)
      printf("Not found! %d is not present in the list.\n", search);
   return 0;  
}

int main(int argc, char** argv) {
  return id_query_loop(argc, argv,
                    (mk_index_fn)mk_indexed,
                    (free_index_fn)free_indexed,
                    (lookup_fn)lookup_indexed);
}