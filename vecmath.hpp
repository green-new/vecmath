#pragma once
#include <cstdint>
#include <iostream>
#include <functional>
#include <math.h>

#define VM_MAX_VECTOR_DIM   0xFF
#define PI                  3.1415926f

// Represents a sphereical coordinate
// Convention: (radius, elevation, azimuth)
// Angles are represented in radians
typedef struct {
    float radial_distance;
    float polar_angle;
    float azimuthal_angle;
} spherical_coord_t;

class vec4 {
private:
    static const uint8_t DIM = 4;
public:
    mutable float _data[DIM];
    // Parameters: none
    // Returns: new vec4
    // Constructs a vector of 4 dimensions with 0.0f, 0.0f, 0.0f
    vec4();
    // Parameters: float
    // Returns: new vec4
    // Constructs a vector of 4 dimensions with _A, _A, _A
    vec4(float _A);
    // Parameters: float, float, float
    // Returns: new vec4
    // Constructs a vector of 4 dimensions with _A, _B, _C, 1.0f
    vec4(float _A, float _B, float _C);
    // Parameters: vec3
    // Returns: new vec4
    // Constructs a vector of 4 dimensions with vec3, 1.0f
    vec4(const vec3& _A);
    // Parameters: vec3, float
    // Returns: new vec4
    // Constructs a vector of 4 dimensions with vec3, _W
    vec4(const vec3& _A, float _W);
    // Parameters: float, float, float
    // Returns: new vec4
    // Constructs a vector of 4 dimensions with _A, _B, _C, _D
    vec4(float _A, float _B, float _C, float _D);
    // Parameters: reference of a constant vec3 object
    // Returns: new vec4
    // Copy constructor
    vec4(const vec4& old);
    ~vec4();

    // Parameters: none
    // Returns: the X value by reference
    // X by reference method
    float& x() const;
    // Parameters: none
    // Returns: the Y value by reference
    // Y by reference method
    float& y() const;
    // Parameters: none
    // Returns: the Z value by reference
    // Z by reference method
    float& z() const;
    // Parameters: none
    // Returns: the W value by reference
    // W by reference method
    float& w() const;

    // Parameters: the rvalue vector
    // Returns: new vec3
    // Performs simple vector addition
    vec4 operator+(const vec4& _other) const;
    // Parameters: the rvalue vector
    // Returns: new vec3
    // Performs simple vector subtraction
    vec4 operator-(const vec4& _other) const;
    // Parameters: the rvalue vector
    // Returns: new vec3
    // Performs the dot product where float = lvalue * rvalue
    float operator*(const vec4& _other) const;
    // Parameters: the rvalue vector
    // Returns: reference to vec3
    // Copy assignment operator overload
    vec4& operator=(const vec4& _other);
};

class mat4 {
private:
    typedef std::function<void(const uint8_t&, const uint8_t&, const float&)> ForEachFunc;
    static const uint8_t ROWS = 4;
    static const uint8_t COLS = 4;
    mutable float _data[ROWS][COLS];
public:
    // Parameters: none
    // Returns: new mat4x4
    // Constructs a matrix of 4x4 with elements of 0.0f
    mat4();
    // Parameters: none
    // Returns: new mat4x4
    // Constructs a matrix of 4x4 with elements in a diagonal of _A
    mat4(float _A);
    // Parameters: none
    // Returns: new mat4x4
    // Copy constructor
    mat4(const mat4& _other);
    ~mat4();

    // Parameters: unsigned 8-bit int, unsigned 8-bit int
    // Returns: float reference
    // Returns the reference of mat4x4[i][j]
    float& entry(const uint8_t i, const uint8_t j) const;
    // Parameters: function for each entry
    // Returns: none
    // Hardcoded foreach functionality, returns i, j, and data value
    void foreach(const ForEachFunc& func) const;

