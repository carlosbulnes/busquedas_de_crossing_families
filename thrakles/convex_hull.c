#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double x;
  double y;
} point_t;

typedef point_t* point_ptr_t;

/* Three points are a counter-clockwise turn if ccw > 0, clockwise if
 * ccw < 0, and collinear if ccw = 0 because ccw is a determinant that
 * gives the signed area of the triangle formed by p1, p2 and p3.
 */
static double
ccw(point_t* p1, point_t* p2, point_t* p3)
{
  return (p2->x - p1->x)*(p3->y - p1->y) - (p2->y - p1->y)*(p3->x - p1->x);
}

/* Returns a list of points on the convex hull in counter-clockwise order.
 * Note: the last point in the returned list is the same as the first one.
 */
void
convex_hull(point_t* points, ssize_t npoints, point_ptr_t** out_hull, ssize_t* out_hullsize)
{
  point_ptr_t* hull;
  ssize_t i, t, k = 0;

  hull = *out_hull;

  /* lower hull */
  for (i = 0; i < npoints; ++i) {
    while (k >= 2 && ccw(hull[k-2], hull[k-1], &points[i]) <= 0) --k;
    hull[k++] = &points[i];
  }

  /* upper hull */
  for (i = npoints-2, t = k+1; i >= 0; --i) {
    while (k >= t && ccw(hull[k-2], hull[k-1], &points[i]) <= 0) --k;
    hull[k++] = &points[i];
  }

  *out_hull = hull;
  *out_hullsize = k;
}


int main(int argc, char *argv[]){
  point_t puntos[8];
  point_t **hull;
  ssize_t hull_size;
  int i;

  hull = (point_t **)malloc(8*sizeof(point_t));

  for(i = 0; i < 8; i++){
    hull[i] = (point_t *)malloc(sizeof(point_t));
  }

/*
  puntos[0].x = 218;
  puntos[0].y = 48;
  puntos[1].x = 157;
  puntos[1].y = 54;
  puntos[2].x = 88;
  puntos[2].y = 66;
  puntos[3].x = 76;
  puntos[3].y = 72;
  puntos[4].x = 61;
  puntos[4].y = 90;
  puntos[5].x = 13;
  puntos[5].y = 177;
  puntos[6].x = 55;
  puntos[6].y = 210;
  puntos[7].x = 243;
  puntos[7].y = 53;
*/
  puntos[0].x = 142;
  puntos[0].y = 62;
  puntos[1].x = 86;
  puntos[1].y = 136;
  puntos[2].x = 105;
  puntos[2].y = 152;
  puntos[3].x = 98; 
  puntos[3].y = 197;
  puntos[4].x = 122;
  puntos[4].y = 143;
  puntos[5].x = 138;
  puntos[5].y = 151;
  puntos[6].x = 160;
  puntos[6].y = 135;
  puntos[7].x = 170;
  puntos[7].y = 141;

  convex_hull(puntos, 8, &hull, &hull_size);

  for(i = 0; i < hull_size-1; i++){
    printf("(%.0lf, %.0lf)\n", hull[i]->x, hull[i]->y);
  }

  printf("%d\n", (int)(hull_size-1));

  return 0;
}