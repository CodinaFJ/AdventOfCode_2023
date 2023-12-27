#include "AOC.h"

// void search_parallels(t_line *line1, t_line *line2)
// {
// 	float	nx;
// 	float	ny;
// 	float	nz;
// 	float	tx;
// 	float	ty;
// 	float	tz;
// 	float	dot_prod_norm;

// 	(void) nx;
// 	(void) ny;
// 	(void) nz;
// 	nx = line1->vx / line2->vx;
// 	ny = line1->vy / line2->vy;
// 	nz = line1->vz / line2->vz;
// 	tx = (line2->x - line1->x) / (line1->vx - line2->vx);
// 	ty = (line2->y - line1->y) / (line1->vy - line2->vy);
// 	tz = (line2->z - line1->z) / (line1->vz - line2->vz);
// 	dot_prod_norm = (line1->vx * line2->vx) + (line1->vy * line2->vy) + (line1->vz * line2->vz);
// 	norm_1 = sqrt(line1->vx * line1->vx + line1->vy * line1->vy + line1->vz * line1->vz);
// 	norm_2 = sqrt(line2->vx * line2->vx + line2->vy * line2->vy + line2->vz * line2->vz);
// 	if (dot_prod_norm == 1)
// 	{
// 		printf("\nLines: \n");
// 		print_line_r3(line1);
// 		printf("\n");
// 		print_line_r3(line2);
// 		printf("\nAre parallel\n");
// 	}
// 	if (dot_prod == 0)
// 	{
// 		printf("\nLines: \n");
// 		print_line_r3(line1);
// 		printf("\n");
// 		print_line_r3(line2);
// 		printf("\nAre ortogonals\n");
// 	}
// 	if (tx == ty && ty == tz)
// 	{
// 		printf("\nLines: \n");
// 		print_line_r3(line1);
// 		printf("\n");
// 		print_line_r3(line2);
// 		printf("\nCut\n");
// 	}
// }

// Definir la función que representa el sistema de ecuaciones no lineales
int solver(const gsl_vector *v, void *params, gsl_vector *f) {
    double x1 = gsl_vector_get(v, 0);
    double x2 = gsl_vector_get(v, 1);
    double x3 = gsl_vector_get(v, 2);
    double x4 = gsl_vector_get(v, 3);
    double x5 = gsl_vector_get(v, 4);
    double x6 = gsl_vector_get(v, 5);

	t_equation *eq = (t_equation *) params;
    // Definir aquí las ecuaciones no lineales
	// printf("Eq: x1 [%f] x2 [%f] x3 [%f] x4 [%f] x5 [%f] x6 [%f]\n", x1, x2, x3, x4, x5, x6);
	//printf("\n");
	for (int ind = 0; ind < 3; ind++)
	{
		//printf("Eq: x1 [%f] x2 [%f] x3 [%f] x4 [%f] x5 [%f] x6 [%f]\n", eq->pos[ind][0], eq->pos[ind][1], eq->pos[ind][2], eq->vel[ind][0], eq->vel[ind][1], eq->vel[ind][2]);
    	gsl_vector_set(f, 0 + 2 * ind, x2 * x4 - x1 * x5 + eq->vel[ind][1] * x1 + eq->pos[ind][0] * x5 - eq->vel[ind][0] * x2 - eq->pos[ind][1] * x4 - eq->pos[ind][0] * eq->vel[ind][1] + eq->pos[ind][1] * eq->vel[ind][0]);
    	gsl_vector_set(f, 1 + 2 * ind, x3 * x4 - x1 * x6 + eq->vel[ind][2] * x1 + eq->pos[ind][0] * x6 - eq->vel[ind][0] * x3 - eq->pos[ind][2] * x4 - eq->pos[ind][0] * eq->vel[ind][2] + eq->pos[ind][2] * eq->vel[ind][0]);	
	}
    return GSL_SUCCESS;
}

