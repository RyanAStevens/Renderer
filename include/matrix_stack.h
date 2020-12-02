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
    void rotate_x(float theta);
    void rotate_y(float theta);
    void rotate_z(float theta);
    void push_matrix();
    int32_t pop_matrix();
private:
    std::stack <TransformMatrix> _stack;
    
};

#endif //MATRIX_STACK_H_
