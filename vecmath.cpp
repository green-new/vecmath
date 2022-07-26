#include "vecmath.hpp"

// Vec3 class
vec3::vec3() : _data {0.0f, 0.0f, 0.0f} { }
vec3::vec3(float _A) : _data {_A, _A, _A} { }
vec3::vec3(float _A, float _B, float _C) : _data {_A, _B, _C} { }
vec3::vec3(const vec3& old) : _data { old.x(), old.y(), old.z() } { }
vec3::~vec3() {
    // delete _data;
}
float& vec3::x() const {
    return _data[0];
}
float& vec3::y() const {
    return _data[1];
}
float& vec3::z() const {
    return _data[2];
}
vec3 vec3::operator+(const vec3& _other) const {
    return vec3(x() + _other.x(), y() + _other.y(), z() + _other.z());
}
vec3 vec3::operator-(const vec3& _other) const {
    return vec3(x() - _other.x(), y() - _other.y(), z() - _other.z());
}
float vec3::operator*(const vec3& _other) const {
    return (x() * _other.x()) + (y() * _other.y()) + (z() * _other.z());
}
vec3& vec3::operator=(const vec3& _other) {
    // Protection against invalid self-assignment
    if (this != &_other) {
        _data[0] = _other._data[0];
        _data[1] = _other._data[1];
        _data[2] = _other._data[2];
    }
    return *this;
}


// Vec4 class
vec4::vec4() : _data {0.0f, 0.0f, 0.0f, 0.0f} { }
vec4::vec4(float _A) : _data {_A, _A, _A, _A} { }
vec4::vec4(float _A, float _B, float _C) : _data {_A, _B, _C, 1.0f} { }
vec4::vec4(float _A, float _B, float _C, float _D) : _data {_A, _B, _C, _D} { }
vec4::vec4(const vec4& old) : _data { old.x(), old.y(), old.z(), old.w() } { }
vec4::vec4(const vec3& vec) : _data { vec._data[0], vec._data[1], vec._data[2], 1.0f } { }
vec4::vec4(const vec3& vec, float _W) : _data { vec._data[0], vec._data[1], vec._data[2], _W } { }
vec4::~vec4() {
    // delete _data;
}
float& vec4::x() const {
    return _data[0];
}
float& vec4::y() const {
    return _data[1];
}
float& vec4::z() const {
    return _data[2];
}
float& vec4::w() const {
    return _data[3];
}
vec4 vec4::operator+(const vec4& _other) const {
    return vec4(x() + _other.x(), y() + _other.y(), z() + _other.z(), w() + _other.w());
}
vec4 vec4::operator-(const vec4& _other) const {
    return vec4(x() - _other.x(), y() - _other.y(), z() - _other.z(), w() - _other.w());
}
float vec4::operator*(const vec4& _other) const {
    return (x() * _other.x()) + (y() * _other.y()) + (z() * _other.z() + (w() * _other.w()));
}
vec4& vec4::operator=(const vec4& _other) {
    // Protection against invalid self-assignment
    if (this != &_other) {
        _data[0] = _other._data[0];
        _data[1] = _other._data[1];
        _data[2] = _other._data[2];
        _data[3] = _other._data[3];
    }
    return *this;
}



// Mat4x4 class
mat4::mat4() : _data {  {0.0f, 0.0f, 0.0f, 0.0f},
                        {0.0f, 0.0f, 0.0f, 0.0f},
                        {0.0f, 0.0f, 0.0f, 0.0f},
                        {0.0f, 0.0f, 0.0f, 0.0f},} 
{

}

mat4::mat4(float _A) : _data {  {_A, 0.0f, 0.0f, 0.0f},
                                {0.0f, _A, 0.0f, 0.0f},
                                {0.0f, 0.0f, _A, 0.0f},
                                {0.0f, 0.0f, 0.0f, _A}} 
{

}
mat4::~mat4() {
    // delete _data;
}

void mat4::foreach(const ForEachFunc& func) const {
    for (uint8_t i = 0; i < ROWS; i++) {
        for (uint8_t j = 0; j < COLS; j++) {
            func((const uint8_t&)i, (const uint8_t&)j, (const float&)_data[i][j]);
        }
    }
}

mat4::mat4(const mat4& _other) {
    auto t = [&](const uint8_t& i, const uint8_t& j, const float& val) -> void {
        _data[i][j] = _other._data[i][j];
    };
    foreach(t);
}

