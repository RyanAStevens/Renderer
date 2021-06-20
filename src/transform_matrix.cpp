#include <transform_matrix.h>
#include <cstdio>
#include <cmath>

TransformMatrix::TransformMatrix()
{
    data = new std::vector<Vector3H>;
    for(int i = 0; i < 4; i++)
    {
        Vector3H column;
        data->push_back(column);
    }

    (*data)[0][0] = 1.0;
    (*data)[1][1] = 1.0;
    (*data)[2][2] = 1.0;
    (*data)[3][3] = 1.0;
}

TransformMatrix::TransformMatrix(int win_width, int win_height)
{
    //Windowing Transform Matrix
    data = new std::vector<Vector3H>;
    
    for(int i = 0; i < 4; i++)
    {
        Vector3H column;
        data->push_back(column);
    }
    
    (*data)[0][0] = double(win_width) / 2.0;
    (*data)[0][3] = double(win_width - 1) / 2.0;
    (*data)[1][1] = double(win_height) / 2.0;
    (*data)[1][3] = double(win_height - 1) / 2.0;
    (*data)[2][2] = 1.0;
    (*data)[3][3] = 1.0;
}

TransformMatrix::TransformMatrix(enum matrix_constructor_t mat_type)
{
    data = new std::vector<Vector3H>;
    
    for(int i = 0; i < 4; i++)
    {
        Vector3H column;
        data->push_back(column);
    }
    
    (*data)[0][0] = 1.0;
    (*data)[1][1] = 1.0;
    (*data)[2][2] = 1.0;
    (*data)[3][3] = 1.0;
    
    switch(mat_type)
    {
        case IDENTITY:
            break;
        case INVERT_Y:
            (*data)[1][1] = -1.0;
            break;
        default:
            ;
    }
}


TransformMatrix::TransformMatrix(enum matrix_constructor_t mat_type, double val)
{
    data = new std::vector<Vector3H>;
    
    for(int i = 0; i < 4; i++)
    {
        Vector3H column;
        data->push_back(column);
    }
    
    (*data)[0][0] = 1.0;
    (*data)[1][1] = 1.0;
    (*data)[2][2] = 1.0;
    (*data)[3][3] = 1.0;
    
    switch(mat_type)
    {
        case SCALE:
            (*data)[0][0] = val;
            (*data)[1][1] = val;
            (*data)[2][2] = val;
            break;
        case SCALE_X:
            (*data)[0][0] = val;
            break;
        case SCALE_Y:
            (*data)[1][1] = val;
            break;
        case SCALE_Z:
            (*data)[2][2] = val;
            break;
        case TRANSLATE_X:
            (*data)[0][3] = val;
            break;
        case TRANSLATE_Y:
            (*data)[1][3] = val;
            break;
        case TRANSLATE_Z:
            (*data)[2][3] = val;
            break;
        case ROTATE_X:
            (*data)[1][1] = std::cos(val);
            (*data)[1][2] = -1.0 * std::sin(val);
            (*data)[2][1] = std::sin(val);
            (*data)[2][2] = std::cos(val);
            break;
        case ROTATE_Y:
            (*data)[0][0] = std::cos(val);
            (*data)[0][2] = std::sin(val);
            (*data)[2][0] = -1.0 * std::sin(val);
            (*data)[2][2] = std::cos(val);
            break;
        case ROTATE_Z:
            (*data)[0][0] = std::cos(val);
            (*data)[0][1] = -1.0 * std::sin(val);
            (*data)[1][0] = std::sin(val);
            (*data)[1][1] = std::cos(val);
            break;
        default:
            ;
    }
    
}

TransformMatrix::TransformMatrix(enum matrix_constructor_t mat_type, double x_val, double y_val, double z_val)
{
    data = new std::vector<Vector3H>;
    
    for(int i = 0; i < 4; i++)
    {
        Vector3H column;
        data->push_back(column);
    }
    
    (*data)[0][0] = 1.0;
    (*data)[1][1] = 1.0;
    (*data)[2][2] = 1.0;
    (*data)[3][3] = 1.0;
    
    switch(mat_type)
    {
        case SCALE:
            (*data)[0][0] = x_val;
            (*data)[1][1] = y_val;
            (*data)[2][2] = z_val;
            (*data)[3][3] = 1.0;
            break;
        case TRANSLATE:
            (*data)[0][3] = x_val;
            (*data)[1][3] = y_val;
            (*data)[2][3] = z_val;
            (*data)[3][3] = 1.0;
            break;
        default:
            ;
    }
    
}

TransformMatrix::TransformMatrix(const TransformMatrix& tm)
{
    data = new std::vector<Vector3H>;
    
    for(int i = 0; i < 4; i++)
    {
        Vector3H column;
        data->push_back(column);
    }
   
    if(NULL != data && NULL != tm.data)
    {
        for(int row = 0; row < 4; row++)
        {
            for(int col = 0; col < 4; col++)
            {
                (*data)[row][col] = (*tm.data)[row][col];
            }
        }
    }
    else
    {
        printf("TransformMatrix copy constructor: NULL data pointer\n");
    }
}

TransformMatrix::TransformMatrix(Vector3H r0, Vector3H r1, Vector3H r2, Vector3H r3)
{
    data = new std::vector<Vector3H>;
    this->data->push_back(r0);
    this->data->push_back(r1);
    this->data->push_back(r2);
    this->data->push_back(r3);
}

TransformMatrix::~TransformMatrix()
{
}

TransformMatrix TransformMatrix::operator*(TransformMatrix rhs)
{
    TransformMatrix ret;
    //A(l x m) * B(m x n) = C(l x n)
    int l = 4;
    int m = 4;
    int n = 4; 
    float sum = 0;
    for(int row = 0; row < l; row++)
    {
       for(int col = 0; col < n; col++)
       {
           sum = 0;
           for(int i = 0; i < m; i++)
           {
               sum += (*(this->data))[row][i] * (*rhs.data)[i][col];
           }
           (*ret.data)[row][col] = sum;
       }
    }
    return ret;
}

Vertex TransformMatrix::operator*(Vertex rhs)
{
    Vertex ret;
    int l = 4;
    int m = 4;
    float sum = 0;
    for(int row = 0; row < l; row++)
    {
           sum = 0;
           for(int i = 0; i < m; i++)
           {
               sum += (*(this->data))[row][i] * rhs.components[i];
           }
           ret.components[row] = sum;
    }
    return ret;
}

TransformMatrix& TransformMatrix::operator=(TransformMatrix rhs)
{
    if(rhs.data->size() == data->size())
    {
            std::vector<Vector3H>::iterator it_i_orig;
            std::vector<Vector3H>::iterator it_i_dest;
            for(it_i_orig = rhs.data->begin(), it_i_dest = data->begin(); (it_i_orig != rhs.data->end()) || (it_i_dest != data->end()); ++it_i_orig, ++it_i_dest)
            {
                for(int row = 0; row < 4; row++)
                {
                    (*it_i_dest)[row] = (*it_i_orig)[row];
                }
            }
    }
    else
    {
        printf("ERROR: cannot assign. matrix size mismatch\n");
    }

	return *this;
}

Vector3H& TransformMatrix::operator[](int i)
{
    return (*data)[i];
}   

void TransformMatrix::print()
{
    for(int column = 0; column < data->size(); column++)
    {   
        printf("| ");
        for(int row = 0; row < 4; row++)
        {
            printf("%5.2f ", (*data)[column][row]);
        }
        printf("|\n");
    }
}
