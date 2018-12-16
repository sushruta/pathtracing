#include <iostream>
#include "vecmath/vecmath.h"

using namespace std;

int main() {
    int nx = 200;
    int ny = 100;
    cout << "P3" << endl << nx << " " << ny << endl << "255" << endl;
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vector3f v = Vector3f(float(i) / float(nx), float(j) / float(ny), 0.2);

            int ir = int(256 * v[0]);
            int ig = int(256 * v[1]);
            int ib = int(256 * v[2]);

            cout << ir << " " << ig << " " << ib << endl;
        }
    }

    return 0;
}
