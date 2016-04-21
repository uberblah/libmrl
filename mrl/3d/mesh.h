#ifndef MRL_3D_MESH_H
#define MRL_3D_MESH_H

typedef struct mesh mesh;

struct mesh
{
    vec3* verts;
    unsigned int* tris;
    vec3 color;
    unsigned int nverts;
    unsigned int ntris;
};

void mesh_draw(mesh* m);

#endif
