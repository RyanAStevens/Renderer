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
    MatrixStack operator=(const MatrixStack& rhs);
    void initialize(void);
    void print_ctm();
    void translate(float x,float y,float z);
    void scale(float x,float y,float z);
    void rotateX(float theta);
    void rotateY(float theta);
    void rotateZ(float theta);
    void pushMatrix(TransformMatrix matIn);
    void popMatrix(void);
private:
    std::stack <TransformMatrix> matStack;
    
};