float& mat4::entry(const uint8_t i, const uint8_t j) const {
    return _data[i][j];
}

mat4 mat4::operator+(const mat4& _other) const {
    mat4 m;
    auto t = [*this, _other, &m](const uint8_t& i, const uint8_t& j, const float& val) -> void {
        m._data[i][j] = val + _other._data[i][j];
    };
    foreach(t); 

    return m;
}

mat4 mat4::operator-(const mat4& _other) const {
    mat4 m;
    auto t = [*this, _other, &m](const uint8_t& i, const uint8_t& j, const float& val) -> void {
        m._data[i][j] = val - _other._data[i][j];
    };
    foreach(t); 

    return m;
}

mat4 mat4::operator*(const mat4& _other) const {
    mat4 m;
    auto t = [*this, _other, &m](const uint8_t& i, const uint8_t& j, const float& val) -> void {
        for (uint8_t k = 0; k < ROWS; k++) {
            m._data[i][j] = m._data[i][j] + _data[i][k] * _other._data[k][j];
        }
    };
    foreach(t); 
    return m;
}

mat4 mat4::operator*(const float& scalar) const {
    mat4 m;
    auto t = [scalar, &m](const uint8_t& i, const uint8_t& j, const float& val) -> void {
        m._data[i][j] = val * scalar;
    };
    foreach(t);
    return m;
}

vec4 mat4::operator*(const vec4& _other) const {
    vec4 v;
    auto t = [*this, _other, &v](const uint8_t& i, const uint8_t& j, const float& val) -> void {
        v._data[i] = v._data[i] + _data[j][i] * _other._data[i];
    };
    foreach(t); 
    return v;
}

mat4& mat4::operator=(const mat4& _other) {
    // Protection against invalid self-assignment
    if (this != &_other) {
        for (uint8_t i = 0; i < ROWS; i++) {
            for (uint8_t j = 0; j < COLS; j++) {
                 _data[i][j] = _other._data[i][j];
             }
         }
    }
    return *this;
}

// Basic methods
vec3 cross(const vec3& _b, const vec3& _c) {
    return vec3((_b.x() * _c.z()) - (_b.z() * _c.y()), (_b.z() * _c.x()) - (_b.x() * _c.z()), (_b.x() * _c.y()) - (_b.y() * _c.x()));
}

void print_vec3(const vec3& _vec, std::ostream& _os) {
    _os << "(" << _vec.x() << ", " << _vec.y() << ", " << _vec.z() << ")\n";
}

void print_vec4(const vec4& _vec, std::ostream& _os) {
    _os << "(" << _vec.x() << ", " << _vec.y() << ", " << _vec.z() << ", " << _vec.w() << ")\n";
}

void print_mat4(const mat4& mat, std::ostream& _os) {
    auto t = [mat, &_os](const uint8_t& i, const uint8_t& j, const float& val) -> void {
        if (i == 0 && j == 0) 
            _os << "[";

        _os << " " << mat.entry(i, j);

        if (j < 3 || i < 3) 
            _os << ",";
        if (j == 3 && i == 3) 
            _os << " ]";
        if (j >= 3)
            _os << "\n ";
    };
    mat.foreach(t);
}

spherical_coord_t get_spherical_coords(const vec3& vec) {
    spherical_coord_t sc;
    float rd = length_vec3(vec);
    float pa = acos(vec.z() / rd);
    float aa = atan2f(vec.y(), vec.x());
    sc.radial_distance = rd;
    sc.polar_angle = pa;
    sc.azimuthal_angle = aa;
    return sc;
}

float length_vec3(const vec3& vec) {
    float length = sqrt((vec.x() * vec.x()) + (vec.y() * vec.y()) + (vec.z() * vec.z()));
    return length;
}

void normalize(vec3& vec) {
    // Calculate length
    float l = length_vec3(vec);

    // Divide each of its components by its length
    vec.x() = vec.x() / l;
    vec.y() = vec.y() / l;
    vec.z() = vec.z() / l;
}

void to_degrees(float& radians) {
    radians *= 180.0f / PI;
}

void to_radians(float& degrees) {
    degrees *= PI / 180.0f;
}

mat4 translate(const mat4& m, const vec4& o) {
    mat4 n = m;
    vec4 buf = m * o;
    n.entry(0, 3) += buf._data[0];
    n.entry(1, 3) += buf._data[1];
    n.entry(2, 3) += buf._data[2];
    return n;
}