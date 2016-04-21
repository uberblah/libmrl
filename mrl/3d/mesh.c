#include <GLFW/glfw3.h>
#include <mrl/3d/mesh.h>

void draw_mesh(mesh* m)
{
    glColor4fv(&(m->color));
    glBegin(GL_TRIANGLES);
    unsigned int maxidx = m->ntris * 3;
    for(unsigned int i = 0; i < maxidx; i+=3)
    {
	glVertex3fv(&(m->verts[m->tris[i]]));
	glVertex3fv(&(m->verts[m->tris[i + 1]]));
	glVertex3fv(&(m->verts[m->tris[i + 2]]));
    }
    glEnd();
}
