#include "glut.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>


using namespace std;

string path = "Dino.obj";
bool sign = false;
float c = 3.1415926 / 180.0f;
float r = 1.0f;
float x_old = -1;
float y_old = -1;
float z_old = -1;
float x_delta = 0;
float y_delta = 0;
float z_delta = 0;
float degree = 90;
float crossX, crossY, crossZ;
float theta;
int nowx, nowy, nowz;
vector<float> degrees;
vector<float> x_deltas, y_deltas, z_deltas;

class ObjLoader {
    public:
        ObjLoader(string filename);//constructor
        void Draw();
    private:
        vector<vector<GLfloat>> vertices;
        vector<vector<GLint>> faces;
};

ObjLoader::ObjLoader(string filename)
{
    string line;
    fstream f;
    f.open(filename, ios::in);
    if (!f.is_open()) {
        cout << "Wrong When Opening files" << endl;
    }

    GLfloat xMax = 0, xMin = 0; // 38.8387
    GLfloat yMax = 0, yMin = 0; // 115.918
    GLfloat zMax = 0, zMin = 0; // 97.9894
    GLfloat x_range = 115.918;
    GLfloat y_range = 115.918;
    GLfloat z_range = 115.918;

    while (getline(f, line)) {
        vector<string> tokens;
        string spilt = " ";
        string ans = "";

        line = line.append(spilt);
        for (int i = 0; i < line.length(); i++) {
            char ch = line[i];
            if (ch != ' ') 
                ans += ch;
            else {
                tokens.push_back(ans); // tokenize by space
                ans = "";
            }
        }
        
        if (tokens[0] == "v") { // vertice
            vector<GLfloat> point;
            GLfloat x = atof(tokens[1].c_str());
            GLfloat y = atof(tokens[2].c_str());
            GLfloat z = atof(tokens[3].c_str());
            point.push_back(x/x_range);
            point.push_back(y/y_range);
            point.push_back(z/z_range);

            /*if (x < xMin)
                xMin = x;
            if (x > xMax)
                xMax = x;
            if (y < yMin)
                yMin = y;
            if (y > yMax)
                yMax = y;
            if (z < zMin)
                zMin = z;
            if (z > zMax)
                zMax = z;*/
            
            vertices.push_back(point);
        }

        else if (tokens[0] == "f") { // face
            vector<GLint> idx;
            // start from 0 in program, so need to -1
            GLint u = atof(tokens[1].c_str()) - 1;
            GLint v = atof(tokens[2].c_str()) - 1;
            GLint w = atof(tokens[3].c_str()) - 1;
            idx.push_back(u);
            idx.push_back(v);
            idx.push_back(w);
            
            faces.push_back(idx);
        }
    }

    f.close();
    //cout << "x: " << xMax - xMin << '\n';
    //cout << "y: " << yMax - yMin << '\n';
    //cout << "z: " << zMax - zMin << '\n';
}

void ObjLoader::Draw()
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < faces.size(); i++) {
        GLfloat v1[3];
        GLfloat v2[3];
        GLfloat v3[3];
        // index of vertices
        GLint idx1 = (faces[i])[0];
        GLint idx2 = (faces[i])[1];
        GLint idx3 = (faces[i])[2];

        v1[0] = (vertices[idx1])[0];
        v1[1] = (vertices[idx1])[1];
        v1[2] = (vertices[idx1])[2];

        v2[0] = (vertices[idx2])[0];
        v2[1] = (vertices[idx2])[1];
        v2[2] = (vertices[idx2])[2];

        v3[0] = (vertices[idx3])[0];
        v3[1] = (vertices[idx3])[1];
        v3[2] = (vertices[idx3])[2];

        GLfloat normalV[3];
        GLfloat nv1[3], nv2[3], nv3[3];
        // (x2-x1, y2-y1, z2-z1)
        nv1[0] = v1[0] - v2[0];
        nv1[1] = v1[1] - v2[1];
        nv1[2] = v1[2] - v2[2];
        // (x3-x2, y3-y2, z3-z2)
        nv2[0] = v1[0] - v3[0];
        nv2[1] = v1[1] - v3[1];
        nv2[2] = v1[2] - v3[2];
        // (x3-x1, y3-y1, z3-z1)
        nv3[0] = nv1[1] * nv2[2] - nv1[2] * nv2[1];
        nv3[1] = nv2[0] * nv1[2] - nv2[2] * nv1[0];
        nv3[2] = nv2[1] * nv1[0] - nv2[0] * nv1[1];

        GLfloat distance = sqrt(pow(nv3[0], 2) + pow(nv3[1], 2) + pow(nv3[2], 2));
        normalV[0] = nv3[0] / distance;
        normalV[1] = nv3[1] / distance;
        normalV[2] = nv3[2] / distance;

        glNormal3f(normalV[0], normalV[1], normalV[2]);
        glVertex3f(v1[0], v1[1], v1[2]);
        glVertex3f(v2[0], v2[1], v2[2]);
        glVertex3f(v3[0], v3[1], v3[2]);
    }

    glEnd();
}

ObjLoader objModel = ObjLoader(path);

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 10.0, 0.0, 5.0, 0.0 };
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat local_view[] = { 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat mat_ambient[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat low_shininess[] = { 50 };
    GLfloat no_mat[4] = { 0.0, 0.0, 0.0, 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void display()
{
    glColor3f(1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(0.0f, 0.0f, 0.0f);

    gluLookAt(0, 0, 2, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    //glRotatef(theta*180*0.5, crossX, crossY, crossZ); // cross
    //cout << crossX << " " << crossY << " " << crossZ << endl;
    int size = degrees.size();
    for (int i = size-1; i >= 0; i--) {
        glRotatef(degrees[i] * 180 * 0.5, x_deltas[i], y_deltas[i], z_deltas[i]);
    }
    
    glPushMatrix();    

    objModel.Draw();

    glPopMatrix();
    glutSwapBuffers(); 
}

void reshape(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0f, 10000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// mouse control
void mouse(int button, int state, int x, int y)
{   
    x = x - 300;
    y = 300 - y;
    if (x * x + y * y > 90000)
        return;
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            x_old = x;
            y_old = y;
            sign = true;
        }
        if (state == GLUT_UP)
        {
            sign = false;
        }
    }
}

void motion(int x, int y)
{
    z_old = sqrt(300 * 300 - pow(x_old, 2) - pow(y_old, 2));
    x = x - 300;
    y = 300 - y;
    if (x * x + y * y > 90000)
        return;
    int z = sqrt(300 * 300 - pow(x, 2) - pow(y, 2));
    nowx = x;
    nowy = y;
    nowz = z;
    crossX = -1*(y * z_old - y_old * z);
    crossY = -1*(z * x_old - z_old * x);
    crossZ = -1*(x * y_old - x_old * y);

    GLfloat dotXYZ;
    dotXYZ = x * x_old + y * y_old + z * z_old;
    theta = acos(dotXYZ / (300 * 300));
    x_deltas.push_back(crossX);
    y_deltas.push_back(crossY);
    z_deltas.push_back(crossZ);
    degrees.push_back(theta);
    
    x_old = x;
    y_old = y;
}


void idle()
{
    glutPostRedisplay();
    
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    int mode = GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH;
    glutInitDisplayMode(mode);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(250, 60);
    glutCreateWindow(argv[0]);
    glutSetWindowTitle("109550087 單宇晟");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}