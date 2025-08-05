#include "entities.h"
#include "gc.h"

sphere	*generate_sphere(sphere *s)
{
	sphere	*ret;

	ret = gc_manager(malloc(sizeof(sphere)), MODE_ADD);
	ret->pos = s->pos;
	ret->color = s->color;
	ret->dia = s->dia;
}
