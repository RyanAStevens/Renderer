#ifndef MATRIX_STACK_H_
#define MATRIX_STACK_H_

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
    int32_t popMatrix();
private:
    std::stack <TransformMatrix> _stack;
    
};

#endif //MATRIX_STACK_H_
