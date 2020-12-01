
ProjectionSetter::ProjectionSetter()
{
    this->mode = "NULL";
}

void ProjectionSetter::setOrtho(double left, double right, double bottom, double top, double near, double far)
{
        this->mode = "ORTHO";
        this->left = left;
        this->right = right;
        this->bottom = bottom;
        this->top = top;
        this->near = near;
        this->far = far;
}

void ProjectionSetter::setPerspect(double fov, double near, double far)
{
        this->mode = "PERSPECT";
        this->fov = fov;
        this->near = near;
        this->far = far;
}
