#include <mrl/3d/vec3.h>
#include <math.h>

inline vec3 vec3_new(float x, float y, float z)
{
    vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

inline vec3 vec3_copy(vec3 v)
{
    vec3 r;
    r.x = v.x;
    r.y = v.y;
    r.z = v.z;
    return r;
}

inline vec3 vec3_mul(vec3 v, float m)
{
    vec3 r;
    r.x = v.x * m;
    r.y = v.y * m;
    r.z = v.z * m;
    return r;
}

inline vec3 vec3_div(vec3 v, float d)
{
    vec3 r;
    r.x = v.x / d;
    r.y = v.y / d;
    r.z = v.z / d;
    return r;
}

inline vec3 vec3_add(vec3 a, vec3 b)
{
    vec3 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

inline vec3 vec3_sub(vec3 a, vec3 b)
{
    vec3 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

inline float vec3_dot(vec3 a, vec3 b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

inline float vec3_mag2(vec3 v)
{
    return vec3_dot(v, v);
}

inline float vec3_mag(vec3 v)
{
    return sqrtf(vec3_mag2(v));
}

inline float vec3_cos(vec3 a, vec3 b)
{
    return vec3_dot(a, b) / (vec3_mag(a) * vec3_mag(b));
}

inline float vec3_angle(vec3 a, vec3 b)
{
    return acosf(vec3_cos(a, b));
}

inline vec3 vec3_norm(vec3 v)
{
    return vec3_div(v, vec3_mag(v));
}

inline vec3 vec3_resize(vec3 v, float s)
{
    return vec3_mul(v, s / vec3_mag(v));
}

inline vec3 vec3_cross(vec3 a, vec3 b)
{
    vec3 r;
    r.x = (a.y * b.z) - (a.z * b.y);
    r.y = (a.z * b.x) - (a.x * b.z);
    r.z = (a.x * b.y) - (a.y * b.x);
    return r;
}

inline vec3 vec3_proj(vec3 v, vec3 t)
{
    return vec3_mul(t, vec3_dot(v, vec3_norm(t)));
}

inline vec3 vec3_ortho(vec3 v, vec3 t)
{
    return vec3_sub(v, vec3_proj(v, t));
}
