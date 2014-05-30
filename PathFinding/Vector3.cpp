

#include "Vector3.hpp"
#include <math.h>

namespace GejbEngine {
	Vector3::Vector3() :
		x(0),
		y(0) {
	}

	Vector3::Vector3(const Vector3 &v) {
		*this = v;
	}

	Vector3::Vector3(double x, double y, double z) {
		Set(x, y, z);
	}

	Vector3::~Vector3() {
	}

	void Vector3::Set(const Vector3 &v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	void Vector3::Set(double xValue, double yValue, double zValue) {
		x = xValue;
		y = yValue;
		z = zValue;
	}

	void Vector3::Move(double dx, double dy, double dz) {
		x += dx;
		y += dy;
		z += dz;
	}

	void Vector3::operator+=(const Vector3 &v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}

	void Vector3::operator-=(const Vector3 &v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	void Vector3::operator/=(const Vector3 &v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
	}

	void Vector3::operator*=(const Vector3 &v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}

	bool Vector3::operator==(const Vector3 &v) const {
		return(
			(((v.x - 0.0001f) < x) && (x < (v.x + 0.0001f))) &&
			(((v.y - 0.0001f) < y) && (y < (v.y + 0.0001f))) &&
			(((v.z - 0.0001f) < z) && (z < (v.z + 0.0001f))));
	}

	bool Vector3::operator!=(const Vector3 &v) const {
		return (!(*this == v));
	}

	Vector3 &Vector3::operator=(const Vector3 &v) {
		Set(v);
		return *this;
	}

	Vector3 Vector3::operator+(const Vector3 &v) const{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 Vector3::operator-(const Vector3 &v) const{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	double Vector3::Distance(const Vector3 &v) const{
		return sqrt((v.x - x)*(v.x - x) + (v.y - y)*(v.y - y));
	}

	double Vector3::Length() const{
		return sqrt(x*x + y*y + z*z);
	}

	double Vector3::DotProduct(const Vector3 &v) const{
		return (x*v.x + y*v.y + z*v.z);
	}

	Vector3 Vector3::Normal() const{
		double length;
		if(Length() == 0) {
			length = 0;
		} else {
			length = 1 / Length();
		}
		double nx = x*length;
		double ny = y*length;
		double nz = z*length;

		return Vector3(nx, ny, nz);
	}

}