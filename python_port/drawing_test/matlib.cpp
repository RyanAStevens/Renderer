/* Ryan Stevens;
    CS 3451 Computer Graphics;
    Georgia Institute of Technology;
    Spring 2017;
*/

// Matrix Stack Library -- My code from Project 1A

#include <math.h>

//class for matrix_stack object
class my_matrix_stack(object)
{
};

//instantiate stack object
myMatrix = my_matrix_stack();

// my own matrix multiplication function
int matrix_mult(A, B)
{
    //check for proper input
    if(len(A[0]) != len(B))
    {
        printf("Error: Number of columns in A must match number of rows in B");
        return 1;
    }
    
    //initialize the result matrix
    iLen = len(A);
    jLen = len(B[0]);
    kLen = len(B);
    res = [];
    for(row in range(0, iLen))
    {
        res.append([]);
        res[row] = [];
        for(col in range(0, jLen))
        {
            res[row].append(0.0);
        }
    }
            
    //perform multiplication       ;
    index = 0;
    for(i in range(0,iLen))
    {
        for(j in range(0,jLen))
        {
            for(k in range(0,kLen))
            {
                res[index/jLen][index%jLen] = res[index/jLen][index%jLen] + (A[i][k] * B[k][j]);
            }
            index = index + 1;
        }
    }
    return res;
}

void gtInitialize()
{
    // initialize stack with a single 4x4 identity matrix
    myMatrix.stack = [[[1,0,0,0], [0,1,0,0], [0,0,1,0], [0,0,0,1]]];
}

void gtPushMatrix()
{
    //copy top of stack and push onto stack
    myMatrix.stack.append(myMatrix.stack[-1]);
}

void gtPopMatrix()
{
    // check to see if stack can be popped
    if(len(myMatrix.stack) > 1
    {
        myMatrix.stack.pop();
    }
    else
    {
        printf("cannot pop the matrix stack\n");
    }
}

void gtTranslate(x, y, z)
{
    // create translation matrix
    T = [[1,0,0,x], [0,1,0,y], [0,0,1,z], [0,0,0,1]];
    
    //multiply by CTM
    myMatrix.stack[-1] = matrix_mult(myMatrix.stack[-1], T);
}

void gtScale(x, y, z)
{
    // create scale matrix
    S = [[x,0,0,0], [0,y,0,0], [0,0,z,0], [0,0,0,1]];

    //multiply by CTM
    myMatrix.stack[-1] = matrix_mult(myMatrix.stack[-1], S);
}

void gtRotateX(theta)
{
    // create rotation matrix
    Rx = [[1,0,0,0], [0,math.cos(theta*math.pi/180.0),-math.sin(theta*math.pi/180.0),0], [0,math.sin(theta*math.pi/180.0),math.cos(theta*math.pi/180.0),0], [0,0,0,1]];

    //multiply Rx by CTM
    myMatrix.stack[-1] = matrix_mult(myMatrix.stack[-1], Rx);
}

void gtRotateY(theta)
{
    // create rotation matrix
    Ry = [[math.cos(theta*math.pi/180.0),0,math.sin(theta*math.pi/180.0),0], [0,1,0,0], [-math.sin(theta*math.pi/180.0),0,math.cos(theta*math.pi/180.0),0], [0,0,0,1]];

    //multiply by CTM
    myMatrix.stack[-1] = matrix_mult(myMatrix.stack[-1], Ry);
}

void gtRotateZ(theta)
{
    // create rotation matrix
    Rz = [[math.cos(theta*math.pi/180.0),-math.sin(theta*math.pi/180.0),0,0], [math.sin(theta*math.pi/180.0),math.cos(theta*math.pi/180.0),0,0], [0,0,1,0], [0,0,0,1]];

    //multiply by CTM
    myMatrix.stack[-1] = matrix_mult(myMatrix.stack[-1], Rz);
}
