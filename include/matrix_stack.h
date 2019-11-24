/*
Transformation matrix stack
*/
#include <transform_matrix.h>
#include <stack>

//class MatrixStack : public std::stack {
class MatrixStack {
public:
	MatrixStack();
	~MatrixStack();
    void initialize();
    void print_ctm();
    TransformMatrix& get_ctm();
    void translate(float x,float y,float z);
    void scale(float x,float y,float z);
    void rotateX(float theta);
    void rotateY(float theta);
    void rotateZ(float theta);
    void pushMatrix();
    void popMatrix();
private:
    std::stack <TransformMatrix> _stack;
    
};
