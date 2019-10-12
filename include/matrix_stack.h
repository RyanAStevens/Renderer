/*
Transformation matrix stack
*/

#include <stack>

class MatrixStack : public std::Stack {
public:
	MatrixStack();
	~MatrixStack();
    void initialize(void);
    void print_ctm();
    void translate(float x,float y,float z);
    void scale(float x,float y,float z);
    void rotateX(float theta);
    void rotateY(float theta);
    void rotateZ(float theta);
    void pushMatrix();
    void popMatrix();
private:
    
};
