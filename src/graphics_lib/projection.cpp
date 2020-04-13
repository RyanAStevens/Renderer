void Orthographic::project_vertex(Vector3)
{
    vert1[0][0] = (vert1[0][0] - this->left)*(this->width/(projMode.right - projMode.left))
    vert1[1][0] = (vert1[1][0] - projMode.bottom)*(width/(projMode.top - projMode.bottom))
}

void Perspective::project_vertex(Vector3);
