#include <iostream>
#include <vector>
using std::cout; using std::endl; using std::vector;

class Matrix{
    int rows;
    int cols;

    // Checks if assignment values for the matrix is acceptable
    bool valid_assignment(vector<vector<double>> rawVals) {
        int iterations = rawVals.size();
        unsigned int columnLength = rawVals[0].size();

        if (rawVals.size() == 0 || columnLength == 0) {
            throw std::invalid_argument("no arguments provided");
        }

        for (int i = 1; i < iterations; i++) {
            if (columnLength != rawVals[i].size()) {
                return false;
            }
        }
        return true;
    }

public:
    vector<vector<double>> value;
    void assign(vector<vector<double>> rawVals) {
        if (!valid_assignment(rawVals)) {
            throw std::invalid_argument("array does not have constant number of columns");
        }
        value = rawVals;
        rows = rawVals.size();
        cols = rawVals[0].size();
    }

    vector<int> get_shape() {
        return {rows,cols};
    }

    void show() {
        cout << "[ ";
        for (int i = 0; i < rows; i++) {
            if (i > 0) {
                cout << "  ";
            }
            for (int j = 0; j < cols; j++) {
                cout << value[i][j] << " ";
            }
            if (rows != i+1){
                cout << endl;
            }
        }
        cout << "]" << endl;
    }

    Matrix operator+(Matrix& b) {
        if (get_shape() != b.get_shape()) {
            throw std::invalid_argument("Invalid arguments for + operator");
        }
        Matrix to_return;
        to_return.assign(value);

        for (int i = 0; i < rows; i++ ) {
            for (int j = 0; j < cols; j++) {
                to_return.value[i][j] += b.value[i][j];
            }
        }
         return to_return;
      }
    Matrix operator*(Matrix& b) {
        if (cols != b.get_shape()[0]) {
            throw std::invalid_argument("Invalid arguments for * operator");
        }
        Matrix to_return;
        vector<double> temp;
        vector<vector<double>> final;
        int sum;
        for (int i = 0; i < rows; i++) {
            temp = {};
            for (int j = 0; j < b.get_shape()[1]; j++) {
                sum = 0;
                for (int k = 0; k < cols; k++) {
                    sum += value[i][k] * b.value[k][j];
                }
                temp.push_back(sum);
            }
            final.push_back(temp);
        }
        to_return.assign(final);
        return to_return;
        }
};

int main() {

    Matrix A, B, C;
    A.assign({{3,-1},
              {-2,4}});
    B.assign({{1,2},
              {3,-1}});
    C.assign({{1,0},
              {2,3}});
    
    (A*B).show();
    cout << endl;
    (A+B).show();

    Matrix X, Y;
    X.assign({{1,2,3,4,5,6,7,8,9,10},{11,12,13,14,15,16,17,18,19,20}});
    Y.assign({{1,2,3},{1,2,3},{1,2,3},{1,2,3},{1,2,3},{1,2,3},{1,2,3},
              {1,2,3},{1,2,3},{1,2,3}});
    (X*Y).show();
    


    return 0;
}