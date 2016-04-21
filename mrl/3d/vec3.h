#ifndef MRL_3D_VEC3_H
#define MRL_3D_VEC3_H

typedef struct vec3 vec3;
struct vec3
{
    float x;
    float y;
    float z;
    float w;
};

inline vec3 vec3_new(float x, float y, float z);
inline vec3 vec3_copy(vec3 v);

inline vec3 vec3_mul(vec3 v, float m);
inline vec3 vec3_div(vec3 v, float d);
inline vec3 vec3_add(vec3 a, vec3 b);
inline vec3 vec3_sub(vec3 a, vec3 b);

inline float vec3_dot(vec3 a, vec3 b);
inline float vec3_cos(vec3 a, vec3 b);
inline float vec3_angle(vec3 a, vec3 b);
inline float vec3_mag2(vec3 v);
inline float vec3_mag(vec3 v);

inline vec3 vec3_norm(vec3 v);
inline vec3 vec3_resize(vec3 v, float s);
inline vec3 vec3_cross(vec3 a, vec3 b);
inline vec3 vec3_proj(vec3 v, vec3 t);
inline vec3 vec3_ortho(vec3 v, vec3 t);

#endif