int	print_state (size_t iter, gsl_multiroot_fsolver * s)
{
  	printf ("iter = %3llu x = % .3f % .3f % .3f vx = % .3f % .3f % .3f "
          "f(x) = % .3e % .3e % .3e % .3e % .3e % .3e\n",
          iter,
          gsl_vector_get (s->x, 0),
          gsl_vector_get (s->x, 1),
          gsl_vector_get (s->x, 2),
          gsl_vector_get (s->x, 3),
          gsl_vector_get (s->x, 4),
          gsl_vector_get (s->x, 5),
          gsl_vector_get (s->f, 0),
          gsl_vector_get (s->f, 1),
          gsl_vector_get (s->f, 2),
          gsl_vector_get (s->f, 3),
          gsl_vector_get (s->f, 4),
          gsl_vector_get (s->f, 5));
	return (0);
}

int calc_equations(void *params) 
{
    const gsl_multiroot_fsolver_type *T;
    gsl_multiroot_fsolver *s;

    int status;
    size_t iter = 0;

    const size_t n = 6; // Número de incógnitas (x1, x2, x3, x4, x5, x6)
    gsl_multiroot_function f = {&solver, n, params};

    double x_init[] = {364193859817003, 337161998875178, 148850519939119, -100, 400, 100};
    gsl_vector *x = gsl_vector_alloc(n);
    for (size_t i = 0; i < n; i++) {
        gsl_vector_set(x, i, x_init[i]);
    }

    T = gsl_multiroot_fsolver_hybrids;
    s = gsl_multiroot_fsolver_alloc(T, n);
    gsl_multiroot_fsolver_set(s, &f, x);

	print_state(iter, s);

    do {
        iter++;
        status = gsl_multiroot_fsolver_iterate(s);

		print_state(iter, s);
		
        if (status)
            break;

        status = gsl_multiroot_test_residual(s->f, 0.1);
    } while (status == GSL_CONTINUE && iter < 10000000);

    printf("Status: %s\n", gsl_strerror(status));
    printf("Iteraciones: %zu\n", iter);
    printf("Resultado: x1 = %.5f, x2 = %.5f, x3 = %.5f, x4 = %.5f, x5 = %.5f, x6 = %.5f\n -> %lld",
           gsl_vector_get(s->x, 0), gsl_vector_get(s->x, 1),
           gsl_vector_get(s->x, 2), gsl_vector_get(s->x, 3),
		   gsl_vector_get(s->x, 4), gsl_vector_get(s->x, 5),
		   (long long) gsl_vector_get(s->x, 0) + (long long) gsl_vector_get(s->x, 1) + (long long)gsl_vector_get(s->x, 2));

    gsl_multiroot_fsolver_free(s);
    gsl_vector_free(x);

    return 0;
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			**strs;
	char			**positions;
	char			**vels;
	t_line			**lines;
	t_equation		*eqs;
	char			*aux;
	long long		res = 0;
	int				i = 0;

	(void) res;
	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}
	eqs = malloc(sizeof(t_equation));
	eqs->pos = malloc(sizeof(double *) * 310);
	eqs->vel = malloc(sizeof(double *) * 310);
	lines = malloc(sizeof(t_line *) * 310);
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break ;
		aux = ft_strtrim(str, "\n");
		strs = ft_split(aux, '@');
		positions = ft_split(strs[0], ',');
		vels = ft_split(strs[1], ',');
		eqs->pos[i] = malloc(sizeof(double) * 3);
		eqs->vel[i] = malloc(sizeof(double) * 3);
		for(int idx = 0; idx < 3; idx++)
		{
			eqs->pos[i][idx] = atof(positions[idx]);
			eqs->vel[i][idx] = atof(vels[idx]);
		}
		free_strs(positions);
		free_strs(strs);
		free_strs(vels);
		free(aux);
		i++;
	}
	calc_equations((void *) eqs);

	for (int idx = 0; idx < i; idx++)
	{
		free(eqs->pos[idx]);
		free(eqs->vel[idx]);
	}
	free(eqs->pos);
	free(eqs->vel);
	free(eqs);
	lines[i] = NULL;
	//printf("\n[SOLUTION] -> %lld\n", res);
	fclose(f);
	exit (0);
}
