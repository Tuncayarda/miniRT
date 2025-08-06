#include <math.h>
#include "minirt.h"
#include "parser.h"
#include "libft.h"
#include "mlx_interface.h"
#include "debug.h"

static void init_mlx(mlx *m)
{
    m->ptr  = mlx_init();
    m->win  = mlx_new_window(m->ptr, WIDTH, HEIGHT, "miniRT");
    m->img  = mlx_new_image(m->ptr, WIDTH, HEIGHT);
    m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->line_len, &m->endian);
}

static inline vec3 vec_cross(vec3 a, vec3 b)
{
    return (vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

static vec3 gen_ray(camera *cam, int x, int y)
{
    float ar = (float)WIDTH / HEIGHT;
    float s  = tanf((cam->fov * M_PI / 180.f) * 0.5f);
    float px = (2 * ((x + 0.5f) / (float)WIDTH)  - 1) * ar * s;
    float py = (1 - 2 * ((y + 0.5f) / (float)HEIGHT)) * s;

    vec3 forward = vec_norm(cam->dir);
    vec3 up      = (vec3){0,1,0};
    if (fabsf(vec_dot(forward, up)) > 0.99f)
        up = (vec3){0,0,1};
    vec3 right   = vec_norm(vec_cross(up, forward));
    up           = vec_cross(forward, right);

    vec3 world = vec_add(vec_add(vec_scale(right, px),
                                 vec_scale(up,    py)),
                         forward);
    return vec_norm(world);
}

static bool hit_sphere(vec3 ro, vec3 rd, sphere *s, float *t, vec3 *p, vec3 *n)
{
    vec3 oc = vec_sub(ro, s->pos);
    float r = s->dia * 0.5f;
    float a = vec_dot(rd, rd);
    float b = 2 * vec_dot(oc, rd);
    float c = vec_dot(oc, oc) - r*r;
    float d = b*b - 4*a*c;
    if (d < 0) return false;
    float sq = sqrtf(d);
    float t0 = (-b - sq) / (2*a);
    float t1 = (-b + sq) / (2*a);
    float tt = (t0 > 1e-4f) ? t0 : ((t1 > 1e-4f)?t1:-1);
    if (tt < 0) return false;
    *t = tt;
    if (p) *p = vec_add(ro, vec_scale(rd, tt));
    if (n) *n = vec_norm(vec_sub(*p, s->pos));
    return true;
}

static bool hit_plane(vec3 ro, vec3 rd, plane *pl, float *t, vec3 *p, vec3 *n)
{
    float denom = vec_dot(pl->axis, rd);
    if (fabsf(denom) < 1e-6f) return false;
    float d = vec_dot(vec_sub(pl->pos, ro), pl->axis) / denom;
    if (d < 1e-4f) return false;
    *t = d;
    if (p) *p = vec_add(ro, vec_scale(rd, d));
    if (n) *n = vec_norm(pl->axis);
    return true;
}

static bool hit_cyl(vec3 ro, vec3 rd, cylinder *c, float *t, vec3 *p, vec3 *n)
{
    vec3 ca = vec_norm(c->axis);
    vec3 oc = vec_sub(ro, c->pos);
    float r = c->dia * 0.5f;

    float card = vec_dot(rd, ca);
    float caoc = vec_dot(oc, ca);
    vec3  rd_p = vec_sub(rd, vec_scale(ca, card));
    vec3  oc_p = vec_sub(oc, vec_scale(ca, caoc));

    float a = vec_dot(rd_p, rd_p);
    float b = 2 * vec_dot(rd_p, oc_p);
    float cc = vec_dot(oc_p, oc_p) - r * r;
    float disc = b * b - 4 * a * cc;

    float t_side = INFINITY, t_cap = INFINITY; vec3 n_side = {0}, n_cap = {0};

    if (disc >= 0 && fabsf(a) > 1e-6f)
    {
        float sq = sqrtf(disc);
        float t0 = (-b - sq) / (2 * a);
        float t1 = (-b + sq) / (2 * a);
        float ts = (t0 > 1e-4f) ? t0 : ((t1 > 1e-4f) ? t1 : -1);
        if (ts > 0)
        {
            float y = caoc + ts * card;
            if (y >= 0 && y <= c->h)
            {
                t_side = ts;
                if (p || n) {
                    vec3 hit = vec_add(ro, vec_scale(rd, ts));
                    vec3 v   = vec_sub(hit, c->pos);
                    vec3 proj= vec_scale(ca, vec_dot(v, ca));
                    n_side   = vec_norm(vec_sub(v, proj));
                    if (p) *p = hit;
                }
            }
            const float EPS = 1e-3f;
            if (y >= -EPS && y < 0)
            {
                t_cap = ts;
                n_cap = vec_scale(ca, -1);
            }
            else if (y > c->h && y <= c->h + EPS)
            {
                t_cap = ts;
                n_cap = ca;
            }
        }
    }

    float denom = vec_dot(rd, ca);
    if (fabsf(denom) > 1e-6f)
    {
        float tb = vec_dot(vec_sub(c->pos, ro), ca) / denom;
        if (tb > 1e-4f && denom > 0)
        {
            vec3 pb = vec_add(ro, vec_scale(rd, tb));
            if (vec_length(vec_sub(pb, c->pos)) <= r)
            {
                t_cap = tb;
                n_cap = vec_scale(ca, -1);
                if (p) *p = pb;
            }
        }
        float tt = vec_dot(vec_sub(vec_add(c->pos, vec_scale(ca, c->h)), ro), ca) / denom;
        if (tt > 1e-4f && denom < 0 && tt < t_cap)
        {
            vec3 pt = vec_add(ro, vec_scale(rd, tt));
            if (vec_length(vec_sub(pt, vec_add(c->pos, vec_scale(ca, c->h)))) <= r)
            {
                t_cap = tt;
                n_cap = ca;
                if (p) *p = pt;
            }
        }
    }

    if (t_side == INFINITY && t_cap == INFINITY) return false;

    if (t_cap < t_side)
    {
        *t = t_cap;
        if (n) *n = n_cap;
    }
    else
    {
        *t = t_side;
        if (n) *n = n_side;
    }
    return true;
}

static bool is_shadowed(scene *sc, entity *skip, vec3 point, vec3 Lpos, float max_dist)
{
    vec3 dir = vec_norm(vec_sub(Lpos, point));
    float  t, dist_hit;
    vec3   dummy_p, dummy_n;
    for (size_t i = 0; i < sc->ent_count; ++i)
    {
        entity *e = &sc->ents[i];
        if (e == skip) continue;
        bool hit = false;
        if (e->type == ENT_SPHERE) {
            hit = hit_sphere(point, dir, (sphere*)e->ent, &dist_hit, &dummy_p, &dummy_n);
        } else if (e->type == ENT_PLANE) {
            hit = hit_plane(point, dir, (plane*)e->ent, &dist_hit, &dummy_p, &dummy_n);
        } else if (e->type == ENT_CYLINDER) {
            hit = hit_cyl(point, dir, (cylinder*)e->ent, &dist_hit, &dummy_p, &dummy_n);
        }
        if (hit && dist_hit > 1e-3f && dist_hit < max_dist - 1e-3f)
            return true;
    }
    return false;
}

static bool checker_sphere(sphere *s, vec3 hit, float scale)
{
    if (scale < 1e-6f) scale = 1.0f;

    vec3 rel = vec_norm(vec_sub(hit, s->pos));
    float u = (atan2f(rel.z, rel.x) + (float)M_PI) / ((float)M_PI * 2.f);
    float v = acosf(rel.y) / (float)M_PI;
    int iu = (int)floorf(u / scale);
    int iv = (int)floorf(v / scale);

    return (((iu + iv) & 1) != 0);
}

static bool checker_cylinder(cylinder *c, vec3 hit, float scale)
{
    vec3 rel = vec_sub(hit, c->pos);
    float h  = vec_dot(rel, vec_norm(c->axis));
    vec3 axis = vec_norm(c->axis);
    vec3 radial = vec_sub(rel, vec_scale(axis, h));
    float ang = atan2f(radial.z, radial.x);
    if (ang < 0) ang += (float)M_PI * 2.f;
    int uu = (int)floorf(ang / (scale));
    int vv = (int)floorf(h   / (scale));
    return ((uu + vv) & 1) != 0;
}

static color shade_all(scene *sc, entity *self, color bas, material *mat, vec3 hit, vec3 norm, vec3 ro, color amb)
{
    if (mat && mat->has_checker)
    {
        float s = (mat->checker_scale > 1e-6f) ? mat->checker_scale : 1.0f;
        bool swap = false;
        if (self->type == ENT_CYLINDER)
            swap = checker_cylinder((cylinder*)self->ent, hit, s);
        else if (self->type == ENT_SPHERE)
            swap = checker_sphere((sphere*)self->ent, hit, s);
        else
        {
            int cx = (int)floorf(hit.x / s);
            int cz = (int)floorf(hit.z / s);
            swap = (((cx + cz) & 1) != 0);
        }
        if (swap) bas = mat->checker_color;
    }
    color out;
    out.r = fminf(bas.r * (amb.r / 255.f), 255);
    out.g = fminf(bas.g * (amb.g / 255.f), 255);
    out.b = fminf(bas.b * (amb.b / 255.f), 255);
    out.a = bas.a;
    for (size_t li = 0; li < sc->light_count; ++li)
    {
        light L = sc->lights[li];
        vec3  Ld = vec_norm(vec_sub(L.pos, hit));

        float dist_light = vec_length(vec_sub(L.pos, hit));
        if (is_shadowed(sc, self, vec_add(hit, vec_scale(norm, 1e-3f)), L.pos, dist_light))
            continue;

        float spot_att = L.ratio;
        if (L.type == LIGHT_SPOT)
        {
            vec3 Sd = vec_norm(L.dir);
            float cosTh = vec_dot(vec_scale(Ld, -1), Sd);
            float cut = cosf(L.angle * M_PI / 180.0f);
            if (cosTh < cut)
                continue;
            spot_att *= powf(cosTh, 4.0f);
        }

        float ndotl = vec_dot(norm, Ld);
        if (ndotl <= 0) continue;
        float diff = ndotl * spot_att;
        vec3 V = vec_norm(vec_sub(ro, hit));
        vec3 R = vec_sub(vec_scale(norm, 2 * vec_dot(norm, Ld)), Ld);
        float spec = 0;
        if (mat && mat->has_spc)
            spec = powf(fmaxf(vec_dot(V, R), 0.0f), mat->shininess) * mat->specular_strength;
        spec *= spot_att;

        out.r = fminf(out.r + bas.r * diff * (L.color.r / 255.f) + L.color.r * spec, 255);
        out.g = fminf(out.g + bas.g * diff * (L.color.g / 255.f) + L.color.g * spec, 255);
        out.b = fminf(out.b + bas.b * diff * (L.color.b / 255.f) + L.color.b * spec, 255);
    }
    out.a = bas.a;
    return out;
}

static color shade(color bas, material *mat, vec3 hit, vec3 norm, vec3 ro, light L, color amb)
{
    vec3  Ld = vec_norm(vec_sub(L.pos, hit));
    float diff = fmaxf(vec_dot(norm, Ld), 0.0f);
    vec3  V   = vec_norm(vec_sub(ro, hit));
    vec3  R   = vec_sub(vec_scale(norm, 2*vec_dot(norm, Ld)), Ld);
    float spec = 0;
    if (mat && mat->has_spc)
        spec = powf(fmaxf(vec_dot(V,R),0.0f), mat->shininess) * mat->specular_strength;

    float lr = L.color.r / 255.f, lg = L.color.g / 255.f, lb = L.color.b / 255.f;

    color out;
    out.r = fminf(bas.r * diff * lr + L.color.r * spec + amb.r, 255);
    out.g = fminf(bas.g * diff * lg + L.color.g * spec + amb.g, 255);
    out.b = fminf(bas.b * diff * lb + L.color.b * spec + amb.b, 255);
    out.a = bas.a;
    return out;
}

int main(int ac, char **av)
{
    scene sc; ft_memset(&sc,0,sizeof(sc));
    init_mlx(&sc.mlx);
    parser(&sc, ac, av);
	print_scene_debug(&sc);
    color amb = { .r = sc.ambient.color.r * sc.ambient.ratio,
                  .g = sc.ambient.color.g * sc.ambient.ratio,
                  .b = sc.ambient.color.b * sc.ambient.ratio,
                  .a = 255 };

    for (int y=0; y<HEIGHT; ++y)
    for (int x=0; x<WIDTH;  ++x)
    {
        vec3 ro = sc.cam.pos;
        vec3 rd = gen_ray(&sc.cam, x, y);
        float best = INFINITY;  color pix = amb;

        for (size_t i=0;i<sc.ent_count;++i)
        {
            float t; vec3 hit, n; bool ok=false; color col; material *mat=NULL;
            entity *e=&sc.ents[i];
            if (e->type==ENT_SPHERE) ok = hit_sphere(ro,rd,(sphere*)e->ent,&t,&hit,&n), col=((sphere*)e->ent)->color, mat=&((sphere*)e->ent)->mat;
            else if (e->type==ENT_PLANE) ok=hit_plane(ro,rd,(plane*)e->ent,&t,&hit,&n), col=((plane*)e->ent)->color, mat=&((plane*)e->ent)->mat;
            else if (e->type==ENT_CYLINDER) ok=hit_cyl(ro,rd,(cylinder*)e->ent,&t,&hit,&n), col=((cylinder*)e->ent)->color, mat=&((cylinder*)e->ent)->mat;
            if (ok && t<best)
            {
                best = t;
                pix  = shade_all(&sc, e, col, mat, hit, n, ro, amb);
            }
        }
        put_pix(&sc.mlx, x, y, pix);
    }

    mlx_put_image_to_window(sc.mlx.ptr, sc.mlx.win, sc.mlx.img, 0, 0);
    mlx_loop(sc.mlx.ptr);
    gc_manager(NULL, MODE_FREE);
    return 0;
}