    // Parameters: the rvalue vector
    // Returns: new mat4x4
    // Performs matrix addition
    // Must have equal rows and cols
    mat4 operator+(const mat4& _other) const;
    // Parameters: the rvalue vector
    // Returns: new vec3
    // Performs matrix subtraction
    // Must have equal rows and cols
    mat4 operator-(const mat4& _other) const;
    // Parameters: the rvalue vector
    // Returns: new mat4
    // Performs matrix multiplication with mat4 * mat4
    mat4 operator*(const mat4& _other) const;
    // Parameters: the scalar
    // Returns: new mat4
    // Performs matrix multiplication with mat4 * scalar
    mat4 operator*(const float& scalar) const;
    // Parameters: vec4
    // Returns: new vec4
    // Performs matrix multiplication with mat4 * vec4
    vec4 operator*(const vec4& vec4) const;
    // Parameters: the rvalue vector
    // Returns: reference to mat4
    // Copy assignment operator overload
    mat4& operator=(const mat4& _other);
};

class vec3 {
private:
    static const uint8_t DIM = 3;
public:
    mutable float _data[DIM];
    // Parameters: none
    // Returns: new vec3
    // Constructs a vector of 3 dimensions with 0.0f, 0.0f, 0.0f
    vec3();
    // Parameters: float
    // Returns: new vec3
    // Constructs a vector of 3 dimensions with _A, _A, _A
    vec3(float _A);
    // Parameters: float, float, float
    // Returns: new vec3
    // Constructs a vector of 3 dimensions with _A, _B, _C
    vec3(float _A, float _B, float _C);
    // Parameters: reference of a constant vec3 object
    // Returns: new vec3
    // Copy constructor
    vec3(const vec3& old);
    ~vec3();

    // Parameters: none
    // Returns: the X value by reference
    // X by reference method
    float& x() const;
    // Parameters: none
    // Returns: the Y value by reference
    // Y by reference method
    float& y() const;
    // Parameters: none
    // Returns: the Z value by reference
    // Z by reference method
    float& z() const;

    // Parameters: the rvalue vector
    // Returns: new vec3
    // Performs simple vector addition
    vec3 operator+(const vec3& _other) const;
    // Parameters: the rvalue vector
    // Returns: new vec3
    // Performs simple vector subtraction
    vec3 operator-(const vec3& _other) const;
    // Parameters: the rvalue vector
    // Returns: new vec3
    // Performs the dot product where float = lvalue * rvalue
    float operator*(const vec3& _other) const;
    // Parameters: the rvalue vector
    // Returns: reference to vec3
    // Copy assignment operator overload
    vec3& operator=(const vec3& _other);
    // Parameters: none
    // Returns: none
    // vec3 ---> vec4 typecast
    operator vec4() { return vec4(_data[0], _data[1], _data[2]); }
};

// Parameters: vec3, vec3 
// Returns: new vec3
// Performs the cross product where new vec3 = _b * _c
// (i) b×c has magnitude |b||c|sinθ where θ is the angle between the directions of b and c;
// (ii) b×c is perpendicular to b and c with direction such that the vectors b, c and b×c form a right handed set so that b×c and c×b are in opposite directions.
vec3 cross(const vec3& _b, const vec3& _c);
// Parameters: vec3
// Returns: none
// Normalizes the given vector into a unit vector [-1.0f, -1.0f, -1.0f] - [1.0f, 1.0f, 1.0f];
void normalize(vec3& vec);
// Parameters: vec3
// Returns: float
// Returns the Pythagorean length of the vector
float length_vec3(const vec3& vec);
// Parameters: vec3
// Returns: sphereical_coordinate_t
// Returns the sphereical coordinate of the vector
spherical_coord_t get_spherical_coords(const vec3& vec);
// Parameters: vec3, ostream
// Returns: none
// Writes the contents of the given vector to the given output stream (default = std::cout)
void print_vec3(const vec3& vec, std::ostream& _os = std::cout);
// Parameters: vec4, ostream
// Returns: none
// Writes the contents of the given vector to the given output stream (default = std::cout)
void print_vec4(const vec4& _vec, std::ostream& _os = std::cout);
// Parameters: mat4, ostream
// Returns: none
// Writes the contents of the given matrix4x4 to the given output stream (default = std::cout)
void print_mat4(const mat4& mat, std::ostream& _os = std::cout);
// Parameters: float
// Returns: none
// Converts given radians to degrees
void to_degrees(float& radians);
// Parameters: float
// Returns: none
// Converts given radians to degrees
void to_radians(float& degrees);
// Parameters: mat4, vec4
// Returns: mat4
// Translates mat4 m by o
mat4 translate(const mat4& m, const vec4& o);