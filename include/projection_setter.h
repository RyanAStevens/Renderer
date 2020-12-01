//Class to keep track of projection settings
class ProjectionSetter
{
public:
    ProjectionSetter();
    std::string mode = "NULL";
    double left, right, bottom, top, near, far, fov;
    void setOrtho(double left, double right, double bottom, double top, double near, double far);
    void setPerspect(double fov, double near, double far);
}
